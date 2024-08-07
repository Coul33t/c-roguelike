#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <stdbool.h>

#include "../dungeon/dungeon.h"
#include "../fov.h"
#include "../entity.h"

#include "../comp/position.h"

#include "../messages/messages_manager.h"
#include "../targeting_list.h"
#include "../common.h"

void handle_input(int input, Entity* player, Dungeon* dungeon, FOVMap* fov_map, Entity* monsters[], TargetingList* targeting_list,
                  MessagesList* msg_lst, GameState* game_state);

void handle_game_input(int input, Entity* player, Dungeon* dungeon, FOVMap* fov_map, Entity* monsters[], TargetingList* targeting_list,
                       MessagesList* msg_lst, GameState* game_state);

void handle_targeting_input(int input, Entity* player, Dungeon* dungeon, FOVMap* fov_map, Entity* monsters[], TargetingList* targeting_list,
                            MessagesList* msg_lst, GameState* game_state);

void move_if_valid(Entity* entity, DIRECTION dir, Dungeon* dungeon, Entity* monsters[], MessagesList* msg_lst);

#endif