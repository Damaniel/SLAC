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

#include "globals.h"

Inventory *g_inventory;
std::vector<int> g_scrambled_potion_icons;
std::vector<int> g_scrambled_scroll_icons;
std::vector<bool> g_identified_potions;
std::vector<bool> g_identified_scrolls;

unsigned short g_collected_artifacts[NUM_ARTIFACTS];
unsigned short g_active_artifacts[NUM_ARTIFACTS];

//==================================================================
// Non-inventory class item functions
//==================================================================

//----------------------------------------------------------------------------
// Copies all artifacts the player has collected in this run to the 
// running artifact total.  
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//
// Notes:  artifacts 
//----------------------------------------------------------------------------
void move_new_artifacts_to_existing(void) {
    for (int i=0; i < NUM_ARTIFACTS; i++) {
        if (i >= MULTIGEN_ARTIFACT_OFFSET) {
            if (g_collected_artifacts[i] > 0) {
                g_active_artifacts[i] += 1;
            }
        }
        else {
            g_active_artifacts[i] += g_collected_artifacts[i];
        }
        g_collected_artifacts[i] = 0;
    }
}

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
    if (item->can_stack == false) {
        return -1;
    }

    // Iterate through the inventory.  If an item with the same gid 
    // is found in a slot, return the slot number.  Otherwise,
    // return -1.
    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        if(inv[i] != NULL) {
            if (item->gid == inv[i]->gid) {
                return i;
            }
        }
    }
    
    // There's no existing stackable item in the inventory.
    return -1;
}

//----------------------------------------------------------------------------
// Determines which inventory slot a particular Item * represents
//
// Arguments: 
//   i - the item to check
//
// Returns:
//   The inventory slot number, or -1 if not in the inventory
//----------------------------------------------------------------------------
int Inventory::get_slot_of_item(Item *i) {
    if (i == NULL)
        return -1;

    for (int idx = 0; idx < InventoryConsts::INVENTORY_SIZE; ++idx) {
        if (i == inv[idx])
            return idx;
    }
    return -1;
}

//----------------------------------------------------------------------------
// Clears an existing item slot (after a transfer to somewhere else)
//
// Arguments: 
//   slot - the slot of the item to clear out
//
// Returns:
//----------------------------------------------------------------------------
void Inventory::remove_item_in_slot(int slot) {
    inv[slot] = NULL;
}

//==================================================================
// Item
//==================================================================

//----------------------------------------------------------------------------
// Dumps item information to the console.
//
// Arguments:
//   None
//
// Returns:
//   None
//----------------------------------------------------------------------------
void Item::dump_item(void) {
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

    switch (item_class) {
        case ItemConsts::WEAPON_CLASS:
            std::cout << "====== Weapon Specific ===================" << std::endl;
            std::cout << "Type:      " << g_weapon_type_ids[g_weapon_base_ids[id].type_id].name << std::endl;
            std::cout << "Attack:    " << attack << std::endl;
            std::cout << "Cursed:    " << is_cursed << std::endl;
            dump_prefix();
            dump_suffix();
            break;
        case ItemConsts::ARMOR_CLASS:
            std::cout << "====== Armor Specific ===================" << std::endl;
            std::cout << "Type:      " << g_armor_type_ids[g_armor_base_ids[id].type_id].name << std::endl;
            std::cout << "Defense:    " << defense << std::endl;
            std::cout << "Cursed:    " << is_cursed << std::endl;
            dump_prefix();
            dump_suffix();
            break;
        case ItemConsts::CURRENCY_CLASS:
            std::cout << "====== Currency Specific ===================" << std::endl;
            std::cout << "  Nothing yet" << std::endl;
            break;
        case ItemConsts::POTION_CLASS:
            std::cout << "====== Armor Specific ===================" << std::endl;
            std::cout << "Type:      " << type_id << std::endl;
            std::cout << "Effect ID: " << effect_id << " (expanded form TBD)" << std::endl;
            break;
        case ItemConsts::SCROLL_CLASS:
            std::cout << "====== Scroll Specific ===================" << std::endl;
            std::cout << "Type:      " << type_id << std::endl;
            std::cout << "Effect ID: " << effect_id << " (expanded form TBD)" << std::endl;
            break;
        case ItemConsts::ARTIFACT_CLASS:
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
            break;
    }
}

//----------------------------------------------------------------------------
// Item::Item
//
// Constructor.
//
// Constructs a dummy item (weapon)with base id of zero.  This item will
// generally be something modified later using generate(). 
//----------------------------------------------------------------------------
Item::Item() {
    init (ItemConsts::WEAPON_CLASS, 0);
}

//----------------------------------------------------------------------------
// Item::Item
//
// Constructor.
//
// Constructs an item of a base type using the appropriate base type table
//----------------------------------------------------------------------------
Item::Item(int item_class, int idx) {
    init(item_class, idx);
}

//----------------------------------------------------------------------------
// Item::Item
//
// Constructor.
//
// Constructs a generic item of a base type using the appropriate base type table
//----------------------------------------------------------------------------
Item::Item(int item_class) {
    init(item_class, 0);
}

//----------------------------------------------------------------------------
// Gets the base name of the item type
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the base type name.
//----------------------------------------------------------------------------
std::string Item::get_type_name() {
    if (item_class == ItemConsts::CURRENCY_CLASS) {
        return "Currency";
    }
    else if (item_class == ItemConsts::SCROLL_CLASS) {
        return "Scroll";
    }
    else if (item_class == ItemConsts::POTION_CLASS) {
        return "Potion";
    }
    else {
        return name;
    }
}

//----------------------------------------------------------------------------
// Gets the full name of the item type.
//
// Arguments: 
//   None
//
// Returns:
//   A string containing the full item name.
//----------------------------------------------------------------------------
std::string Item::get_full_name() {
    std::string prefix_text;
    std::string suffix_text;

    if (item_class == ItemConsts::ARMOR_CLASS || item_class == ItemConsts::WEAPON_CLASS) 
    {
        if (is_identified) {
            if (can_have_prefix && prefix_id >= 0) {
                if (is_cursed) 
                    prefix_text = g_cursed_item_prefix_ids[prefix_id].name + " ";        

                else
                    prefix_text = g_item_prefix_ids[prefix_id].name + " ";        
            }
            else {
                prefix_text = "";
            }
            if (can_have_suffix && suffix_id >= 0) {
                if (is_cursed)
                    suffix_text = " " + g_cursed_item_suffix_ids[suffix_id].name;
                else
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
    if (item_class == ItemConsts::POTION_CLASS || item_class == ItemConsts::SCROLL_CLASS) {
        if (is_identified) {
            return name;
        }
        else {
            return "(?) " + get_type_name();
        }
    }
    if (item_class == ItemConsts::CURRENCY_CLASS) {
        char name[32];
        sprintf(name, "%d gold worth of %s", quantity, (char *)g_currency_ids[id].name.c_str());
        return std::string(name);        
    }
    if (item_class == ItemConsts::ARTIFACT_CLASS) {
        return get_type_name();        
    }
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
void Item::dump_prefix() {
    if (item_class == ItemConsts::ARMOR_CLASS || item_class == ItemConsts::WEAPON_CLASS) {
        if (can_have_prefix && prefix_id >= 0) {
            ItemPrefixType *it;
            if (is_cursed) {
                it = &(g_cursed_item_prefix_ids[prefix_id]);
            }
            else {
                it = &(g_item_prefix_ids[prefix_id]);
            }
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
void Item::dump_suffix() {
    if (item_class == ItemConsts::ARMOR_CLASS || item_class == ItemConsts::WEAPON_CLASS) {
        if (can_have_suffix && suffix_id >= 0) {
            ItemSuffixType *it;
            if (is_cursed) {
                it = &(g_cursed_item_suffix_ids[suffix_id]);
            }
            else {
                it = &(g_item_suffix_ids[suffix_id]);
            }
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
}

//----------------------------------------------------------------------------
// Initializes an item using an offset into the appropriate base table
//  table.
//
// Arguments: 
//   ic - the type of item to init
//   idx - the offset into the item type table to use
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void Item::init(int ic, int idx) {
    item_class = ic;
    WeaponBaseType *wb;
    ArmorBaseType *ab;
    CurrencyType *cb;
    ScrollType *sb;
    PotionType *pb;
    ArtifactType *arb;

    // set some default values common to all cases (or which are overriden)
    attack = -1;
    defense = -1;
    description = "";
    is_equipped = false;
    is_cursed = false;
    prefix_id = -1;
    suffix_id = -1;
    quantity = 1;
    is_identified = false;

    switch (item_class) {
        case ItemConsts::WEAPON_CLASS:
            wb = &(g_weapon_base_ids[idx]);
            // Assign the fields from the weapon base type here
            id = wb->id;
            name = wb->name;
            gid = wb->gid;
            type_id = wb->type_id;
            attack = wb->attack;
            rarity = wb->rarity;
            ilevel = wb->ilevel;
            value = wb->value;
            can_be_cursed = wb->can_be_cursed;
            can_have_prefix = wb->can_have_prefix;
            can_have_suffix = wb->can_have_suffix;
            can_stack = wb->can_stack;
            can_equip = wb->can_equip;
            can_drop = wb->can_drop;
            can_use = wb->can_use;
            break;
        case ItemConsts::ARMOR_CLASS:
            ab = &(g_armor_base_ids[idx]);
            id = ab->id;
            name = ab->name;
            gid = ab->gid;
            type_id = ab->type_id;
            defense = ab->defense;
            rarity = ab->rarity;
            ilevel = ab->ilevel;
            value = ab->value;
            can_be_cursed = ab->can_be_cursed;
            can_have_prefix = ab->can_have_prefix;
            can_have_suffix = ab->can_have_suffix;
            can_stack = ab->can_stack;
            can_equip = ab->can_equip;
            can_drop = ab->can_drop;
            can_use = ab->can_use;
            break;
        case ItemConsts::CURRENCY_CLASS:
            cb = &(g_currency_ids[idx]);
            id = cb->id;
            name = cb->name;
            gid = cb->gid;
            type_id = cb->type_id;
            rarity = cb->rarity;
            ilevel = cb->ilevel;
            value = cb->value;
            can_be_cursed = cb->can_be_cursed;
            can_have_prefix = cb->can_have_prefix;
            can_have_suffix = cb->can_have_suffix;
            can_stack = cb->can_stack;
            can_equip = cb->can_equip;
            can_drop = cb->can_drop;
            can_use = cb->can_use;
            is_identified = true;
            quantity = cb->value * (rand() % 50 + 1);    
            break;
        case ItemConsts::POTION_CLASS:
            pb = &(g_potion_ids[idx]);
            id = pb->id;
            name = pb->name;
            description = pb->description;
            gid = pb->gid;
            type_id = pb->type_id;
            effect_id = pb->effect_id;
            rarity = pb->rarity;
            ilevel = pb->ilevel;
            value = pb->value;
            can_be_cursed = pb->can_be_cursed;
            can_have_prefix = pb->can_have_prefix;
            can_have_suffix = pb->can_have_suffix;
                can_stack = pb->can_stack;
            can_equip = pb->can_equip;
            can_drop = pb->can_drop;
            can_use = pb->can_use;
            is_identified = g_identified_potions[id];
            break;
        case ItemConsts::SCROLL_CLASS:
            sb = &(g_scroll_ids[idx]);
            id = sb->id;
            name = sb->name;
            description = sb->description;
            gid = sb->gid;
            type_id = sb->type_id;
            effect_id = sb->effect_id;
            rarity = sb->rarity;
            ilevel = sb->ilevel;
            value = sb->value;
            can_be_cursed = sb->can_be_cursed;
            can_have_prefix = sb->can_have_prefix;
            can_have_suffix = sb->can_have_suffix;
            can_stack = sb->can_stack;
            can_equip = sb->can_equip;
            can_drop = sb->can_drop;
            can_use = sb->can_use;
            is_identified = g_identified_scrolls[id];
            quantity = 1;
            break;
        case ItemConsts::ARTIFACT_CLASS:
            arb = &(g_artifact_ids[idx]);
            id = arb->id;
            name = arb->name;
            description = arb->description;
            gid = arb->gid;
            type_id = arb->type_id;
            pieces = arb->pieces;
            effect_id = arb->effect_id;
            rarity = arb->rarity;
            ilevel = arb->ilevel;
            can_be_cursed = arb->can_be_cursed;
            can_have_prefix = arb->can_have_prefix;
            can_have_suffix = arb->can_have_suffix;
            can_stack = arb->can_stack;
            can_equip = arb->can_equip;
            can_drop = arb->can_drop;
            can_use = arb->can_use;
            is_identified = true;
            break;
    }
}

//----------------------------------------------------------------------------
// 'Uses' the item; i.e. applies its effect
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void Item::use() {
    switch (item_class) {
        case ItemConsts::POTION_CLASS:
            g_text_log.put_line("You use the " + get_full_name() + ".");
            use_potion_action(id);
            //std::cout << "use: potion used" << std::endl;
            break;
        case ItemConsts::SCROLL_CLASS:
            g_text_log.put_line("You use the " + get_full_name() + ".");
            // Do the thing based on the particular item
            use_scroll_action(id);
            //std::cout << "use: scroll used" << std::endl;
            break;
    }
}

//----------------------------------------------------------------------------
// Non-class functions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Do all tasks related to identification.  This includes marking the 
// item as identified, marking all potions and scrolls of the identified type
// as identified, and optionally displaying a message to the log
//
// Arguments:
//   i - the item to identify
//   log - log to game log if true, don't log otherwise
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void perform_identification_action(Item *i, bool log) {
	std::string old_name = i->get_full_name();
                
	i->is_identified = true;
	if (i->item_class == ItemConsts::POTION_CLASS)
		g_identified_potions[i->id] = true;
	if (i->item_class == ItemConsts::SCROLL_CLASS)
		g_identified_scrolls[i->id] = true;
    if (log) {
        g_text_log.put_line(old_name + " is " + i->get_full_name() + ".");
    }
}

//----------------------------------------------------------------------------
// Gets the tile ID of the item to be rendered.  For most items, this is just
// the GID.  For scrolls and potions, the offset is stored in a list of
// scrambled tile IDs.
//
// Arguments:
//   i - the item to get the tile ID of
//
// Returns:
//   the tile ID
//----------------------------------------------------------------------------
int get_tile_to_render(Item *i) {

	if (i->item_class == ItemConsts::POTION_CLASS) {
		return g_scrambled_potion_icons[i->id];
	}
	else if (i->item_class == ItemConsts::SCROLL_CLASS) {
		return g_scrambled_scroll_icons[i->id];	
	}
	else {
		return i->gid;
	}
}

//----------------------------------------------------------------------------
// For any items sitting at the player's feet, identify them if they're a
// potion or scroll that has previously been identified
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void identify_previously_known_items_at_player() {
	int item_count = g_dungeon.get_num_items_at(g_player.get_x_pos(), g_player.get_y_pos());

	if (item_count > 0) {
		std::list<Item *> items = g_dungeon.get_items_at(g_player.get_x_pos(), g_player.get_y_pos());
		for (std::list<Item *>::iterator it = items.begin(); it != items.end(); ++ it) {
			identify_if_previously_known((*it));
		}
	}
}

//----------------------------------------------------------------------------
// Drops an item (throwing it on the ground)
//
// Arguments:
//   i - the item to drop
//   x, y - the location on the ground to drop it
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void drop_item_at(Item *i, int x, int y) {
	bool dropped = false;

	if(g_dungeon.maze->stairs_here(x, y) != MazeConsts::NO_STAIRS) {
		g_text_log.put_line("Unable to drop an item onto stairs.");
	}
	else {
		if (i != NULL) {
			g_text_log.put_line("Dropped the " + i->get_full_name() + ".");
			g_dungeon.add_item(x, y, i);
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_description = true;
		}
	}
}
