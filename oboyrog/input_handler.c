#include "input_handler.h"

void handle_input(char input, struct Entity* player) {
    if (input == 'z') {
        player->pos.y -= 1;
    }

    else if (input == 's') {
        player->pos.y += 1;
    }

    else if (input == 'd') {
        player->pos.x += 1;
    }

    else if (input == 'q') {
        player->pos.x -= 1;
    }
}