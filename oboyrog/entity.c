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
    player->stats.hp.val = 100;
    player->stats.hp.max = 100;
    player->stats.dmg = 3;
    player->stats.def = 2;
    player->stats.stamina.val = 100;
    player->stats.stamina.max = 100;
    player->stats.xp = 0;
    player->stats.xp_value = 0;
    // -----

    player->colour = COLOR_PAIR(VISIBLE_COLOURS);
    player->dead_colour = COLOR_PAIR(RED_FG_COLOUR);

    player->seen_once = true;

    return player;
}

Entity* get_monster(int x, int y, char* name, char chr, char dead_chr, Stats* stats, int fov_radius, 
                    int colour, int dead_colour) {
    
    Entity* monster = calloc(1, sizeof(Entity));
    
    monster->pos.x = x;
    monster->pos.y = y;
    strcpy(monster->name, name);

    monster->chr = chr;
    monster->dead_chr = dead_chr;

    monster->fov_radius = fov_radius;

    monster->colour = colour;
    monster->dead_colour = dead_colour;

    monster->stats.hp.val = stats->hp.val;
    monster->stats.hp.max = stats->hp.max;
    monster->stats.dmg = stats->dmg;
    monster->stats.def = stats->def;
    monster->stats.stamina.val = stats->stamina.val;
    monster->stats.stamina.max = stats->stamina.max;
    monster->stats.xp_value = stats->xp_value;

    monster->seen_once = false;

    return monster;
}

Entity* get_imp(int x, int y) {
    Stats stats;
    stats.hp.val = 5;
    stats.hp.max = 5;
    stats.dmg = 1;
    stats.def = 0;
    stats.stamina.val = 10;
    stats.stamina.max = 10;
    stats.xp_value = 5;

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

bool take_damage(Entity* self, int val) {
    int final_damage = val - self->stats.def;
    
    if (final_damage > 0) {
        self->stats.hp.val -= val;
        if (self->stats.hp.val <= 0) {
            self->is_dead = true;
            return true;
        }
    }

    return false;
}

void attack(Entity* self, Entity* target, MessagesList* msg_lst) {
    bool result = take_damage(target, self->stats.dmg);

    self->target = target;

    if (result) {
        self->stats.xp += target->stats.xp_value;
        // +1 probably for the termination char? Idk
        int buffer_size = 13 + get_str_size(target->name) + 1;
        char str_buffer[buffer_size];
        snprintf(str_buffer, buffer_size, "You kill the %s", target->name);
        add_msg(msg_lst, str_buffer);
    }

    else {
        // +1 probably for the termination char? Idk
        int buffer_size = 15 + get_str_size(target->name) + 1;
        char str_buffer[buffer_size];
        snprintf(str_buffer, buffer_size, "You attack the %s", target->name);
        add_msg(msg_lst, str_buffer);
    }
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

float get_distance_from_entities(Entity* e1, Entity* e2) {
    return get_distance_from_pos(e1->pos, e2->pos);
}

void sort_entities_array_by_dst(Entity* array[], Entity* player) {
    int current_smallest_idx;
    float current_smallest_dst;
    float dst;

    // For each monster, we check if it's the closest to the player
    // If not, we swap it with the closest one
    // - 1 because we compare it with the next value
    for (int i = 0; i < NB_MAX_MONSTERS - 1; i++) {
        if (array[i] == NULL) {
            return;
        }

        current_smallest_idx = i;
        current_smallest_dst = get_distance_from_entities(player, array[i]);

        // For each monster after the current one, check if there's a closer one
        // if there's a closer one, mark it as the new closest one
        for (int j = i + 1; j < NB_MAX_MONSTERS; j++) {
            // We've reach the last monster of the list, so everything before is ordered
            if (array[j] == NULL) {
                return;
            }

            dst = get_distance_from_entities(player, array[j]);
            if (dst < current_smallest_dst) {
                current_smallest_dst = dst;
                current_smallest_idx = j;
            }
        }

        // Once every monster has been processed, we're assured to have the smallest monster idx
        // Swap if it's not the current monster
        if (current_smallest_idx != i) {
            swap_entities_by_idx(array, i, current_smallest_idx);
        }
    }
}

void swap_entities(Entity* ent_1, Entity* ent_2) {
    Entity tmp = *ent_1;
    *ent_1 = *ent_2;
    *ent_2 = tmp;
}

void swap_entities_by_idx(Entity* a[], int idx_1, int idx_2) {
    Entity* temp = a[idx_1];
    a[idx_1] = a[idx_2];
    a[idx_2] = temp;
}
