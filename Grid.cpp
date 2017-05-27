//
// Created by Ignacio Mora on 5/9/17.
//


#include <cmath>
#include "Grid.h"

Grid::Grid(char side) {
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            grid[i][j] = new Cell(i,j);

        }
    }

    addNeighbors();
    if (side == 'L'){
    start = grid[0][0];
    end = grid[4][N-1];
    }
    else if (side == 'R'){
        start = grid[0][N-1];
        end = grid[4][0];
    }

    while (towerCells.size() <  20){
        int randRow = rand() % 10;
        int randCol = rand() % 10;
        if (std::find(towerCells.begin(), towerCells.end(), grid[randRow][randCol]) == towerCells.end() && grid[randRow][randCol] != start && grid[randRow][randCol] != end ){
            towerCells.push_back(grid[randRow][randCol]);
            grid[randRow][randCol]->obstacle = true;
        }
    }
}



void Grid::remove(Cell* cell){
    int i;
    for (i = 0; i < openSet.size(); i++){
        if (openSet[i] == cell){
            openSet.erase(openSet.begin()+i);
        }
    }

}

bool Grid::contains(std::vector<Cell*> vector, Cell* cell){
    int i;
    for (i = 0; i < vector.size(); i++){
        if (vector[i] == cell){
            return true;
        }
    }
    return false;
}

int Grid::heuristic(Cell* a, Cell* b, Gladiator gladiator){
    return abs((b->row-a->row)*gladiator.dna.genes[VericalCost])+abs((b->col-a->col)*gladiator.dna.genes[HorizontalCost]);
}

void Grid::addNeighbors(){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            // Abajo
            if (i < N -1) {
                grid[i][j]->neighbors[0] = grid[i + 1][j];
            } else
                grid[i][j]->neighbors[0] = nullptr;
            // Arriba
            if (i > 0){
                grid[i][j]->neighbors[1] = grid[i - 1][j];
            } else
                grid[i][j]->neighbors[1] = nullptr;
            // Derecha
            if (j < N - 1) {
                grid[i][j]->neighbors[2] = grid[i][j + 1];
            } else
                grid[i][j]->neighbors[2] = nullptr;
            // Izquierda
            if (j > 0 ) {
                grid[i][j]->neighbors[3] = grid[i][j - 1];
            } else
                grid[i][j]->neighbors[3] = nullptr;
//            Diagonales
//            if (j > 0 && i > 0) {
//                grid[i][j]->neighbors[4] = grid[i - 1][j - 1];
//            } else
//                grid[i][j]->neighbors[4] = nullptr;
//            if (j > 0 && i < N - 1) {
//                grid[i][j]->neighbors[5] = grid[i + 1][j - 1];
//            } else
//                grid[i][j]->neighbors[5] = nullptr;
//            if (j < N - 1 && i > 0) {
//                grid[i][j]->neighbors[6] = grid[i - 1][j + 1];
//            } else
//                grid[i][j]->neighbors[6] = nullptr;
//            if (j < N - 1 && i < N - 1) {
//                grid[i][j]->neighbors[7] = grid[i + 1][j + 1];
//            } else
//                grid[i][j]->neighbors[7] = nullptr;
        }
    }
}


void Grid::solve(Gladiator gladiator){
    bool notSolved = true;
    this->openSet.push_back(start);
    int i;
    int winner = 0;
    while(notSolved) {
        if (openSet.size() > 0) {
            for (i = 0; i < openSet.size(); i++){
                if (openSet[i]->f < openSet[winner]->f){
                    winner = i;
                }
            }

            Cell* current = openSet[winner];

            if (current == end) {
                path.push_back(current);
                while (current->previous){
                    path.push_back(current->previous);
                    current = current->previous;
                }

                notSolved = false;
            }

            this->remove(current);
            closedSet.push_back(current);

            for (i = 0; i < 4; i++){
                if (current->neighbors[i] != nullptr){
                    Cell* neighbor = current->neighbors[i];

                    if (!contains(closedSet, neighbor) && !neighbor->obstacle){
                        int tempG = current->g + 1;

                        if (contains(openSet, neighbor)){
                            if (tempG < neighbor->g){
                                neighbor->g = tempG;
                            }

                        } else {
                            neighbor->g = tempG;
                            openSet.push_back(neighbor);
                        }

                        neighbor->h = heuristic(neighbor, end, gladiator);
                        neighbor->f = neighbor->g + neighbor->h;
                        neighbor->previous = current;
                    }


                }
            }

        } else {
            // no solution
        }
    }


}


void Grid::printGrid(){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            std::cout <<  grid[i][j]->obstacle << ", ";
        }
        std::cout << std::endl;
    }
}

void Grid::printPath(){
    int i;
    for (i = 0; i < path.size(); i++){
        std::cout << "[" << path[i]->row << ", " << path[i]->col << "], ";
    }
}

void Grid::generatePixelPath(){
    int i;
    for (i = 0; i < path.size(); i++) {
        pixelPath.push_back(new sf::Vector2f(path[i]->col * 45, 175 + path[i]->row * 45));
    }
}

std::vector<sf::Vector2f *> Grid::getPixelPath() {
    return pixelPath;
}






