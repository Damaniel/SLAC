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
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "enemy.h"
#include "itemgen.h"
#include "globals.h"

typedef struct {
	float max_hp;		// Max HP
	float str;			// Strength
	float con;			// Constitution
	float dex;			// Dexterity
	float atk;			// Attack
	float def;			// Defense
	float spd;			// Speed
	float acc;          // accuracy
	float f_def;		// Fire defense
	float i_def;		// Ice defense
	float l_def;		// Lightning defense
	float max_f_def;	// Maximum fire defense
	float max_i_def;	// Maximum ice defense
	float max_l_def;	// Maximum lightning defense
	float f_atk;		// Fire attack damage
	float i_atk;		// Ice attack damage
	float l_atk;		// Lightning attack damage
	float f_dmg;       // Fire damage taken (pre-resist)
	float i_dmg;       // Ice damage taken (pre-resist)
	float l_dmg;       // Lightning damage taken (pre-resist)
	float a_dmg;		// All damage taken (pre-resist)
	float apt;			// Attacks per turn
	float block;		// Absolute chance to block
	float gold_drop;    // relative multiplier of gold drop rate
} Stats;

typedef struct {
	bool auto_identify;
	bool permanent_discovery;
	bool permanent_decurse;
	bool bragging_rights;
} ArtifactEffectFlags;

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
	unsigned short acc;
	unsigned short spd;
} BaseStatSet;

typedef struct {
	bool enabled;
	unsigned char turns_remaining;
} PotionEffect;

namespace PlayerConsts {
	const int MAX_LEVEL = 100;

	// The highest elemental resistance (in percent) the player can have
	const int MAX_ELEM_DEF = 95;
	
	const int TOWN_START_X = 4;
	const int TOWN_START_Y = 32;

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
	//
	// The 'to next level' for each level is:
	//  2 -    10  |  22 - 11063  |  42 -  52119  |  62 - 128294  |  82 - 242665
	//  3 -    35  |  23 - 12345  |  43 -  55064  |  63 - 133084  |  83 - 249429
	//  4 -    80  |  24 - 13705  |  44 -  58096  |  64 - 137970  |  84 - 256306
	//  5 -   163  |  25 - 15141  |  45 -  61219  |  65 - 142952  |  85 - 263264
	//  6 -   294  |  26 - 16657  |  46 -  64431  |  66 - 148030  |  86 - 270335
	//  7 -   480  |  27 - 18252  |  47 -  67732  |  67 - 153206  |  87 - 277507
	//  8 -   723  |  28 - 19928  |  48 -  71123  |  68 - 158479  |  88 - 284782
	//  9 -  1025  |  29 - 21684  |  49 -  74606  |  69 - 163850  |  89 - 292160
	// 10 -  1390  |  30 - 23521  |  50 -  78179  |  70 - 169317  |  90 - 299642
	// 11 -  1816  |  31 - 25440  |  51 -  81843  |  71 - 174883  |  91 - 307226
	// 12 -  2308  |  32 - 27442  |  52 -  85600  |  72 - 180548  |  92 - 314914
	// 13 -  2866  |  33 - 29527  |  53 -  89449  |  73 - 186312  |  93 - 322705
 	// 14 -  3492  |  34 - 31696  |  54 -  93390  |  74 - 192173  |  94 - 330602
	// 15 -  4186  |  35 - 33948  |  55 -  97424  |  75 - 198135  |  95 - 338601
	// 16 -  4950  |  36 - 36286  |  56 - 101551  |  76 - 204195  |  96 - 346706
	// 17 -  5786  |  37 - 38709  |  57 - 105773  |  77 - 210356  |  97 - 354915
	// 18 -  6693  |  38 - 41218  |  58 - 110087  |  78 - 216617  |  98 - 363229
	// 19 -  7674  |  39 - 43812  |  59 - 114497  |  79 - 222977  |  99 - 371648
	// 20 -  8729  |  40 - 46494  |  60 - 119001  |  80 - 229439  | 100 - 380172
	// 21 -  9859  |  41 - 49263  |  61 - 123599  |  81 - 236002  |   x - 388803
	const int g_player_exp_table[MAX_LEVEL] = {
		      0,       10,       45,      125,      288,      582,     1062,     1785,     2810,     4200,     
		   6016,     8324,    11190,    14682,    18868,    23818,    29604,    36297,    43971,    52700,
	      62559,    73622,    85967,    99672,   114813,   131470,   149722,   169650,   191334,   214855,   
		 240295,   267737,   297264,   328960,   362908,   399194,   437903,   479121,   522933,   569427,  
		 618690,   670809,   725873,   783969,   845188,   909619,   977351,  1048474,  1123080,  1201259,  
		 1283102, 1368702,  1458151,  1551541,  1648965,  1750516,  1856289,  1966376,  2080873,  2199874,  
		 2323473, 2451767,  2584851,  2722821,  2865773,  3013803,  3167009,  3325488,  3489338,  3658655,  
		 3833538, 4014086,  4200398,  4392571,  4590706,  4794901,  5005257,  5221874,  5444851,  5674290,  
		 5910292, 6152957,  6402386,  6658682,  6921946,  7192281,  7469788,  7754570,  8046730,  8346372,  
		 8653598, 8968512,  9291217,  9621819,  9960420, 10307126, 10662041, 11025270, 11396918, 11777090
	};

	// The base stats for the player at each experience level (n+1)
	//
	// These values are placeholders to help write leveling code
	const BaseStatSet g_player_base_stats[MAX_LEVEL + 1] = {
		{ 50, 10, 10, 10, 10, 10, 10,100 },
		{ 55, 11, 11, 11, 11, 11, 10, 100 },
		{ 60, 12, 12, 12, 12, 12, 10, 100 },
		{ 65, 13, 13, 13, 13, 13, 10, 100 },
		{ 70, 14, 14, 14, 14, 14, 10, 100 },
		{ 75, 15, 15, 15, 15, 15, 11, 100 },
		{ 80, 16, 16, 16, 16, 16, 11, 100 },
		{ 85, 17, 17, 17, 17, 17, 11, 100 },
		{ 90, 18, 18, 18, 18, 18, 11, 100 },
		{ 95, 19, 19, 19, 19, 19, 11, 100 },
		{ 100, 20, 20, 20, 20, 20, 12, 105 },
		{ 105, 21, 21, 21, 21, 21, 12, 105 },
		{ 110, 22, 22, 22, 22, 22, 12, 105 },
		{ 115, 23, 23, 23, 23, 23, 12, 105 },
		{ 120, 24, 24, 24, 24, 24, 12, 105 },
		{ 125, 25, 25, 25, 25, 25, 13, 105 },
		{ 130, 26, 26, 26, 26, 26, 13, 105 },
		{ 135, 27, 27, 27, 27, 27, 13, 105 },
		{ 140, 28, 28, 28, 28, 28, 13, 105 },
		{ 145, 29, 29, 29, 29, 29, 13, 105 },
		{ 150, 30, 30, 30, 30, 30, 14, 110 },
		{ 155, 31, 31, 31, 31, 31, 14, 110 },
		{ 160, 32, 32, 32, 32, 32, 14, 110 },
		{ 165, 33, 33, 33, 33, 33, 14, 110 },
		{ 170, 34, 34, 34, 34, 34, 14, 110 },
		{ 175, 35, 35, 35, 35, 35, 15, 110 },
		{ 180, 36, 36, 36, 36, 36, 15, 110 },
		{ 185, 37, 37, 37, 37, 37, 15, 110 },
		{ 190, 38, 38, 38, 38, 38, 15, 110 },
		{ 195, 39, 39, 39, 39, 39, 15, 110 },
		{ 200, 40, 40, 40, 40, 40, 16, 115 },
		{ 205, 41, 41, 41, 41, 41, 16, 115 },
		{ 210, 42, 42, 42, 42, 42, 16, 115 },
		{ 215, 43, 43, 43, 43, 43, 16, 115 },
		{ 220, 44, 44, 44, 44, 44, 16, 115 },
		{ 225, 45, 45, 45, 45, 45, 17, 115 },
		{ 230, 46, 46, 46, 46, 46, 17, 115 },
		{ 235, 47, 47, 47, 47, 47, 17, 115 },
		{ 240, 48, 48, 48, 48, 48, 17, 115 },
		{ 245, 49, 49, 49, 49, 49, 17, 115 },
		{ 250, 50, 50, 50, 50, 50, 18, 120 },
		{ 255, 51, 51, 51, 51, 51, 18, 120 },
		{ 260, 52, 52, 52, 52, 52, 18, 120 },
		{ 265, 53, 53, 53, 53, 53, 18, 120 },
		{ 270, 54, 54, 54, 54, 54, 18, 120 },
		{ 275, 55, 55, 55, 55, 55, 19, 120 },
		{ 280, 56, 56, 56, 56, 56, 19, 120 },
		{ 285, 57, 57, 57, 57, 57, 19, 120 },
		{ 290, 58, 58, 58, 58, 58, 19, 120 },
		{ 295, 59, 59, 59, 59, 59, 19, 120 },
		{ 300, 60, 60, 60, 60, 60, 20, 125 },
		{ 305, 61, 61, 61, 61, 61, 20, 125 },
		{ 310, 62, 62, 62, 62, 62, 20, 125 },
		{ 315, 63, 63, 63, 63, 63, 20, 125 },
		{ 320, 64, 64, 64, 64, 64, 20, 125 },
		{ 325, 65, 65, 65, 65, 65, 21, 125 },
		{ 330, 66, 66, 66, 66, 66, 21, 125 },
		{ 335, 67, 67, 67, 67, 67, 21, 125 },
		{ 340, 68, 68, 68, 68, 68, 21, 125 },
		{ 345, 69, 69, 69, 69, 69, 21, 125 },
		{ 350, 70, 70, 70, 70, 70, 21, 130 },
		{ 355, 71, 71, 71, 71, 71, 22, 130 },
		{ 360, 72, 72, 72, 72, 72, 22, 130 },
		{ 365, 73, 73, 73, 73, 73, 22, 130 },
		{ 370, 74, 74, 74, 74, 74, 22, 130 },
		{ 375, 75, 75, 75, 75, 75, 22, 130 },
		{ 380, 76, 76, 76, 76, 76, 23, 130 },
		{ 385, 77, 77, 77, 77, 77, 23, 130 },
		{ 390, 78, 78, 78, 78, 78, 23, 130 },
		{ 395, 79, 79, 79, 79, 79, 23, 130 },
		{ 400, 80, 80, 80, 80, 80, 23, 135 },
		{ 405, 81, 81, 81, 81, 81, 24, 135 },
		{ 410, 82, 82, 82, 82, 82, 24, 135 },
		{ 415, 83, 83, 83, 83, 83, 24, 135 },
		{ 420, 84, 84, 84, 84, 84, 24, 135 },
		{ 425, 85, 85, 85, 85, 85, 24, 135 },
		{ 430, 86, 86, 86, 86, 86, 25, 135 },
		{ 435, 87, 87, 87, 87, 87, 25, 135 },
		{ 440, 88, 88, 88, 88, 88, 25, 135 },
		{ 445, 89, 89, 89, 89, 89, 25, 135 },
		{ 450, 90, 90, 90, 90, 90, 25, 140 },
		{ 455, 91, 91, 91, 91, 91, 26, 140 },
		{ 460, 92, 92, 92, 92, 92, 26, 140 },
		{ 465, 93, 93, 93, 93, 93, 26, 140 },
		{ 470, 94, 94, 94, 94, 94, 26, 140 },
		{ 475, 95, 95, 95, 95, 95, 26, 140 },
		{ 480, 96, 96, 96, 96, 96, 27, 140 },
		{ 485, 97, 97, 97, 97, 97, 27, 140 },
		{ 490, 98, 98, 98, 98, 98, 27, 140 },
		{ 495, 99, 99, 99, 99, 99, 27, 140 },
		{ 500, 100, 100, 100, 100, 100, 27, 145 },
		{ 505, 101, 101, 101, 101, 101, 28, 145 },
		{ 510, 102, 102, 102, 102, 102, 28, 145 },
		{ 515, 103, 103, 103, 103, 103, 28, 145 },
		{ 520, 104, 104, 104, 104, 104, 28, 145 },
		{ 525, 105, 105, 105, 105, 105, 28, 145 },
		{ 530, 106, 106, 106, 106, 106, 29, 145 },
		{ 535, 107, 107, 107, 107, 107, 29, 145 },
		{ 540, 108, 108, 108, 108, 108, 29, 145 },
		{ 545, 109, 109, 109, 109, 109, 29, 145 },
		{ 550, 110, 110, 110, 110, 110, 29, 150 }
	};
}

//------------------------------------------------------------------------------
// Player class definition
//------------------------------------------------------------------------------
class Player {
// For now, all members are public.
public:
	std::string name;				// The player's name
	short hp;						// The player's current HP
	unsigned short level;			// The player's current level 
	int gold;						// Amount of currency the player has
	int exp;						// The player's current number of experience points
	Stats base;						// The player's base stats
	Stats actual;					// The player's fully modified (by gear, items, etc) stats
	EquipmentSet equipment;			// Equipment
	ArtifactEffectFlags effects;	// Artifact effects
	bool is_alive;					// Is the player still alive
	bool is_poisoned;				// Is the player poisoned?
	bool is_equip_poisoned; 		// Is cursed equipment poisoning the player
	PotionEffect potion_effects[ItemConsts::NUM_TURN_POTION_EFFECTS];	// Are these potions active, and for how long?

	int x_pos;				// The position of the player in the current area
	int y_pos;
	int last_room_entered;

	int recall_x_pos;		// The place in the dungeon where a recall scroll activated
	int recall_y_pos;		// (and where the player will return when moving back to
							// the recall point)
	int recall_floor;       // The floor the recall scroll was used from
	int recall_count;		// The number of turns until a recall scroll activates
	bool recall_active;		// Is a scroll of recall active?
	
	int residual_action_points;		// Any action points left after their last turn

	Player();
	Player(int x, int y);
	void init(int x, int y);
	void init_base_stats();
	int get_last_room_entered() { return last_room_entered; }
	void set_last_room_entered(int room) { last_room_entered = room; }
	void set_position(int x, int y);
	void assign_base_stats_to_actual();
	void activate_potion_effect(int effect, int duration);
	void deactivate_potion_effect(int effect);
	void decrement_potion_turn_count();
	int num_effect_turns_remaining(int effect);
	bool is_potion_active(int effect);
	void add_potion_effects_to_stats();
	void apply_stats_to_actual(Stats *fixed, Stats *multiplicative);
	ArtifactEffectFlags *get_effect_flags() { return &effects; }
    void init_temp_stats(Stats *f, Stats *m);
	int get_x_pos();
	int get_y_pos();
	int get_action_residual() { return residual_action_points; }
	void set_action_residual(int amount) { residual_action_points = amount; }
	void set_x_pos(int pos);
	void set_y_pos(int pos);
	void add_gold(int amount);
	int get_gold();
	void set_hp(int new_hp);
	Item **get_item_slot_by_type(int type);
	void recalculate_actual_stats();
	void get_next_gen_stats();
	void equip(Item *i);
	void unequip(Item **i);
	void dump_stats(Stats *s);
	void apply_experience(int quantity);
	void level_up(void);
	float pct_exp_to_next_level(void);
	void apply_artifact_mods(Stats *fixed, Stats *multiplicative);
	void place_in_town_start() { x_pos = PlayerConsts::TOWN_START_X; y_pos = PlayerConsts::TOWN_START_Y; }
};

void perform_player_combat(Enemy *target);

#endif