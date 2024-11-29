//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2024 Shaun Brandt / Holy Meatgoat Software
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


//----------------------------------------------------------------------------
// Inventory::Inventory
//
// Constructor.
//----------------------------------------------------------------------------
Inventory::Inventory() {
    inv = std::vector<Item *>(InventoryConsts::INVENTORY_SIZE);
    for(int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        inv[i] = NULL;
    }
}

//----------------------------------------------------------------------------
// Inventory::~Inventory
//
// Destructor.  Frees any allocated Item objects along the way
//----------------------------------------------------------------------------    
Inventory::~Inventory() {
    for (std::vector<Item *>::iterator it = inv.begin(); it != inv.end(); ++it) {
        if(*it != NULL)
            delete *it;
    }
}

//----------------------------------------------------------------------------
// Gets the item in the selected slot.
//
// Arguments:
//   slot - the slot containing the item
//
// Returns:
//   A pointer to the Item in the slot, or NULL if the slot is empty.
//----------------------------------------------------------------------------
Item *Inventory::get_item_in_slot(int slot) {
    return inv[slot];
}

//----------------------------------------------------------------------------
// Adds an item at the specified slot, removing any existing item from it.
// 
// Arguments:
//   i - the item to be added to the inventory
//   slot - the slot to add the item at
//
// Returns:
//   The slot the item was added at.  This will be the same as the value of 
//   'slot'.
//----------------------------------------------------------------------------
int Inventory::add_at_slot(Item *i, int slot) {
    delete_item_in_slot(slot);
    inv[slot] = i;
    return slot;
}

//----------------------------------------------------------------------------
// Adds an item at the first empty inventory slot.
//
// Arguments:
//   i - the item to be added to the inventory
//
// Returns:
//   The index of the slot it was added at, or -1 if the inventory is full.
//----------------------------------------------------------------------------
int Inventory::add_at_first_empty(Item *i) {
    if (!inventory_is_full()) {
        int slot = get_first_empty_slot();
        add_at_slot(i, slot);
        //std::cout << "add_at_first_empty: added to slot " << slot << std::endl;
        return slot;
    }
    return -1;
}

//----------------------------------------------------------------------------
// Gets the location of the first empty inventory slot.  
//
// Arguments:
//   None
//
// Returns:
//   The index of the empty slot, or -1 if the inventory is full.
//----------------------------------------------------------------------------
int Inventory::get_first_empty_slot() {
    int first_empty = -1;
    for(int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        if (inv[i] == NULL) {
            first_empty = i;
            break;
        }
    }

    //std::cout << "First empty slot was " << (int)first_empty << std::endl;
    return first_empty;
}

//----------------------------------------------------------------------------
// Gets the number of used inventory slots.  
//
// Arguments:
//   None
//
// Returns:
//   The number of used inventory slots.
//----------------------------------------------------------------------------
int Inventory::get_num_slots_in_use() {
    int slots_in_use = 0;

    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; i++) {
        if (inv[i] != NULL)
            ++slots_in_use;
    }
    return slots_in_use;
}

//----------------------------------------------------------------------------
// Determines if the inventory is full.
//
// Arguments: 
//   None
//
// Returns:
//   true if inventory is full, false if not.
//----------------------------------------------------------------------------
bool Inventory::inventory_is_full() {
    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; i++) {
        if (inv[i] == NULL)
            return false;
    }
    return true;
}

//----------------------------------------------------------------------------
// Removes an item from the specified inventory slot
//
// Arguments: 
//   idx - the slot to delete the item from
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Inventory::delete_item_in_slot(int slot) {
    if (inv[slot] != NULL) { 
        delete inv[slot];
        inv[slot] = NULL;
    }
}

void Inventory::dump_inventory(void) {
    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        if (inv[i] != NULL) {
            std::cout << "Item " << (i+1) << ": " << inv[i]->get_full_name() << std::endl;
        }
        else {
            std::cout << "Item " << (i+1) << ": <empty>" << std::endl;
        }
    }
}

//----------------------------------------------------------------------------
// If stackable, finds and returns the item slot where any existing stack of
// the specified item is.
//
// Arguments: 
//   i - the item to check
//
// Returns:
//   The index where others of that item are stored; -1 otherwise
//----------------------------------------------------------------------------
int Inventory::get_stackable_item_slot(Item *item) {

    // First check if the item is stackable.  If not,
    // return
    if (item->can_it_stack() == false) {
        return -1;
    }

    // Iterate through the inventory.  If an item with the same gid 
    // is found in a slot, return the slot number.  Otherwise,
    // return -1.
    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        if(inv[i] != NULL) {
            if (item->get_gid() == inv[i]->get_gid()) {
                return i;
            }
        }
    }
    
    // There's no existing stackable item in the inventory.
    return -1;
}

//==================================================================
// Item
//==================================================================

//----------------------------------------------------------------------------
// Dumps information common to all Items to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Item::dump_item_common(void) {
    std::cout << "====== Common ============================" << std::endl;
    std::cout << "Name:        " << get_full_name() << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "ID:          " << id << std::endl;
    std::cout << "GID:         " << gid << std::endl;
    std::cout << "Base name:   " << name << std::endl;
    std::cout << "Rarity:      " << (int)rarity << std::endl;
    std::cout << "iLevel:      " << (int)ilevel << std::endl;
    std::cout << "Value:       " << value << std::endl;
    std::cout << "Flags:       ";
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

//----------------------------------------------------------------------------
// Gets the base name of the equipment type.
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the base type name.
//----------------------------------------------------------------------------
std::string Equipment::get_type_name() {
    return name;
}

//----------------------------------------------------------------------------
// Gets the full name (base+affixes) of the equipment type.
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the full item name.
//----------------------------------------------------------------------------
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
        prefix_text = "(?) ";
    }

    return prefix_text + name + suffix_text;
}

//----------------------------------------------------------------------------
// Dumps information about the item's prefix to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
// Dumps information about the item's suffix to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
// Initializes a Weapon using an entry from the weapon base type
//  table.
//
// Arguments: 
//   b - a pointer to an entry in the weapon base type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Weapon::init(WeaponBaseType *b) {
    // Assign the fields from the weapon base type here
    id = b->id;
    name = b->name;
    description = "";
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
    quantity = 1;
}

//----------------------------------------------------------------------------
// Initializes a weapon using an index into the weapon base type table
//
// Arguments:
//   idx - the index into the weapon base type table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Weapon::init(int idx) {
    init(&(g_weapon_base_ids[idx]));
}

//----------------------------------------------------------------------------
// Weapon::Weapon
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Weapon::Weapon() {
    //std::cout << "Creating weapon" << std::endl;
    WeaponBaseType *b = &(g_weapon_base_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Weapon::Weapon
//
// Constructor.
//
// Constructs using a pointer to an entry in the base types table
//----------------------------------------------------------------------------
Weapon::Weapon(WeaponBaseType *b) {
    init(b);
}

//----------------------------------------------------------------------------
// Weapon::Weapon
//
// Constructor.
//
// Constructs using an offset (relative to to the base types table).
//----------------------------------------------------------------------------
Weapon::Weapon(unsigned int idx) {
    //std::cout << "Creating weapon" << std::endl;
    // Assign the fields from the weapon base type list at index idx here
    WeaponBaseType *b = &(g_weapon_base_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// Sets the 'is_equipped' state of the item
// 
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Weapon::mark_equipped() {
    is_equipped = true;
}

//----------------------------------------------------------------------------
// Clears the 'is_equipped' state of the item
// 
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Weapon::mark_removed() {
    //std::cout << "weapon removed" << std::endl;
    is_equipped = false;
}

//----------------------------------------------------------------------------
// Gets the item class of a weapon.
// 
// Arguments:
//   None
//
// Returns:
//   WEAPON_CLASS
//----------------------------------------------------------------------------
int Weapon::get_item_class() {
    return ItemConsts::WEAPON_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to weapons to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
// Initializes an Armor using an entry from the armor base type
//  table.
//
// Arguments: 
//   b - a pointer to an entry in the armor base type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Armor::init(ArmorBaseType *b) {
    // Assign the fields from the armor base type here
    id = b->id;
    name = b->name;
    description = "";
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
    quantity = 1;
}

//----------------------------------------------------------------------------
// Initializes an Armor using an index into the armor base type table
//
// Arguments:
//   idx - the index into the armor base types table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Armor::init(int idx) {
    init(&(g_armor_base_ids[idx]));
}

//----------------------------------------------------------------------------
// Armor::Armor
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Armor::Armor() {
    //std::cout << "Creating armor" << std::endl;
    ArmorBaseType *b = &(g_armor_base_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Armor::Armor
//
// Constructor.
//
// Constructs using a pointer to an entry in the base types table
//----------------------------------------------------------------------------
Armor::Armor(ArmorBaseType *b) {
    //std::cout << "Creating armor" << std::endl;
    init(b);
}

//----------------------------------------------------------------------------
// Armor::Armor
//
// Constructor.
//
// Constructs using an offset (relative to to the base types table).
//----------------------------------------------------------------------------
Armor::Armor(unsigned int idx) {
    ArmorBaseType *b = &(g_armor_base_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// Marks the armor as equipped
// 
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Armor::mark_equipped() {
    is_equipped = true;
}

//----------------------------------------------------------------------------
// Marks the armor as removed
// 
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Armor::mark_removed() {
    //std::cout << "armor removed" << std::endl;
    is_equipped = false;
}

//----------------------------------------------------------------------------
// Gets the item class of an armor.
// 
// Arguments:
//   None
//
// Returns:
//   ARMOR_CLASS
//----------------------------------------------------------------------------
int Armor::get_item_class() {
    return ItemConsts::ARMOR_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to armor to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Armor::dump_item() {
    dump_item_common();
    std::cout << "====== Armor Specific ===================" << std::endl;
    std::cout << "Type:      " << g_armor_type_ids[g_armor_base_ids[id].type_id].name << std::endl;
    std::cout << "Defense:    " << defense << std::endl;
    std::cout << "Cursed:    " << is_cursed << std::endl;
    dump_prefix();
    dump_suffix();
}


//==================================================================
// Consumable
//==================================================================

//----------------------------------------------------------------------------
// Gets the full name of the consumable, depending on whether it has been
// identified or not
// 
// Arguments:
//   None
//
// Returns:
//   The full name of the item
//----------------------------------------------------------------------------
std::string Consumable::get_full_name() {
    if (is_identified) {
        return name;
    }
    else {
        return "(?) " + get_type_name();
    }
}

//==================================================================
// Currency
//==================================================================

//----------------------------------------------------------------------------
// Initializes a Currency using an entry from the currency type table.
//
// Arguments: 
//   b - a pointer to an entry in the currency type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Currency::init(CurrencyType *b) {
    // Assign the fields from the armor base type here
    id = b->id;
    name = b->name;
    description = "";
    gid = b->gid;
    type_id = b->type_id;
    rarity = b->rarity;
    ilevel = b->ilevel;
    // The 'value' is the size of the pile of coins
    // It's set to some random value * the base value
    value = b->value;
    can_be_cursed = b->can_be_cursed;
    can_have_prefix = b->can_have_prefix;
    can_have_suffix = b->can_have_suffix;
    can_stack = b->can_stack;
    can_equip = b->can_equip;
    can_drop = b->can_drop;
    can_use = b->can_use;
    is_identified = true;
    quantity = b->value * (rand() % 50 + 1);
}

//----------------------------------------------------------------------------
// Initializes a Currency using an index into the currency type table
//
// Arguments:
//   idx - the index into the currency type table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Currency::init(int idx) {
    init(&(g_currency_ids[idx]));
}

//----------------------------------------------------------------------------
// Currency::Currency
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Currency::Currency() {
    //std::cout << "Creating currency" << std::endl;
    CurrencyType *b = &(g_currency_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Currency::Currency
//
// Constructor.
//
// Constructs using a pointer to an entry in the currency table
//----------------------------------------------------------------------------
Currency::Currency(CurrencyType *b) {
    //std::cout << "Creating currency" << std::endl;
    init(b);
}

//----------------------------------------------------------------------------
// Currency::Currency
//
// Constructor.
//
// Constructs using an offset (relative to to the type table).
//----------------------------------------------------------------------------
Currency::Currency(unsigned int idx) {
    CurrencyType *b = &(g_currency_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// Gets the item class of currency.
// 
// Arguments:
//   None
//
// Returns:
//   CURRENCY_CLASS
//----------------------------------------------------------------------------
int Currency::get_item_class() {
    return ItemConsts::CURRENCY_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to currency to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Currency::dump_item() {
    dump_item_common();
    std::cout << "====== Currency Specific ===================" << std::endl;
    std::cout << "  Nothing yet" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the currency's full name
// 
// Arguments:
//   None
//
// Returns:
//   A string containing the full name
//----------------------------------------------------------------------------
std::string Currency::get_full_name() {
    char name[32];

    sprintf(name, "%d gold worth of %s", quantity, (char *)g_currency_ids[id].name.c_str());
    return std::string(name);
}

//----------------------------------------------------------------------------
// Gets the currency's type name
// 
// Arguments:
//   None
//
// Returns:
//   A string containing the type name
//----------------------------------------------------------------------------
std::string Currency::get_type_name() {
    return "Currency";
}

//==================================================================
// Potion
//==================================================================

//----------------------------------------------------------------------------
// Initializes a Potion using an entry from the potion type table
//
// Arguments: 
//   b - a pointer to an entry in the potion type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Potion::init(PotionType *b) {
    // Assign the fields from the potion type here
    id = b->id;
    name = b->name;
    description = b->description;
    gid = b->gid;
    type_id = b->type_id;
    effect_id = b->effect_id;
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
    is_identified = false;
    quantity = 1;
}

//----------------------------------------------------------------------------
// Initializes a Potion using an index into the potion type table
//
// Arguments:
//   idx - an index into the potion type table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Potion::init(int idx) {
    init(&(g_potion_ids[idx]));
}

//----------------------------------------------------------------------------
// Potion::Potion
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Potion::Potion() {
    //std::cout << "Creating potion" << std::endl;
    PotionType *b = &(g_potion_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Potion::Potion
//
// Constructor.
//
// Constructs using a pointer to an entry in the types table
//----------------------------------------------------------------------------
Potion::Potion(PotionType *b) {
    //std::cout << "Creating potion" << std::endl;
    init(b);
}

//----------------------------------------------------------------------------
// Potion::Potion
//
// Constructor.
//
// Constructs using an offset (relative to to the types table).
//----------------------------------------------------------------------------
Potion::Potion(unsigned int idx) {
    PotionType *b = &(g_potion_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// 'Uses' the potion; i.e. applies its effect
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Potion::use() {
    //std::cout << "use: potion used" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the item class of a potion.
// 
// Arguments:
//   None
//
// Returns:
//   POTION_CLASS
//----------------------------------------------------------------------------
int Potion::get_item_class() {
    return ItemConsts::POTION_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to potions to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Potion::dump_item() {
    dump_item_common();
    std::cout << "====== Armor Specific ===================" << std::endl;
    std::cout << "Type:      " << type_id << std::endl;
    std::cout << "Effect ID: " << effect_id << " (expanded form TBD)" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the item's type name
// 
// Arguments:
//   None
//
// Returns:
//   "Potion";
//----------------------------------------------------------------------------
std::string Potion::get_type_name() {
    return "Potion";
}

//==================================================================
// Scroll
//==================================================================

//----------------------------------------------------------------------------
// Initializes a Scroll using an entry from the scroll type table
//
// Arguments: 
//   b - a pointer to an entry in the scroll type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Scroll::init(ScrollType *b) {
    // Assign the fields from the potion type here
    id = b->id;
    name = b->name;
    description = b->description;
    gid = b->gid;
    type_id = b->type_id;
    effect_id = b->effect_id;
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
    is_identified = false;
    quantity = 1;
}
//----------------------------------------------------------------------------
// Initializes a Scroll using an index into the scroll type table
//
// Arguments:
//   idx - an index into the scroll type table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Scroll::init(int idx) {
    init(&(g_scroll_ids[idx]));
}

//----------------------------------------------------------------------------
// Scroll::Scroll
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Scroll::Scroll() {
    //std::cout << "Creating scroll" << std::endl;
    ScrollType *b = &(g_scroll_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Scroll::Scroll
//
// Constructor.
//
// Constructs using a pointer to an entry in the types table
//----------------------------------------------------------------------------
Scroll::Scroll(ScrollType *b) {
    //std::cout << "Creating scroll" << std::endl;
    init(b);
}

//----------------------------------------------------------------------------
// Scroll::Scroll
//
// Constructor.
//
// Constructs using an offset (relative to to the types table).
//----------------------------------------------------------------------------
Scroll::Scroll(unsigned int idx) {
    ScrollType *b = &(g_scroll_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// 'Uses' the potion; i.e. applies its effect
//
// Arguments:
//   None
// 
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Scroll::use() {
    //std::cout << "use: scroll used" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the item class of a scroll.
// 
// Arguments:
//   None
//
// Returns:
//   SCROLL_CLASS
//----------------------------------------------------------------------------
int Scroll::get_item_class() {
    return ItemConsts::SCROLL_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to potions to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Scroll::dump_item() {
    dump_item_common();
    std::cout << "====== Scroll Specific ===================" << std::endl;
    std::cout << "Type:      " << type_id << std::endl;
    std::cout << "Effect ID: " << effect_id << " (expanded form TBD)" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the scroll's type name
// 
// Arguments:
//   None
//
// Returns:
//   A string containing the scroll type ('Scroll')
//----------------------------------------------------------------------------
std::string Scroll::get_type_name() {
    return "Scroll";
}

//==================================================================
// Artifact
//==================================================================

//----------------------------------------------------------------------------
// Initializes an Artifact using an entry from the artifact type table
//
// Arguments: 
//   b - a pointer to an entry in the artifact type table
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Artifact::init(ArtifactType *b) {
    // Assign the fields from the potion type here
    id = b->id;
    name = b->name;
    description = b->description;
    gid = b->gid;
    type_id = b->type_id;
    pieces = b->pieces;
    effect_id = b->effect_id;
    rarity = b->rarity;
    ilevel = b->ilevel;
    can_be_cursed = b->can_be_cursed;
    can_have_prefix = b->can_have_prefix;
    can_have_suffix = b->can_have_suffix;
    can_stack = b->can_stack;
    can_equip = b->can_equip;
    can_drop = b->can_drop;
    can_use = b->can_use;
    is_identified = false;
    quantity = 1;
}

//----------------------------------------------------------------------------
// Initializes an Artifact using an index into the artifact type table
//
// Arguments:
//   idx - the index into the artifact type table
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Artifact::init(int idx) {
    init(&(g_artifact_ids[idx]));
}

//----------------------------------------------------------------------------
// Artifact::Artifact
//
// Constructor.
//
// Constructs a dummy item with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Artifact::Artifact() {
    //std::cout << "Creating artifact" << std::endl;
    ArtifactType *b = &(g_artifact_ids[0]);
    init(b);
}

//----------------------------------------------------------------------------
// Artifact::Artifact
//
// Constructor.
//
// Constructs using a pointer to an entry in the artifacts table
//----------------------------------------------------------------------------
Artifact::Artifact(ArtifactType *b) {
    //std::cout << "Creating artifact" << std::endl;
    init(b);
}

//----------------------------------------------------------------------------
// Artifact::Artifact
//
// Constructor.
//
// Constructs using an offset (relative to to the artifacts table).
//----------------------------------------------------------------------------
Artifact::Artifact(unsigned int idx) {
    ArtifactType *b = &(g_artifact_ids[idx]);
    init(b);
}

//----------------------------------------------------------------------------
// Gets the item class of an artifact.
// 
// Arguments:
//   None
//
// Returns:
//   ARTIFACT_CLASS
//----------------------------------------------------------------------------
int Artifact::get_item_class() {
    return ItemConsts::ARTIFACT_CLASS;
}

//----------------------------------------------------------------------------
// Dumps information specific to artifacts to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Artifact::dump_item() {
    dump_item_common();
    std::cout << "====== Artifact Specific ===================" << std::endl;
    std::cout << "Type: ";
    if(type_id == ItemConsts::STANDARD_ARTIFACT) {
        std::cout << "Standard" << std::endl;
    } 
    else if (type_id == ItemConsts::MULTIPART_ARTIFACT) {
        std::cout << "Multipart: (" << pieces << " parts)" << std::endl;
    }
    else if (type_id == ItemConsts::MULTIGEN_ARTIFACT) {
        std::cout << "Multi-generation (" << pieces << " generations)" << std::endl;
    }
    std::cout << "Effect ID: " << effect_id << " (expanded form TBD)" << std::endl;
}

//----------------------------------------------------------------------------
// Gets the arftifact's full name
// 
// Arguments:
//   None
//
// Returns:
//   A string containing the full name of the artifact (which is just the 
//   type name)
//----------------------------------------------------------------------------
std::string Artifact::get_full_name() {
    return get_type_name();
}

//----------------------------------------------------------------------------
// Gets the artifact's type name
// 
// Arguments:
//   None
//
// Returns:
//   A string containing the type name
//----------------------------------------------------------------------------
std::string Artifact::get_type_name() {
    return name;
}