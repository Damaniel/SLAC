#ifndef __ITEMGEN_H__
#define __ITEMGEN_H__

#include "invntory.h"

enum {
    WEAPON_CLASS,
    ARMOR_CLASS,
    CURRENCY_CLASS,
    CONSUMABLE_CLASS,
    ARTIFACT_CLASS,
    KEY_ITEM_CLASS
};

enum {
    PREFIX_CLASS,
    SUFFIX_CLASS
};

// Values that determine the odds that a particular action will be taken
const int CHANCE_OF_AFFIX  = 30;
const int MAX_GENERATOR_REROLLS = 10;

// odds of generating an item - weapon 27%, armor 27%, currency 10%, consumable 35%, artifact 1% 
// Note: key items will be handled separately.
const int g_item_class_pool[]= {0, 27, 54, 64, 99, 100};
const int g_item_class_pool_count = 6;
const int g_item_class_pool_entries = 100;

// A class that generates instances of items according to weighting rules.  All
// public methods return a pointer to a generated item, with any rolled
// affixes and other modifiers already applied.
class ItemGenerator {
private:
    static int roll_from_pool(const int *pool, int pool_size, int max_val);
    static void apply_affix(Item *i, int affix_type, int ilevel);
public:
    static Item *generate();
    static Item *generate(int ilevel);
    static Item *generate(int item_type, int ilevel);
};

#endif
