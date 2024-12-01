//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2021 Shaun Brandt / Holy Meatgoat Software
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
protected:
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
public:
    virtual std::string get_full_name() = 0;
    virtual std::string get_type_name() = 0;
    virtual void init(int idx) = 0;
    virtual void dump_item() = 0;
    virtual void dump_prefix() = 0;
    virtual void dump_suffix() = 0;
    virtual void add_prefix(int pid) = 0;
    virtual void add_suffix(int sid) = 0;
    virtual void set_curse_state(bool curse) = 0;
    virtual int get_prefix() = 0;
    virtual int get_suffix() = 0;
    virtual void use() = 0;
    virtual void remove_prefix() = 0;
    virtual void remove_suffix() = 0;
    virtual bool is_it_cursed() = 0;
    virtual int get_item_class() = 0;
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual void mark_equipped() = 0;
    virtual void mark_removed() = 0;
    virtual bool is_it_equipped() = 0;
    void dump_item_common();
    int get_value() { return (int)value; }
    bool can_have_a_prefix() { return can_have_prefix; }
    bool can_have_a_suffix() { return can_have_suffix; }
    bool can_have_curse() { return can_be_cursed; }
    bool can_it_stack() { return can_stack; }
    bool can_be_used() { return can_use; }
    bool can_be_dropped() { return can_drop; }
    bool can_be_equipped() { return can_equip; }
    void identify() { is_identified = true; }
    bool is_it_identified() { return is_identified; }
    unsigned short get_quantity() { return quantity; }
    void adjust_quantity(int amount) { quantity += amount; }
    std::string get_description() { return description; }
    unsigned short get_gid() { return gid; }
    unsigned short get_id() { return id; }
    unsigned short get_type_id() { return type_id; }
    virtual ~Item() { /*std::cout << "~Item: Deleting item" << std::endl;*/ }
};

// A piece of equipment.  This represents any item that can be equipped
// by the player, and generally consists of a base equipment type and any 
// prefix/suffix attached to it.
class Equipment : public Item {
protected:
    short prefix_id;
    short suffix_id;
    bool is_cursed;
    bool is_equipped;
public:
    virtual void mark_equipped() = 0;
    virtual void mark_removed() = 0;
    virtual void dump_item() = 0;
    virtual void init(int idx) = 0;
    virtual int get_item_class() = 0;
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    std::string get_full_name();
    std::string get_type_name();
    void use() {}
    int get_prefix() { return prefix_id; }
    int get_suffix() { return suffix_id; }
    void dump_prefix();
    void dump_suffix();
    void set_curse_state(bool curse) { is_cursed = curse; }
    void add_prefix(int pid) { can_have_prefix ? prefix_id = pid : prefix_id = -1; }
    void add_suffix(int sid) { can_have_suffix ? suffix_id = sid : suffix_id = -1; }
    bool is_it_cursed() { return is_cursed; }
    bool is_it_equipped() { return is_equipped; }
    void remove_prefix() { add_prefix(-1); }
    void remove_suffix() { add_suffix(-1); }

    virtual ~Equipment() { /*std::cout << "   Deleting equipment" << std::endl; */ }
};

// A weapon - a piece of equipment that has an attack rating and is equipped in a weapon slot
class Weapon : public Equipment {
private:
    unsigned short attack;
    void init(WeaponBaseType *b);
public:
    Weapon();
    Weapon(WeaponBaseType *b);
    Weapon(unsigned int idx);
    void init(int idx);
    int get_attack(void) { return attack; }
    int get_defense(void) { return -1; }
    int get_item_class(void);
    void dump_item();
    void mark_equipped();
    void mark_removed();
};

// Armor - a piece of equipment that has a defense rating and is equipped in an armor slot
class Armor : public Equipment {
private:
    unsigned short defense;
    void init(ArmorBaseType *b);
public:
    Armor();
    Armor(ArmorBaseType *b);
    Armor(unsigned int idx);
    void init(int idx);
    int get_attack(void) { return -1; }
    int get_defense(void) { return defense; }
    int get_item_class(void);
    void dump_item();
    void mark_equipped();
    void mark_removed();
};

// A 'consumable'.  This represents any kind of item which can be used
// in some way, but not equipped.  This includes items like potions
// and scrolls.
class Consumable: public Item {
private:
    bool  effect_active;
    short effect_turns_remaining;
public:
    virtual std::string get_full_name();
    virtual std::string get_type_name() = 0;
    virtual void dump_item() = 0;
    virtual void use() = 0;
    virtual void init(int idx) = 0;
    virtual int get_item_class() = 0;
    int get_prefix() { return -1; }
    int get_suffix() { return -1; }
    int get_attack() { return -1; }
    int get_defense() { return -1; }
    void dump_prefix() {}
    void dump_suffix() {}
    void add_prefix(int pid) {}
    void add_suffix(int sid) {}
    void set_curse_state(bool curse) {}
    void remove_prefix() {}
    void remove_suffix() {}
    bool is_it_cursed() { return false; }
    bool is_it_equipped() { return false; }
    void mark_equipped() {}
    void mark_removed() {}
    virtual ~Consumable() { /*std::cout << "   Deleting consumable" << std::endl;*/ } 
};

// Potions
class Potion: public Consumable {
private:
    unsigned short effect_id;
    void init(PotionType *t);
public:
    Potion();
    Potion(PotionType *t);
    Potion(unsigned int idx);
    void init(int idx);
    int get_item_class();
    std::string get_type_name();
    void dump_item();
    void use();
};

// Scroll
class Scroll: public Consumable {
private:
    unsigned short effect_id;
    void init(ScrollType *t);
public:
    Scroll();
    Scroll(ScrollType *t);
    Scroll(unsigned int idx);
    void init(int idx);
    int get_item_class();
    std::string get_type_name();
    void dump_item();
    void use();
};

class Artifact: public Item {
private:
    unsigned short effect_id;
    unsigned short type;
    unsigned short pieces;
    void init(ArtifactType *t);
public:
    Artifact();
    Artifact(ArtifactType *t);
    Artifact(unsigned int idx);
    void init(int idx);
    int get_item_class();
    void dump_item();
    int get_prefix() { return -1; }
    int get_suffix() { return -1; }
    int get_attack() { return -1; }
    int get_defense() { return -1; }
    void dump_prefix() {}
    void dump_suffix() {}
    void add_prefix(int pid) {}
    void add_suffix(int sid) {}
    void set_curse_state(bool curse) {}
    void remove_prefix() {}
    void remove_suffix() {}
    bool is_it_cursed() {return false; }
    bool is_it_equipped() { return false; }
    void mark_equipped() {}
    void mark_removed() {}
    void use() {}
    std::string get_full_name();
    std::string get_type_name();
    ~Artifact() { /*std::cout << "   Deleting artifact" << std::endl; */ }
};

class Currency: public Item {
    void init(CurrencyType *t);
public:
    Currency();
    Currency(CurrencyType *t);
    Currency(unsigned int idx);
    void init(int idx);
    int get_item_class();
    void dump_item();
    int get_prefix() { return -1; }
    int get_suffix() { return -1; }
    int get_attack() { return -1; }
    int get_defense() { return -1; }
    void dump_prefix() {}
    void dump_suffix() {}
    void add_prefix(int pid) {}
    void add_suffix(int sid) {}
    void set_curse_state(bool curse) {}
    void remove_prefix() {}
    void remove_suffix() {}
    bool is_it_cursed() {return false; }
    bool is_it_equipped() { return false; }
    void mark_equipped() {}
    void mark_removed() {}
    void use() {}
    std::string get_full_name();
    std::string get_type_name();
    ~Currency() { /* std::cout << "   Deleting currency" << std::endl; */ }
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
    int add_at_slot(Item *i, int slot);
    int add_at_first_empty(Item *i);
    int get_first_empty_slot();
    bool inventory_is_full();
    int get_num_slots_in_use();
    void delete_item_in_slot(int slot);
    void remove_item_in_slot(int slot);
    void dump_inventory(void);
    int get_stackable_item_slot(Item *it);
    //void drop_item_qty_in_slot(int slot, int quantity);
};

extern Inventory *g_inventory;

// The list of scrambled tile IDs for the potions and scrolls
extern std::vector<int> g_scrambled_potion_icons;
extern std::vector<int> g_scrambled_scroll_icons;

// A set of bools - for each potion/scroll, true if identified, false if not
extern std::vector<bool> g_identified_potions;
extern std::vector<bool> g_identified_scrolls;
#endif
