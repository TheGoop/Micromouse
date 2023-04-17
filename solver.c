#include "solver.h"
#include "API.h"
#include "queue.h"
#include "hashset.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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


void updateDirectionAfterTurning(Heading *dir, Action action) {
    if (*dir == NORTH) {
        if (action == LEFT) {
            *dir = WEST;
        }
        else if (action == RIGHT) {
            *dir = EAST;
        }
    }
    else if (*dir == SOUTH) {
        if (action == LEFT) {
            *dir = EAST;
        }
        else if (action == RIGHT) {
            *dir = WEST;
        }
    }
    else if (*dir == EAST) {
        if (action == LEFT) {
            *dir = NORTH;
        }
        else if (action == RIGHT) {
            *dir = SOUTH;
        }
    }
    // west
    else {
        if (action == LEFT) {
            *dir = SOUTH;
        }
        else if (action == RIGHT) {
            *dir = NORTH;
        }
    }
}

void updateCoordAfterMovingForward(Coord *curr, Heading dir) {

    if (dir == NORTH) {
        curr->row -= 1;
    }

    else if (dir == SOUTH) {
        curr->row += 1;
    }

    else if (dir == EAST) {
        curr->col += 1;
    }
    
    // west
    else {
        curr->col -= 1;
    }
    
}

int validCoords(Coord curr) {
    if ((curr.row >= 0 && curr.row < NUM_ROWS) && (curr.col >= 0 && curr.col < NUM_COLS)) {
        return 1;
    }
    return 0;
}

Coord* getValidMoves(int **dists, int **long_walls, int **lat_walls, Coord curr, int notFloodFill) {
    Coord invalid = {-1,-1};
    Coord* moves = (Coord*)malloc(4 * sizeof(Coord));
    for (int i = 0; i < 4; i++) {
        moves[i] = invalid;
    }

    
    Coord north = {curr.row, curr.col};
    if (validCoords(north) && (long_walls[north.row][north.col] == 0)) {
        moves[0].row = curr.row - 1;
        moves[0].col = curr.col;
    }
    Coord south = {curr.row + 1, curr.col};
    if (validCoords(south) && (long_walls[south.row][south.col] == 0)) {
        moves[1].row = curr.row + 1;
        moves[1].col = curr.col;
    }
    Coord west = {curr.row, curr.col};
    if (validCoords(west) && (lat_walls[curr.row][curr.col] == 0)) {
        moves[2].row = curr.row;
        moves[2].col = curr.col - 1;
    }
    Coord east = {curr.row, curr.col + 1};
    if (validCoords(east) && (lat_walls[east.row][east.col] == 0)) {
        moves[3].row = curr.row;
        moves[3].col = curr.col + 1;
    }

    return moves;
}


void recalculateDists(int **dists, int **long_walls, int **lat_walls, Coord goal, int debug) { 
    // reset dists to an impossibly high number so that we don't accidentally maintain any old info
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            dists[i][j] = 100000;
        }
    }

    // printLatWalls(lat_walls);
    // printLongWalls(long_walls);
    // printGridDistances(dists);

    Queue *q = create_queue();
    int curr_steps = 0;
    enqueue(q, goal);


    HashSet *visited = hashset_create((NUM_ROWS + 1) * (NUM_COLS + 1));
    
    fprintf(stderr, "Queue Size: %d, Visited Size: %d\n", queue_size(q), hashset_size(visited));

    // BFS
    while (is_empty(q) == 0) {
        if(debug) {
            fprintf(stderr, "--------- FLOOD LEVEL %d ---------\n", curr_steps);
        }
        // look at all of the blocks one flood level outwards
        int iters = queue_size(q);
        for (int i = 0; i < iters; i++) {
            // examine a block  
            Coord temp = dequeue(q);

            // if block already looked at, move on
            if (hashset_contains(visited, temp)) {
                continue;
            }

            // mark its distance from the goal
            dists[temp.row][temp.col] = curr_steps < dists[temp.row][temp.col] ? curr_steps : dists[temp.row][temp.col];

            // fprintf(stderr, "Curr: %d, %d\n", temp.row, temp.col);
            // usleep(10000);
            // add the next level of flood to the queue
            Coord* validMoves = getValidMoves(dists, long_walls, lat_walls, temp, 0);
            for (int j = 0; j < 4; j++) {
                // if valid moves, and not visited before, we will visit it
                if (validCoords(validMoves[j]) && hashset_contains(visited, validMoves[j]) == 0) {
                    if(debug) {
                        fprintf(stderr, "Curr: %d, %d to Valid Coords: %d, %d\n", temp.row, temp.col, validMoves[j].row, validMoves[j].col);
                    }
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

void markDirectionalWall(Coord curr, Heading wall_dir, int **long_walls, int **lat_walls) {

    // 13 0 -> check 13 0
    if (wall_dir == NORTH) {
        long_walls[curr.row][curr.col] = 1;
    }

    // 13 0 -> check 14 0
    else if (wall_dir == SOUTH) {
        long_walls[curr.row + 1][curr.col] = 1;
    }

    // 15 0 -> check 15 0 
    else if (wall_dir == WEST) {
        lat_walls[curr.row][curr.col] = 1;
    }

    // 15 0 -> check 15 1
    else {
        lat_walls[curr.row][curr.col + 1] = 1;
    }

}

void markWallsAround(Coord curr, Heading dir, int **long_walls, int **lat_walls) {
    if (dir == NORTH) {
        // if wall north of us
        if (API_wallFront()) {
            debug_log("Seen Wall North");
            markDirectionalWall(curr, NORTH, long_walls, lat_walls);
        }

        // if wall west of us
        if (API_wallLeft()) {
            debug_log("Seen Wall West");
            markDirectionalWall(curr, WEST, long_walls, lat_walls);
        }

        // if wall east of us
        if (API_wallRight()) {
            debug_log("Seen Wall East");
            markDirectionalWall(curr, EAST, long_walls, lat_walls);
        }
    }

    else if (dir == SOUTH) {
        // if wall south of us
        if (API_wallFront()) {
            debug_log("Seen Wall South");
            markDirectionalWall(curr, SOUTH, long_walls, lat_walls);
        }

        // if wall east of us
        if (API_wallLeft()) {
            debug_log("Seen Wall East");
            markDirectionalWall(curr, EAST, long_walls, lat_walls);
        }

        // if wall west of us
        if (API_wallRight()) {
            debug_log("Seen Wall West");
            markDirectionalWall(curr, WEST, long_walls, lat_walls);
        }
    }

    else if (dir == WEST) {
        // if wall west of us
        if (API_wallFront()) {
            debug_log("Seen Wall West");
            markDirectionalWall(curr, WEST, long_walls, lat_walls);
        }

        // if wall south of us
        if (API_wallLeft()) {
            debug_log("Seen Wall South");
            markDirectionalWall(curr, SOUTH, long_walls, lat_walls);
        }

        // if wall north of us
        if (API_wallRight()) {
            debug_log("Seen Wall North");
            markDirectionalWall(curr, NORTH, long_walls, lat_walls);
        }
    }

    // else we are facing east
    else {
        // if wall east of us
        if (API_wallFront()) {
            debug_log("Seen Wall East");
            markDirectionalWall(curr, EAST, long_walls, lat_walls);
        }

        // if wall north of us
        if (API_wallLeft()) {
            debug_log("Seen Wall North");
            markDirectionalWall(curr, NORTH, long_walls, lat_walls);
        }

        // if wall south of us
        if (API_wallRight()) {
            debug_log("Seen Wall South");
            markDirectionalWall(curr, SOUTH, long_walls, lat_walls);
        }
    }

}

// Gets action to change from facing one direction to change to facing an intended direction
Action getActionToSwitchDirections(Heading curr_dir, Heading intended_dir) {
    if (curr_dir == intended_dir) {
        return FORWARD;
    }

    else if (curr_dir == NORTH) {
        if (intended_dir == SOUTH) { 
            return RIGHT;
        }
        else if (intended_dir == WEST) { 
            return LEFT;
        }
        // east
        else { 
            return RIGHT;
        }
    }

    else if (curr_dir == EAST) {
        if (intended_dir == SOUTH) { 
            return RIGHT;
        }
        else if (intended_dir == WEST) { 
            return RIGHT;
        }
        // north
        else { 
            return LEFT;
        }
    }

    else if (curr_dir == WEST) {
        if (intended_dir == SOUTH) { 
            return LEFT;
        }
        else if (intended_dir == NORTH) { 
            return RIGHT;
        }
        // east
        else { 
            return RIGHT;
        }
    }

    // SOUTH
    else {
        if (intended_dir == NORTH) { 
            return RIGHT;
        }
        else if (intended_dir == WEST) { 
            return RIGHT;
        }
        // east
        else { 
            return LEFT;
        }
    }
}


// Gets the action to get robot facing dir direction at start coordinate to go to end coord
// end coord should be directly adjacent to start.
Action getActionForNextMove(Coord start, Coord end, Heading dir) {
    if (abs(start.row - end.row) + abs(start.col - end.col) > 1) {
        exit(EXIT_FAILURE);
    }

    // if we need to head north
    if (start.row - end.row == 1) {
        return getActionToSwitchDirections(dir, NORTH);
    }

    // we need to head south
    else if (start.row - end.row == -1) {
        return getActionToSwitchDirections(dir, SOUTH);

    }

    // we need to head west
    else if (start.col - end.col == 1) {
        return getActionToSwitchDirections(dir, WEST);
    }

    // we need to head east
    else {
        return getActionToSwitchDirections(dir, EAST);
    }
}

// Put your implementation of floodfill here!
Action floodFill(int **dists, int **long_walls, int **lat_walls, 
        Coord goal, Coord *curr, Heading dir) 
{

    // check for walls around curr and update wall matrices
    markWallsAround(*curr, dir, long_walls, lat_walls);

    // debug_log("Recalculating Distances...");
    // update manhattan distances
    recalculateDists(dists, long_walls, lat_walls, goal, 0);

    if (curr->row == goal.row && curr->col == goal.col) {
        return IDLE;
    }


    int smallestDist = NUM_ROWS * NUM_COLS + 2;
    Coord nextBlock = {-1,-1};

    // debug_log("Getting Valid Moves...");
    // get valid blocks
    Coord *valid_pos = getValidMoves(dists, long_walls, lat_walls, *curr, 1);

    // pick block with smallest manhattan distance 
    for (int i = 0; i < 4; i++) {
        // fprintf(stderr, "%d, %d\n", valid_pos[i].row, valid_pos[i].col);
        // fprintf(stderr, "Smallest Distance: %d\n", smallestDist);
        if (validCoords(valid_pos[i])) {
            // fprintf(stderr, "Coord distance: %d\n", dists[valid_pos[i].row][valid_pos[i].col]);
            if (i == 0 || dists[valid_pos[i].row][valid_pos[i].col] < smallestDist) {
                nextBlock.row = valid_pos[i].row;
                nextBlock.col = valid_pos[i].col;
                smallestDist = dists[valid_pos[i].row][valid_pos[i].col];
                // debug_log("Something chosen");
            }
        }
    }
    if (nextBlock.row == -1 && nextBlock.col == -1) {
        fprintf(stderr, "Block chosen is null.\n");
        printLatWalls(lat_walls);
        printLongWalls(long_walls);
        printGridDistances(dists);
        exit(EXIT_FAILURE);
    }
    debug_log("Chose Best Block.");

    fprintf(stderr, "Move to: (%d, %d)\n", nextBlock.row, nextBlock.col);

    // figure out relative to curr and dir, which direction to go for block
    Action nextAction = getActionForNextMove(*curr, nextBlock, dir);
    free(valid_pos);
    return nextAction;
}
