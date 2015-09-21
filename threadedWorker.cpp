//
// Created by kagudkov on 20.09.15.
//

#include "threadedWorker.h"
#include "ThreadManager.h"

namespace {
    void wakeWhenReaches(int &watched, int desired, Mutex &m, Cond &c) {
        MutexLocker locker(m);
        while (watched < desired)
            c.wait(m);
    }

    void incAndWakeAll(int &x, Mutex &m, Cond &c) {
        MutexLocker locker(m);
        ++x;
        c.wakeAll();
    }
} // namespace anonymous



ThreadWorkerShared::ThreadWorkerShared() :
        iterationCalced(0),
        iterationPublished(0) { }

int ThreadWorkerShared::getIterationCalced() const { return iterationCalced; }

int ThreadWorkerShared::getIterationPublished() const { return iterationPublished; }

void ThreadWorkerShared::wakeWhenCalcs(int needed) {
    wakeWhenReaches(iterationCalced, needed, calcedMutex, calcedCond);
}

void ThreadWorkerShared::wakeWhenPublishes(int needed) {
    wakeWhenReaches(iterationPublished, needed, publishMutex, publishCond);
}

void ThreadWorkerShared::incIterationCalced() {
    // debug() << "worker finished calcing iteration" << getIterationCalced() + 1;
    incAndWakeAll(iterationCalced, calcedMutex, calcedCond);
}

void ThreadWorkerShared::incIterationPublished() {
    // debug() << "worker publishing iteration " << getIterationPublished() + 1;
    incAndWakeAll(iterationPublished, publishMutex, publishCond);
}


void ThreadedWorker::start(
        ThreadManagerShared &manager,
        Field &domain,
        const std::vector<ThreadWorkerShared *> &neighShared) {
    this->manager = &manager;
    this->neighShared = neighShared;
    this->domain = &domain;

    Thread::start();
}

ThreadWorkerShared &ThreadedWorker::getShared() { return myShared; }

void ThreadedWorker::run() {
    //debug("worker started");

    size_t h = domain->getHeight();
    size_t w = domain->getWeight();

    Section innerResult = domain->getInner();
    std::vector<Section> resultBorders = domain->getBorders();

    Field tempDomain(h, w);
    Section innerTemp = tempDomain.getInner();
    std::vector<Section> tempBorders = tempDomain.getBorders();

    size_t nsz = neighShared.size();

 //   debug("worker ready to calc");
    while (manager->wakeWhenNextIterationNeeded(myShared.iterationPublished)) {
        Worker::makeIterations(innerResult, innerTemp);

        for (size_t i = 0; i < nsz; ++i)
            neighShared[i]->wakeWhenPublishes(myShared.iterationPublished);

        for (size_t i = 0; i < resultBorders.size(); ++i)
            Worker::makeIterations(resultBorders[i], tempBorders[i]);

        myShared.incIterationCalced();
        for (size_t i = 0; i < nsz; ++i)
            neighShared[i]->wakeWhenCalcs(myShared.iterationCalced);

        domain->copyValues(tempDomain);
        myShared.incIterationPublished();
    }

    //   debug("worker stopped");
}