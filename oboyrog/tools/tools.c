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

float get_distance_from_entities(Entity* e1, Entity* e2) {
    return get_distance_from_pos(e1->pos, e2->pos);
}

void sort_entities_array_by_dst(Entity* array[], Entity* player) {
    int current_smallest_idx;
    float current_smallest_dst;
    float dst;

    // For each monster, we check if it's the closest to the player
    // If not, we swap it with the closest one
    // - 1 because we compare it with the next value
    for (int i = 0; i < NB_MAX_MONSTERS - 1; i++) {
        if (array[i] == NULL) {
            return;
        }

        current_smallest_idx = i;
        current_smallest_dst = get_distance_from_entities(player, array[i]);

        // For each monster after the current one, check if there's a closer one
        // if there's a closer one, mark it as the new closest one
        for (int j = i + 1; j < NB_MAX_MONSTERS; j++) {
            dst = get_distance_from_entities(player, array[j]);
            if (dst < current_smallest_dst) {
                current_smallest_dst = dst;
                current_smallest_idx = j;
            }
        }

        // Once every monster has been processed, we're assured to have the smallest monster idx
        // Swap if it's not the current monster
        if (current_smallest_idx != i) {
            swap_entities_by_idx(array, i, current_smallest_idx);
        }
    }
}

void swap_entities(Entity* ent_1, Entity* ent_2) {
    Entity tmp = *ent_1;
    *ent_1 = *ent_2;
    *ent_2 = tmp;
}

void swap_entities_by_idx(Entity* a[], int idx_1, int idx_2) {
    Entity* temp = a[idx_1];
    a[idx_1] = a[idx_2];
    a[idx_2] = temp;
}
