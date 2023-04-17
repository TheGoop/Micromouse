#ifndef SOLVER_H
#define SOLVER_H


#include "coord.h"
typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

Action solver();
Action leftWallFollower();
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord *curr, Heading dir, int NUM_ROWS, int NUM_COLS);
void recalculateDists();
Coord* getValidMoves(int **dists, int **long_walls, int **lat_walls, Coord curr, int NUM_ROWS, int NUM_COLS, int notFloodFill);
void updateCoordAfterMovingForward(Coord *curr, Heading dir);
void updateDirectionAfterTurning(Heading *dir, Action action);


#endif