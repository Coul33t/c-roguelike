#ifndef __POSITION_H__
#define __POSITION_H__

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} DIRECTION;

typedef struct Position {
    int x;
    int y;
} Position;

#endif