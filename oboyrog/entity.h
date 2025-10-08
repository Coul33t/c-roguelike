#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "include_curses.h"

#include "comp/position.h"
#include "comp/stats.h"

#include "messages/messages_manager.h"

#include "constants.h"

#include "tools/tools.h"

typedef struct Entity {
    Position pos;
    Position last_seen;

    char chr;
    char dead_chr;
    char name[30];
    int colour;
    int dead_colour;

    int fov_radius;
    bool seen_once;

    Stats stats;
    bool is_dead;

    struct Entity* target;
} Entity;

Entity* get_player(int x, int y, char* name);

Entity* get_monster(int x, int y, char* name, char chr, char dead_chr, Stats* stats, int fov_radius,
                    int colour, int dead_colour);
Entity* get_imp(int x, int y);

void destroy_entity(Entity* entity);

bool check_if_tile_has_monster(Entity* monsters[], DIRECTION dir, int x, int y, bool must_be_alive);
Entity* get_monster_at_tile(Entity* monsters[], DIRECTION dir, int x, int y);

bool take_damage(Entity* self, int val);
// Returns true if target is dead
void attack(Entity* self, Entity* target, MessagesList* msg_lst);
void move_entity(Entity* self, DIRECTION direction);


float get_distance_from_entities(Entity* e1, Entity* e2);
void sort_entities_array_by_dst(Entity* array[], Entity* player);

void swap_entities(Entity* ent_1, Entity* ent_2);
void swap_entities_by_idx(Entity* a[], int idx_1, int idx_2);

#endif
