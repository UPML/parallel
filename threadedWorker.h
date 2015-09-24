//
// Created by kagudkov on 20.09.15.
//

#ifndef PARALLEL_THREADEDWORKER_H
#define PARALLEL_THREADEDWORKER_H

#include <vector>
#include "thread.h"
#include "Field.h"
#include "Worker.h"

class ThreadManagerShared;

class ThreadedWorker;

class ThreadWorkerShared {
public:
    ThreadWorkerShared();

    int getIterationPublished() const;

    void wakeWhenCalcs(int iteration);

    void wakeWhenPublishes(int iteration);

private:
    friend class ThreadedWorker;

    void incIterationCalced();

    int iterationCalced;
    Mutex calcedMutex;
    Cond calcedCond;

    void incIterationPublished();

    int iterationPublished;
    Mutex publishMutex;
    Cond publishCond;
};

class ThreadedWorker : public Thread, protected Worker {
public:
    void start(
            ThreadManagerShared &manager,
            Section &domain,
            const std::vector<ThreadWorkerShared *> &neighShared);

    ThreadWorkerShared &getShared();

protected:
    void run();

private:
    ThreadWorkerShared myShared;

    ThreadManagerShared *manager;
    Section *domain;
    std::vector<ThreadWorkerShared *> neighShared;
};

#endif //PARALLEL_THREADEDWORKER_H
