#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "tile.h"
#include "../comp/position.h"
#include "../tools.h"

#define DUNGEON_SIZE_X 100
#define DUNGEON_SIZE_Y 100

typedef struct Dungeon {
    // 1D array for a 2D map
    Tile* map[DUNGEON_SIZE_X * DUNGEON_SIZE_Y];

    Position safe_start_position;
} Dungeon;

Dungeon* create_basic_dungeon();

#endif