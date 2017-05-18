//
// Created by Ignacio Mora on 5/9/17.
//


#include <cmath>
#include "Grid.h"

Grid::Grid() {
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            grid[i][j] = new Cell(i,j);

        }
    }

    addNeighbors();
    start = grid[0][0];
    end = grid[N - 1][N - 1];
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

int Grid::heuristic(Cell* a, Cell* b){
    return sqrt((b->row-a->row)*(b->row-a->row)+(b->col-a->col)*(b->col-a->col));
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
            if (j > 0 && i > 0) {
                grid[i][j]->neighbors[4] = grid[i - 1][j - 1];
            } else
                grid[i][j]->neighbors[4] = nullptr;
            if (j > 0 && i < N - 1) {
                grid[i][j]->neighbors[5] = grid[i + 1][j - 1];
            } else
                grid[i][j]->neighbors[5] = nullptr;
            if (j < N - 1 && i > 0) {
                grid[i][j]->neighbors[6] = grid[i - 1][j + 1];
            } else
                grid[i][j]->neighbors[6] = nullptr;
            if (j < N - 1 && i < N - 1) {
                grid[i][j]->neighbors[7] = grid[i + 1][j + 1];
            } else
                grid[i][j]->neighbors[7] = nullptr;
        }
    }
}


void Grid::solve(){
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

                        neighbor->h = heuristic(neighbor, end);
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
