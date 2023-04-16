#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "API.h"
#include "coord.h"
#include "matrix.h"



char* dirToString(Heading dir) {
    if (dir == NORTH) {
        return "NORTH";
    }
    else if (dir == SOUTH) {
        return "SOUTH";
    }

    else if (dir == WEST) {
        return "WEST";
    }
    else {
        return "EAST";
    }
}


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
    

    // recalculateDists(dists, long_walls, lat_walls);
    int count = 0;
    while (1) {
        debug_log("-----------------------");
        fprintf(stderr, "Figuring out move from position (%d, %d). Facing %s \n", curr.row, curr.col, dirToString(dir));
        Action nextMove = floodFill(dists, long_walls, lat_walls, goal, &curr, dir);
        printLatWalls(lat_walls);
        // printLongWalls(long_walls);
        switch(nextMove){
            case FORWARD:
                API_moveForward();
                updateCoordAfterMovingForward(&curr, dir);
                debug_log("MOVE FORWARD");
                break;
            case LEFT:
                API_turnLeft();
                updateDirectionAfterTurning(&dir, LEFT);
                debug_log("TURN LEFT");
                break;
            case RIGHT:
                API_turnRight();
                updateDirectionAfterTurning(&dir, RIGHT);
                debug_log("TURN RIGHT");
                break;
            case IDLE:
                break;
        }

        fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr.row, curr.col, dirToString(dir));
        count += 1;
        if (count > 7) {
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