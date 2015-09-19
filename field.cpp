//
// Created by kagudkov on 19.09.15.
//

#include <stdlib.h>
#include <iostream>
#include "field.h"

void field::randomFill(const double probability) {
    fieldState.resize(getHeight());
    srand((unsigned int) time(0));
    for (size_t i = 0; i < getHeight(); ++i) {
        fieldState.at(i).resize(getWeight());
        for (bool cell : fieldState.at(i)) {
            cell = ((rand() / RAND_MAX) < probability);
        }
    }
}

void field::print() {
    for (size_t i = 0; i < getHeight(); ++i) {
        for (size_t j = 0; j < getWeight(); ++j) {
            if (isLive(i, j)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
