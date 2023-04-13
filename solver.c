#include "solver.h"
#include "API.h"
#include "coord.h"
#include "queue.h"
#include "hashset.h"
#include <stdlib.h>

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
    Coord invalid = {-1,-1};
    Coord* moves = (Coord*)malloc(4 * sizeof(Coord));
    for (int i = 0; i < 4; i++) {
        moves[i] = invalid;
    }

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
    // reset dists to an impossibly high number so that we don't accidentally maintain any old info
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            dists[i][j] = NUM_ROWS * NUM_COLS + 2;
        }
    }

    Queue *q = create_queue();
    int curr_steps = 0;
    enqueue(q, goal);

    HashSet *visited = hashset_create((NUM_ROWS + 1) * (NUM_COLS + 1));
    // BFS
    while (!is_empty(q)) {
        // look at all of the blocks one flood level outwards
        int iters = queue_size(q);
        for (int i = 0; i < iters; i++) {
            // examine a block and mark its distance from the goal
            Coord temp = dequeue(q);
            dists[temp.row][temp.col] = curr_steps < dists[temp.row][temp.col] ? curr_steps : dists[temp.row][temp.col];

            // add the next level of flood to the queue
            Coord* validMoves = getValidMoves(dists, long_walls, lat_walls, temp);
            for (int j = 0; j < 4; j++) {
                // if valid moves, and not visited before, we will visit it
                if (validCoords(validMoves[j]) && hashset_contains(visited, validMoves[j]) == 0) {
                    enqueue(q, validMoves[j]);
                }
            }
            free(validMoves);

            // mark the node we examined as visited
            hashset_add(visited, temp);
        }
        // increment the flood level count
        curr_steps += 1;
    }

    hashset_free(visited);
    destroy_queue(q);
}

// Put your implementation of floodfill here!
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord curr, Heading dir) 
{
    return IDLE;
}