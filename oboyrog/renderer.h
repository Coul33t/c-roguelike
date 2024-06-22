#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "constants.h"

void init_ncurses_rendering();
void clear_console();
void close_ncurses_rendering();

void render_entity(Entity* entity);
void render_dungeon(Dungeon* dungeon);

#endif