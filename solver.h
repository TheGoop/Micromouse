#ifndef SOLVER_H
#define SOLVER_H

#define NUM_ROWS 5
#define NUM_COLS 5

typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

Action solver();
Action leftWallFollower();
Action floodFill();
void recalculateDists();


#endif