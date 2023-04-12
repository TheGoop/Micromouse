#ifndef SOLVER_H
#define SOLVER_H

#define NUM_ROWS 5
#define NUM_COLS 5

typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

typedef struct {
    int row;
    int col;
} Coord;

Action solver();
Action leftWallFollower();
Action floodFill();


#endif