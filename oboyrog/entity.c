#include "entity.h"

void take_damage(Entity* self, int val) {
        self->stats.hp -= val;
        if (self->stats.hp <= 0) {
            self->is_dead = true;
        }
}

void attack(Entity* self, Entity* target) {
    take_damage(target, self->stats.dmg);
}

void move_entity(Entity* self, DIRECTION direction) {
    switch (direction) {
        case NORTH: self->pos.y--; break;
        case  EAST: self->pos.x++; break;
        case SOUTH: self->pos.y++; break;
        case  WEST: self->pos.x--; break;
        default: break;
    }
}