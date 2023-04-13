#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "API.h"
#include "coord.h"
#include "matrix.h"


// You do not need to edit this file.
// This program just runs your solver and passes the choices
// to the simulator.
int main(int argc, char* argv[]) {
    debug_log("Running...");

    int **dists = create_manhattan_dists(NUM_ROWS, NUM_COLS);
    int **long_walls = create_long_walls(NUM_ROWS, NUM_COLS);
    int **lat_walls = create_lat_walls(NUM_ROWS, NUM_COLS);


    // we start at the bottom left of the grid
    Coord curr = {NUM_ROWS - 1,0};
    Heading dir = NORTH;

    // we aim to get to the middle of the grid
    Coord goal = {NUM_ROWS / 2, NUM_COLS / 2};

    while (1) {
        debug_log("Figuring out move.");
        Action nextMove = floodFill(dists, long_walls, lat_walls, goal, curr, dir);

        // printLongWalls(long_walls);
        // printLatWalls(lat_walls);
        switch(nextMove){
            case FORWARD:
                API_moveForward();
                break;
            case LEFT:
                API_turnLeft();
                break;
            case RIGHT:
                API_turnRight();
                break;
            case IDLE:
                break;
        }
    }
}


/**
    lat_walls[NUM_ROWS - 1][1] = 1;
    lat_walls[NUM_ROWS - 2][1] = 1;
    lat_walls[NUM_ROWS - 3][1] = 1;
    printLatWalls(lat_walls);

    long_walls[1][2] = 1;
    long_walls[2][2] = 1;
    long_walls[3][2] = 1;
    printLongWalls(long_walls);

    recalculateDists(dists, long_walls, lat_walls, goal);
    printGridDistances(dists, NUM_ROWS, NUM_COLS);
*/