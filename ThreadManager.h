//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_MANAGER_H
#define PARALLEL_MANAGER_H

#include "Field.h"

class ThreadManager {
public:
    enum State {
        NOT_STARTED,
        STOPPED,
        RUNNING,
        STOPPING,
        FINISHED
    };


    const State &getState_() const {
        return state_;
    }
    void start(Field field, long numberOfWorkers);

private:
    State state_;

};

#endif //PARALLEL_MANAGER_H
