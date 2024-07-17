#ifndef __TARGETING__LIST_H__
#define __TARGETING__LIST_H__

#include <stdbool.h>

#include "entity.h"

#include "fov.h"

#include "constants.h"

typedef struct TargetingList {
    Entity* lst[NB_MAX_MONSTERS];
    int current_idx;
    bool is_ordered;
} TargetingList;

TargetingList* get_empty_targeting_list();
void get_visible_entities(TargetingList* lst, Entity* monsters[], FOVMap* fov_map);
void next_target(TargetingList* target_lst);
void clean_targeting_list(TargetingList* lst);

#endif