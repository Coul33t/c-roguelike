#include "fov.h"

void init_fov_map(FOVMap* fov_map) {
    for (int y = 0; y < DUNGEON_SIZE_Y; y++) {
        for (int x = 0; x < DUNGEON_SIZE_X; x++) {
            fov_map->visible_map[get_1d_from_2d_dungeon(x, y)] = false;
            fov_map->seen_map[get_1d_from_2d_dungeon(x, y)] = false;
        }
    }
}

void make_fov(Entity* player, Dungeon* dungeon, FOVMap* fov_map) {
    int distance;
    Position target;

    dungeon->map[get_1d_idx_from_2d_coord(player->pos.x, player->pos.y, DUNGEON_SIZE_Y)]->visible = true;
    dungeon->map[get_1d_idx_from_2d_coord(player->pos.x, player->pos.y, DUNGEON_SIZE_Y)]->seen = true;

    fov_map->visible_map[get_1d_idx_from_2d_coord(player->pos.x, player->pos.y, DUNGEON_SIZE_Y)] = true;
    fov_map->seen_map[get_1d_idx_from_2d_coord(player->pos.x, player->pos.y, DUNGEON_SIZE_Y)] = true;

    for (int y = player->pos.y - player->fov_radius; y < player->pos.y + player->fov_radius; y++) {
        for (int x = player->pos.x - player->fov_radius; x < player->pos.x + player->fov_radius; x++) {
            target.x = x;
            target.y = y;

            distance = get_distance_from_pos(player->pos, target);

            if (distance < player->fov_radius) {
                if (is_in_map(x, y) && line_of_sight(dungeon, player->pos, target)) {
                    fov_map->visible_map[get_1d_from_2d_dungeon(x, y)] = true;
                    fov_map->seen_map[get_1d_from_2d_dungeon(x, y)] = true;
                    dungeon->map[get_1d_from_2d_dungeon(x, y)]->visible = true;
                    dungeon->map[get_1d_from_2d_dungeon(x, y)]->seen = true;
                }
            }
        }
    }
}

void clear_fov(Dungeon* dungeon, FOVMap* fov_map) {
    for (int y = 0; y < DUNGEON_SIZE_Y; y++) {
        for (int x = 0; x < DUNGEON_SIZE_X; x++) {
            dungeon->map[get_1d_from_2d_dungeon(x, y)]->visible = false;
            fov_map->visible_map[get_1d_from_2d_dungeon(x, y)] = false;
        }
    }
}

bool is_visible(Entity* entity, FOVMap* fov_map) {
    if (fov_map->visible_map[get_1d_from_2d_dungeon(entity->pos.x, entity->pos.y)]) {
        return true;
    }

    return false;
}

bool line_of_sight(Dungeon* dungeon, Position origin, Position target) {
    int delta_x = origin.x - target.x;
    int delta_y = origin.y - target.y;

    int abs_delta_x = abs(delta_x);
    int abs_delta_y = abs(delta_y);

    int sign_x = get_sign(delta_x);
    int sign_y = get_sign(delta_y);

    int x = target.x;
    int y = target.y;

    int t;

    if (abs_delta_x > abs_delta_y) {
        t = abs_delta_y * 2 - abs_delta_x;

        do {

            if (t >= 0) {
                y += sign_y;
                t -= abs_delta_x * 2;
            }

            x += sign_x;
            t += abs_delta_y * 2;

            if (x == origin.x && y == origin.y) {
                return true;
            }

        } while (dungeon->map[get_1d_from_2d_dungeon(x, y)]->transparent);

        return false;
    }

    else {
        
        t = abs_delta_x * 2 - abs_delta_y;

        do {
            if (t >= 0) {
                x += sign_x;
                t -= abs_delta_y * 2;
            }

            y += sign_y;
            t += abs_delta_x * 2;

            if (x == origin.x && y == origin.y) {
                return true;
            }

        } while (dungeon->map[get_1d_from_2d_dungeon(x, y)]->transparent);

        return false;
    }
}

int get_sign(int a){
  return (a < 0) ? -1 : 1;
}