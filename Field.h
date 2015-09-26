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
typedef size_t widthCoordinate;
static const double PROBABILITY = 0.33;

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

    Field(size_t height, size_t weight) : height_(height), width_(weight) {
        randomFill(PROBABILITY);
    };

    Field(Section section);

    size_t getHeight() const {
        return height_;
    }

    size_t getWidth() const {
        return width_;
    }

    bool isLive(heightCoordinate h, widthCoordinate w) {
        return fieldState.at((h + getHeight()) % getHeight()).at((w + getWidth()) % getWidth()).isLive();
    }

    void setState(heightCoordinate h, widthCoordinate w, bool isLived) {
        fieldState.at((h + getHeight()) % getHeight()).at((w + getWidth()) % getWidth()).setLive(isLived);
    }

    size_t numberOfLiveCellsNearly(heightCoordinate h, widthCoordinate w);

    void print();

    Section getInner();

    std::vector<Section> getBorders();

    void copyValues(Field field);

private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<Cell>> fieldState;
};


class Section {
public:

    Section(size_t startHeight, size_t startWeight, size_t finishHeight, size_t finishWeight, Field &field)
            : startHeight(
            startHeight), startWidth(startWeight), finishHeight(finishHeight), finishWidth(finishWeight),
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
        return startWidth;
    }

    void setStartWeight(size_t startWeight) {
        Section::startWidth = startWeight;
    }

    size_t getFinishWeight() const {
        return finishWidth;
    }

    void setFinishWeight(size_t finishWeight) {
        Section::finishWidth = finishWeight;
    }

    bool isLive(heightCoordinate h, widthCoordinate w);

    void setState(heightCoordinate h, widthCoordinate w, bool isLived);

    size_t numberOfLiveCellsNearly(heightCoordinate h, widthCoordinate w);

    bool isEmpty() const;

    size_t getHeight();

    size_t getWight();

    Section getInner();


    std::vector<Section> getBorders();

    void copyValue(Field &f);
    void print();

private:
    size_t startHeight;
    size_t startWidth;
    size_t finishHeight;
    size_t finishWidth;
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
