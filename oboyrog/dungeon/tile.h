#ifndef __TILE_H__
#define __TILE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    WALL,
    FLOOR,
    GLASS
} TILE_TYPE;

typedef struct Tile {
    char chr;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
} Tile;

Tile* get_tile(TILE_TYPE tile_type);
Tile* get_debug();
Tile* get_void();
Tile* get_wall();
Tile* get_floor();
Tile* get_glass();

#endif