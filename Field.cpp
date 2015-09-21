//
// Created by kagudkov on 19.09.15.
//

#include "Field.h"

void Field::randomFill(const double probability) {
    fieldState.resize(getHeight());
    srand((unsigned int) time(0));
    for (size_t i = 0; i < getHeight(); ++i) {
        fieldState.at(i).resize(getWeight());
        for (Cell cell : fieldState.at(i)) {
            cell.setLive((rand() / RAND_MAX) < probability);
        }
    }
}

void Field::print() {
    for (size_t i = 0; i < getHeight(); ++i) {
        for (size_t j = 0; j < getWeight(); ++j) {
            if (isLive(i, j)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

size_t Field::numberOfLiveCellsNearly(heightCoordinate h, weightCoordinate w) {
    size_t answer = 0;
    for (size_t i = 0; i < DIRECTION_COUNT; ++i) {
        if (isLive((h + DIRECTION[i][0]) % getHeight(), (w + DIRECTION[i][1]) % getWeight())) {
            answer++;
        };
    }
    return answer;
}

Section Field::getInner() {
    return Section(1, 1, getHeight() - 2, getWeight() - 2, *this);
}

std::vector<Section> Field::getBorders() {
    std::vector<Section> answer;
    answer.clear();
    answer.push_back(Section(0, 0, 0, getWeight() - 1, *this));
    answer.push_back(Section(getHeight() - 1, 0, getHeight() - 1, getWeight() - 1, *this));
    answer.push_back(Section(1, 0, getHeight() - 2, 0, *this));
    answer.push_back(Section(1, getWeight() - 1, 1, getWeight() - 1, *this));
    return answer;
}

void Section::setState(heightCoordinate h, weightCoordinate w, bool isLived) {
    field->setState(h + startHeight, w + startWeight, isLived);


}

size_t Section::numberOfLiveCellsNearly(heightCoordinate h, weightCoordinate w) {
    field->numberOfLiveCellsNearly(h + startHeight, w + startWeight);
}

bool Section::isLive(heightCoordinate h, weightCoordinate w) {
    return field->isLive(h + startHeight, w + startWeight);
}

void Field::copyValues(Field field) {
    fieldState.resize(field.getHeight());
    for (size_t i = 0; i < field.getHeight(); ++i) {
        fieldState.at(i).resize(getWeight());
        for (size_t j = 0; j < field.getWeight(); ++j) {
            setState(i, j, field.isLive(i, j));
        }
    }
}

bool Section::isEmpty() {
    return (startWeight == finishWeight || startHeight == finishHeight);
}

Field::Field(Section section) {
    fieldState.resize(section.getHeight());
    for (size_t i = section.getStartHeight(); i < section.getFinishHeight(); ++i) {
        fieldState.resize(section.getWight());
        for(size_t j = section.getStartWeight(); j < section.getFinishWeight(); ++j){
            setState(i - section.getStartWeight(), j - section.getStartWeight(), section.isLive(i, j));
        }
    }
}

size_t Section::getHeight() {
    return getFinishWeight() - getStartWeight();
}

size_t Section::getWight() {
    return getFinishWeight() - getStartWeight();
}
