#include "input_handler.h"

void handle_input(int input, Entity* player, Dungeon* dungeon, FOVMap* fov_map, Entity* monsters[], TargetingList* targeting_list, 
                  MessagesList* msg_lst, GameState* game_state) {
    switch (*game_state) {
        case GAME: 
            handle_game_input(input, player, dungeon, monsters, msg_lst, game_state); 
            break;

        case TARGETING:
            if (!targeting_list->is_ordered) {
                get_visible_entities(targeting_list, monsters, fov_map);
                sort_entities_array_by_dst(targeting_list->lst, player);
                targeting_list->is_ordered = true;
            }

            handle_targeting_input(input, player, dungeon, fov_map, monsters, targeting_list, msg_lst, game_state); 
            break;

        default: break;
    }
}

void handle_game_input(int input, Entity* player, Dungeon* dungeon, Entity* monsters[],
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

    else if (input == 'f') {
        *game_state = TARGETING;
    }
}

void handle_targeting_input(int input, Entity* player, Dungeon* dungeon, FOVMap* fov_map, Entity* monsters[], TargetingList* targeting_list,
                            MessagesList* msg_lst, GameState* game_state) {
    if (input == 'c') {
        targeting_list->is_ordered = false;
        *game_state = GAME;
    }

    if (input == KEY_STAB) {
        next_target(targeting_list);
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