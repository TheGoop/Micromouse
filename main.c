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

int gotoGoal(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord *curr, Heading *dir, int debug_mode) {
    int flag = 1;
    int count = 0;
    while (flag) {
        if (debug_mode) {
            debug_log("-----------------------");
            fprintf(stderr, "Figuring out move from position (%d, %d). Facing %s \n", curr->row, curr->col, dirToString(*dir));
        }
        Action nextMove = floodFill(dists, long_walls, lat_walls, goal, curr, *dir);
        // printLongWalls(long_walls);
        switch(nextMove){
            case FORWARD:
                API_moveForward();
                updateCoordAfterMovingForward(curr, *dir);
                if (debug_mode) {
                    debug_log("MOVE FORWARD");
                }
                count += 1;
                break;
            case LEFT:
                API_turnLeft();
                updateDirectionAfterTurning(dir, LEFT);
                if (debug_mode) {
                    debug_log("TURN LEFT");
                }
                break;
            case RIGHT:
                API_turnRight();
                updateDirectionAfterTurning(dir, RIGHT);
                if (debug_mode) {
                    debug_log("TURN RIGHT");
                }
                break;
            case IDLE:
                flag = 0;
                break;
        }

        // fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr->row, curr->col, dirToString(*dir));
    }

    return count;
}


// You do not need to edit this file.
// This program just runs your solver and passes the choices
// to the simulator.
int main(int argc, char* argv[]) {
    debug_log("Running...");

    int **dists = create_manhattan_dists(NUM_ROWS, NUM_COLS);
    int **long_walls = create_long_walls(NUM_ROWS, NUM_COLS);
    int **lat_walls = create_lat_walls(NUM_ROWS, NUM_COLS);

    Coord origin = {NUM_ROWS - 1,0};
    // we start at the bottom left of the grid
    Coord curr = {NUM_ROWS - 1,0};
    Heading dir = NORTH;

    // we aim to get to the middle of the grid
    Coord goal = {NUM_ROWS / 2, NUM_COLS / 2};

    int moves;
    moves = gotoGoal(dists, long_walls, lat_walls, goal, &curr, &dir, 0);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr.row, curr.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);

    moves = gotoGoal(dists, long_walls, lat_walls, origin, &curr, &dir, 0);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr.row, curr.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);

    moves = gotoGoal(dists, long_walls, lat_walls, goal, &curr, &dir, 0);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr.row, curr.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);
}

