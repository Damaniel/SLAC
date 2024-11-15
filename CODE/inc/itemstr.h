#ifndef __ITEMSTR_H__
#define __ITEMSTR_H__
#include <string>
#include <vector>

#define NUM_CAVES       3

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

// Base equipment types.  These are particular base versions of the fundamental types, used
// to hold stats that are loaded into specific item objects
typedef struct {
    unsigned short id;
    std::string name;
    unsigned short gid;
    unsigned short type_id;
    unsigned short attack;
    unsigned char rarity;
    unsigned char depth[NUM_CAVES];
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
    unsigned char depth[NUM_CAVES];
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
} ArmorBaseType;

// An 'item'.  This represents anything that can be held in an inventory slot.
class Item {
protected:
    unsigned short id;
    std::string name;
    unsigned short gid;
    unsigned short type_id;
    unsigned char rarity;
    unsigned char depth[NUM_CAVES];
    unsigned short value;
    bool can_be_cursed;
    bool can_have_prefix;
    bool can_have_suffix;
    bool can_stack;
    bool can_equip;
    bool can_drop;
    bool can_use;
public:
    virtual std::string get_full_name() = 0;
    virtual std::string get_type_name() = 0;
    virtual ~Item() { }
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
    virtual std::string get_full_name() = 0;
    virtual std::string get_type_name() = 0;
    virtual void equip() = 0;
    virtual void remove() = 0;
    virtual ~Equipment() {}
};

// A weapon - a piece of equipment that has an attack rating and is equipped in a weapon slot
class Weapon : public Equipment {
private:
    unsigned short attack;
    void init(WeaponBaseType *b);
public:
    Weapon(WeaponBaseType *b);
    Weapon(unsigned int idx);
    std::string get_full_name();
    std::string get_type_name();
    void equip();
    void remove();
};

// Armor - a piece of equipment that has a defense rating and is equipped in an armor slot
class Armor : public Equipment {
private:
    unsigned short defense;
    void init(ArmorBaseType *b);
public:
    Armor(ArmorBaseType *b);
    Armor(unsigned int idx);
    std::string get_full_name();
    std::string get_type_name();
    void equip();
    void remove();
};

// A 'consumable'.  This represents any kind of item which can be used
// in some way, but not equipped.  This includes items like potions
// and scrolls.
class Consumable: public Item {
public:
    virtual std::string get_full_name() = 0;
    virtual std::string get_type_name() = 0;
    virtual void use() = 0;
    virtual ~Consumable();
};

// Potions
class Potion: public Consumable {
private:
    unsigned short id;
    unsigned short effect_id;
public:
    std::string get_full_name();
    std::string get_type_name();
    void use();
};

class Empty: public Item {
public:
    std::string get_full_name();
    std::string get_type_name();
};

// An inventory.  This consists of a list of Item pointers, plus
// operations to manipulate the inventory (add, remove, find an empty spot, etc.)
class Inventory {
private:
    std::vector<Item *> inv;
public:
    Inventory();
    ~Inventory();
    Item *get_item_at_slot(unsigned char slot);
    unsigned char add_at_slot(Item *i, unsigned char slot);
    unsigned char add_at_first_empty(Item *i);
    unsigned char get_first_empty_slot();
    bool is_inventory_full();
    unsigned char get_num_slots_in_use();
    void drop(Item *i);
    void drop_item_at_slot(unsigned char slot);
    std::string get_item_name_at_slot(unsigned char slot);
    void equip_item_in_slot(unsigned char slot);
    void unequip_item_in_slot(unsigned char slot);
    void drop_item_in_slot(unsigned char slot);
    void drop_item_qty_in_slot(unsigned char slot, unsigned short quantity);
};

#endif