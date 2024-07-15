#include "targeting_list.h"

TargetingList* get_empty_targeting_list() {
    TargetingList* target_lst = calloc(1, sizeof(TargetingList));
    target_lst->current_idx = 0;
    return target_lst;
}

void next_target(TargetingList* target_lst) {
    target_lst->current_idx++;
    if (target_lst->current_idx == NB_MAX_MONSTERS) {
        target_lst->current_idx = 0;
    }
}