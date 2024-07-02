#include "entity.h"

Entity* get_player(int x, int y, char* name) {
    Entity* player = calloc(1, sizeof(Entity));
    player->pos.x = x;
    player->pos.y = y;
    player->chr = '@';
    player->dead_chr = 'X';
    player->fov_radius = 10;
    strcpy(player->name, name);

    // Stats
    player->stats.hp = 100;
    player->stats.dmg = 3;
    player->stats.def = 2;
    player->stats.stamina = 100;
    // -----

    player->colour = COLOR_PAIR(VISIBLE_COLOURS);
    player->dead_colour = COLOR_PAIR(RED_FG_COLOUR);

    player->seen_once = true;

    return player;
}

Entity* get_monster(int x, int y, char* name, char chr, char dead_chr, Stats* stats, int fov_radius, int colour, int dead_colour) {
    Entity* monster = calloc(1, sizeof(Entity));
    monster->pos.x = x;
    monster->pos.y = y;
    strcpy(monster->name, name);
    monster->chr = chr;
    monster->dead_chr = dead_chr;

    monster->fov_radius = fov_radius;

    monster->colour = colour;
    monster->dead_colour = dead_colour;

    monster->stats.hp = stats->hp;
    monster->stats.dmg = stats->dmg;
    monster->stats.def = stats->def;
    monster->stats.stamina = stats->stamina;

    monster->seen_once = false;

    return monster;
}

Entity* get_imp(int x, int y) {
    Stats stats;
    stats.hp = 5;
    stats.dmg = 1;
    stats.def = 0;
    stats.stamina = 10;

    return get_monster(x, y, "Imp", 'i', '%', &stats, BASE_FOV, COLOR_PAIR(YELLOW_FG_COLOUR), COLOR_PAIR(RED_FG_COLOUR));
}

void destroy_entity(Entity* entity) {
    free(entity);
}

bool check_if_tile_has_monster(Entity* monsters[], DIRECTION dir, int x, int y, bool must_be_alive) {
    int new_x = x;
    int new_y = y;

    switch (dir) {
        case NORTH: new_y--; break;
        case SOUTH: new_y++; break;
        case EAST : new_x++; break;
        case WEST : new_x--; break;
        default: break;
    }

    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        // If the pointer is NULL, there's no more monsters
        if (!monsters[i]) {
            return false;
        }

        // We found a monster at the desired coordinates
        if (monsters[i]->pos.x == new_x && monsters[i]->pos.y == new_y) {

            // If the monster must be alive, we check that it is actually alive
            // Or if we don't care about the state of the monster, we return true
            if ((must_be_alive && !monsters[i]->is_dead) || !must_be_alive) {
                return true;
            }

            // Else, we return false
            return false;
        }
    }

    return false;
}

Entity* get_monster_at_tile(Entity* monsters[], DIRECTION dir, int x, int y) {
    int new_x = x;
    int new_y = y;

    switch (dir) {
        case NORTH: new_y--; break;
        case SOUTH: new_y++; break;
        case EAST : new_x++; break;
        case WEST : new_x--; break;
        default: break;
    }

    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        if (monsters[i]->pos.x == new_x && monsters[i]->pos.y == new_y) {
            return monsters[i];
        }
    }

    return NULL;
}

void take_damage(Entity* self, int val) {
    int final_damage = val - self->stats.def;
    
    if (final_damage > 0) {
        self->stats.hp -= val;
        if (self->stats.hp <= 0) {
            self->is_dead = true;
        }
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