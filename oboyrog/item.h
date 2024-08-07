#ifndef __ITEM_H__
#define __ITEM_H__

typedef enum {
    HEAD,
    CHEST,
    ARMS,
    HANDS,
    LEGS,
    FOOT
} Slot;

typedef struct Item {
    int heal;
    int dmg;
    bool equip;
    Slot slot;
    bool usable;
    bool consummable;
    int nb_of_use;
} Item;

#endif