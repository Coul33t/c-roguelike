#ifndef __FOV_H__
#define __FOV_H__

#include "entity.h"
#include "dungeon/dungeon.h"

// TODO: FOV map different from the map (useful for checking if a monster is in FOV or not)
typedef struct FOVMap {
    bool visible_map[DUNGEON_SIZE_X * DUNGEON_SIZE_Y];
    bool seen_map[DUNGEON_SIZE_X * DUNGEON_SIZE_Y];
} FOVMap;

void init_fov_map(FOVMap* fov_map);
void make_fov(Entity* player, Dungeon* dungeon, FOVMap* fov_map);
void clear_fov(Dungeon* dungeon, FOVMap* fov_map);
bool is_visible(Entity* entity, FOVMap* fov_map);
bool line_of_sight(Dungeon* dungeon, Position origin, Position target);
int get_sign(int a);
#endif