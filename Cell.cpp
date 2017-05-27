//
// Created by Ignacio Mora on 5/9/17.
//

#include "Cell.h"
#include <time.h>

Cell::Cell(int i, int j) {
    this->row = i;
    this->col = j;
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->previous = nullptr;
    this->obstacle = false;
    if (rand() % 100 < 10){
        this->obstacle = true;
    }
    if (((i == 0 && j == 0) || (i == 4 && j == N - 1) ) || ((i == 0 && j == N - 1) || (i == 4 && j == 0) ))
        this->obstacle = false;

}

