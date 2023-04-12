#include "solver.h"
#include "API.h"
#include "coord.h"
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

int validCoords(Coord curr) {
    if ((curr.row >= 0 && curr.row < NUM_ROWS) && (curr.col >= 0 && curr.col < NUM_COLS)) {
        return 1;
    }
    return 0;
}

// int* getValidMoves(int **dists, int **long_walls, int **lat_walls, Coord curr_pos) {
    
//     Coord north = {curr_pos.row - 1, curr_pos.col};
//     Coord south = {curr_pos.row + 1, curr_pos.col};
//     Coord east = {curr_pos.row, curr_pos.col + 1};
//     Coord west = {curr_pos.row, curr_pos.col - 1};

//     // Coord possible_moves = 
//     return 

// }

void recalculateDists(int **dists, int **long_walls, int **lat_walls, Coord goal) { 
    Queue *q = create_queue();
    int curr_steps = 0;
    enqueue(q, goal);

    while (!is_empty(q)) {
        
    }
}

// Put your implementation of floodfill here!
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord curr, Heading dir) 
{
    return IDLE;
}