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
	unsigned short max_hp;		// Max HP
	unsigned short str;			// Strength
	unsigned short con;			// Constitution
	unsigned short dex;			// Dexterity
	unsigned short atk;			// Attack
	unsigned short def;			// Defense
	unsigned short spd;			// Speed
	unsigned short f_def;		// Fire defense
	unsigned short i_def;		// Ice defense
	unsigned short l_def;		// Lightning defense
	unsigned short f_atk;		// Fire attack damage
	unsigned short i_atk;		// Ice attack damage
	unsigned short l_atk;		// Lightning attack damage
	unsigned short apt;			// Attacks per turn
	unsigned short block;		// Absolute chance to block
} Stats;

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
	float apt;			// Attacks per turn
	float block;		// Absolute chance to block
} MultiplicativeStats;

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
	bool is_paralyzed;		// Is the player paralyzed?

	// TODO - consider whether these values, and the *_last_room_entered functions
	// should be moved elsewhere
	int x_pos;				// The position of the player in the current area
	int y_pos;
	int last_room_entered;

	Player();
	Player(int x, int y);
	int get_last_room_entered() { return last_room_entered; }
	void set_last_room_entered(int room) { last_room_entered = room; }
	void set_position(int x, int y);
	void assign_base_stats_to_actual();
	void apply_stats_to_actual(Stats &fixed, MultiplicativeStats &multiplicative);
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
};

#endif