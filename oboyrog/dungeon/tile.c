#include "tile.h"

Tile* get_tile(TILE_TYPE tile_type) {
    switch (tile_type) {
        case WALL: return get_wall(); break;
        case FLOOR: return get_floor(); break;
        case GLASS: return get_glass(); break;
        default: break;
    }
}

Tile* get_void() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->type = VOID;
    tile->chr = ' ';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_debug() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->type = DEBUG;
    tile->chr = 'D';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_wall() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->type = WALL;
    tile->chr = '#';
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_floor() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->type = FLOOR;
    tile->chr = '.';
    tile->walkable = true;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_glass() {
    Tile* tile = calloc(sizeof(Tile), 1);
    tile->type = GLASS;
    tile->chr = '=';
    tile->walkable = false;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}