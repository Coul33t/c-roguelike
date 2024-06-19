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

void render_entity(Entity* entity) {
    mvaddch(entity->pos.y, entity->pos.x, entity->chr);
}

void render_dungeon(Dungeon* dungeon) {

}