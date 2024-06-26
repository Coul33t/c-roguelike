#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "fov.h"
#include "constants.h"

void init_ncurses_rendering();
void clear_console();
void close_ncurses_rendering();

void render_entity(Entity* entity, FOVMap* fov_map);
void render_monsters(Entity* monsters[], FOVMap* fov_map);
void render_dungeon(Dungeon* dungeon, FOVMap* fov_map);

#endif