#ifndef __ITEMGEN_H__
#define __ITEMGEN_H__

#include "invntory.h"

// Tunable values for the item generator

namespace ItemConsts {
    // %chance that an item will generate an affix (prefix or suffix)
    const int BASE_CHANCE_OF_AFFIX  = 10;

    // %chance that an item will be cursed.  This is consistent across all types of equipment
    const int CHANCE_OF_CURSE  = 10;

    // The maximum number of attempts to reroll an item aspect to meet the ilevel requirements
    const int MAX_GENERATOR_REROLLS = 10;

    // odds tables for generating main item classes.  Currently:
    //
    //   weapon: 10% 
    //   armor 30%
    //   currency 29%
    //   potion 15%
    //   scroll: 15%
    //   artifact 1% 
    // 
    // Note: key items will be handled separately.
    const int g_item_class_pool[]= {10, 40, 69, 84, 99, 100};
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

    enum {
        ARMOR_TYPE_HAT,
        ARMOR_TYPE_HELM,
        ARMOR_TYPE_GLOVES,
        ARMOR_TYPE_GAUNTLETS,
        ARMOR_TYPE_SHIRT,
        ARMOR_TYPE_MAIL,
        ARMOR_TYPE_PANTS,
        ARMOR_TYPE_LEGGINGS,
        ARMOR_TYPE_SHOES,
        ARMOR_TYPE_BOOTS,
        ARMOR_TYPE_BUCKLER,
        ARMOR_TYPE_SHIELD,
        ARMOR_TYPE_RING,
        ARMOR_TYPE_AMULET,
        NUM_ARMOR_TYPES
    };

    enum {
        WEAPON_TYPE_DAGGER,
        WEAPON_TYPE_SWORD,
        WEAPON_TYPE_BROADSWORD,
        WEAPON_TYPE_AXE,
        WEAPON_TYPE_BATTLEAXE,
        WEAPON_TYPE_MACE,
        WEAPON_TYPE_MAUL
    };

    enum { 
        MODIFIER_STR,
        MODIFIER_CON,
        MODIFIER_DEX,
        MODIFIER_ATK,
        MODIFIER_DEF,
        MODIFIER_SPD,
        MODIFIER_FATK,
        MODIFIER_IATK,
        MODIFIER_LATK,
        MODIFIER_FDEF,
        MODIFIER_IDEF,
        MODIFIER_LDEF,
        MODIFIER_APT,
        MODIFIER_MAX_HP,
        MODIFIER_FDMG,
        MODIFIER_IDMG,
        MODIFIER_LDMG,
        MODIFIER_POIS,
        MODIFIER_BLOCK,
        MODIFIER_ADMG,
        NUM_MODIFIERS
    };
    
    const int FIRST_POTION_GID =  130;
    const int LAST_POTION_GID =   141;
    const int NUM_POTIONS = (LAST_POTION_GID - FIRST_POTION_GID) + 1;

    const int FIRST_SCROLL_GID = 142;
    const int LAST_SCROLL_GID = 153;
    const int NUM_SCROLLS = (LAST_SCROLL_GID - FIRST_SCROLL_GID) + 1;
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
