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

Coord* getValidMoves(int **dists, int **long_walls, int **lat_walls, Coord curr) {
    
    Coord* moves = (Coord*)malloc(4 * sizeof(Coord));
    Coord north = {curr.row - 1, curr.col};
    if (validCoords(north) && (long_walls[curr.row][curr.col] == 0)) {
        moves[0] = north;
    }
    Coord south = {curr.row + 1, curr.col};
    if (validCoords(south) && (long_walls[south.row][south.col] == 0)) {
        moves[1] = south;
    }
    Coord west = {curr.row, curr.col - 1};
    if (validCoords(west) && (lat_walls[curr.row][curr.col] == 0)) {
        moves[2] = west;
    }
    Coord east = {curr.row, curr.col + 1};
    if (validCoords(east) && (lat_walls[east.row][east.col] == 0)) {
        moves[3] = east;
    }

    return moves;
}

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