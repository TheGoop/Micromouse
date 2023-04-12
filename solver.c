#include "solver.h"
#include "API.h"
#include "queue.h"

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

int isValidCoord(int row, int col) {
    if ((row >= 0 && row < NUM_GRID_ROWS) && (col >= 0 && col < NUM_GRID_COLS)) {
        return 1;
    }
    return 0;
}

// Recalculates all of the manhattan distances of grid based upon new wall information
void recalculateDistances(struct GridBlock** grid) {
    return;
    
}

// Put your implementation of floodfill here!
Action floodFill(struct GridBlock **grid, struct Coord curr, Heading dir, struct Coord goal) {


    return IDLE;
}