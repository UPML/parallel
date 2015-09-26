//
// Created by kagudkov on 19.09.15.
//

#include "Field.h"

void Field::randomFill(const double probability) {
    fieldState.resize(getHeight());
    srand((unsigned int) time(0));
    for (size_t i = 0; i < getHeight(); ++i) {
        fieldState.at(i).resize(getWidth());
        for (size_t j = 0; j < getWidth(); ++j) {
            double randomNumber = (double(rand()) / RAND_MAX);
            fieldState.at(i).at(j).setLive(randomNumber < probability);
        }
    }
}

void Field::print() {
    std::cout << "Field Size = " << getHeight() << "x" << getWidth() << "\n";

    for (size_t i = 0; i < getHeight(); ++i) {
        for (size_t j = 0; j < getWidth(); ++j) {
            if (!isLive(i, j)) {
                std::cout << ".";
            } else {
                std::cout << "#";
            }
        }
        std::cout << "\n";
    }
}

size_t Field::numberOfLiveCellsNearly(heightCoordinate h, widthCoordinate w) {
    size_t answer = 0;
    for (size_t i = 0; i < DIRECTION_COUNT; ++i) {
        if (isLive((h + DIRECTION[i][0] + getHeight()) % getHeight(), (w + DIRECTION[i][1] + getWidth()) % getWidth())) {
            answer++;
        };
    }
    return answer;
}

Section Field::getInner() {
    return Section(0, 1, getHeight() - 1, getWidth() - 2, *this);
}

std::vector<Section> Field::getBorders() {
    std::vector<Section> answer;
    answer.clear();
    answer.push_back(Section(0, 0, getHeight() - 1, 0, *this));
    answer.push_back(Section(0, getWidth() - 1, getHeight() - 1 , getWidth() - 1, *this));
    return answer;
}

void Section::setState(heightCoordinate h, widthCoordinate w, bool isLived) {
    field->setState(h + startHeight, w + startWidth, isLived);


}

size_t Section::numberOfLiveCellsNearly(heightCoordinate h, widthCoordinate w) {
    field->numberOfLiveCellsNearly(h + startHeight, w + startWidth);
}

bool Section::isLive(heightCoordinate h, widthCoordinate w) {
    return field->isLive(h + startHeight, w + startWidth);
}

void Field::copyValues(Field field) {
    fieldState.resize(field.getHeight());
    for (size_t i = 0; i < field.getHeight(); ++i) {
        fieldState.at(i).resize(getWidth());
        for (size_t j = 0; j < field.getWidth(); ++j) {
            setState(i, j, field.isLive(i, j));
        }
    }
}

bool Section::isEmpty()const {
    return (startWidth == finishWidth || startHeight == finishHeight);
}

Field::Field(Section section) {
    width_ = section.getWight();
    height_ = section.getHeight();
    fieldState.resize(section.getHeight());
    for (size_t i = section.getStartHeight(); i < section.getFinishHeight(); ++i) {
        fieldState.at(i).resize(section.getWight());
        for (size_t j = section.getStartWeight(); j < section.getFinishWeight(); ++j) {
            setState(i - section.getStartWeight(), j - section.getStartWeight(), section.isLive(i, j));
        }
    }
}

size_t Section::getHeight() {
    return getFinishHeight() - getStartHeight() + 1;
}

size_t Section::getWight() {
    return getFinishWeight() - getStartWeight() + 1;
}

Section Section::getInner() {
    return Section(getStartHeight(), getStartWeight() + 1, getFinishHeight(), getFinishWeight() - 1, *field);
}

std::vector<Section> Section::getBorders() {
    std::vector<Section> bord;
    bord.clear();
    bord.push_back(Section(getStartHeight(), getStartWeight(), getFinishHeight(), getStartWeight(), *field));
    bord.push_back(Section(getStartHeight(), getFinishWeight(), getFinishHeight(), getFinishWeight(), *field));
    return bord;
}

void Section::copyValue(Field &f) {
    for(size_t i = getStartHeight(); i <= getFinishHeight(); ++i) {
        for(size_t j = getStartWeight(); j <= getFinishWeight(); ++j){
            field->setState(i, j, f.isLive(i, j));
        }
    }

}

void Section::print() {
    field->print();

}
