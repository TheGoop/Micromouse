#ifndef SOLVER_H
#define SOLVER_H

#define NUM_ROWS 16
#define NUM_COLS 16


#include "coord.h"
typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

Action solver();
Action leftWallFollower();
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord *curr, Heading dir);
void recalculateDists();

void updateCoordAfterMovingForward(Coord *curr, Heading dir);
void updateDirectionAfterTurning(Heading *dir, Action action);


#endif