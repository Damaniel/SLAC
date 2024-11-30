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
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "globals.h"

typedef struct {
	float max_hp;		// Max HP
	float str;			// Strength
	float con;			// Constitution
	float dex;			// Dexterity
	float atk;			// Attack
	float def;			// Defense
	float spd;			// Speed
	float f_def;		// Fire defense
	float i_def;		// Ice defense
	float l_def;		// Lightning defense
	float f_atk;		// Fire attack damage
	float i_atk;		// Ice attack damage
	float l_atk;		// Lightning attack damage
	float f_dmg;       // Fire damage taken (pre-resist)
	float i_dmg;       // Ice damage taken (pre-resist)
	float l_dmg;       // Lightning damage taken (pre-resist)
	float a_dmg;		// All damage taken (pre-resist)
	float apt;			// Attacks per turn
	float block;		// Absolute chance to block
} Stats;

typedef struct {
	Item *weapon;
	Item *shield;
	Item *head;
	Item *chest;
	Item *hands;
	Item *legs;
	Item *feet;
	Item *amulet;
	Item *ring;
} EquipmentSet;

//------------------------------------------------------------------------------
// Player class definition
//------------------------------------------------------------------------------
class Player {
// For now, all members are public.
public:
	std::string name;		// The player's name
	int generation;			// The current generation of the player
	unsigned short hp;		// The player's current HP
	unsigned short level;	// The player's current level 
	int gold;				// Amount of currency the player has
	int exp;				// The player's current number of experience points
	Stats base;				// The player's base stats
	Stats actual;			// The player's fully modified (by gear, items, etc) stats
	EquipmentSet equipment;	// Equipment
	bool is_poisoned;		// Is the player poisoned?
	bool is_equip_poisoned; // Is cursed equipment poisoning the player
	bool is_paralyzed;		// Is the player paralyzed?

	// TODO - consider whether these values, and the *_last_room_entered functions
	// should be moved elsewhere
	int x_pos;				// The position of the player in the current area
	int y_pos;
	int last_room_entered;

	Player();
	Player(int x, int y);
	void init_base_stats();
	int get_last_room_entered() { return last_room_entered; }
	void set_last_room_entered(int room) { last_room_entered = room; }
	void set_position(int x, int y);
	void assign_base_stats_to_actual();
	void apply_stats_to_actual(Stats *fixed, Stats *multiplicative);
    void init_temp_stats(Stats *f, Stats *m);
	int get_x_pos();
	int get_y_pos();
	void set_x_pos(int pos);
	void set_y_pos(int pos);
	void add_gold(int amount);
	int get_gold();
	Item **get_item_slot_by_type(int type);
	void recalculate_actual_stats();
	void equip(Item *i);
	void unequip(Item *i);
	void dump_stats(Stats *s);
};

#endif