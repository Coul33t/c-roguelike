#include "input_handler.h"

void handle_input(char input, Entity* player, Dungeon* dungeon, Entity* monsters[], 
                  MessagesList* msg_lst, GameState* game_state) {
    switch (*game_state) {
        case GAME: handle_game_input(input, player, dungeon, monsters, msg_lst, game_state); break;
        default: break;
    }
}

void handle_game_input(char input, Entity* player, Dungeon* dungeon, Entity* monsters[],
                       MessagesList* msg_lst, GameState* game_state) {
    if (input == 'z') {
        move_if_valid(player, NORTH, dungeon, monsters, msg_lst);
    }

    else if (input == 's') {
        move_if_valid(player, SOUTH, dungeon, monsters, msg_lst);
    }

    else if (input == 'd') {
        move_if_valid(player, EAST, dungeon, monsters, msg_lst);
    }

    else if (input == 'q') {
        move_if_valid(player, WEST, dungeon, monsters, msg_lst);
    }

    else if (input == 'i') {
        *game_state = INVENTORY;
    }
}

void move_if_valid(Entity* entity, DIRECTION dir, Dungeon* dungeon, Entity* monsters[], MessagesList* msg_lst) {
    if (get_dungeon_tile_from_dir(dungeon, dir, entity->pos.x, entity->pos.y)->walkable) {
        // No monster on the tile (dead or alive)
        if (!check_if_tile_has_monster(monsters, dir, entity->pos.x, entity->pos.y, true)) {
            move_entity(entity, dir);
            add_msg(msg_lst, "You move");
        }

        // If there's a monster alive, we attack it
        else if (check_if_tile_has_monster(monsters, dir, entity->pos.x, entity->pos.y, true)) {
            attack(entity, get_monster_at_tile(monsters, dir, entity->pos.x, entity->pos.y), msg_lst);
        }
        
    }
}