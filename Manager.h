//
// Created by kagudkov on 20.09.15.
//


#ifndef PARALLEL_MANAGER_H
#define PARALLEL_MANAGER_H

#include "thread.h"
#include "Field.h"
#include <vector>


class Manager : public Thread {
public:
    static std::vector<Section> chooseDomains(Field &t, int parts);

    static std::vector<std::vector<int> > makeNeighbors(
            const Field &t, const std::vector<Section> &r);

    enum State {
        NOT_STARTED,
        RUNNING,
        STOPPING,
        STOPPED,
        FINISHED
    };

    Manager();

    State getState() const;

    std::string getStateStr() const;

    static std::string stateStr(State s);

    void wakeWhenStateIs(State s) const;

    void wakeWhenStateIsNot(State s) const;

protected:
    void setState(State s);

    void start();

private:
    State s;
    mutable Mutex stateMutex;
    mutable Cond stateCond;
};

#endif //PARALLEL_MANAGER_H
