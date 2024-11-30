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

//------------------------------------------------------------------------------
// Player::Player
//
// Constructor.  Initializes the player at (0, 0).
//
// Arguments:
//   None
//------------------------------------------------------------------------------
Player::Player(void) {
	x_pos = 0;
	y_pos = 0;
	gold = 0;
	name = "Damaniel";
	generation = 1;
	level = 1;
	exp = 0;
	hp = 100;
	base.max_hp = 100;

	// Null out the item slots
	equipment.amulet = NULL;
	equipment.chest = NULL;
	equipment.feet = NULL;
	equipment.hands = NULL;
	equipment.head = NULL;
	equipment.legs = NULL;
	equipment.ring = NULL;
	equipment.shield = NULL;
	equipment.weapon = NULL;
}

//------------------------------------------------------------------------------
// Player::Player
//
// Constructor.  Initializes the player at the specified location
//
// Arguments:
//   x, y - the position to place the player
//------------------------------------------------------------------------------
Player::Player(int x, int y) {
	x_pos = x;
	y_pos = y;
}

//------------------------------------------------------------------------------
// sets the player's position
//
// Arguments:
//   x, y - the player's new position
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_position(int x, int y) {
	x_pos = x;
	y_pos = y;
}

//------------------------------------------------------------------------------
// Gets the player's x position
// 
// Arguments:
//   None
//
// Returns:
//   The player's x position
//------------------------------------------------------------------------------
int Player::get_x_pos() {
	return x_pos;
}

//------------------------------------------------------------------------------
// Gets the player's y position
// 
// Arguments:
//   None
//
// Returns:
//   The player's y position
//------------------------------------------------------------------------------
int Player::get_y_pos() {
	return y_pos;
}

//------------------------------------------------------------------------------
// Sets the player's x position
// 
// Arguments:
//   pos - the position to set to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_x_pos(int pos) {
	x_pos = pos;
}

//------------------------------------------------------------------------------
// Sets the player's y position
// 
// Arguments:
//   pos - the position to set to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_y_pos(int pos) {
	y_pos = pos;
}

//------------------------------------------------------------------------------
// Adds to the player's copper stash
// 
// Arguments:
//   amount - the amount to add
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::add_gold(int amount) {
	gold += amount;
}

//------------------------------------------------------------------------------
// Retreives the player's gold
// 
// Arguments:
//   None
//
// Returns:
//   Amount of gold the player has
//------------------------------------------------------------------------------
int Player::get_gold(void) {
	return gold;
}

//------------------------------------------------------------------------------
// Gets a pointer to the item slot associated with the specified item type
// 
// Arguments:
//   type - the item (presumably equipment) type associated with a part
//
// Returns:
//   A pointer to the Item * of the slot, or NULL if the requested item
//   type doesn't correspond to a slot
//------------------------------------------------------------------------------
Item** Player::get_item_slot_by_type(int type) {
	Item **item_slot;

	switch (type) {
			case ItemConsts::ARMOR_TYPE_HAT:
			case ItemConsts::ARMOR_TYPE_HELM:
				//std::cout << "get_item_slot_by_type: Item is for head" << std::endl;
				item_slot = &(equipment.head);
				break;
			case ItemConsts::ARMOR_TYPE_GLOVES:
			case ItemConsts::ARMOR_TYPE_GAUNTLETS:
				//std::cout << "get_item_slot_by_type: Item is for hands" << std::endl;
				item_slot = &(equipment.hands);
				break;
			case ItemConsts::ARMOR_TYPE_SHIRT:
			case ItemConsts::ARMOR_TYPE_MAIL:
				//std::cout << "get_item_slot_by_type: Item is for chest" << std::endl;
				item_slot = &(equipment.chest);
				break;
			case ItemConsts::ARMOR_TYPE_PANTS:
			case ItemConsts::ARMOR_TYPE_LEGGINGS:
				//std::cout << "get_item_slot_by_type: Item is for legs" << std::endl;
				item_slot = &(equipment.legs);
				break;
			case ItemConsts::ARMOR_TYPE_SHOES:
			case ItemConsts::ARMOR_TYPE_BOOTS:
				//std::cout << "get_item_slot_by_type: Item is for feet" << std::endl;
				item_slot = &(equipment.feet);
				break;
			case ItemConsts::ARMOR_TYPE_BUCKLER:
			case ItemConsts::ARMOR_TYPE_SHIELD:
				//std::cout << "get_item_slot_by_type: Item is for shield slot" << std::endl;
				item_slot = &(equipment.shield);
				break;
			case ItemConsts::ARMOR_TYPE_RING:
				//std::cout << "get_item_slot_by_type: Item is for ring slot" << std::endl;
				item_slot = &(equipment.ring);
				break;
			case ItemConsts::ARMOR_TYPE_AMULET:
				//std::cout << "get_item_slot_by_type: Item is for amulet slot" << std::endl;
				item_slot = &(equipment.amulet);
				break;
			default:
				return NULL;
				break;
	}

	return item_slot;
}

//------------------------------------------------------------------------------
// Equips an item by attaching an item (presumably from the inventory) to the
// appropriate player equipment slot
// 
// Arguments:
//   i - the item (presumably equipment) type
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::equip(Item *i) {
	int item_type = i->get_item_class();
	Item **item_slot;

	// If not a weapon or armor, do nothing
	if (item_type != ItemConsts::WEAPON_CLASS && item_type != ItemConsts::ARMOR_CLASS) {
		return;
	}

	// If a weapon, get the weapon slot.  Otherwise, get the appropriate armor slot
	// based on what the item is
	if (item_type == ItemConsts::WEAPON_CLASS) {
		item_slot = &(equipment.weapon);
	}
	else {
		item_slot = get_item_slot_by_type(i->get_type_id());
		// If the item slot isn't empty, unequip it
		if (item_slot == NULL) {
			//std::cout << "equip: Not a valid item slot!" << std::endl;
			return;
		}
	}
	
	// Unequip any existing item if something is equipped (or no-op if nothing is there)
	unequip(i);

	// Attach the item to the slot and equip it
	//std::cout << "equip: Attaching item to item slot" << std::endl;
	if ((*item_slot == NULL) || !(*item_slot)->is_it_cursed()) {
		*item_slot = i;
		(*item_slot)->mark_equipped();
		g_text_log.put_line("Equipped the " + (*item_slot)->get_full_name() + ".");
		if ((*item_slot)->is_it_cursed()) {
			g_text_log.put_line("Oh no!  The " + (*item_slot)->get_full_name() + " is cursed!");
		}
		g_state_flags.update_text_dialog = true;	
		g_state_flags.update_display = true;
	}
	recalculate_actual_stats();
}

//------------------------------------------------------------------------------
// Removes an item by detaching an item (in the player's inventory, attached
// to the player) from the appropriate player equipment slot
// 
// Arguments:
//   i - the item (presumably equipment) type
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::unequip(Item *i) {
	int item_type = i->get_item_class();
	Item **item_slot;

	// Do nothing if not a weapon or armor
	if (item_type != ItemConsts::WEAPON_CLASS && item_type != ItemConsts::ARMOR_CLASS) {
		return;
	}

	// If a weapon, select the weapon slot, otherwise figure out what kind of armor
	// it is and select that slot
	if (item_type == ItemConsts::WEAPON_CLASS) {
		item_slot = &(equipment.weapon);
		//std::cout << "unequip: Item is a weapon" << std::endl;
	}
	else {
		//std::cout << "unequip: Item is an armor" << std::endl;
		item_slot = get_item_slot_by_type(i->get_type_id());
		// If the item slot isn't empty, unequip it
		if (item_slot == NULL) {
			//std::cout << "unequip: Invalid item slot!" << std::endl;
			return;
		}
	} 
	
	//std::cout << "unequip:  The item slot requested appears to be valid" << std::endl;

	// Free the item slot if it has an item and it isn't cursed.  
	// Note that the item still exists in the inventory so it's not actually deleted here.
	if (*item_slot != NULL) {
		// If the item is cursed, it can't be removed.
		if ((*item_slot)->is_it_cursed()) {
			g_text_log.put_line("Unfortunately you can't remove that.");
			g_text_log.put_line("The " + (*item_slot)->get_full_name() + " is cursed.");
			g_state_flags.update_text_dialog = true;
			g_state_flags.update_display = true;
			return;
		}
		//std::cout << "process_unequip: calling remove on item" << std::endl;
		g_text_log.put_line("Removed the " + (*item_slot)->get_full_name() + ".");
		g_state_flags.update_text_dialog = true;
		g_state_flags.update_display = true;
		(*item_slot)->mark_removed();
		//std::cout << "process_unequip:  Remove called" << std::endl;
		*item_slot = NULL;
	}

	recalculate_actual_stats();
}

//------------------------------------------------------------------------------
// Moves the player's base stats into their actual (computed) stats
// 
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::assign_base_stats_to_actual(void) {
	actual.apt = base.apt;
	actual.atk = base.atk;
	actual.block = base.block;
	actual.con = base.con;
	actual.def = base.def;
	actual.dex = base.dex;
	actual.f_atk = base.f_atk;
	actual.f_def = base.f_def;
	actual.i_atk = base.i_atk;
	actual.i_def = base.i_def;
	actual.l_atk = base.l_atk;
	actual.l_def = base.l_def;
	actual.max_hp = base.max_hp;
	actual.spd = base.spd;
	actual.str = base.str;
}

//------------------------------------------------------------------------------
// Takes a set of fixed and multiplicative stats and applies them to the 
// player's actual (computed) stats
// 
// Arguments:
//   fixed - a set of fixed stat values
//   multiplicative - a set of multiplicative stat values
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::apply_stats_to_actual(Stats &fixed, MultiplicativeStats &multiplicative) {
	// Additive first
	actual.apt += fixed.apt;
	actual.atk += fixed.atk;
	actual.block += fixed.block;
	actual.con += fixed.con;
	actual.def += fixed.def;
	actual.dex += fixed.dex;
	actual.f_atk += fixed.f_atk;
	actual.f_def += fixed.f_def;
	actual.i_atk += fixed.i_atk;
	actual.i_def += fixed.i_def;
	actual.l_atk += fixed.l_atk;
	actual.l_def += fixed.l_def;
	actual.max_hp += fixed.max_hp;
	actual.spd += fixed.spd;
	actual.str += fixed.str;

	// Then multiplicative
	actual.apt = (int)((float)actual.apt * multiplicative.apt);
	actual.atk = (int)((float)actual.atk * multiplicative.atk);
	actual.block = (int)((float)actual.block * multiplicative.block);	
	actual.con = (int)((float)actual.con * multiplicative.con);
	actual.def = (int)((float)actual.def * multiplicative.def);
	actual.dex = (int)((float)actual.dex * multiplicative.dex);
	actual.f_atk = (int)((float)actual.f_atk * multiplicative.f_atk);
	actual.f_def = (int)((float)actual.f_def * multiplicative.f_def);
	actual.i_atk = (int)((float)actual.i_atk * multiplicative.i_atk);
	actual.i_def = (int)((float)actual.i_def * multiplicative.i_def);
	actual.l_atk = (int)((float)actual.l_atk * multiplicative.l_atk);
	actual.l_def = (int)((float)actual.l_def * multiplicative.l_def);
	actual.max_hp = (int)((float)actual.max_hp * multiplicative.max_hp);
	actual.spd = (int)((float)actual.spd * multiplicative.spd);
	actual.str = (int)((float)actual.str * multiplicative.str);
}

//------------------------------------------------------------------------------
// Iterates through all equipped items and used items with active effects,
// calculating what the player's modified (that is, actual) stats are.
// 
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::recalculate_actual_stats(void) {
	Stats fixed;
	MultiplicativeStats multiplicative;

	//std::cout << "recalculate_actual_stats:  performing recalculation" << std::endl;

	// Assign the base stat values to the actual stats
	assign_base_stats_to_actual();

	// Iterate through the player's equipped items, adding fixed and multiplicitive 
	// totals
	if(equipment.amulet != NULL) 
		apply_item_values_to_stats(equipment.amulet, fixed, multiplicative);
	if(equipment.chest != NULL)
		apply_item_values_to_stats(equipment.chest, fixed, multiplicative);
	if(equipment.feet != NULL)
		apply_item_values_to_stats(equipment.feet, fixed, multiplicative);
	if(equipment.hands != NULL)
		apply_item_values_to_stats(equipment.hands, fixed, multiplicative);
	if(equipment.head != NULL)
		apply_item_values_to_stats(equipment.head, fixed, multiplicative);
	if(equipment.legs != NULL)
		apply_item_values_to_stats(equipment.legs, fixed, multiplicative);
	if(equipment.ring != NULL)
		apply_item_values_to_stats(equipment.ring, fixed, multiplicative);
	if(equipment.shield != NULL)
		apply_item_values_to_stats(equipment.shield, fixed, multiplicative);
	if(equipment.weapon != NULL)
		apply_item_values_to_stats(equipment.weapon, fixed, multiplicative);

	// Add together all increases from item effects and save them
	// TODO - get item effects up and running

	// Add all of the fixed increases to the actual stats
	apply_stats_to_actual(fixed, multiplicative);

	//std::cout << "Finished" << std::endl;
}

