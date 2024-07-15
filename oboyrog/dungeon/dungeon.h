#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include <stdlib.h>
#include <stdbool.h>

#include "tile.h"
#include "room.h"
#include "../comp/position.h"
#include "../tools/tools.h"
#include "../constants.h"

typedef struct Dungeon {
    // 1D array for a 2D map
    Tile* map[DUNGEON_SIZE_X * DUNGEON_SIZE_Y];

    // 50 rooms at most is enough yo
    Room* rooms[50];
    int nb_of_rooms;

    Position safe_start_position;
} Dungeon;

// ---------------------------------
// ----- DUNGEON ROOM CREATION -----
// ---------------------------------
void draw_h_line(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int w, bool link_rooms);
void draw_v_line(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int h, bool link_rooms);

void draw_rectangle(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int w, int h);

void draw_room(Dungeon* dungeon, int x, int y, int w, int h);

// TODO
void draw_h_corridor(Dungeon* dungeon, int x, int y, int w);
void draw_v_corridor(Dungeon* dungeon, int x, int y, int h);

// ----------------------
// ----- DEBUG GRID -----
// ----------------------
void draw_debug_grid(Dungeon* dungeon, int gap);


// ----------------------------
// ----- DUNGEON CREATION -----
// ----------------------------
Dungeon* create_empty_dungeon();
Dungeon* create_wall_dungeon();
Dungeon* create_basic_dungeon();

void draw_test_lines(Dungeon* dungeon);

Tile* get_dungeon_tile_from_dir(Dungeon* dungeon, DIRECTION dir, int x, int y);
Tile* get_dungeon_tile(Dungeon* dungeon, int x, int y);

bool is_in_map(int x, int y);

Room* get_random_room(Dungeon* dungeon);

void count_seen_and_visible(Dungeon* dungeon);


#endif