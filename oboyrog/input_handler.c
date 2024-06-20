#include "input_handler.h"

void handle_input(char input, Entity* player) {
    if (input == 'z') {
        move_entity(player, NORTH);
    }

    else if (input == 's') {
        move_entity(player, SOUTH);
    }

    else if (input == 'd') {
        move_entity(player, EAST);
    }

    else if (input == 'q') {
        move_entity(player, WEST);
    }
}