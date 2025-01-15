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
#ifndef __INVNTORY_H__
#define __INVNTORY_H__

#include "globals.h"

// The number of artifacts in the artifact table.  Used in a couple arrays
// that hold the quantity of artifacts collected
const int NUM_ARTIFACTS = 70;
// The offset to multigen artifacts in the table; they're handled differently
// than the other kinds (limit one per character generation)
const int MULTIGEN_ARTIFACT_OFFSET = 47;

namespace InventoryConsts {
    const int INVENTORY_SIZE = 48;
    const int MAX_MODIFIERS  = 5;
}

// Fundamental item/equipment types.  All base types (and rare versions of the base types) are all
// assigned to one of these fundamental categories
typedef struct {
    unsigned short id;
    std::string name;
} BodyPartType;

typedef struct {
    unsigned short id;
    std::string name;
    unsigned char hands;
} WeaponType;

typedef struct {
    unsigned short id;
    std::string name;
    unsigned short body_part_id;
} ArmorType;

// A type for a modifier magnitude, i.e. the amount that something
// can be adjusted.  The modifier modes are:
//
// 0 - relative (i.e. 'increase by 10%')
// 1 - absolute (i.e. 'increase by 1')
// 2 - secondary modifier relative to primary modifier (i.e. '10% of physical attack as fire damage')
//     (the primary modifier is 'modifier_id', the secondary is 'secondary_id')
// 3 - enable effect (i.e. applies poison to player)
// 4 - 'special effect' - defined in a code block expressed by 'effect_id'
//     (this captures effects that aren't otherwise trivial to express)
//
// This is mainly used for equipment prefixes and suffixes.
typedef struct {
    unsigned short modifier_id;
    unsigned char modifier_mode;
    float magnitude;
    unsigned short secondary_id;
} ModifierMagType;

// Base equipment types.  These are particular base versions of the fundamental types, used
// to hold stats that are loaded into specific item objects
typedef struct {
    unsigned short id;
    std::string name;
    unsigned short gid;
    unsigned short type_id;
    unsigned short attack;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} WeaponBaseType;

typedef struct {
    unsigned short id;
    std::string name;
    unsigned short gid;
    unsigned short type_id;
    unsigned short defense;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} ArmorBaseType;

typedef struct {
    unsigned short id;
    std::string name;
    unsigned short gid;
    unsigned short type_id;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} CurrencyType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned short type_id;
    unsigned short effect_id;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} PotionType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned short type_id;
    unsigned short effect_id;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} ScrollType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned short type_id;
    unsigned char pieces;
    unsigned short effect_id;
    unsigned char rarity;
    unsigned char ilevel;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} ArtifactType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned char num_modifiers;
    ModifierMagType modifiers[InventoryConsts::MAX_MODIFIERS];
} ItemPrefixType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned char num_modifiers;
    ModifierMagType modifiers[InventoryConsts::MAX_MODIFIERS];
} ItemSuffixType;

typedef struct {
    unsigned short id;
    std::string name;
    std::string abbrev_name;
} ModifierType;

// An 'item'.  This represents anything that can be held in an inventory slot.
class Item {
public:
    unsigned short id;
    unsigned short quantity;
    std::string name;
    std::string description;
    unsigned short gid;
    unsigned short type_id;
    unsigned char rarity;
    unsigned char ilevel;
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
    bool is_identified;
    short prefix_id;
    short suffix_id;
    bool is_cursed;
    bool is_equipped;
    short attack;
    short defense;
    unsigned short effect_id;
    unsigned short type;
    unsigned short pieces;
    int item_class;

    Item(int item_class);
    Item(int item_class, int idx);
    Item();
    ~Item() { /*std::cout << "~Item: Deleting item" << std::endl;*/ }
    std::string get_full_name();
    std::string get_type_name();
    void init(int ic, int idx);
    void dump_item();
    void dump_prefix();
    void dump_suffix();
    int get_attack();
    int get_defense();
    void use();
};

// An inventory.  This consists of a list of Item pointers, plus
// operations to manipulate the inventory (add, remove, find an empty spot, etc.)
class Inventory {
private:
    std::vector<Item *> inv;
public:
    Inventory();
    ~Inventory();
    Item *get_item_in_slot(int slot);
    int get_slot_of_item(Item *i);
    int add_at_slot(Item *i, int slot);
    int add_at_first_empty(Item *i);
    int get_first_empty_slot();
    bool inventory_is_full();
    int get_num_slots_in_use();
    void delete_item_in_slot(int slot);
    void remove_item_in_slot(int slot);
    void dump_inventory(void);
    int get_stackable_item_slot(Item *it);
};

extern Inventory *g_inventory;
extern Inventory *g_weapon_shop_inventory;
extern Inventory *g_item_shop_inventory;

// The list of total active artifacts (which are applied to the player's stats)
// and collected artifacts (which will also be applied to the next player's stats)
extern unsigned short g_collected_artifacts[NUM_ARTIFACTS];
extern unsigned short g_active_artifacts[NUM_ARTIFACTS];

// The list of scrambled tile IDs for the potions and scrolls
extern std::vector<int> g_scrambled_potion_icons;
extern std::vector<int> g_scrambled_scroll_icons;

// A set of bools - for each potion/scroll, true if identified, false if not
extern std::vector<bool> g_identified_potions;
extern std::vector<bool> g_identified_scrolls;

// Function prototypes
void move_new_artifacts_to_existing(void);
void perform_identification_action(Item *i, bool log);
void identify_previously_known_items_at_player();
void identify_if_previously_known(Item *i);
void drop_item_at(Item *i, int x, int y);
int get_tile_to_render(Item *i);

#endif
