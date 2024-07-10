#ifdef _WIN32
    #include "../extlib/pdcurses/include/curses.h"
#endif

#ifdef __unix__
    #include <ncurses.h>
#endif

void put_char(int x, int y, char chr);
void move_cursor(int x, int y);