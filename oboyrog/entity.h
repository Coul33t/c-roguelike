#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "comp/position.h"
#include "entity.h"

typedef struct Entity {
    struct Position pos;
    char chr;
    char name[30];
    int fov_radius;
} Entity;

#endif