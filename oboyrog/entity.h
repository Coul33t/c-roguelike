#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "include_curses.h"

#include "comp/position.h"
#include "comp/stats.h"

#include "constants.h"

typedef struct Entity {
    Position pos;
    Position last_seen;
    char chr;
    char dead_chr;
    char name[30];
    int colour;
    int dead_colour;
    int fov_radius;
    Stats stats;
    bool is_dead;
    bool seen_once;
} Entity;

Entity* get_player(int x, int y, char* name);

Entity* get_monster(int x, int y, char* name, char chr, char dead_chr, Stats* stats, int fov_radius, int colour, int dead_colour);
Entity* get_imp(int x, int y);

void destroy_entity(Entity* entity);

bool check_if_tile_has_monster(Entity* monsters[], DIRECTION dir, int x, int y, bool must_be_alive);
Entity* get_monster_at_tile(Entity* monsters[], DIRECTION dir, int x, int y);

void take_damage(Entity* self, int val);
void attack(Entity* self, Entity* target);
void move_entity(Entity* self, DIRECTION direction);

#endif