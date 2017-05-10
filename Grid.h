//
// Created by Ignacio Mora on 5/9/17.
//

#ifndef GENETICCOLOSSEUM_GRID_H
#define GENETICCOLOSSEUM_GRID_H


#include "Cell.h"
#include <iostream>
#include <vector>

#define N 30
class Cell;

class Grid {

public:
    Grid();
    Cell* grid[N][N];
    Cell* start;
    Cell* end;
    void printGrid();
    void addNeighbors();
    void solve();
    void remove(Cell*);
    std::vector<Cell*> path;
    std::vector<Cell*> openSet;
    void printPath();
private:

    std::vector<Cell*> closedSet;


    bool contains(std::vector<Cell *, std::allocator<Cell *>> vector, Cell *cell);

    int heuristic(Cell *a, Cell *b);


};



#endif //GENETICCOLOSSEUM_GRID_H