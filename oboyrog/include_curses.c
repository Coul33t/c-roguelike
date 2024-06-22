#include "include_curses.h"

void put_char(int x, int y, char chr) {
    mvaddch(y, x, chr);
}