//
// Created by kagudkov on 19.09.15.
//

#include "Worker.h"

void Worker::makeIterations(Section current, Section next) {
    for(size_t i = current.getStartHeight(); i < current.getFinishHeight(); ++i){
        for(size_t j = current.getStartWeight(); j < current.getFinishWeight(); ++j){
            size_t liveNearly = current.numberOfLiveCellsNearly(i, j);
            if(current.isLive(i, j)) {
                next.setState(i, j, liveNearly == 2 || liveNearly == 3);
            } else {
                next.setState(i, j, liveNearly == 3);
            }
        }
    }
}