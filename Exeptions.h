//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_EXEPTION_H
#define PARALLEL_EXEPTION_H

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

#endif //PARALLEL_EXEPTIONS_H
