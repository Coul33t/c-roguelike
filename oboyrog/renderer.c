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
    mvaddch(entity->pos.y, entity->pos.x, entity->chr);
}

void render_dungeon(Dungeon* dungeon) {
    for (int x = 0; x < DUNGEON_SIZE_X; x++) {
        for (int y = 0; y < DUNGEON_SIZE_Y; y++) {
            mvaddch(x, y, dungeon->map[(x * DUNGEON_SIZE_Y) + y]->chr);
        }
    }
}