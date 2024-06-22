#include "input_handler.h"

void handle_input(char input, Entity* player, Dungeon* dungeon) {
    if (input == 'z') {
        move_if_valid(player, NORTH, dungeon);
    }

    else if (input == 's') {
        move_if_valid(player, SOUTH, dungeon);
    }

    else if (input == 'd') {
        move_if_valid(player, EAST, dungeon);
    }

    else if (input == 'q') {
        move_if_valid(player, WEST, dungeon);
    }
}

void move_if_valid(Entity* entity, DIRECTION dir, Dungeon* dungeon) {
    if (get_dungeon_tile_from_dir(dungeon, dir, entity->pos.x, entity->pos.y)->walkable) {
        move_entity(entity, dir);
    }
}