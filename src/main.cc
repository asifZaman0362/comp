#include <fstream>
#include <iostream>
#include <sstream>

#include "option.hpp"
#include "result.hpp"

enum class ArithmeticError { DivisionByZero };

Result<float, ArithmeticError> divide(float a, float b) {
    if (b == 0)
        return Err<float>(ArithmeticError::DivisionByZero);
    else
        return Ok<ArithmeticError>(a / b);
}

Option<std::string> read_file(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::stringstream stream;
        while (!file.eof()) {
            std::string str;
            file >> str;
            stream << str;
        }
        return Some(stream.str());
    } else
        return None;
}

int main() {
    auto printer = [](std::string content) {
        std::cout << content << std::endl;
    };
    auto res = divide(10, 3).map<float>([](float a) { return a * 20; });
    res.and_then<void>([](float a) { std::cout << a << std::endl; });
    res.match<void>(
        [](float x) { std::cout << "result: " << x << "\n"; },
        [](ArithmeticError err) { std::cout << "Division by zero!\n"; });
    read_file("res/file.txt").and_then<void>(printer);
    read_file("res/this_file_doesnt_exist.txt")
        .match<void>(
            [](std::string x) { std::cout << "content: " << x << std::endl; },
            [](NoneT) { std::cout << "No file!\n"; });
}
