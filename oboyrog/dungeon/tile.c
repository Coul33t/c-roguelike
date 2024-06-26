#include "tile.h"

Tile* get_tile(TILE_TYPE tile_type) {
    switch (tile_type) {
        case WALL: return get_wall(); break;
        case FLOOR: return get_floor(); break;
        case GLASS: return get_glass(); break;
        case VOID: return get_void(); break;
        default: return get_void(); break;
    }
}

Tile* get_void() {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->type = VOID;
    tile->chr = ' ';
    tile->colour = COLOR_PAIR(VISIBLE_COLOURS);
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_debug() {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->type = DEBUG;
    tile->chr = 'D';
    tile->colour = COLOR_PAIR(VISIBLE_COLOURS);
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_wall() {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->type = WALL;
    tile->chr = '#';
    tile->colour = COLOR_PAIR(VISIBLE_COLOURS);
    tile->walkable = false;
    tile->transparent = false;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_floor() {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->type = FLOOR;
    tile->chr = '.';
    tile->colour = COLOR_PAIR(VISIBLE_COLOURS);
    tile->walkable = true;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}

Tile* get_glass() {
    Tile* tile = calloc(1, sizeof(Tile));
    tile->type = GLASS;
    tile->chr = '=';
    tile->colour = COLOR_PAIR(VISIBLE_COLOURS);
    tile->walkable = false;
    tile->transparent = true;
    tile->visible = false;
    tile->seen = false;
    return tile;
}