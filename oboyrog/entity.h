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
    char chr;
    char name[30];
    int colour;
    int fov_radius;
    Stats stats;
    bool is_dead;
} Entity;

Entity* get_player(int x, int y, char* name);
void take_damage(Entity* self, int val);
void attack(Entity* self, Entity* target);
void move_entity(Entity* self, DIRECTION direction);

#endif