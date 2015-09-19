//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_FIELD_H
#define PARALLEL_FIELD_H


#include <glob.h>
#include <bits/stl_bvector.h>

typedef size_t heightCoordinate;
typedef size_t weightCoordinate;
static const double PROBABILITY = 1/5;

class field {
public:
    void randomFill(const double probability);

    field(size_t height, size_t weight):height_(height), weight_(weight){
        randomFill(PROBABILITY);
    };
    size_t getHeight() const {
            return height_;
    }

    size_t getWeight() const {
            return weight_;
    }

    bool isLive(heightCoordinate h, weightCoordinate w){
        return fieldState.at(h).at(w);
    }

    void setState(heightCoordinate h, weightCoordinate w, bool isLived){
        fieldState.at(h).at(w) = isLived;
    }

    void print(){

    }
private:
    size_t height_;
    size_t weight_;
    std::vector<std::vector<bool >> fieldState;
};

static const size_t DIRECTION_COUNT = 8 ;
static const int DIRECTION[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
};


#endif //PARALLEL_FIELD_H
