//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_WORKWR_H
#define PARALLEL_WORKWR_H

#include "Field.h"

class Worker{
public:
    void makeIterations(Section current, Section next);
};

#endif //PARALLEL_WORKWR_H
