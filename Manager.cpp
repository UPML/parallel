//
// Created by kagudkov on 20.09.15.
//

#include "Manager.h"
#include "Exceptions.h"

std::vector<Section> Manager::chooseDomains(Field &t, int parts) {
    if (parts <= 0) {
        throw IncorrectCommandWorkException("Wrong parts number");
    }
    size_t toOne = t.getHeight() / parts;
    size_t added = t.getHeight() % parts;
    std::vector<Section> answer;
    answer.clear();
    size_t currentPosition = 0;
    while (currentPosition < t.getHeight() - 1) {
        if (added > 0) {
            answer.push_back(Section(currentPosition, 0, currentPosition + toOne, t.getWeight() - 1,  t));
            currentPosition++;
        } else {
            answer.push_back(Section(currentPosition,0,  currentPosition + toOne - 1, t.getWeight() - 1, t));
        }
        currentPosition += toOne;
    }
    return answer;
}


Manager::Manager() : s(NOT_STARTED) {
}

Manager::State Manager::getState() const {
    return s;
}

void Manager::wakeWhenStateIs(Manager::State s) const {
    MutexLocker locker(stateMutex);
    while (getState() != s)
        stateCond.wait(stateMutex);

}

void Manager::wakeWhenStateIsNot(Manager::State s) const {
    MutexLocker locker(stateMutex);
    while (getState() == s)
        stateCond.wait(stateMutex);
}

void Manager::setState(Manager::State s) {
    if (this->s == s)
        return;
    MutexLocker locker(stateMutex);
   // debug() << "Manager: new state: " << stateStr(s);
    this->s = s;
    stateCond.wakeAll();
}

void Manager::start()
{
    Thread::start();
}

std::vector<std::vector<int>> Manager::makeNeighbors(const Field &t, const std::vector<Section> &r) {
    int n = r.size();
    std::vector<std::vector<int> > ret(n);
    for (int i = 0; i < n; ++i)
        if (!r[i].isEmpty())
        {
            ret[i].push_back((i-1+n)%n);
            ret[i].push_back((i+1)%n);
        }
    return ret;
    return std::vector<vector< int, allocator < int>>>();
}
