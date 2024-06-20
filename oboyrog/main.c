#include "include_ncurses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "input_handler.h"
#include "renderer.h"


int main(void) {

    init_ncurses_rendering();

    char input = ',';

    Entity player = {{10, 20}, '@', 15};
    Dungeon* dungeon = create_empty_dungeon();
    //draw_debug_grid(dungeon, 5);
    draw_room(dungeon, 10, 10, 20, 10);



    while (input != 'a') {
        // Get inputted char with needing to validate with ENTER
        input = getch();

        // Handle user input
        handle_input(input, &player);

        mvaddch(10, 10, input);

        // Copy void character to the whole console
        clear_console();

        render_dungeon(dungeon);
        // Display player
        render_entity(&player);
    }

    close_ncurses_rendering();

    return 0;
}