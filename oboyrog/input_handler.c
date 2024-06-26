#include "input_handler.h"

void handle_input(char input, Entity* player, Dungeon* dungeon, Entity* monsters[]) {
    if (input == 'z') {
        move_if_valid(player, NORTH, dungeon, monsters);
    }

    else if (input == 's') {
        move_if_valid(player, SOUTH, dungeon, monsters);
    }

    else if (input == 'd') {
        move_if_valid(player, EAST, dungeon, monsters);
    }

    else if (input == 'q') {
        move_if_valid(player, WEST, dungeon, monsters);
    }
}

void move_if_valid(Entity* entity, DIRECTION dir, Dungeon* dungeon, Entity* monsters[]) {
    if (get_dungeon_tile_from_dir(dungeon, dir, entity->pos.x, entity->pos.y)->walkable) {
        // No monster on the tile (dead or alive)
        if (!check_if_tile_has_monster(monsters, dir, entity->pos.x, entity->pos.y, true)) {
            move_entity(entity, dir);
        }

        // If there's a monster alive, we attack it
        else if (check_if_tile_has_monster(monsters, dir, entity->pos.x, entity->pos.y, true)) {
            attack(entity, get_monster_at_tile(monsters, dir, entity->pos.x, entity->pos.y));
        }
        
    }
}