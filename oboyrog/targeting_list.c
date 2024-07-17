#include "targeting_list.h"

TargetingList* get_empty_targeting_list() {
    TargetingList* target_lst = calloc(1, sizeof(TargetingList));
    target_lst->current_idx = 0;
    target_lst->is_ordered = false;
    return target_lst;
}

void get_visible_entities(TargetingList* lst, Entity* monsters[], FOVMap* fov_map) {
    clean_targeting_list(lst);
    int lst_idx = 0;

    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        if (monsters[i] == NULL) {
            return;
        }

        if (fov_map->visible_map[get_1d_from_2d_dungeon(monsters[i]->pos.x, monsters[i]->pos.y)]) {
            lst->lst[lst_idx] = monsters[i];
            ++lst_idx;
        }
    }
}

void next_target(TargetingList* target_lst) {
    target_lst->current_idx++;
    if (target_lst->current_idx == NB_MAX_MONSTERS) {
        target_lst->current_idx = 0;
    }
}

void clean_targeting_list(TargetingList* lst) {
    for (int i = 0; i < NB_MAX_MONSTERS; i++) {
        lst->lst[i] = NULL; // Don't free, the monsters aren't dead
    }
}