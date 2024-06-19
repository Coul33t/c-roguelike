#include <ncurses.h>
#include "entity.h"
#include "input_handler.h"
#include "renderer.h"

int main(void) {

    init_ncurses_rendering();

    char input;

    Entity player = {{10, 20}, '@', 15};

    while (input != 'a') {
        // Get inputted char with needing to validate with ENTER
        input = getch();

        // Handle user input
        handle_input(input, &player);

        // Copy void character to the whole console
        clear_console();

        // Display player
        render_entity(&player);
    }


    endwin();

    return 0;
}