#include "entity.h"

Entity* get_player(int x, int y, char* name) {
    Entity* player = calloc(1, sizeof(Entity));
    player->pos.x = x;
    player->pos.y = y;
    player->chr = '@';
    player->fov_radius = 10;
    strcpy(player->name, name);
    player->colour = COLOR_PAIR(VISIBLE_COLOURS);

    return player;
}

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