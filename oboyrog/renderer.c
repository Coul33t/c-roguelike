#include "renderer.h"

void init_ncurses_rendering() {
    // Starts ncurse
    initscr();

    // Prevent from immediately drawing on screen
    noecho();

    // Invisible cursor
    curs_set(0);

    if (has_colors()) {
        start_color();

        init_pair(VISIBLE_COLOURS, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOURS, COLOR_BLUE, COLOR_BLACK);
    }

    else {
        // TODO: print message
    }
}

void clear_console() {
    clear();
}

void close_ncurses_rendering() {
    endwin();
}

void render_entity(Entity* entity) {
    put_char(entity->pos.x, entity->pos.y, entity->chr);
}

void render_dungeon(Dungeon* dungeon) {
    for (int x = 0; x < DUNGEON_SIZE_X; x++) {
        for (int y = 0; y < DUNGEON_SIZE_Y; y++) {
            put_char(x, y, dungeon->map[get_1d_idx_from_2d_coord(x, y, DUNGEON_SIZE_Y)]->chr);
        }
    }
}