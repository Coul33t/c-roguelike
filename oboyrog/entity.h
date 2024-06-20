#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdbool.h>

#include "comp/position.h"
#include "comp/stats.h"

typedef struct Entity {
    struct Position pos;
    char chr;
    char name[30];
    int fov_radius;
    Stats stats;
    bool is_dead;
} Entity;

void take_damage(Entity* self, int val);
void attack(Entity* self, Entity* target);
void move_entity(Entity* self, DIRECTION direction);

#endif