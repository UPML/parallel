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
    for(size_t i = 0; i < DIRECTION_COUNT; ++i){
        if(isLive((h + DIRECTION[i][0]) % getHeight(), (w + DIRECTION[i][1]) % getWeight())){
            answer++;
        };
    }
    return answer;
}
