#include "include_curses.h"
#include "entity.h"
#include "dungeon/dungeon.h"
#include "input_handler/input_handler.h"
#include "renderer.h"
#include "fov.h"
#include "common.h"
#include "messages/messages_manager.h"

int main(void) {

    init_ncurses_rendering();

    int input = ',';

    Entity* player = get_player(5, 10, "Prout");
    Dungeon* dungeon = create_wall_dungeon();

    // Array that stores all monsters
    Entity* monsters[NB_MAX_MONSTERS];

    // Init everything to NULL (is that useful?)
    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        monsters[i] = NULL;
    }

    // Array that stores all valid targets (can't be bigger than NB_MAX_MONSTERS)
    Entity* targeting_list[NB_MAX_MONSTERS];

    GameState game_state = MENU;
    
    

    monsters[0] = get_imp(6, 11);
    monsters[1] = get_imp(51, 16);

    //draw_debug_grid(dungeon, 5);
    draw_room(dungeon, 5, 10, 30, 5);
    draw_room(dungeon, 50, 15, 5, 3);

    draw_h_corridor(dungeon, 10, 2, 40);
    draw_h_corridor(dungeon, 10, 15, 40);

    FOVMap* fov_map = calloc(1, sizeof(FOVMap));

    make_fov(player, dungeon, fov_map);
    clear_console();

    render_dungeon(dungeon, fov_map);
    render_monsters(monsters, fov_map);
    render_entity(player, fov_map);

    MessagesList* msg_lst = get_msgs_lst();

    game_state = GAME;

    while (input != 'a') {

        // Get inputted char with needing to validate with ENTER
        input = getch();

        // Copy void character to the whole console
        clear_console();

        // Handle user input
        handle_input(input, player, dungeon, fov_map, monsters, targeting_list, msg_lst, &game_state);

        clear_fov(dungeon, fov_map);
        make_fov(player, dungeon, fov_map);

        render_dungeon(dungeon, fov_map);
        render_monsters(monsters, fov_map);
        render_entity(player, fov_map);
        render_stats_panel(player, NULL);

        display_messages(msg_lst);

        count_seen_and_visible(dungeon);

        mvaddch(1, 1, input);
    }

    close_ncurses_rendering();

    return 0;
}
