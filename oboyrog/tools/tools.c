#include "tools.h"

int get_1d_idx_from_2d_coord(int x, int y, int w) {
    return (y * w) + x;
}

int get_1d_from_2d_dungeon(int x, int y) {
    return (y * DUNGEON_SIZE_Y) + x;
}

float get_distance_from_coords(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

float get_distance_from_pos(Position origin, Position target) {
    return get_distance_from_coords(origin.x, origin.y, target.x, target.y);
}

int get_str_size(char* str) {
    int idx = 0;

    while (str[idx] != '\0') {
        idx++;
    }

    return idx;
}