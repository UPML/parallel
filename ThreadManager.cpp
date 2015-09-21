//
// Created by kagudkov on 19.09.15.
//

#include "ThreadManager.h"
#include "Manager.h"
#include "threadedWorker.h"

ThreadManagerShared::ThreadManagerShared(ThreadManager &manager) :
        workersWaiting(0),
        stop(0),
        manager(manager) { }

bool ThreadManagerShared::wakeWhenNextIterationNeeded(int have) {
    MutexLocker locker(stopMutex);
    if (stop != -1 && stop <= have) {
        incWorkersWaiting();
        while (stop != -1 && stop <= have)
            stopCond.wait(stopMutex);
        decWorkersWaiting();
    }
    return stop != -1;
}

int ThreadManagerShared::getStop() const { return stop; }

int ThreadManagerShared::getWorkersWaiting() const {
    return workersWaiting;
}

void ThreadManagerShared::incWorkersWaiting() {
    MutexLocker locker(workersMutex);
    ++workersWaiting;
    // debug() << workersWaiting << "/" << workersCount << " workers waiting";
    if (workersWaiting == workersCount)
        manager.updateState();
}

void ThreadManagerShared::decWorkersWaiting() {
    MutexLocker locker(workersMutex);
    --workersWaiting;
    //debug() << workersWaiting << "/" << workersCount << " workers waiting";
}

void ThreadManagerShared::setWorkersCount(int count) {
    workersCount = count;
}

void ThreadManagerShared::setStop(int newStop) {
    MutexLocker locker(stopMutex);
    //debug() << "setting iteration stopper to " << newStop;
    stop = newStop;
    stopCond.wakeAll();
}

ThreadManager::ThreadManager() :
        myShared(*this),
        pauseFlag(false),
        runMore(0),
        shutdownFlag(false),
        updateFlag(false) { }

ThreadManager::~ThreadManager() {
    assert(Manager::getState() == Manager::NOT_STARTED || getState() == FINISHED);
}

void ThreadManager::start(Field &t, int concurrency) {
    this->matrix = &t;
    this->concurrency = concurrency;

    Manager::start();
}

ThreadManagerShared &ThreadManager::getShared() { return myShared; }

void ThreadManager::pauseAll() {
    MutexLocker locker(mutex);
    pauseFlag = true;
    cond.wakeOne();
}

void ThreadManager::runForMore(int iterations) {
    MutexLocker locker(mutex);
    pauseFlag = false;
    runMore += iterations;
    cond.wakeOne();
}

void ThreadManager::shutdown() {
    MutexLocker locker(mutex);
    shutdownFlag = true;
    cond.wakeOne();
}

void ThreadManager::updateState() {
    MutexLocker locker(mutex);
    updateFlag = true;
    cond.wakeOne();
}

void ThreadManager::run() {
    Manager::setState(Manager::RUNNING);
    getShared().setWorkersCount(concurrency);

    UniqueArray<ThreadedWorker> workers(concurrency);
    UniqueArray<Field> domains(concurrency);

    Field torus(*matrix);

    std::vector<Section> domainRects = chooseDomains(torus, concurrency);
    for (int i = 0; i < concurrency; ++i)
        domains[i] = Field(domainRects[i]);

    std::vector<std::vector<int>> neigs = makeNeighbors(torus, domainRects);

    for (int i = 0; i < concurrency; ++i) {
        std::vector<ThreadWorkerShared *> shareds(neigs[i].size());
        for (size_t j = 0; j < neigs[i].size(); ++j)
            shareds[j] = &workers[neigs[i][j]].getShared();
        workers[i].start(myShared, domains[i], shareds);
    }

    int stop = 0;
    setState(STOPPED);
    while (true) {
        int runMore = 0;
        bool pauseFlag = false;
        bool updateFlag = false;
        {
            MutexLocker locker(mutex);
            while (!this->pauseFlag
                   && !this->runMore
                   && !this->shutdownFlag
                   && !this->updateFlag)
                cond.wait(mutex);

            if (this->shutdownFlag)
                break;
            else if (this->pauseFlag)
                pauseFlag = true;
            else {
                runMore = this->runMore;
                updateFlag = this->updateFlag;
            }
            this->pauseFlag = false;
            this->runMore = 0;
            this->updateFlag = false;
        }

        if (pauseFlag) {
            myShared.setStop(0);
            for (int i = 0; i < concurrency; ++i) {
                int newStop = std::min(stop,
                                       workers[i].getShared().getIterationPublished() + 1);
                if (newStop > myShared.stop)
                    myShared.setStop(newStop);
            }
            for (int i = 0; i < concurrency; ++i)
                workers[i].getShared().wakeWhenPublishes(myShared.stop);
            stop = myShared.stop;
            setState(STOPPED);
        }

        if (runMore) {
            stop += runMore;
            myShared.setStop(stop);
            setState(RUNNING);
        }

        if (updateFlag) {
            if (getState() == RUNNING
                && getShared().getWorkersWaiting() == concurrency)
                setState(STOPPED);
        }
    }
    myShared.setStop(-1);

    for (int i = 0; i < concurrency; ++i) {
        int id = workers[i].getId();
        workers[i].join();
      //  debug() << "manager joined worker thread " << id;
    }

    setState(FINISHED);
}

