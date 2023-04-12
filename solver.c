#include "solver.h"
#include "API.h"

Action solver() {
    return leftWallFollower();
}

// This is an example of a simple left wall following algorithm.
Action leftWallFollower() {
    if(API_wallFront()) {
        if(API_wallLeft()){
            return RIGHT;
        }
        return LEFT;
    }
    return FORWARD;
}

int validCoords(Coord curr) {
    if ((curr.row >= 0 && curr.row < NUM_ROWS) && (curr.col >= 0 && curr.col < NUM_COLS)) {
        return 1;
    }
    return 0;
}

void recalculateDists(int **dists, int **long_walls, int **lat_walls, Coord goal) { 

}

// Put your implementation of floodfill here!
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord curr, Heading dir) 
{
    return IDLE;
}