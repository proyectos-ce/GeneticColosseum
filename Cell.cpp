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


}

