//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_FIELD_H
#define PARALLEL_FIELD_H

#include <stdlib.h>
#include <iostream>

#include <glob.h>
#include <vector>

typedef size_t heightCoordinate;
typedef size_t weightCoordinate;
static const double PROBABILITY = 1 / 5;

class Cell {
    size_t h;
    size_t w;
public:
    bool isLive() const {
        return live;
    }

    void setLive(bool live) {
        Cell::live = live;
    }

private:
    bool live;
};


class Field {
public:
    void randomFill(const double probability);

    Field() { };

    Field(size_t height, size_t weight) : height_(height), weight_(weight) {
        randomFill(PROBABILITY);
    };

    size_t getHeight() const {
        return height_;
    }

    size_t getWeight() const {
        return weight_;
    }

    bool isLive(heightCoordinate h, weightCoordinate w) {
        return fieldState.at(h).at(w).isLive();
    }

    void setState(heightCoordinate h, weightCoordinate w, bool isLived) {
        fieldState.at(h).at(w).setLive(isLived);
    }
    size_t numberOfLiveCellsNearly(heightCoordinate h, weightCoordinate w);

    void print();

private:
    size_t height_;
    size_t weight_;
    std::vector<std::vector<Cell>> fieldState;
};

static const size_t DIRECTION_COUNT = 8;
static const int DIRECTION[8][2] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0,  -1},
        {0,  1},
        {1,  -1},
        {1,  0},
        {1,  1}
};


#endif //PARALLEL_FIELD_H
