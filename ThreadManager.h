//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_MANAGER_H
#define PARALLEL_MANAGER_H

#include "Field.h"

class ThreadManager {
    enum State {
        NOT_STARTED,
        STOPPED,
        RUNNING,
        STOPPING,
        FINISHED
    };

public:
    const State &getState_() const {
        return state_;
    }

private:
    State state_;

    void start(Field field, long numberOfWorkers);
};

#endif //PARALLEL_MANAGER_H
