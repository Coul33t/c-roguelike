#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <math.h>

#include "../comp/position.h"
#include "../constants.h"

int get_1d_idx_from_2d_coord(int x, int y, int w);
int get_1d_from_2d_dungeon(int x, int y);
float get_distance_from_coords(int x1, int y1, int x2, int y2);
float get_distance_from_pos(Position origin, Position target);
int get_str_size(char* str);
#endif