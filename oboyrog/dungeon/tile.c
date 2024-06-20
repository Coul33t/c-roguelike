#include "tile.h"

Tile* get_tile(TILE_TYPE tile_type) {

}

Tile* get_void() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->chr = ' ';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_debug() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->chr = 'D';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_wall() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->chr = '#';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_floor() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->chr = '.';
    tile->walkable = true;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_glass() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->chr = '=';
    tile->walkable = false;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}