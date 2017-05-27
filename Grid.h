//
// Created by Ignacio Mora on 5/9/17.
//

#ifndef GENETICCOLOSSEUM_GRID_H
#define GENETICCOLOSSEUM_GRID_H

#include "gladiator.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>

#define N 10
class Cell;

class Grid {

public:
    Grid(char side);
    Cell* grid[N][N];
    Cell* start;
    Cell* end;
    void printGrid();
    void addNeighbors();
    void solve(Gladiator gladiator);
    void remove(Cell*);
    std::vector<Cell*> path;
    std::vector<Cell*> openSet;
    void printPath();
    std::vector<sf::Vector2f*> getPixelPath();
    void generatePixelPath();
private:

    std::vector<Cell*> closedSet;
    std::vector<sf::Vector2f*> pixelPath;


    bool contains(std::vector<Cell *, std::allocator<Cell *>> vector, Cell *cell);

    int heuristic(Cell *a, Cell *b, Gladiator gladiator);



};



#endif //GENETICCOLOSSEUM_GRID_H
