#ifndef SOLVER_H
#define SOLVER_H

typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

#define NUM_GRID_ROWS 8
#define NUM_GRID_COLS 8

Action solver();
Action leftWallFollower();
Action floodFill();

struct Coord {
    int row;
    int col;
};

struct GridBlock {
    struct Coord coord;
    int hasNorthWall;
    int hasSouthWall;
    int hasEastWall;
    int hasWestWall;
    int distance;
};

#endif