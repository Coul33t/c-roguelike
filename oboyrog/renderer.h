#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <ncurses.h>
#include "entity.h"
#include "dungeon/dungeon.h"

void init_ncurses_rendering();
void clear_console();

void render_entity(Entity* entity);
void render_dungeon(Dungeon* dungeon);

#endif