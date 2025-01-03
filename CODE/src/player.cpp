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
	init(0, 0);
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
	init(x, y);
}

//------------------------------------------------------------------------------
// Player::init
//
// Sets basic values for a new player
//
// Arguments:
//   x, y - the position to place the player
//------------------------------------------------------------------------------
void Player::init(int x, int y) {
	x_pos = x;
	y_pos = y;
	gold = 0;
	name = "Damaniel";
	generation = 1;
	level = 1;
	exp = 0;
	residual_action_points = 0;

	init_base_stats();
	// Move a copy of the base stats into the actual stats
	assign_base_stats_to_actual();

	effects.auto_identify = false;
	effects.bragging_rights = false;
	effects.permanent_decurse = false;
	effects.permanent_discovery = false;

	// Set the base HP
	hp = (int)base.max_hp;

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
			case ItemConsts::WEAPON_TYPE_AXE:
			case ItemConsts::WEAPON_TYPE_BATTLEAXE:
			case ItemConsts::WEAPON_TYPE_BROADSWORD:
			case ItemConsts::WEAPON_TYPE_DAGGER:
			case ItemConsts::WEAPON_TYPE_MACE:
			case ItemConsts::WEAPON_TYPE_MAUL:
			case ItemConsts::WEAPON_TYPE_SWORD:
				//std::cout << "get_item_slot_by_type: Item is for weapon" << std::endl;
				item_slot = &(equipment.weapon);
				break;
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
	int item_class = i->get_item_class();
	Item **item_slot;
	Item **extra_slot;

	// If not a weapon or armor, do nothing
	if (item_class != ItemConsts::WEAPON_CLASS && item_class != ItemConsts::ARMOR_CLASS) {
		return;
	}

	int item_type = i->get_type_id();

	// If a weapon, get the weapon slot.  Otherwise, get the appropriate armor slot
	// based on what the item is
	if (item_class == ItemConsts::WEAPON_CLASS) {
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
	
	// If the item to equip is a shield and a two handed weapon is equipped, then 
	// unequip the weapon 
	if (item_type == ItemConsts::ARMOR_TYPE_SHIELD || item_type == ItemConsts::ARMOR_TYPE_BUCKLER) {
		extra_slot = &(equipment.weapon);
		if (*extra_slot != NULL) {
			int extra_type = (*extra_slot)->get_type_id();
			if (extra_type == ItemConsts::WEAPON_TYPE_BATTLEAXE || 
			    extra_type == ItemConsts::WEAPON_TYPE_BROADSWORD ||
				extra_type == ItemConsts::WEAPON_TYPE_MAUL) {
					unequip(extra_slot);
				}			
		}
	}	

	// If the item to equip is a two-handed weapon and a shield is equipped, then
	// unequip the shield
	if (item_type == ItemConsts::WEAPON_TYPE_BATTLEAXE ||
	    item_type == ItemConsts::WEAPON_TYPE_BROADSWORD ||
		item_type == ItemConsts::WEAPON_TYPE_MAUL) {
		extra_slot = &(equipment.shield);
		if (*extra_slot != NULL) {
			unequip(extra_slot);
		}
	}

	// Unequip any existing item if something is equipped (or no-op if nothing is there)
	if (*item_slot != NULL) 
		unequip(item_slot);

	// Attach the item to the slot and equip it
	//std::cout << "equip: Attaching item to item slot" << std::endl;
	if ((*item_slot == NULL) || !(*item_slot)->is_it_cursed()) {
		*item_slot = i;
		(*item_slot)->mark_equipped();
		g_text_log.put_line("Equipped the " + (*item_slot)->get_full_name() + ".");
		if ((*item_slot)->is_it_cursed()) {
			g_text_log.put_line("Oh no!  The " + (*item_slot)->get_full_name() + " is cursed!");
		}
	}
	recalculate_actual_stats();
}

//------------------------------------------------------------------------------
// Removes an item by detaching an item (in the player's inventory, attached
// to the player) from the appropriate player equipment slot
// 
// Arguments:
//   slot - the item slot
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::unequip(Item **slot) {
	// Free the item slot if it has an item and it isn't cursed.  
	// Note that the item still exists in the inventory so it's not actually deleted here.
	// If the item is cursed, it can't be removed.
	if ((*slot)->is_it_cursed()) {
		g_text_log.put_line("Unfortunately you can't remove that.");
		g_text_log.put_line("The " + (*slot)->get_full_name() + " is cursed.");
		return;
	}
	//std::cout << "process_unequip: calling remove on item" << std::endl;
	g_text_log.put_line("Removed the " + (*slot)->get_full_name() + ".");
	(*slot)->mark_removed();
	//std::cout << "process_unequip:  Remove called" << std::endl;
	*slot = NULL;
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
	actual.f_dmg = base.f_dmg;
	actual.i_atk = base.i_atk;
	actual.i_def = base.i_def;
	actual.i_dmg = base.i_dmg;
	actual.l_atk = base.l_atk;
	actual.l_def = base.l_def;
	actual.l_dmg = base.l_dmg;
	actual.a_dmg = base.a_dmg;
	actual.max_hp = base.max_hp;
	actual.spd = base.spd;
	actual.str = base.str;
	actual.gold_drop = base.gold_drop;
	actual.max_f_def = base.max_f_def;
	actual.max_i_def = base.max_i_def;
	actual.max_l_def = base.max_l_def;
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
void Player::apply_stats_to_actual(Stats *fixed, Stats *multiplicative) {
	// Additive first
	actual.apt += fixed->apt;
	actual.atk += fixed->atk;
	actual.block += fixed->block;
	actual.gold_drop += fixed->gold_drop;
	actual.max_f_def += fixed->max_f_def;
	actual.max_i_def += fixed->max_i_def;
	actual.max_l_def += fixed->max_l_def;
	actual.con += fixed->con;
	actual.def += fixed->def;
	actual.dex += fixed->dex;
	actual.f_atk += fixed->f_atk;
	actual.f_def += fixed->f_def;
	actual.f_dmg += fixed->f_dmg;
	actual.i_atk += fixed->i_atk;
	actual.i_def += fixed->i_def;
	actual.i_dmg += fixed->i_dmg;
	actual.l_atk += fixed->l_atk;
	actual.l_def += fixed->l_def;
	actual.l_dmg += fixed->l_dmg;
	actual.a_dmg += fixed->a_dmg;
	actual.max_hp += fixed->max_hp;
	actual.spd += fixed->spd;
	actual.str += fixed->str;

	// // Then multiplicative
	actual.apt = actual.apt * multiplicative->apt;
	actual.atk = actual.atk * multiplicative->atk;
	actual.block = actual.block * multiplicative->block;	
	actual.gold_drop = actual.gold_drop * multiplicative->gold_drop;
	actual.max_f_def = actual.max_f_def * multiplicative->max_f_def;
	actual.max_i_def = actual.max_i_def * multiplicative->max_i_def;
	actual.max_l_def = actual.max_l_def * multiplicative->max_l_def;
	actual.con = actual.con * multiplicative->con;
	actual.def = actual.def * multiplicative->def;
	actual.dex = actual.dex * multiplicative->dex;
	actual.f_atk = actual.f_atk * multiplicative->f_atk;
	actual.f_def = actual.f_def * multiplicative->f_def;
	actual.f_dmg = actual.f_dmg * multiplicative->f_dmg;
	actual.i_atk = actual.i_atk * multiplicative->i_atk;
	actual.i_def = actual.i_def * multiplicative->i_def;
	actual.i_dmg = actual.i_dmg * multiplicative->i_dmg;
	actual.l_atk = actual.l_atk * multiplicative->l_atk;
	actual.l_def = actual.l_def * multiplicative->l_def;
	actual.l_dmg = actual.l_dmg * multiplicative->l_dmg;
	actual.a_dmg = actual.a_dmg * multiplicative->a_dmg;
	actual.max_hp = actual.max_hp * multiplicative->max_hp;
	actual.spd = actual.spd * multiplicative->spd;
	actual.str = actual.str * multiplicative->str;

	// Handle cap/overflow of elemental defense
	if (actual.max_f_def >= PlayerConsts::MAX_ELEM_DEF)
		actual.max_f_def = PlayerConsts::MAX_ELEM_DEF;
	if (actual.max_i_def >= PlayerConsts::MAX_ELEM_DEF)
		actual.max_i_def = PlayerConsts::MAX_ELEM_DEF;
	if (actual.max_l_def >= PlayerConsts::MAX_ELEM_DEF)
		actual.max_l_def = PlayerConsts::MAX_ELEM_DEF;
	if (actual.f_def >= actual.max_f_def)
		actual.f_def = actual.max_f_def;
	if (actual.i_def >= actual.max_i_def)
		actual.i_def = actual.max_i_def;
	if (actual.l_def >= actual.max_l_def)
		actual.l_def = actual.max_l_def;
}

//------------------------------------------------------------------------------
// Initializes all of the values of a fixed and multiplicative stats table set
// 
// Arguments:
//   f - a set of fixed stat values
//   m - a set of multiplicative stat values
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::init_temp_stats(Stats *f, Stats *m) {

	f->apt = 0;
	f->atk = 0;
	f->block = 0;
	f->con = 0;
	f->def = 0;
	f->dex = 0;
	f->f_atk = 0;
	f->f_def = 0;
	f->f_dmg = 0;
	f->i_atk = 0;
	f->i_def = 0;
	f->i_dmg = 0;
	f->l_atk = 0;
	f->l_def = 0;
	f->l_dmg = 0;
	f->a_dmg = 0;
	f->max_hp = 0;
	f->spd = 0;
	f->str = 0;
	f->gold_drop = 1.0;
	f->max_f_def = 0;
	f->max_i_def = 0;
	f->max_l_def = 0;

	m->apt = 1.0;
	m->atk = 1.0;
	m->block = 1.0;
	m->con = 1.0;
	m->def = 1.0;
	m->dex = 1.0;
	m->f_atk = 1.0;
	m->f_def = 1.0;
	m->f_dmg = 1.0;
	m->i_atk = 1.0;
	m->i_def = 1.0;
	m->i_dmg = 1.0;
	m->l_atk = 1.0;
	m->l_def = 1.0;
	m->l_dmg = 1.0;
	m->a_dmg = 1.0;
	m->max_hp = 1.0;
	m->spd = 1.0;
	m->str = 1.0;
	m->gold_drop = 1.0;
	f->max_f_def = 1.0;
	f->max_i_def = 1.0;
	f->max_l_def = 1.0;
}

//------------------------------------------------------------------------------
// Iterates through all equipped items, artifacts and used items with active effects,
// calculating what the player's modified (that is, actual) stats are.
// 
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------q
void Player::recalculate_actual_stats(void) {
	Stats fixed;
	Stats multiplicative;
	std::vector<ModifierMagType> type_2_mods;

	//std::cout << "recalculate_actual_stats:  performing recalculation" << std::endl;

	// Assign the base stat values to the actual stats
	assign_base_stats_to_actual();

	// reset the two temporary stat tables
	init_temp_stats(&fixed, &multiplicative);

	//std::cout << "recalculate_actual_stats: before" << std::endl;
	//dump_stats(&actual);

	// Iterate through the player's equipped items, adding fixed and multiplicitive 
	// totals
	if(equipment.amulet != NULL) {
		apply_item_values_to_stats(equipment.amulet, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.chest != NULL) {
		apply_item_values_to_stats(equipment.chest, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.feet != NULL) {
		apply_item_values_to_stats(equipment.feet, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.hands != NULL) {
		apply_item_values_to_stats(equipment.hands, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.head != NULL) {
		apply_item_values_to_stats(equipment.head, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.legs != NULL) {
		apply_item_values_to_stats(equipment.legs, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.ring != NULL) {
		apply_item_values_to_stats(equipment.ring, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.shield != NULL) {
		apply_item_values_to_stats(equipment.shield, &fixed, &multiplicative, type_2_mods);
	}
	if(equipment.weapon != NULL) {
		apply_item_values_to_stats(equipment.weapon, &fixed, &multiplicative, type_2_mods);
	}

	// TODO - get item effects up and running

	// Apply all of the artifact effects for each quantity of collected artifact
	apply_artifact_mods(&fixed, &multiplicative);

	// Add all of the fixed/mutiplicative increases to the actual stats
	apply_stats_to_actual(&fixed, &multiplicative);

	// Finally, apply all type 2 modifiers (take x% of something as something else)
	// for any items that have them.
	for (std::vector<ModifierMagType>::iterator it = type_2_mods.begin(); it != type_2_mods.end(); ++it) {
		apply_mode_2_modifier_value(*it);
	}

	// Our HP vs max HP may have changed; update the display.
	g_state_flags.update_status_hp_exp = true;
	g_state_flags.update_display = true;

	//std::cout << "recalculate_actual_stats: after" << std::endl;
	//dump_stats(&actual);

	//std::cout << "Finished" << std::endl;
}

//------------------------------------------------------------------------------
// Adds experience to the player's experience pool, leveling up if needed
//
// Arguments:
//   quantity - the amount of experience to add
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::apply_experience(int quantity) {
	exp += quantity;

	//std::cout << "exp = " << exp << ", next level = " << PlayerConsts::g_player_exp_table[level] << std::endl;
	// Check the total experience to the table and level up if ready
	if (exp >= PlayerConsts::g_player_exp_table[level]) {
		level_up();
	}
}

//------------------------------------------------------------------------------
// Performs level up tasks (assigns new base stats, recalculates actual stats)
//
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::level_up() {
	char text[40];
	level += 1;

	base.max_hp = PlayerConsts::g_player_base_stats[level - 1].max_hp;
	base.str = PlayerConsts::g_player_base_stats[level - 1].str;
	base.con = PlayerConsts::g_player_base_stats[level - 1].con;
	base.dex = PlayerConsts::g_player_base_stats[level - 1].dex;
	base.atk = PlayerConsts::g_player_base_stats[level - 1].atk;
	base.def = PlayerConsts::g_player_base_stats[level - 1].def;
	base.spd = PlayerConsts::g_player_base_stats[level - 1].spd;

	recalculate_actual_stats();
	
	// Refill the player's health now that we've recalculated
	hp = (unsigned short)base.max_hp;

	sprintf(text, "You have reached level %d!", level);
	g_text_log.put_line(text);
	g_state_flags.update_status_dialog = true;
	g_state_flags.update_status_hp_exp = true;
	g_state_flags.update_display = true;
}

//------------------------------------------------------------------------------
// Returns the required amount of experience required for the next level
// threshold
//
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
float Player::pct_exp_to_next_level() {
	int cur = exp - PlayerConsts::g_player_exp_table[level - 1];
	int next = PlayerConsts::g_player_exp_table[level] - PlayerConsts::g_player_exp_table[level - 1];

	//std::cout << "pct_exp_to_next_level: " << cur << ", " << next << ", " << (float)((float)cur / (float)next) << std::endl;
	return (float)((float)cur / (float)next);
}

//------------------------------------------------------------------------------
// Sets the player's base stats to defaults
// 
// Arguments:
//   None
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::init_base_stats() {
	base.max_hp = PlayerConsts::g_player_base_stats[0].max_hp;
	base.str = PlayerConsts::g_player_base_stats[0].str;
	base.con = PlayerConsts::g_player_base_stats[0].con;
	base.dex = PlayerConsts::g_player_base_stats[0].dex;
	base.atk = PlayerConsts::g_player_base_stats[0].atk;
	base.def = PlayerConsts::g_player_base_stats[0].def;
	base.spd = PlayerConsts::g_player_base_stats[0].spd;
	base.f_def = 0;
	base.i_def = 0;
	base.l_def = 0;
	base.max_f_def = 80;
	base.max_i_def = 80;
	base.max_l_def = 80;
	base.f_atk = 0;
	base.i_atk = 0;
	base.l_atk = 0;
	base.f_dmg = 1.0;
	base.i_dmg = 1.0;
	base.l_dmg = 1.0;
	base.a_dmg = 1.0;
	base.apt = 1;
	base.block = 0;
}

//----------------------------------------------------------------------------
// Iterates through all active artifacts and applies their effects to the
// player's stats
//
// Arguments:
//   p - the player
//   fixed - fixed stats
//
// Returns:
//   Nothing
//
// Notes:  This code is ugly since it uses 70 magic numbers and assumes the
// artifacts are in a particular order.  If this is a problem in the future,
// then future me will deal with it then.
//----------------------------------------------------------------------------
void Player::apply_artifact_mods(Stats *fixed, Stats *multiplicative) {

    //------------------------------------------
    // Single piece
    //------------------------------------------

    fixed->str += g_active_artifacts[0];    // Sign of Strength
    fixed->con += g_active_artifacts[1];    // Sign of Constitution
    fixed->dex += g_active_artifacts[2];    // Sign of Dexterity
    fixed->atk += g_active_artifacts[3];    // Sign of Attack
    fixed->def += g_active_artifacts[4];    // Sign of Defense
    // Sign of accuracy currently does nothing
    fixed->spd += g_active_artifacts[6];    // Sign of Speed
    
    fixed->str += (g_active_artifacts[7] * 2);    // Medal of Strength
    fixed->con += (g_active_artifacts[8] * 2);    // Medal of Constitution
    fixed->dex += (g_active_artifacts[9] * 2);    // Medal of Dexterity
    fixed->atk += (g_active_artifacts[10] * 2);   // Medal of Attack
    fixed->def += (g_active_artifacts[11] * 2);   // Medal of Defense
    // Medal of accuracty currently does nothing
    fixed->spd += (g_active_artifacts[13] * 2);   // Medal of Speed

    fixed->str += (g_active_artifacts[14] * 3);   // Trophy of Strength
    fixed->con += (g_active_artifacts[15] * 3);   // Trophy of Constitution
    fixed->dex += (g_active_artifacts[16] * 3);   // Trophy of Dexterity
    fixed->atk += (g_active_artifacts[17] * 3);   // Trophy of Attack
    fixed->def += (g_active_artifacts[18] * 3);   // Trophy of Defense
    // Trophy of accuracy currently does nothing
    fixed->spd += (g_active_artifacts[20] * 3);   // Trophy of Speed

    fixed->f_def += g_active_artifacts[21];         // Ward of Fire
    fixed->i_def += g_active_artifacts[22];         // Ward of Ice
    fixed->l_def += g_active_artifacts[23];         // Ward of Lightning
    fixed->f_def += (g_active_artifacts[24] * 2);   // Sigil of Fire
    fixed->i_def += (g_active_artifacts[25] * 2);   // Sigil of Ice
    fixed->l_def += (g_active_artifacts[26] * 2);   // Sigil of Lightning
    fixed->f_def += (g_active_artifacts[27] * 3);   // Relic of Fire
    fixed->i_def += (g_active_artifacts[28] * 3);   // Relic of Ice
    fixed->l_def += (g_active_artifacts[29] * 3);   // Relic of Lightning'

    fixed->gold_drop += (g_active_artifacts[30] * 0.01);    // Lucky Token
    fixed->gold_drop += (g_active_artifacts[31] * 0.02);    // Lucky Coin
    fixed->gold_drop += (g_active_artifacts[32] * 0.03);    // Lucky Pendant

    //------------------------------------------
    // Multi-piece
    //------------------------------------------
    int effect_quantity;

    // Book of the Warrior
    effect_quantity = g_active_artifacts[33] / g_artifact_ids[33].pieces;
    fixed->str += effect_quantity;
    fixed->con += effect_quantity;
    // Book of the Thief
    effect_quantity = g_active_artifacts[34] / g_artifact_ids[34].pieces;
    fixed->spd += effect_quantity;
    fixed->dex += effect_quantity;
    // Book of the Combatant
    effect_quantity = g_active_artifacts[35] / g_artifact_ids[35].pieces;
    fixed->atk += effect_quantity;
    fixed->def += effect_quantity;
    // Tome of the Warrior
    effect_quantity = g_active_artifacts[36] / g_artifact_ids[36].pieces;
    fixed->str += effect_quantity * 2;
    fixed->con += effect_quantity * 2;
    // Tome of the Thief
    effect_quantity = g_active_artifacts[37] / g_artifact_ids[37].pieces;
    fixed->spd += effect_quantity * 2;
    fixed->dex += effect_quantity * 2;
    // Tome of the Combatant
    effect_quantity = g_active_artifacts[38] / g_artifact_ids[38].pieces;
    fixed->atk += effect_quantity * 2;
    fixed->def += effect_quantity * 2;
    // Bible of the Warrior
    effect_quantity = g_active_artifacts[39] / g_artifact_ids[39].pieces;
    fixed->str += effect_quantity * 3;
    fixed->con += effect_quantity * 3;
    // Bible of the Thief
    effect_quantity = g_active_artifacts[40] / g_artifact_ids[40].pieces;
    fixed->spd += effect_quantity * 3;
    fixed->dex += effect_quantity * 3;
    // Bible of the Combatant
    effect_quantity = g_active_artifacts[41] / g_artifact_ids[41].pieces;
    fixed->atk += effect_quantity * 3;
    fixed->def += effect_quantity * 3;
    // Ward of Elements
    effect_quantity = g_active_artifacts[42] / g_artifact_ids[42].pieces;
    fixed->f_def += effect_quantity;
    fixed->i_def += effect_quantity;
    fixed->l_def += effect_quantity;
    // Sigil of Elements
    effect_quantity = g_active_artifacts[43] / g_artifact_ids[43].pieces;
    fixed->f_def += effect_quantity * 2;
    fixed->i_def += effect_quantity * 2;
    fixed->l_def += effect_quantity * 2;
    // Relic of Elements
    effect_quantity = g_active_artifacts[44] / g_artifact_ids[44].pieces;
    fixed->f_def += effect_quantity * 3;
    fixed->i_def += effect_quantity * 3;
    fixed->l_def += effect_quantity * 3;
    // Cup of wealth
    effect_quantity = g_active_artifacts[45] / g_artifact_ids[45].pieces;
    fixed->gold_drop += effect_quantity * 0.1;
    // Puzzle Box of Frivolity
    effect_quantity = g_active_artifacts[46] / g_artifact_ids[46].pieces;
    if (effect_quantity > 0) 
        effects.bragging_rights = true;
    else
        effects.bragging_rights = false;

    //------------------------------------------
    // Multi-generational
    //------------------------------------------

    // Book of the Polymath
    effect_quantity = g_active_artifacts[47] / g_artifact_ids[47].pieces;
    fixed->spd += effect_quantity;
    fixed->atk += effect_quantity;
    fixed->def += effect_quantity;
    // Book of the Gladiator
    effect_quantity = g_active_artifacts[48] / g_artifact_ids[48].pieces;
    fixed->str += effect_quantity;
    fixed->con += effect_quantity;
    fixed->dex += effect_quantity;
    // Tome of the Polymath
    effect_quantity = g_active_artifacts[49] / g_artifact_ids[49].pieces;
    fixed->spd += effect_quantity * 2;
    fixed->atk += effect_quantity * 2;
    fixed->def += effect_quantity * 2;
    // Tome of the Gladiator
    effect_quantity = g_active_artifacts[50] / g_artifact_ids[50].pieces;
    fixed->str += effect_quantity * 2;
    fixed->con += effect_quantity * 2;
    fixed->dex += effect_quantity * 2;
    // Bible of the Polymath
    effect_quantity = g_active_artifacts[51] / g_artifact_ids[51].pieces;
    fixed->spd += effect_quantity * 3;
    fixed->atk += effect_quantity * 3;
    fixed->def += effect_quantity * 3;
    // Bible of the Gladiator
    effect_quantity = g_active_artifacts[52] / g_artifact_ids[52].pieces;
    fixed->str += effect_quantity * 3;
    fixed->con += effect_quantity * 3;
    fixed->dex += effect_quantity * 3;
    // Trickster Trinket
    effect_quantity = g_active_artifacts[53] / g_artifact_ids[53].pieces;
    fixed->apt += effect_quantity;
    // Prismatic Mirror
    effect_quantity = g_active_artifacts[54] / g_artifact_ids[54].pieces;
    fixed->f_def += effect_quantity * 10;
    fixed->i_def += effect_quantity * 10;
    fixed->l_def += effect_quantity * 10;
    // Glasses of Foresight
    effect_quantity = g_active_artifacts[55] / g_artifact_ids[55].pieces;
    if (effect_quantity > 0) 
        effects.permanent_discovery = true;
    else
        effects.permanent_discovery = false;
    // Ethereal Barrier
    effect_quantity = g_active_artifacts[56] / g_artifact_ids[56].pieces;
    fixed->a_dmg -= effect_quantity * 0.01;
    // Righteous Fire
    effect_quantity = g_active_artifacts[57] / g_artifact_ids[57].pieces;
    fixed->max_f_def += effect_quantity;
    // Righteous Ice
    effect_quantity = g_active_artifacts[58] / g_artifact_ids[58].pieces;
    fixed->max_i_def += effect_quantity;
    // Righteous Lightning
    effect_quantity = g_active_artifacts[59] / g_artifact_ids[59].pieces;
    fixed->max_l_def += effect_quantity;
    // Ark of Enlightenment
    effect_quantity = g_active_artifacts[60] / g_artifact_ids[60].pieces;
    if (effect_quantity > 0)
        effects.auto_identify = true;
    else
        effects.auto_identify = false;
    // Chalice of Riches
    effect_quantity = g_active_artifacts[61] / g_artifact_ids[61].pieces;
    if (effect_quantity > 0)
        multiplicative->gold_drop = 2.0;
    else
        multiplicative->gold_drop = 1.0;
    // Amphora of Holy Water
    effect_quantity = g_active_artifacts[62] / g_artifact_ids[62].pieces;
    if (effect_quantity > 0)
        effects.permanent_decurse = true;
    else
        effects.permanent_decurse = false;

    //------------------------------------------
    // HP artifacts added later
    //------------------------------------------
    fixed->max_hp += (g_active_artifacts[63] * 3);      // Sign of Health
    fixed->max_hp += (g_active_artifacts[64] * 8);      // Medal of Health
    fixed->max_hp += (g_active_artifacts[65] * 15);     // Trophy of Health
    // Book of the Healthy
    effect_quantity = g_active_artifacts[66] / g_artifact_ids[66].pieces;
    fixed->max_hp += effect_quantity * 5;
    fixed->con += effect_quantity;
    // Tome of the Healthy
    effect_quantity = g_active_artifacts[67] / g_artifact_ids[67].pieces;
    fixed->max_hp += effect_quantity * 10;
    fixed->con += effect_quantity;
    // Bible of the Healthy
    effect_quantity = g_active_artifacts[68] / g_artifact_ids[68].pieces;
    fixed->max_hp += effect_quantity * 20;
    fixed->con += effect_quantity;
    // Fountain of Youth
    effect_quantity = g_active_artifacts[69] / g_artifact_ids[69].pieces;
    fixed->max_hp += effect_quantity * 100;

}

//------------------------------------------------------------------------------
// Displays a list of the specified stats.
// 
// Arguments:
//   s - the stats to dump
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void Player::dump_stats(Stats *s) {
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "Max HP : " << s->max_hp << std::endl;
	std::cout << "STR    : " << s->str << std::endl;
	std::cout << "CON    : " << s->con << std::endl;
	std::cout << "DEX    : " << s->dex << std::endl;
	std::cout << "ATK    : " << s->atk << std::endl;
	std::cout << "DEF    : " << s->def << std::endl;
	std::cout << "SPD    : " << s->spd << std::endl;
	std::cout << "FDef   : " << s->f_def << std::endl;
	std::cout << "IDef   : " << s->i_def << std::endl;
	std::cout << "LDef   : " << s->l_def << std::endl;
	std::cout << "FAtk   : " << s->f_atk << std::endl;
	std::cout << "IAtk   : " << s->i_atk << std::endl;
	std::cout << "LAtk   : " << s->l_atk << std::endl;
	std::cout << "FDmg   : " << s->f_dmg << std::endl;
	std::cout << "IDmg   : " << s->i_dmg << std::endl;
	std::cout << "LDmg   : " << s->l_dmg << std::endl;
	std::cout << "ADmg   : " << s->a_dmg << std::endl;
	std::cout << "APT    : " << s->apt << std::endl;
	std::cout << "Block  : " << s->block << std::endl;
	std::cout << "Pois   : " << g_player.is_equip_poisoned << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

