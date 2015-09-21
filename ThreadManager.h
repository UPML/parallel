//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_THREAD_MANAGER_H
#define PARALLEL_THREAD_MANAGER_H

#include "Manager.h"

class ThreadManager;

class ThreadManagerShared {
public:
    ThreadManagerShared(ThreadManager &manager);

    bool wakeWhenNextIterationNeeded(int iterationPublished);

    int getStop() const;

protected:
    friend class ThreadManager;

    int getWorkersWaiting() const;

    void incWorkersWaiting();

    void decWorkersWaiting();

    void setWorkersCount(int count);

    void setStop(int newStop);

private:
    int workersCount;
    int workersWaiting;
    SemaphoreMutex workersMutex;

    int stop;
    Mutex stopMutex;
    Cond stopCond;

    ThreadManager &manager;
};

class ThreadManager : public Manager {
public:
    ThreadManager();

    ~ThreadManager();

    void start(Field &m, int concurrency);

    ThreadManagerShared &getShared();

    void pauseAll();

    void runForMore(int iterations);

    void shutdown();

    void updateState();

protected:
    void run();

private:
    ThreadManagerShared myShared;

    Field *matrix;
    int concurrency;

    bool pauseFlag;
    int runMore;
    bool shutdownFlag;
    bool updateFlag;

    Mutex mutex;
    Cond cond;
};

#endif //PARALLEL_MANAGER_H
