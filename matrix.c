#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

// Returns a nxn 2d array of ints of manhattan distances from the middle 
// of maze. 
int **create_manhattan_dists(int rows, int cols) {

    Coord midpoint = {rows / 2, cols / 2};

    int **dists = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dists[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dists[i][j] = abs(midpoint.row - i) + abs(midpoint.col - j);
        }
    }
    return dists;
}


int **create_int_matrix(int rows, int cols){
    int **walls = (int **)malloc((rows) * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        walls[i] = (int *)malloc((cols + 1) * sizeof(int));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            walls[i][j] = 0;
        }
    }
    return walls;
}

// Creates a (n x n+1) matrix of ints that represent whether there is a wall
// between two blocks in the grid/maze preventing going left or right.
// To see whether there is a wall to the left of (0,1) separating it from (0,0),
// check whether walls[0,1] is 1.
int **create_lat_walls(int rows, int cols) {
    int **walls = create_int_matrix(rows, cols + 1);

    for (int i = 0; i < rows; i++) {
        walls[i][0] = 1;
        walls[i][cols] = 1;
    }

    return walls;
}

// Creates a (n+1 x n) matrix of ints that represent whether there is a wall
// between two blocks in the grid/maze preventing going up or down.
// To see whether there is a wall below (1,0) separating it from (0,0),
// check whether walls[1,0] is 1.
int **create_long_walls(int rows, int cols) {
    int **walls = create_int_matrix(rows + 1, cols);
    for (int j = 0; j < cols; j++) {
        walls[0][j] = 1;
        walls[rows][j] = 1;
    }
    return walls;
}

// Prints a grid with the manhattan distances from the center of the grid
void printGridDistances(int **grid, int rows, int cols){
    fprintf(stderr, "Grid Distances... \n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(stderr, "%d ", grid[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void printWalls(int **walls, int rows, int cols) {
    for (int i = 0; i < rows; i ++){
        for (int j = 0; j < cols; j++) {
            fprintf(stderr, "%d ", walls[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void printLongWalls(int **walls) {
    int rows = NUM_ROWS;
    int cols = NUM_COLS;
    fprintf(stderr, "Longitudal Walls... \n");
    printWalls(walls, rows + 1, cols);
}

void printLatWalls(int **walls) {
    int rows = NUM_ROWS;
    int cols = NUM_COLS;
    fprintf(stderr, "Lateral Walls... \n");
    printWalls(walls, rows, cols + 1);
}