#include "renderer.h"

void init_ncurses_rendering() {
    // Starts ncurse
    initscr();

    // Prevent from immediately drawing on screen
    noecho();

    // Invisible cursor
    curs_set(0);
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