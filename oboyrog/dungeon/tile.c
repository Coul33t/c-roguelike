#include "tile.h"

Tile* get_wall() {
    Tile* tile = {'#', false, false, false, false};
    return tile;
}

Tile* get_floor() {
    Tile* tile = {'.', true, true, false, false};
    return tile;
}

Tile* get_glass() {
    Tile* tile = {'=', false, true, false, false};
    return tile;
}