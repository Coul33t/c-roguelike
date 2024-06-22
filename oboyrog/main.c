#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "input_handler.h"
#include "renderer.h"


int main(void) {

    init_ncurses_rendering();

    char input = ',';

    Entity player = {{20, 10}, '@', 15};
    Dungeon* dungeon = create_empty_dungeon();
    //draw_debug_grid(dungeon, 5);
    draw_room(dungeon, 20, 10, 20, 10);
    draw_room(dungeon, 50, 15, 5, 3);

    draw_h_corridor(dungeon, 20, 13, 30, 1);

    while (input != 'a') {

        // Get inputted char with needing to validate with ENTER
        input = getch();

        // Copy void character to the whole console
        clear_console();
        // Handle user input
        handle_input(input, &player, dungeon);

        render_dungeon(dungeon);
        render_entity(&player);

        mvaddch(1, 1, input);
    }

    close_ncurses_rendering();

    return 0;
}