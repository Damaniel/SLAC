//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2025 Shaun Brandt / Holy Meatgoat Software
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.
//==========================================================================================
#ifndef __ITEMGEN_H__
#define __ITEMGEN_H__

#include "invntory.h"

// Tunable values for the item generator

namespace ItemConsts {
    // %chance that an item will generate an affix (prefix or suffix)
    const int BASE_CHANCE_OF_AFFIX  = 10;

    // %chance that an item will be cursed.  This is consistent across all types of equipment
    const int BASE_CHANCE_OF_CURSE  = 10;

    // The maximum number of attempts to reroll an item aspect to meet the ilevel requirements
    const int MAX_GENERATOR_REROLLS = 50;

    // The time range which a scroll of recall is set between when used
    const int RECALL_SCROLL_MIN_TURNS = 8;
    const int RECALL_SCROLL_MAX_TURNS = 15;

    const int NUM_TURN_POTION_EFFECTS = 5;

    enum {
        EFFECT_BERSERK_STRENGTH,
        EFFECT_SPEED,
        EFFECT_HARDINESS,
        EFFECT_EXTRA_ATTACKS,
        EFFECT_POISON
    };

    // odds tables for generating main item classes.  Currently:
    //
    //   weapon: 10%
    //   armor 38%
    //   currency 15%
    //   potion 15%
    //   scroll: 20%
    //   artifact 2%
    //
    // Note: key items will be handled separately.
    const int g_item_class_pool[]= {10, 48, 63, 77, 97, 100};
    // const int g_item_class_pool[]= {10, 48, 63, 78, 79, 100};
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
        WEAPON_TYPE_DAGGER,
        WEAPON_TYPE_SWORD,
        WEAPON_TYPE_BROADSWORD,
        WEAPON_TYPE_AXE,
        WEAPON_TYPE_BATTLEAXE,
        WEAPON_TYPE_MACE,
        WEAPON_TYPE_MAUL,
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
    const int LAST_POTION_GID =   139;
    const int NUM_POTIONS = (LAST_POTION_GID - FIRST_POTION_GID) + 1;

    const int FIRST_SCROLL_GID = 140;
    const int LAST_SCROLL_GID = 150;
    const int NUM_SCROLLS = (LAST_SCROLL_GID - FIRST_SCROLL_GID) + 1;


}

// A class that generates instances of items according to weighting rules.  All
// public methods return a pointer to a generated item, with any rolled
// affixes and other modifiers already applied.
class ItemGenerator {
private:
    static void apply_affix(Item *i, int affix_type, int affix_chance);
    static void apply_curse(Item *i, int curse_chance);
    static int generate_base_type(int item_type);
    static Item *generate_base_item(int item_type, int min_ilevel, int max_ilevel);
    static int get_base_ilevel(int item_type, int item_idx);
public:
    static Item *generate();
    static Item *generate(int ilevel);
    static Item *generate(int item_type, int ilevel);
    static Item *generate(int item_type, int min_ilevel, int max_ilevel);
    static Item *shop_generate();
};

#endif
