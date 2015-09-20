//
// Created by kagudkov on 20.09.15.
//

#include "utile.h"

#include <sstream>

#include <errno.h>
#include <string.h>

#include "Exceptions.h"

void throwCError(int line, const char* file)
{
    std::ostringstream oss;
    oss << file << ':' << line << "\t" << strerror(errno);
    throw std::logic_error(oss.str());
}
