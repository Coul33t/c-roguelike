#ifndef __FOV_H__
#define __FOV_H__

#include "entity.h"
#include "dungeon/dungeon.h"

void make_fov(Entity* player, Dungeon* dungeon);
void clear_fov(Entity* player, Dungeon* dungeon);
bool line_of_sight(Dungeon* dungeon, Position origin, Position target);
int get_sign(int a);
#endif