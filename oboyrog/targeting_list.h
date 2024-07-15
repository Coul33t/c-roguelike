#ifndef __TARGETING__LIST_H__
#define __TARGETING__LIST_H__

#include "entity.h"

#include "constants.h"

typedef struct TargetingList {
    Entity* lst[NB_MAX_MONSTERS];
    int current_idx;
} TargetingList;

TargetingList* get_empty_targeting_list();
void next_target(TargetingList* target_lst);

#endif