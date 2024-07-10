#include "include_curses.h"

void put_char(int x, int y, char chr) {
    mvaddch(y, x, chr);
}

void move_cursor(int x, int y) {
    move(y, x);
}