//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_EXCEPTION_H
#define PARALLEL_EXCEPTION_H

#include <stdexcept>
#include <string>

class IncorrectCommandNameException : public std::runtime_error{
public:
    IncorrectCommandNameException(const std::string &__arg) : runtime_error(__arg) { }
};

class IncorrectCommandWorkException : public std::runtime_error{

public:
    IncorrectCommandWorkException(const std::string &__arg) : runtime_error(__arg) { }
};

class ParseIntException : public std::runtime_error{

public:
    ParseIntException(const std::string &__arg) : runtime_error(__arg) { }
};

class IncorrectStateException : public std::runtime_error{

public:
    IncorrectStateException(const std::string &__arg) : runtime_error(__arg) { }
};
class ReadFileException : public std::runtime_error{

public:
    ReadFileException(const std::string &__arg) : runtime_error(__arg) { }
};
#endif //PARALLEL_EXCEPTIONS_H
