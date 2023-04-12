#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "API.h"


// Creates and returns a 2D array of GridBlocks
// the coords have 0,0 as the bottom left of the grid aka the start point
// When making the manhattan distances, we take them from the middle of the grid
struct GridBlock **createGrid(int rows, int cols) {
    struct GridBlock **grid = (struct GridBlock **) malloc(rows * sizeof(struct GridBlock *));
    
    int i, j;

    struct Coord midpoint = {rows / 2, cols / 2};
    
    for (i = 0; i < rows; i++) {
        grid[i] = (struct GridBlock *) malloc(cols * sizeof(struct GridBlock));
        for (j = 0; j < cols; j++) {
            grid[i][j].coord.row = i;
            grid[i][j].coord.col = j;
            grid[i][j].hasNorthWall = 0;
            grid[i][j].hasSouthWall = 0;
            grid[i][j].hasEastWall = 0;
            grid[i][j].hasWestWall = 0;
            grid[i][j].distance = abs(midpoint.row - i) + abs(midpoint.col - j);
        }
    }

    return grid;
}

// Prints a grid with the manhattan distances from the center of the grid
void printGridDistances(struct GridBlock **grid, int rows, int cols){
    fprintf(stderr, "Grid Distances... \n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(stderr, "%d ", grid[i][j].distance);
        }
        fprintf(stderr, "\n");
    }
}


// This program just runs solver and passes the choices
// to the simulator.
int main(int argc, char* argv[]) {
    debug_log("Running...");

    struct GridBlock **grid = createGrid(NUM_GRID_ROWS, NUM_GRID_COLS);
    // printGridDistances(grid, NUM_GRID_ROWS, NUM_GRID_COLS);


    // Start off at bottom left facing north, goal is to get to middle
    struct Coord goal_position = {NUM_GRID_ROWS/2, NUM_GRID_COLS/2};
    struct Coord curr_position = {0,0};
    Heading dir = NORTH;

    while (1) {
        Action nextMove = solver();
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
