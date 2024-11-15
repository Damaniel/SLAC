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

#include "invntory.h"
#include "gen_data.h"

Inventory *g_inventory;

Inventory::Inventory() {
    inv = std::vector<Item *>(INVENTORY_SIZE);
    for(int i=0;i<INVENTORY_SIZE;++i) {
        inv[i] = new Empty;
    }
}

Inventory::~Inventory() {
    for (std::vector<Item *>::iterator it = inv.begin(); it != inv.end(); ++it) {
        delete *it;
    }
}

Item *Inventory::get_item_at_slot(unsigned char slot) {
    return inv[slot];
}

unsigned char Inventory::add_at_slot(Item *i, unsigned char slot) {
    if (inv[slot] != NULL) {
        std::cout << "Deleting existing inventory item at slot " << slot << std::endl;
        delete inv[slot];
    }
    inv[slot] = i;
    return slot;
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

std::string Weapon::get_type_name() {
    return name;
}

std::string Weapon::get_full_name() {
    return "Test " + name + " of Testing";
}

void Weapon::equip() {
    is_equipped = true;
}

void Weapon::remove() {
    is_equipped = false;
}


// -------- Armor ------------------------------
void Armor::init(ArmorBaseType *b) {

}

Armor::Armor(ArmorBaseType *b) {
    init(b);
}

Armor::Armor(unsigned int idx) {
    ArmorBaseType*b = &(g_armor_base_ids[idx]);
    init(b);
}

std::string Armor::get_type_name() {
    return name;
}

std::string Armor::get_full_name() {
    return "Test " + name + " of Testing";
}

void Armor::equip() {
    is_equipped = true;
}

void Armor::remove() {
    is_equipped = false;
}

// ------- Empty --------------------------------
std::string Empty::get_full_name() {
    return "Empty";
}
std::string Empty::get_type_name() {
    return "Empty";
}