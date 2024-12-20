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

typedef struct {
	unsigned short max_hp;
	unsigned short str;
	unsigned short con;
	unsigned short dex;
	unsigned short atk;
	unsigned short def;
	unsigned short spd;
} BaseStatSet;


namespace PlayerConsts {
	const int MAX_LEVEL = 100;

	// For the following two tables, the 'n'th entry represents the experience the player
	// should have and the stats the player should have at level (n+1)
	//
	// This table is a placeholder - it was generated with the following code
	//   (and adding the value of 0 to the front manually)
	//
	// exp = 10
	// print("int player_exp_table[] = {")
	// print("      10, ", end = '')
	//
	// for i in range(1,100):
	//     old_exp = exp
	//     exp = ((i ** 2.2) * (i) + (i * 8)) * 5
	//     if i % 10 == 9 and i < 99:
	//         print(f"{int(exp):8d},")
	//     elif i % 10 != 9 and i < 99:
	//         print(f"{int(exp):8d}, ", end = '')
	//     else:
	//         print(f"{int(exp):8d}", end = '')
	//         print("};")
	const int g_player_exp_table[MAX_LEVEL + 1] = {
		      0,    10,    45,    125,     288,     582,     1062,     1785,     2810,     4200,     6016,
    	   8324,    11190,    14682,    18868,    23818,    29604,    36297,    43971,    52700,    62559,
   		  73622,    85967,    99672,   114813,   131470,   149722,   169650,   191334,   214855,   240295,
  		 267737,   297264,   328960,   362908,   399194,   437903,   479121,   522933,   569427,   618690,
  		 670809,   725873,   783969,   845188,   909619,   977351,  1048474,  1123080,  1201259,  1283102,
 		1368702,  1458151,  1551541,  1648965,  1750516,  1856289,  1966376,  2080873,  2199874,  2323473,
 		2451767,  2584851,  2722821,  2865773,  3013803,  3167009,  3325488,  3489338,  3658655,  3833538,
 		4014086,  4200398,  4392571,  4590706,  4794901,  5005257,  5221874,  5444851,  5674290,  5910292,
 		6152957,  6402386,  6658682,  6921946,  7192281,  7469788,  7754570,  8046730,  8346372,  8653598,
 		8968512,  9291217,  9621819,  9960420, 10307126, 10662041, 11025270, 11396918, 11777090, 12165893
	};

	// The base stats for the player at each experience level (n+1)
	//
	// These values are placeholders to help write leveling code
	const BaseStatSet g_player_base_stats[MAX_LEVEL + 1] = {
		{ 50, 10, 10, 10, 10, 10, 100 },
		{ 55, 11, 11, 11, 11, 11, 100 },
		{ 60, 12, 12, 12, 12, 12, 100 },
		{ 65, 13, 13, 13, 13, 13, 100 },
		{ 70, 14, 14, 14, 14, 14, 100 },
		{ 75, 15, 15, 15, 15, 15, 100 },
		{ 80, 16, 16, 16, 16, 16, 100 },
		{ 85, 17, 17, 17, 17, 17, 100 },
		{ 90, 18, 18, 18, 18, 18, 100 },
		{ 95, 19, 19, 19, 19, 19, 100 },
		{ 100, 20, 20, 20, 20, 20, 105 },
		{ 105, 21, 21, 21, 21, 21, 105 },
		{ 110, 22, 22, 22, 22, 22, 105 },
		{ 115, 23, 23, 23, 23, 23, 105 },
		{ 120, 24, 24, 24, 24, 24, 105 },
		{ 125, 25, 25, 25, 25, 25, 105 },
		{ 130, 26, 26, 26, 26, 26, 105 },
		{ 135, 27, 27, 27, 27, 27, 105 },
		{ 140, 28, 28, 28, 28, 28, 105 },
		{ 145, 29, 29, 29, 29, 29, 105 },
		{ 150, 30, 30, 30, 30, 30, 110 },
		{ 155, 31, 31, 31, 31, 31, 110 },
		{ 160, 32, 32, 32, 32, 32, 110 },
		{ 165, 33, 33, 33, 33, 33, 110 },
		{ 170, 34, 34, 34, 34, 34, 110 },
		{ 175, 35, 35, 35, 35, 35, 110 },
		{ 180, 36, 36, 36, 36, 36, 110 },
		{ 185, 37, 37, 37, 37, 37, 110 },
		{ 190, 38, 38, 38, 38, 38, 110 },
		{ 195, 39, 39, 39, 39, 39, 110 },
		{ 200, 40, 40, 40, 40, 40, 115 },
		{ 205, 41, 41, 41, 41, 41, 115 },
		{ 210, 42, 42, 42, 42, 42, 115 },
		{ 215, 43, 43, 43, 43, 43, 115 },
		{ 220, 44, 44, 44, 44, 44, 115 },
		{ 225, 45, 45, 45, 45, 45, 115 },
		{ 230, 46, 46, 46, 46, 46, 115 },
		{ 235, 47, 47, 47, 47, 47, 115 },
		{ 240, 48, 48, 48, 48, 48, 115 },
		{ 245, 49, 49, 49, 49, 49, 115 },
		{ 250, 50, 50, 50, 50, 50, 120 },
		{ 255, 51, 51, 51, 51, 51, 120 },
		{ 260, 52, 52, 52, 52, 52, 120 },
		{ 265, 53, 53, 53, 53, 53, 120 },
		{ 270, 54, 54, 54, 54, 54, 120 },
		{ 275, 55, 55, 55, 55, 55, 120 },
		{ 280, 56, 56, 56, 56, 56, 120 },
		{ 285, 57, 57, 57, 57, 57, 120 },
		{ 290, 58, 58, 58, 58, 58, 120 },
		{ 295, 59, 59, 59, 59, 59, 120 },
		{ 300, 60, 60, 60, 60, 60, 125 },
		{ 305, 61, 61, 61, 61, 61, 125 },
		{ 310, 62, 62, 62, 62, 62, 125 },
		{ 315, 63, 63, 63, 63, 63, 125 },
		{ 320, 64, 64, 64, 64, 64, 125 },
		{ 325, 65, 65, 65, 65, 65, 125 },
		{ 330, 66, 66, 66, 66, 66, 125 },
		{ 335, 67, 67, 67, 67, 67, 125 },
		{ 340, 68, 68, 68, 68, 68, 125 },
		{ 345, 69, 69, 69, 69, 69, 125 },
		{ 350, 70, 70, 70, 70, 70, 130 },
		{ 355, 71, 71, 71, 71, 71, 130 },
		{ 360, 72, 72, 72, 72, 72, 130 },
		{ 365, 73, 73, 73, 73, 73, 130 },
		{ 370, 74, 74, 74, 74, 74, 130 },
		{ 375, 75, 75, 75, 75, 75, 130 },
		{ 380, 76, 76, 76, 76, 76, 130 },
		{ 385, 77, 77, 77, 77, 77, 130 },
		{ 390, 78, 78, 78, 78, 78, 130 },
		{ 395, 79, 79, 79, 79, 79, 130 },
		{ 400, 80, 80, 80, 80, 80, 135 },
		{ 405, 81, 81, 81, 81, 81, 135 },
		{ 410, 82, 82, 82, 82, 82, 135 },
		{ 415, 83, 83, 83, 83, 83, 135 },
		{ 420, 84, 84, 84, 84, 84, 135 },
		{ 425, 85, 85, 85, 85, 85, 135 },
		{ 430, 86, 86, 86, 86, 86, 135 },
		{ 435, 87, 87, 87, 87, 87, 135 },
		{ 440, 88, 88, 88, 88, 88, 135 },
		{ 445, 89, 89, 89, 89, 89, 135 },
		{ 450, 90, 90, 90, 90, 90, 140 },
		{ 455, 91, 91, 91, 91, 91, 140 },
		{ 460, 92, 92, 92, 92, 92, 140 },
		{ 465, 93, 93, 93, 93, 93, 140 },
		{ 470, 94, 94, 94, 94, 94, 140 },
		{ 475, 95, 95, 95, 95, 95, 140 },
		{ 480, 96, 96, 96, 96, 96, 140 },
		{ 485, 97, 97, 97, 97, 97, 140 },
		{ 490, 98, 98, 98, 98, 98, 140 },
		{ 495, 99, 99, 99, 99, 99, 140 },
		{ 500, 100, 100, 100, 100, 100, 145 },
		{ 505, 101, 101, 101, 101, 101, 145 },
		{ 510, 102, 102, 102, 102, 102, 145 },
		{ 515, 103, 103, 103, 103, 103, 145 },
		{ 520, 104, 104, 104, 104, 104, 145 },
		{ 525, 105, 105, 105, 105, 105, 145 },
		{ 530, 106, 106, 106, 106, 106, 145 },
		{ 535, 107, 107, 107, 107, 107, 145 },
		{ 540, 108, 108, 108, 108, 108, 145 },
		{ 545, 109, 109, 109, 109, 109, 145 },
		{ 550, 110, 110, 110, 110, 110, 150 }
	};
}

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

	int residual_action_points;		// Any action points left after their last turn

	Player();
	Player(int x, int y);
	void init(int x, int y);
	void init_base_stats();
	int get_last_room_entered() { return last_room_entered; }
	void set_last_room_entered(int room) { last_room_entered = room; }
	void set_position(int x, int y);
	void assign_base_stats_to_actual();
	void apply_stats_to_actual(Stats *fixed, Stats *multiplicative);
    void init_temp_stats(Stats *f, Stats *m);
	int get_x_pos();
	int get_y_pos();
	int get_action_residual() { return residual_action_points; }
	void set_action_residual(int amount) { residual_action_points = amount; }
	void set_x_pos(int pos);
	void set_y_pos(int pos);
	void add_gold(int amount);
	int get_gold();
	Item **get_item_slot_by_type(int type);
	void recalculate_actual_stats();
	void equip(Item *i);
	void unequip(Item *i);
	void dump_stats(Stats *s);
	void apply_experience(int quantity);
	void level_up(void);
	float pct_exp_to_next_level(void);
};

#endif