#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "fov.h"
#include "messages/messages_manager.h"
#include "constants.h"

void init_ncurses_rendering();
void clear_console();
void close_ncurses_rendering();

void render_entity(Entity* entity, FOVMap* fov_map);
void render_monsters(Entity* monsters[], FOVMap* fov_map);
void render_dungeon(Dungeon* dungeon, FOVMap* fov_map);
void render_stats_panel(Entity* player, Entity* target);

void draw_line(Entity* src, Entity* target);

// return the number of lines it took to display the message
int display_message(Message* message, int x, int y);
void display_messages(MessagesList* msg_lst);


#endif