#ifndef __TILE_H__
#define __TILE_H__

#include <stdbool.h>

typedef struct Tile {
    char chr;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
} Tile;

Tile* get_wall();
Tile* get_floor();
Tile* get_glass();

#endif