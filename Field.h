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
static const double PROBABILITY = 0.2;

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

class Section;

class Field {
public:
    void randomFill(const double probability);

    Field() { };

    Field(size_t height, size_t weight) : height_(height), weight_(weight) {
        randomFill(PROBABILITY);
    };

    Field(Section section);

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

    Section getInner();

    std::vector<Section> getBorders();

    void copyValues(Field field);

private:
    size_t height_;
    size_t weight_;
    std::vector<std::vector<Cell>> fieldState;
};


class Section {
public:

    Section(size_t startHeight, size_t startWeight, size_t finishHeight, size_t finishWeight, Field &field)
            : startHeight(
            startHeight), startWeight(startWeight), finishHeight(finishHeight), finishWeight(finishWeight),
              field(&field) { }

    size_t getStartHeight() const {
        return startHeight;
    }

    void setStartHeight(size_t start_) {
        Section::startHeight = start_;
    }

    size_t getFinishHeight() const {
        return finishHeight;
    }

    void setFinishHeight(size_t finish_) {
        Section::finishHeight = finish_;
    }

    size_t getStartWeight() const {
        return startWeight;
    }

    void setStartWeight(size_t startWeight) {
        Section::startWeight = startWeight;
    }

    size_t getFinishWeight() const {
        return finishWeight;
    }

    void setFinishWeight(size_t finishWeight) {
        Section::finishWeight = finishWeight;
    }

    bool isLive(heightCoordinate h, weightCoordinate w);

    void setState(heightCoordinate h, weightCoordinate w, bool isLived);

    size_t numberOfLiveCellsNearly(heightCoordinate h, weightCoordinate w);

    bool isEmpty()const;

    size_t getHeight();

    size_t getWight();

private:
    size_t startHeight;
    size_t startWeight;
    size_t finishHeight;
    size_t finishWeight;
    Field *field;
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
