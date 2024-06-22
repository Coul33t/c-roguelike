#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <stdbool.h>

#include "dungeon/dungeon.h"
#include "entity.h"

#include "comp/position.h"

void handle_input(char input, Entity* player, Dungeon* dungeon);

void move_if_valid(Entity* entity, DIRECTION dir, Dungeon* dungeon);

#endif