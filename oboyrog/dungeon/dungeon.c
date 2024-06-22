#include "dungeon.h"

void draw_h_line(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int w, bool link_rooms) {
    for (int i = x; i < x + w; i++) {
        if (!link_rooms) {
            dungeon->map[get_1d_idx_from_2d_coord(i, y, DUNGEON_SIZE_Y)] = get_tile(tile_type);
        }

        else {
            // TODO: not working as intended
            if (tile_type == FLOOR ||
                (tile_type == WALL && dungeon->map[get_1d_idx_from_2d_coord(i, y, DUNGEON_SIZE_Y)]->type != FLOOR)) {
                dungeon->map[get_1d_idx_from_2d_coord(i, y, DUNGEON_SIZE_Y)] = get_tile(tile_type);
            }
        }
    }
}

void draw_v_line(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int h, bool link_rooms) {
    for (int i = y; i < y + h; i++) {
        if (!link_rooms) {
            dungeon->map[get_1d_idx_from_2d_coord(x, i, DUNGEON_SIZE_Y)] = get_tile(tile_type);
        }

        else {
            // TODO: not working as intended
            if (tile_type == FLOOR ||
                (tile_type == WALL && dungeon->map[get_1d_idx_from_2d_coord(x, i, DUNGEON_SIZE_Y)]->type != FLOOR)) {
                dungeon->map[get_1d_idx_from_2d_coord(x, i, DUNGEON_SIZE_Y)] = get_tile(tile_type);
            }
        }
    }
}

void draw_rectangle(Dungeon* dungeon, TILE_TYPE tile_type, int x, int y, int w, int h) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            dungeon->map[get_1d_idx_from_2d_coord(j, i, DUNGEON_SIZE_Y)] = get_tile(tile_type);
        }
    }
}

void draw_room(Dungeon* dungeon, int x, int y, int w, int h) {
    draw_h_line(dungeon, WALL, x - 1    , y - 1, w + 3, false);
    draw_h_line(dungeon, WALL, x - 1    , y + h, w + 3, false);
    draw_v_line(dungeon, WALL, x - 1    , y - 1, h + 2, false);
    draw_v_line(dungeon, WALL, x + w + 1, y - 1, h + 2, false);

    draw_rectangle(dungeon, FLOOR, x, y, w, h);
}

void draw_h_corridor(Dungeon* dungeon, int x, int y, int w, int wideness) {
    draw_h_line(dungeon,  WALL, x, y - 1, w, true);
    draw_h_line(dungeon, FLOOR, x, y    , w, true);
    draw_h_line(dungeon,  WALL, x, y + 1, w, true);
}

void draw_v_corridor(Dungeon* dungeon, int x, int y, int h, int wideness) {
    draw_v_line(dungeon,  WALL, x - 1, y, h, true);
    draw_v_line(dungeon, FLOOR, x    , y, h, true);
    draw_v_line(dungeon,  WALL, x + 1, y, h, true);
}


void draw_debug_grid(Dungeon* dungeon, int gap) {
    for (int i = 0; i < DUNGEON_SIZE_Y; i += gap) {
        for (int j = 0; j < DUNGEON_SIZE_Y; j+= gap) {
            dungeon->map[get_1d_idx_from_2d_coord(i, j, DUNGEON_SIZE_Y)] = get_debug();
        }
    }
}

Dungeon* create_empty_dungeon() {
    Dungeon* dungeon = calloc(1, sizeof(Dungeon));

    for (int i = 0; i < DUNGEON_SIZE_X * DUNGEON_SIZE_Y; i++) {
        dungeon->map[i] = get_tile(VOID);
    }

    return dungeon;
}

Dungeon* create_wall_dungeon() {
    Dungeon* dungeon = calloc(1, sizeof(Dungeon));

    for (int i = 0; i < DUNGEON_SIZE_X * DUNGEON_SIZE_Y; i++) {
        dungeon->map[i] = get_tile(WALL);
    }

    return dungeon;
}

Dungeon* create_basic_dungeon() {
    Dungeon* dungeon = calloc(1, sizeof(Dungeon));

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
    draw_h_line(dungeon, WALL, 0, 10, 20, false);
    draw_h_line(dungeon, WALL, 0, 15, 25, false);
    draw_h_line(dungeon, WALL, 0, 20, 30, false);
    draw_v_line(dungeon, WALL, 50, 0, 10, false);
    draw_v_line(dungeon, WALL, 52, 0, 15, false);
    draw_v_line(dungeon, WALL, 54, 0, 20, false);
}

Tile* get_dungeon_tile_from_dir(Dungeon* dungeon, DIRECTION dir, int x, int y) {
    switch (dir) {
        case NORTH: return get_dungeon_tile(dungeon, x, y - 1); break;
        case SOUTH: return get_dungeon_tile(dungeon, x, y + 1); break;
        case EAST : return get_dungeon_tile(dungeon, x + 1, y); break;
        case WEST : return get_dungeon_tile(dungeon, x - 1, y); break;
        default: break;
    }
}

Tile* get_dungeon_tile(Dungeon* dungeon, int x, int y) {
    return dungeon->map[get_1d_idx_from_2d_coord(x, y, DUNGEON_SIZE_Y)];
}