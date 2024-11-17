#ifndef __ITEMGEN_H__
#define __ITEMGEN_H__

#include "invntory.h"

enum {
    WEAPON_CLASS,
    ARMOR_CLASS,
    CURRENCY_CLASS,
    CONSUMABLE_CLASS,
    ARTIFACT_CLASS
};

// Values that determine the odds that a particular action will be taken
const int CHANCE_OF_PREFIX  = 30;
const int CHANCE_OF_SUFFIX  = 30;

// odds of generating an item - weapon 27%, armor 27%, currency 10%, consumable 35%, artifact 1% 
const int g_item_class_pool[]= {0, 27, 54, 64, 99, 100};
const int g_item_class_pool_count = 6;
const int g_item_class_pool_entries = 100;

class ItemGenerator {
private:
    static int roll_from_pool(const int *pool, int pool_size, int max_val);
    static void apply_prefix(Item *i);
    static void apply_suffix(Item *i);
public:
    static Item *generate();
    static Item *generate(int item_type);
};

#endif
