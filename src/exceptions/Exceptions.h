#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class FileNotOpen : public std::runtime_error {
public:
    FileNotOpen(const std::string &msg) : std::runtime_error(msg){};
};

class InitializationError : public std::runtime_error {
public:
    InitializationError(const std::string &msg) : std::runtime_error(msg){};
};

class ReadingError : public std::runtime_error {
public:
    ReadingError(const std::string &msg) : std::runtime_error(msg){};
};

class ConvergenceError : public std::runtime_error {
    ConvergenceError(const std::string &msg) : std::runtime_error(msg){};
};

#endif //EXCEPTIONS_H_
