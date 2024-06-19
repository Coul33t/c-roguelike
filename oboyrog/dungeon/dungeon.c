#include "dungeon.h"

Dungeon* create_basic_dungeon() {
    Dungeon* dungeon;
    for (int i = 0; i < 10; i++) {
        dungeon->map[get_1d_idx_from_2d_coord(10, 10 + i, DUNGEON_SIZE_Y)] = get_wall();
    }
}