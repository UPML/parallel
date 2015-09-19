//
// Created by kagudkov on 19.09.15.
//

#ifndef LIFETHEFIRSTVERSION_INCORRECTCOMMANDNAMEEXEPTION_H
#define LIFETHEFIRSTVERSION_INCORRECTCOMMANDNAMEEXEPTION_H


#include <stdexcept>
#include <string>

class IncorrectCommandNameException : public std::runtime_error{
public:
    IncorrectCommandNameException(const std::string &__arg) : runtime_error(__arg) { }
};


#endif //LIFETHEFIRSTVERSION_INCORRECTCOMMANDNAMEEXEPTION_H
