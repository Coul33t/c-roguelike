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
    erase();
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

void render_stats_panel(Entity* player, Entity* target) {
    /*for (int x = STATS_PANEL_X; x < STATS_PANEL_X + STATS_PANEL_W; x++) {
        for (int y = STATS_PANEL_Y; y < STATS_PANEL_Y  + STATS_PANEL_H; y++) {
            put_char(x, y, 'X');
        }
    }*/

    for (int y = STATS_PANEL_Y; y < STATS_PANEL_Y  + STATS_PANEL_H; y++) {
        put_char(STATS_PANEL_X, y, '|');
    }

    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 1);
    printw("%s", player->name);
    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 2);
    printw(" HP: %i / %i", player->stats.hp, player->stats.hp_max);

    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 3);
    printw("STM: %i / %i", player->stats.stamina, player->stats.stamina_max);

    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 4);
    printw("DMG: %i", player->stats.dmg);

    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 5);
    printw("DEF: %i", player->stats.def);

    move_cursor(STATS_PANEL_X + 2, STATS_PANEL_Y + 6);
    printw(" XP: %i", player->stats.xp);

    if (target) {
        // Display info about target
    }
}

void draw_line(Entity* src, Entity* target) {
    Position current_pos = src->pos;
    int tmp_x;
    float coef = fabs((float)(target->pos.x - src->pos.x)  / (float)(abs(target->pos.y - src->pos.y) + 1));
    int nb = 0;

    while (current_pos.x != target->pos.x) {
        tmp_x = target->pos.x - current_pos.x;

        // normalise and keep the sign
        if (coef != 0 && nb > coef) {
            current_pos.y += (target->pos.y - current_pos.y) / abs(target->pos.y - current_pos.y);
            nb = 0;
        } 
        
        current_pos.x += tmp_x / abs(tmp_x);

        put_char(current_pos.x, current_pos.y, 'X');
        ++nb;
    }
}

int display_message(Message* message, int x, int y) {
    int nb_lines = 1;
    int current_x = x;
    int current_y = MESSAGE_BOX_Y + y;

    char current_chr = message->msg[0];
    int current_msg_idx = 0;

    while (current_msg_idx < message->size && current_y < MESSAGE_BOX_Y + MESSAGE_BOX_H) {
        if (current_x == MESSAGE_BOX_X + MESSAGE_BOX_W) {
            ++current_y;
            current_x = x;
            ++nb_lines;
        }

        current_chr = message->msg[current_msg_idx];

        put_char(current_x, current_y, current_chr);

        ++current_x;
        ++current_msg_idx;
    }

    return nb_lines;
}

void display_messages(MessagesList* msg_lst) {

    if (msg_lst->nb_msgs == 0) {
        return;
    }

    // TODO: bug, display only one message
    int nb_lines_written = 0;
    int idx = msg_lst->idx;

    do {
        nb_lines_written += display_message(msg_lst->msgs[idx], 0, nb_lines_written);
      
        --idx;

        if (idx < 0) {
            if (msg_lst->is_full) {
                idx = msg_lst->nb_msgs - 1;
            }

            else {
                return;
            }            
        }

    } while(nb_lines_written < MESSAGE_BOX_H);
}