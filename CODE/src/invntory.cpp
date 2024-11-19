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
// Item
//==================================================================

// Dumps information common to all Items to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
void Item::dump_item_common(void) {
    std::cout << "====== Common ============================" << std::endl;
    std::cout << "Name:      " << get_full_name() << std::endl;
    std::cout << "ID:        " << id << std::endl;
    std::cout << "GID:       " << gid << std::endl;
    std::cout << "Base name: " << name << std::endl;
    std::cout << "Rarity:    " << (int)rarity << std::endl;
    std::cout << "iLevel:    " << (int)ilevel << std::endl;
    std::cout << "Value:     " << value << std::endl;
    std::cout << "Flags:     ";
    if (can_be_cursed)
        std::cout << "C";
    else
        std::cout << "c";
    if (can_have_prefix)
        std::cout << "P";
    else
        std::cout << "p";
    if (can_have_suffix) 
        std::cout << "S";
    else
        std::cout << "s";
    if (can_stack)
        std::cout << "Q";
    else
        std::cout << "q";
    if (can_equip)
        std::cout << "E";
    else
        std::cout << "e";
    if (can_drop)
        std::cout << "D";
    else
        std::cout << "d";
    if (can_use)
        std::cout << "U";
    else
        std::cout << "u";
    std::cout << std::endl;
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

    if (is_identified) {
        if (can_have_prefix && prefix_id >= 0) {
            prefix_text = g_item_prefix_ids[prefix_id].name + " ";        
        }
        else {
            prefix_text = "";
        }
        if (can_have_suffix && suffix_id >= 0) {
            suffix_text = " " + g_item_suffix_ids[suffix_id].name;
        }
        else {
            suffix_text = "";
        }
    }
    else {
        prefix_text = "(Unidentified) ";
    }

    return prefix_text + name + suffix_text;
}

// Dumps information about the item's prefix to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
void Equipment::dump_prefix() {
    if (can_have_prefix && prefix_id >= 0) {
        ItemPrefixType *it = &(g_item_prefix_ids[prefix_id]);
        std::cout << "====== Prefix info ===================" << std::endl;
        std::cout << "Name:      " << it->name << std::endl;
        std::cout << "Num mods:  " << (int)it->num_modifiers << std::endl;
        for (int i = 0; i < it->num_modifiers; ++i) {
            ModifierMagType *mt = &(it->modifiers[i]); 
            std::cout << " Mod " << (i+1) << ":" << std::endl;
            std::cout << "  Name:      " << g_modifier_ids[mt->modifier_id].name << std::endl;
            std::cout << "  Modifier mode:  " << (int)mt->modifier_mode << std::endl;
            std::cout << "  Magnitude: " << mt->magnitude << std::endl;
        }
    }
}

// Dumps information about the item's suffix to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
void Equipment::dump_suffix() {
    if (can_have_suffix && suffix_id >= 0) {
        ItemSuffixType *it = &(g_item_suffix_ids[suffix_id]);
        std::cout << "====== Suffix info ===================" << std::endl;
        std::cout << "Name:      " << it->name << std::endl;
        std::cout << "Num mods:  " << (int)it->num_modifiers << std::endl;
        for (int i = 0; i < it->num_modifiers; ++i) {
            ModifierMagType *mt = &(it->modifiers[i]); 
            std::cout << " Mod " << (i+1) << ":" << std::endl;
            std::cout << "  Name:      " << g_modifier_ids[mt->modifier_id].name << std::endl;
            std::cout << "  Modifier mode:  " << (int)mt->modifier_mode << std::endl;
            std::cout << "  Magnitude: " << mt->magnitude << std::endl;
        }
    }
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
    ilevel = b->ilevel;
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
    is_identified = false;
    prefix_id = -1;
    suffix_id = -1;
}

void Weapon::init(int idx) {
    init(&(g_weapon_base_ids[idx]));
}

// Weapon::Weapon
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
Weapon::Weapon() {
    //std::cout << "Creating weapon" << std::endl;
    WeaponBaseType *b = &(g_weapon_base_ids[0]);
    init(b);
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
    //std::cout << "Creating weapon" << std::endl;
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

// Dumps information specific to weapons to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
void Weapon::dump_item() {
    dump_item_common();
    std::cout << "====== Weapon Specific ===================" << std::endl;
    std::cout << "Type:      " << g_weapon_type_ids[g_weapon_base_ids[id].type_id].name << std::endl;
    std::cout << "Attack:    " << attack << std::endl;
    std::cout << "Cursed:    " << is_cursed << std::endl;
    dump_prefix();
    dump_suffix();
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
    ilevel = b->ilevel;
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
    is_identified = false;
    prefix_id = -1;
    suffix_id = -1;
}

void Armor::init(int idx) {
    init(&(g_armor_base_ids[idx]));
}

// Armor::Armor
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
Armor::Armor() {
    //std::cout << "Creating armor" << std::endl;
    ArmorBaseType *b = &(g_armor_base_ids[0]);
    init(b);
}

// Armor::Armor
//
// Constructor.
//
// Constructs using a pointer to an entry in the base types table
Armor::Armor(ArmorBaseType *b) {
    //std::cout << "Creating armor" << std::endl;
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

// Dumps information specific to armor to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
void Armor::dump_item() {
    dump_item_common();
    std::cout << "====== Armor Specific ===================" << std::endl;
    std::cout << "Type:      " << g_armor_type_ids[g_armor_base_ids[id].type_id].name << std::endl;
    std::cout << "Defense:    " << defense << std::endl;
    std::cout << "Cursed:    " << is_cursed << std::endl;
    dump_prefix();
    dump_suffix();
}