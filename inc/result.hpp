#ifndef RESULT_HPP
#define RESULT_HPP

#include <cassert>
#include <functional>
#include <variant>

template <typename R, typename... A>
using Fn = std::function<R(A...)>;

template <typename T, typename E>
class Result;

template <typename T, typename E>
Result<T, E> Err(E);
template <typename E, typename T>
Result<T, E> Ok(E);

template <typename T, typename E>
class Result {
   protected:
    std::variant<T, E> _data;
    bool success;

   public:
    Result(T data) {
        this->success = true;
        this->_data = data;
    }

    Result(E data) {
        this->success = false;
        this->_data = data;
    }

    T unwrap() {
        if (success)
            return std::get<T>(_data);
        else {
            throw "attempting to unwrap an error value!";
        }
    }

    T unwrap_or(T def) {
        if (success)
            return std::get<T>(_data);
        else {
            return def;
        }
    }

    E err() {
        if (!success)
            return std::get<E>(_data);
        else {
            throw "attempting to unwrap error from an ok value!";
        }
    }

    template <typename U>
    U and_then(Fn<U, T> then) {
        if (success) then(std::get<T>(_data));
    }

    template <typename U>
    Result<U, E> map(Fn<U, T> map) {
        if (success) {
            assert(map && "function target must not be empty!");
            return map(std::get<T>(_data));
        } else
            return Err<U>(std::get<E>(_data));
    }

    template <typename F>
    Result<T, F> map_err(Fn<F, E> map) {
        if (success) {
            assert(map && "function target must not be empty!");
            return map(std::get<T>(_data));
        } else
            return Err<T, F>(std::get<T>(_data));
    }

    template <typename U>
    Result<U, E> map_or(Fn<U, T> map, U def) {
        if (success)
            return map(std::get<T>(_data));
        else
            return def;
    }

    template <typename R>
    R match(Fn<R, T> on_ok, Fn<R, E> on_err) {
        if (success)
            return on_ok(std::get<T>(_data));
        else
            return on_err(std::get<E>(_data));
    }
};

template <typename E, typename T>
Result<T, E> Ok(T val) {
    return Result<T, E>(val);
}

template <typename T, typename E>
Result<T, E> Err(E error) {
    return Result<T, E>(error);
}

#endif
