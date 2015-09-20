//
// Created by kagudkov on 19.09.15.
//

#include "Worker.h"

void Worker::makeIterations(Field &current, Field &next) {
    for(size_t i = 0; i < current.getHeight(); ++i){
        for(size_t j = 0; j < current.getWeight(); ++j){
            size_t liveNearly = current.numberOfLiveCellsNearly(i, j);
            if(current.isLive(i, j)) {
                next.setState(i, j, liveNearly == 2 || liveNearly == 3);
            } else {
                next.setState(i, j, liveNearly == 3);
            }
        }
    }
}