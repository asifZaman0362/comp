#ifndef OPTION_HPP
#define OPTION_HPP

#include "result.hpp"

class NoneT {};

template <typename T>
class Option : public Result<T, NoneT> {
   public:
    Option(NoneT e) : Result<T, NoneT>(e) {}

    Option(T data) : Result<T, NoneT>(data) {}

    NoneT err() = delete;

    Result<T, NoneT> map_err() = delete;

};

template <typename T>
Option<T> Some(T val) {
    return Option<T>(val);
}

#define None \
    NoneT {}

#endif
