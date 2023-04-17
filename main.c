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

int moveTo(Coord dest, Coord *src, Heading *dir, 
                int **dists, int **long_walls, int **lat_walls, int debug_mode, int NUM_ROWS, int NUM_COLS) {
    int flag = 1;
    int count = 0;
    while (flag) {
        if (debug_mode) {
            debug_log("-----------------------");
            fprintf(stderr, "Figuring out move from position (%d, %d). Facing %s \n", src->row, src->col, dirToString(*dir));
        }
        Action nextMove = floodFill(dists, long_walls, lat_walls, dest, src, *dir, NUM_ROWS, NUM_COLS);
        // printLongWalls(long_walls);
        switch(nextMove){
            case FORWARD:
                API_moveForward();
                updateCoordAfterMovingForward(src, *dir);
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

        // fprintf(stderr, "Now at (%d, %d). Facing %s \n", src->row, src->col, dirToString(*dir));
    }

    return count;
}


// You do not need to edit this file.
// This program just runs your solver and passes the choices
// to the simulator.
int main(int argc, char* argv[]) {

    int NUM_ROWS = API_mazeHeight();
    int NUM_COLS = API_mazeWidth();
    debug_log("Running...");
    int **dists = create_manhattan_dists(NUM_ROWS, NUM_COLS);
    int **long_walls = create_long_walls(NUM_ROWS, NUM_COLS);
    int **lat_walls = create_lat_walls(NUM_ROWS, NUM_COLS);
    
    // fprintf(stderr, "%d, %d\n", API_mazeWidth(), API_mazeHeight());
    
    Coord origin = {NUM_ROWS - 1,0};
    
    // we start at the bottom left of the grid headed north
    Coord curr_pos = {NUM_ROWS - 1,0};
    Heading dir = NORTH;
    // we aim to get to the middle of the grid
    Coord goal = {NUM_ROWS / 2, NUM_COLS / 2};

    // ----------- MAZE LEARNING SEGMENT -----------
    // go from origin to middle 
    int moves = moveTo(goal, &curr_pos, &dir, dists, long_walls, lat_walls, 0, NUM_ROWS, NUM_COLS);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr_pos.row, curr_pos.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);
    // middle back to origin
    moves = moveTo(origin, &curr_pos, &dir, dists, long_walls, lat_walls, 0, NUM_ROWS, NUM_COLS);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr_pos.row, curr_pos.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);
    // --------------------------------------------

    // ----------- COMPETITION SEGMENT -----------
    // Go from origin to middle using learned walls and distances
    moves = moveTo(goal, &curr_pos, &dir, dists, long_walls, lat_walls, 0, NUM_ROWS, NUM_COLS);
    fprintf(stderr, "Now at (%d, %d). Facing %s \n", curr_pos.row, curr_pos.col, dirToString(dir));
    fprintf(stderr, "Route took %d moves\n", moves);
    // --------------------------------------------
}

