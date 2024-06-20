#include "dungeon.h"

void draw_h_line(Dungeon* dungeon, int x, int y, int w) {
    for (int i = x; i < x + w; i++) {
        dungeon->map[get_1d_idx_from_2d_coord(i, y, DUNGEON_SIZE_Y)] = get_wall();
    }
}

void draw_v_line(Dungeon* dungeon, int x, int y, int h) {
    for (int i = y; i < y + h; i++) {
        dungeon->map[get_1d_idx_from_2d_coord(x, i, DUNGEON_SIZE_Y)] = get_wall();
    }
}

void draw_room(Dungeon* dungeon, int x, int y, int w, int h) {
    draw_h_line(dungeon, x - 1    , y - 1    , w + 3);
    draw_h_line(dungeon, x - 1    , y + h + 1, w + 3);
    draw_v_line(dungeon, x - 1    , y - 1    , h + 3);
    draw_v_line(dungeon, x + w + 1, y - 1    , h + 3);
}

void draw_debug_grid(Dungeon* dungeon, int gap) {
    for (int i = 0; i < DUNGEON_SIZE_Y; i += gap) {
        for (int j = 0; j < DUNGEON_SIZE_Y; j+= gap) {
            dungeon->map[get_1d_idx_from_2d_coord(i, j, DUNGEON_SIZE_Y)] = get_debug();
        }
    }
}

Dungeon* create_empty_dungeon() {
    Dungeon* dungeon = calloc(sizeof(Dungeon), 1);

    for (int i = 0; i < DUNGEON_SIZE_X * DUNGEON_SIZE_Y; i++) {
        dungeon->map[i] = get_void();
    }

    return dungeon;
}

Dungeon* create_basic_dungeon() {
    Dungeon* dungeon = calloc(sizeof(Dungeon), 1);

    for (int i = 0; i < DUNGEON_SIZE_X * DUNGEON_SIZE_Y; i++) {
        dungeon->map[i] = get_void();
    }

    // horitzontal walls
    for (int i = 0; i < 20; i++) {
        dungeon->map[get_1d_idx_from_2d_coord(20, 10 + i, DUNGEON_SIZE_Y)] = get_wall();
        dungeon->map[get_1d_idx_from_2d_coord(10, 10 + i, DUNGEON_SIZE_Y)] = get_wall();
    }

    // vertical walls
    for (int i = 0; i < 10; i++) {
        dungeon->map[get_1d_idx_from_2d_coord(10 + i, 10, DUNGEON_SIZE_Y)] = get_wall();
        dungeon->map[get_1d_idx_from_2d_coord(10 + i, 30, DUNGEON_SIZE_Y)] = get_wall();
    }

    return dungeon;
}

void draw_test_lines(Dungeon* dungeon) {
    draw_h_line(dungeon, 0, 10, 20);
    draw_h_line(dungeon, 0, 15, 25);
    draw_h_line(dungeon, 0, 20, 30);
    draw_v_line(dungeon, 50, 0, 10);
    draw_v_line(dungeon, 52, 0, 15);
    draw_v_line(dungeon, 54, 0, 20);
}
