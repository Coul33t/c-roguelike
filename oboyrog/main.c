#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "input_handler.h"
#include "renderer.h"
#include "fov.h"


int main(void) {

    init_ncurses_rendering();

    char input = ',';

    Entity* player = get_player(5, 10, "Prout");
    Dungeon* dungeon = create_wall_dungeon();
    //draw_debug_grid(dungeon, 5);
    draw_room(dungeon, 5, 10, 30, 5);
    draw_room(dungeon, 50, 15, 5, 3);

    draw_h_corridor(dungeon, 10, 2, 40, 1);
    draw_h_corridor(dungeon, 10, 15, 40, 1);

    make_fov(player, dungeon);
    clear_console();

    render_dungeon(dungeon);
    render_entity(player);

    while (input != 'a') {

        // Get inputted char with needing to validate with ENTER
        input = getch();

        // Copy void character to the whole console
        clear_console();
        // Handle user input
        handle_input(input, player, dungeon);

        clear_fov(player, dungeon);
        make_fov(player, dungeon);

        render_dungeon(dungeon);
        render_entity(player);

        count_seen_and_visible(dungeon);

        mvaddch(1, 1, input);
    }

    close_ncurses_rendering();

    return 0;
}