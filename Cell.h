//
// Created by Ignacio Mora on 5/9/17.
//

#ifndef GENETICCOLOSSEUM_CELL_H
#define GENETICCOLOSSEUM_CELL_H


#include <list>
#include "Grid.h"

class Grid;

class Cell {

public:
    Cell(int i, int j);
    int row;
    int col;
    int f;
    int g;
    int h;
    bool obstacle;
    Cell* previous;
    Cell* neighbors[8];




};


#endif //GENETICCOLOSSEUM_CELL_H
