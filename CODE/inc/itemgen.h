#ifndef __ITEMGEN_H__
#define __ITEMGEN_H__

#include "invntory.h"

// Tunable values for the item generator

namespace ItemConsts {
    // %chance that an item will generate an affix (prefix or suffix)
    const int CHANCE_OF_AFFIX  = 30;

    // %chance that an item will be cursed
    const int CHANCE_OF_CURSE  = 4;

    // The maximum number of attempts to reroll an item aspect to meet the ilevel requirements
    const int MAX_GENERATOR_REROLLS = 10;

    // odds tables for generating main item classes.  Currently:
    //
    //   weapon: 20% 
    //   armor 20%
    //   currency 29%
    //   potion 15%
    //   scroll: 15%
    //   artifact 1% 
    // 
    // Note: key items will be handled separately.
    const int g_item_class_pool[]= {20, 40, 69, 84, 99, 100};
    const int g_item_class_pool_count = 6;
    const int g_item_class_pool_entries = 100;

    // Various enums

    enum {
        WEAPON_CLASS,
        ARMOR_CLASS,
        CURRENCY_CLASS,
        POTION_CLASS,
        SCROLL_CLASS,
        ARTIFACT_CLASS,
        KEY_ITEM_CLASS
    };

    enum {
        PREFIX_CLASS,
        SUFFIX_CLASS
    };

    enum {
        STANDARD_ARTIFACT,
        MULTIPART_ARTIFACT,
        MULTIGEN_ARTIFACT
    };
}

// A class that generates instances of items according to weighting rules.  All
// public methods return a pointer to a generated item, with any rolled
// affixes and other modifiers already applied.
class ItemGenerator {
private:
    static int roll_from_pool(const int *pool, int pool_size, int max_val);
    static void apply_affix(Item *i, int affix_type, int ilevel);
    static void apply_curse(Item *i);
public:
    static Item *generate();
    static Item *generate(int ilevel);
    static Item *generate(int item_type, int ilevel);
};

#endif
