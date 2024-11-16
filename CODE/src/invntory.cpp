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

#include "globals.h"

Inventory *g_inventory;

//==================================================================
// Inventory
//==================================================================


// Inventory::Inventory
//
// Constructor.
Inventory::Inventory() {
    inv = std::vector<Item *>(INVENTORY_SIZE);
    for(int i=0;i<INVENTORY_SIZE;++i) {
        inv[i] = NULL;
    }
}

// Inventory::~Inventory
//
// Destructor.  Frees any allocated Item objects along the way
Inventory::~Inventory() {
    for (std::vector<Item *>::iterator it = inv.begin(); it != inv.end(); ++it) {
        if(*it != NULL)
            delete *it;
    }
}

// Gets the item in the selected slot.
//
// Arguments:
//   slot - the slot containing the item
//
// Returns:
//   A pointer to the Item in the slot, or NULL if the slot is empty.
Item *Inventory::get_item_in_slot(int slot) {
    return inv[slot];
}

// Adds an item at the specified slot, removing any existing item from it.
// 
// Arguments:
//   i - the item to be added to the inventory
//   slot - the slot to add the item at
//
// Returns:
//   The slot the item was added at.  This will be the same as the value of 'slot'.
int Inventory::add_at_slot(Item *i, int slot) {
    drop_item_in_slot(slot);
    inv[slot] = i;
    return slot;
}

// Adds an item at the first empty inventory slot.
//
// Arguments:
//   i - the item to be added to the inventory
//
// Returns:
//   The index of the slot it was added at, or -1 if the inventory is full.
int Inventory::add_at_first_empty(Item *i) {
    if (!inventory_is_full()) {
        int slot = get_first_empty_slot();
        add_at_slot(i, slot);
        std::cout << "add_at_first_empty: added to slot " << slot << std::endl;
        return slot;
    }
    return -1;
}

// Gets the location of the first empty inventory slot.  
//
// Arguments:
//   None
//
// Returns:
//   The index of the empty slot, or -1 if the inventory is full.
int Inventory::get_first_empty_slot() {
    int first_empty = -1;
    for(int i=0; i<INVENTORY_SIZE; ++i) {
        if (inv[i] == NULL) {
            first_empty = i;
            break;
        }
    }

    std::cout << "First empty slot was " << (int)first_empty << std::endl;
    return first_empty;
}

// Gets the number of used inventory slots.  
//
// Arguments:
//   None
//
// Returns:
//   The number of used inventory slots.
int Inventory::get_num_slots_in_use() {
    int slots_in_use = 0;

    for (int i=0; i < INVENTORY_SIZE; i++) {
        if (inv[i] != NULL)
            ++slots_in_use;
    }
    return slots_in_use;
}

// Determines if the inventory is full.
//
// Arguments: 
//   None
//
// Returns:
//   true if inventory is full, false if not.
bool Inventory::inventory_is_full() {
    for (int i=0; i<INVENTORY_SIZE; i++) {
        if (inv[i] == NULL)
            return false;
    }
    return true;
}

// Removes an item from the specified inventory slot
//
// Arguments: 
//   idx - the slot to delete the item from
//
// Returns:
//   Nothing.
void Inventory::drop_item_in_slot(int slot) {
    if (inv[slot] != NULL) { 
        delete inv[slot];
        inv[slot] = NULL;
    }
}

//==================================================================
// Equipment
//==================================================================

// Gets the base name of the equipment type.
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the base type name.
std::string Equipment::get_type_name() {
    return name;
}

// Gets the full name (base+affixes) of the equipment type.
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the full item name.
std::string Equipment::get_full_name() {
    std::string prefix_text;
    std::string suffix_text;

    if (can_have_prefix && prefix_id >= 0) {
        prefix_text = g_item_prefix_ids[prefix_id].name;        
    }
    if (can_have_suffix && suffix_id >= 0) {
        suffix_text = g_item_suffix_ids[suffix_id].name;
    }

    return prefix_text + " " + name + " " + suffix_text;
}

//==================================================================
// Weapon
//==================================================================

// Initializes a Weapon using an entry from the weapon base type
//  table.
//
// Arguments: 
//   b - a pointer to an entry in the weapon base type table
//
// Returns:
//   Nothing.
void Weapon::init(WeaponBaseType *b) {
    // Assign the fields from the weapon base type here
    id = b->id;
    name = b->name;
    gid = b->gid;
    type_id = b->type_id;
    attack = b->attack;
    rarity = b->rarity;
    for(int i=0;i<NUM_CAVES;++i)
        depth[i] = b->depth[i];
    value = b->value;
    can_be_cursed = b->can_be_cursed;
    can_have_prefix = b->can_have_prefix;
    can_have_suffix = b->can_have_suffix;
    can_stack = b->can_stack;
    can_equip = b->can_equip;
    can_drop = b->can_drop;
    can_use = b->can_use;
    is_equipped = false;
    is_cursed = false;
}

// Weapon::Weapon
//
// Constructor.
//
// Constructs using a pointer to an entry in the base types table
Weapon::Weapon(WeaponBaseType *b) {
    init(b);
}

// Weapon::Weapon
//
// Constructor.
//
// Constructs using an offset (relative to to the base types table).
Weapon::Weapon(unsigned int idx) {
    // Assign the fields from the weapon base type list at index idx here
    WeaponBaseType *b = &(g_weapon_base_ids[idx]);
    init(b);
}


// Equips a weapon.
// 
// Arguments:
//   None
//
// Returns:
//   None
void Weapon::equip() {
    is_equipped = true;
}

// Removes a weapon.
// 
// Arguments:
//   None
//
// Returns:
//   None
void Weapon::remove() {
    is_equipped = false;
}

//==================================================================
// Armor
//==================================================================

// Initializes an Armor using an entry from the armor base type
//  table.
//
// Arguments: 
//   b - a pointer to an entry in the armor base type table
//
// Returns:
//   Nothing.
void Armor::init(ArmorBaseType *b) {
    // Assign the fields from the armor base type here
    id = b->id;
    name = b->name;
    gid = b->gid;
    type_id = b->type_id;
    defense = b->defense;
    rarity = b->rarity;
    for(int i=0;i<NUM_CAVES;++i)
        depth[i] = b->depth[i];
    value = b->value;
    can_be_cursed = b->can_be_cursed;
    can_have_prefix = b->can_have_prefix;
    can_have_suffix = b->can_have_suffix;
    can_stack = b->can_stack;
    can_equip = b->can_equip;
    can_drop = b->can_drop;
    can_use = b->can_use;
    is_equipped = false;
    is_cursed = false;
}

// Armor::Armor
//
// Constructor.
//
// Constructs using a pointer to an entry in the base types table
Armor::Armor(ArmorBaseType *b) {
    init(b);
}

// Armor::Armor
//
// Constructor.
//
// Constructs using an offset (relative to to the base types table).
Armor::Armor(unsigned int idx) {
    ArmorBaseType *b = &(g_armor_base_ids[idx]);
    init(b);
}

// Equips a piece of armor.
// 
// Arguments:
//   None
//
// Returns:
//   None
void Armor::equip() {
    is_equipped = true;
}

// Removes a piece of armor.
// 
// Arguments:
//   None
//
// Returns:
//   None
void Armor::remove() {
    is_equipped = false;
}