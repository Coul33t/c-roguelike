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

        init_pair(DEFAULT_COLOURS, COLOR_WHITE, COLOR_BLACK);
        init_pair(VISIBLE_COLOURS, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOURS, COLOR_BLUE, COLOR_BLACK);

        init_pair(RED_FG_COLOUR, COLOR_RED, COLOR_BLACK);
        init_pair(RED_BG_COLOUR, COLOR_BLACK, COLOR_RED);

        init_pair(YELLOW_FG_COLOUR, COLOR_YELLOW, COLOR_BLACK);
        init_pair(YELLOW_BG_COLOUR, COLOR_BLACK, COLOR_YELLOW);
    }

    else {
        addstr("WARNING! Your console does not support colours.");
        getch();
        // TODO: print message
    }
}

void clear_console() {
    clear();
}

void close_ncurses_rendering() {
    endwin();
}

void render_entity(Entity* entity, FOVMap* fov_map) {
    if (!is_visible(entity, fov_map)) {
        if (entity->seen_once) {
            attron(COLOR_PAIR(SEEN_COLOURS));
            if (!entity->is_dead) {
                put_char(entity->last_seen.x, entity->last_seen.y, entity->chr);
            }

            else {
                put_char(entity->last_seen.x, entity->last_seen.y, entity->dead_chr);
            }
        }
    }
        

    else {
        entity->seen_once = true;
        entity->last_seen.x = entity->pos.x;
        entity->last_seen.y = entity->pos.y;

        if (!entity->is_dead) {
            attron(entity->colour);
            put_char(entity->pos.x, entity->pos.y, entity->chr);
        }

        else {
            attron(entity->dead_colour);
            put_char(entity->pos.x, entity->pos.y, entity->dead_chr);
        }
    } 
    
    attron(COLOR_PAIR(DEFAULT_COLOURS));
}

void render_monsters(Entity* monsters[], FOVMap* fov_map) {
    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        if (!monsters[i]) {
            return;
        }

        else {
            render_entity(monsters[i], fov_map);
        }
    }
}

void render_dungeon(Dungeon* dungeon, FOVMap* fov_map) {
    for (int x = 0; x < DUNGEON_SIZE_X; x++) {
        for (int y = 0; y < DUNGEON_SIZE_Y; y++) {
            // Everything that is visible has been seen
            if (fov_map->seen_map[get_1d_from_2d_dungeon(x, y)]) {
                if (fov_map->visible_map[get_1d_from_2d_dungeon(x, y)]) {
                    attron(COLOR_PAIR(VISIBLE_COLOURS));
                }

                else {
                    attron(COLOR_PAIR(SEEN_COLOURS));
                }

                put_char(x, y, dungeon->map[get_1d_idx_from_2d_coord(x, y, DUNGEON_SIZE_Y)]->chr);
                
            }

            else {
                put_char(x, y, ' ');
            }           
        }
    }

    attron(COLOR_PAIR(DEFAULT_COLOURS));
}