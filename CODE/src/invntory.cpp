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

Inventory::Inventory() {
    inv = std::vector<Item *>(INVENTORY_SIZE);
    for(int i=0;i<INVENTORY_SIZE;++i) {
        inv[i] = NULL;
    }
}

Inventory::~Inventory() {
    for (std::vector<Item *>::iterator it = inv.begin(); it != inv.end(); ++it) {
        if(*it != NULL)
            delete *it;
    }
}

// Returns the item in the selected slot, or NULL otherwise
Item *Inventory::get_item_in_slot(int slot) {
    return inv[slot];
}

// Adds an item at the specified slot, removing any existing item from it
int Inventory::add_at_slot(Item *i, int slot) {
    drop_item_in_slot(slot);
    inv[slot] = i;
    return slot;
}

// Adds an item at the first empty inventory slot.  Returns the slot it was added to,
// or -1 if there was no free slot.
int Inventory::add_at_first_empty(Item *i) {
    if (!inventory_is_full()) {
        int slot = get_first_empty_slot();
        add_at_slot(i, slot);
        std::cout << "add_at_first_empty: added to slot " << slot << std::endl;
        return slot;
    }
    return -1;
}

// Gets the location of the first empty inventory slot.  Returns that slot, or -1
// if there are no empty slots.
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

int Inventory::get_num_slots_in_use() {
    int slots_in_use = 0;

    for (int i=0; i < INVENTORY_SIZE; i++) {
        if (inv[i] != NULL)
            ++slots_in_use;
    }
    return slots_in_use;
}
// Returns true if zero space remains in the inventory, false otherwise.
bool Inventory::inventory_is_full() {
    for (int i=0; i<INVENTORY_SIZE; i++) {
        if (inv[i] == NULL)
            return false;
    }
    return true;
}

//
void Inventory::drop_item_in_slot(int slot) {
    if (inv[slot] != NULL) { 
        delete inv[slot];
        inv[slot] = NULL;
    }
}

// --------- Equipment ------------------------
std::string Equipment::get_type_name() {
    return name;
}

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

// --------- Weapon ---------------------------
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

Weapon::Weapon(WeaponBaseType *b) {
    init(b);
}

Weapon::Weapon(unsigned int idx) {
    // Assign the fields from the weapon base type list at index idx here
    WeaponBaseType *b = &(g_weapon_base_ids[idx]);
    init(b);
}

void Weapon::equip() {
    is_equipped = true;
}

void Weapon::remove() {
    is_equipped = false;
}

// -------- Armor ------------------------------
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

Armor::Armor(ArmorBaseType *b) {
    init(b);
}

Armor::Armor(unsigned int idx) {
    ArmorBaseType *b = &(g_armor_base_ids[idx]);
    init(b);
}

void Armor::equip() {
    is_equipped = true;
}

void Armor::remove() {
    is_equipped = false;
}