
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

//----------------------------------------------------------------------------
// Checks to see if the player is on a dungeon entrance, and enters it if so.
//
// Arguments:
//  x, y - the position to check
//
// Returns:
//   Nothing
//
// Notes:
//   This function is called from an input function that already checked to
//   see if the player used the stairs.
//----------------------------------------------------------------------------
void check_and_process_town_entrances(int x, int y) {
	bool enter = false;
	if (x == TownConsts::DUSTY_TUNNELS_X && y == TownConsts::DUSTY_TUNNELS_Y)
	{
		g_dungeon.maze_id = DUSTY_TUNNELS;
		enter = true;
	}
	if (x == TownConsts::MARBLE_HALLS_X && y == TownConsts::MARBLE_HALLS_Y)
	{
		g_dungeon.maze_id = MARBLE_HALLS;
		enter = true;
	}
	if (x == TownConsts::CRYSTAL_DEPTHS_X && y == TownConsts::CRYSTAL_DEPTHS_Y)
	{
		g_dungeon.maze_id = CRYSTAL_DEPTHS;
		enter = true;
	}

	// If entering a dungeon, generate a new floor and turn off any active
	// scroll of recall
	if (enter) {
		enter_dungeon(1);
	}
}

//----------------------------------------------------------------------------
// Checks the location for a NPC or sign, and if so, display their message.
//
// Arguments:
//  x, y - the location to check
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void check_and_process_npc_here(int x, int y) {
	for (int i = 0; i < TownConsts::NUM_NPC_TEXTS; ++i) {
		if (g_npc_info[i].x == x && g_npc_info[i].y == y) {
			g_text_log.put_line(g_npc_info[i].text);
			g_state_flags.update_text_dialog = true;
			g_state_flags.update_display = true;
			return;
		}
	}
}

//----------------------------------------------------------------------------
// Does the things required to enter the dungeon
//
// Arguments:
//  floor - the floor to enter at
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void enter_dungeon(int floor) {
	// Change the player to in the dungeon
	g_state_flags.in_dungeon = true;

	// Turn off any active scroll of recall
	g_player.recall_active = false;

	// Make a new dungeon floor
	generate_new_dungeon_floor(g_dungeon, floor, MazeConsts::STAIRS_DOWN);
	force_update_screen();
}

//----------------------------------------------------------------------------
// Removes the locks in town for the specified dungeon
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void unlock_dungeon(int dungeon, bool loading_save) {
	// A dungeon should unlock if either:
	//   - the dungeon exists, the player has unlocked the ability to open it,
	//     and the player is attempting to open it
	//   - the dungeon exists, the player has unlocked the ability to open it,
	//     the player has already opened it in the past, and their save game is being loaded
	if (dungeon == MARBLE_HALLS && g_game_flags.can_enter_marble_halls && ((loading_save && g_game_flags.has_unlocked_marble_halls) || (!loading_save && !g_game_flags.has_unlocked_marble_halls))) {
		g_town_tile_data[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = 1;
		g_game_flags.has_unlocked_marble_halls = true;
	}

	if (dungeon == CRYSTAL_DEPTHS && g_game_flags.can_enter_crystal_depths && ((loading_save && g_game_flags.has_unlocked_crystal_depths) || (!loading_save && !g_game_flags.has_unlocked_crystal_depths))) {
		g_town_tile_data[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = 1;
		g_game_flags.has_unlocked_crystal_depths = true;
	}

	// Redraw the maze area in case the locked door is on the screen
	g_state_flags.update_maze_area = true;
	g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Creates a set of items for sale in whichever shop the player is in
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void populate_shop_inventory() {
	if (g_state_flags.in_item_shop) {
		g_item_shop_item_values.clear();
		g_item_shop_item_sell_values.clear();
		int item_quantity = rand() % 12 + 24;
		Item *i;
		for (int idx = 0; idx < item_quantity; ++idx) {
			// Pick a scroll or potion with equal chance
			if (rand() % 2 == 0) {
				i = ItemGenerator::generate(ItemConsts::POTION_CLASS, g_game_flags.max_ilevel);
			}
			else {
				i = ItemGenerator::generate(ItemConsts::SCROLL_CLASS, g_game_flags.max_ilevel);
			}
			i->is_identified = true;

			// Determine if there's already one of these in the inventory
            int stackable_slot = g_item_shop_inventory->get_stackable_item_slot(i);

            // If an existing one is found, add it to the stack, otherwise add it to the inventory
            if (stackable_slot != -1) {
                Item *si = g_item_shop_inventory->get_item_in_slot(stackable_slot);
                si->quantity += 1;
                delete i;
            }
            else {
                g_item_shop_inventory->add_at_first_empty(i);
				g_item_shop_item_values.push_back(get_item_price(i));
				g_item_shop_item_sell_values.push_back(get_item_sell_price(i));
			}
		}
		// std::cout << "=======================" << std::endl;
		// std::cout << "The item shop contains:" << std::endl;
		// std::cout << "=======================" << std::endl;
		// g_item_shop_inventory->dump_inventory();

	}
	if (g_state_flags.in_weapon_shop) {
		g_equipment_shop_item_values.clear();
		g_equipment_shop_item_sell_values.clear();
		// Generate between 24 and 36 items and add htem to the inventory
		int item_quantity = rand() % 12 + 24;
		Item *i;
		for (int idx = 0; idx < item_quantity; ++idx) {
			i = ItemGenerator::shop_generate();
			g_weapon_shop_inventory->add_at_first_empty(i);
			g_equipment_shop_item_values.push_back(get_item_price(i));
			g_equipment_shop_item_sell_values.push_back(get_item_sell_price(i));
		}
		// std::cout << "============================" << std::endl;
		// std::cout << "The equipment shop contains:" << std::endl;
		// std::cout << "============================" << std::endl;
		// g_weapon_shop_inventory->dump_inventory();
	}
}
//----------------------------------------------------------------------------
// Calculates the amount the vendor will sell an item for
//
// Arguments:
//   i - the item to calculate value of
//
// Returns:
//   The value
//----------------------------------------------------------------------------
int get_item_price(Item *i) {
	float price = 2.0 * (float)(i->value);

	if (i->item_class == ItemConsts::WEAPON_CLASS || i->item_class == ItemConsts::ARMOR_CLASS) {
		// Is the item a mystery item?
		if (!i->is_identified) {
			price = price * 0.2;
		}
		else {
			// Adjust price based on item ilevel relative to player ilevel
			int ilevel_diff = i->ilevel - g_game_flags.max_ilevel;
			if (ilevel_diff <= -16)
				price = price * 0.2;
			if (ilevel_diff <= -10 && ilevel_diff >= -15)
				price = price * 0.5;
			if (ilevel_diff <= -9 && ilevel_diff >= -5)
				price = price * 0.8;
			if (ilevel_diff >= 5 && ilevel_diff <= 9)
				price = price * 2.0;
			if (ilevel_diff >= 10 && ilevel_diff <= 15)
				price = price * 5.0;
			if (ilevel_diff >= 16)
				price = price * 10.0;

			// prefix, no suffix
			if (i->prefix_id != -1 && i->suffix_id == -1)
				price = price * 2.0;
			// suffix, no prefix
			if (i->prefix_id == -1 && i->suffix_id == -1)
				price = price * 2.0;
			// prefix and suffix
			if (i->prefix_id != -1 && i->suffix_id != -1)
				price = price * 6.0;
		}

		float offset = 100.0/(float)(rand() % 50 + 75);
		price = price * offset;
	}
	if (i->item_class == ItemConsts::SCROLL_CLASS || i->item_class == ItemConsts::POTION_CLASS) {
		float offset = 100.0/(float(rand() % 20 + 90));
		price = price * offset;
	}

	return (int)price;
}

//----------------------------------------------------------------------------
// Calculates the amount the vendor will buy an item for
//
// Arguments:
//   i - the item to calculate value of
//
// Returns:
//   The value
//----------------------------------------------------------------------------
int get_item_sell_price(Item *i) {
	float price = (float)(i->value);

	if (i->item_class == ItemConsts::WEAPON_CLASS || i->item_class == ItemConsts::ARMOR_CLASS) {
		if (!i->is_identified) {
			return (int)price;
		}
		else if (i->is_identified && i->is_cursed) {
			return (int)(price / 2);
		}
		else if (i->is_identified && i->prefix_id == -1 && i->suffix_id == -1) {
			return (int)price;
		}
		else if (i->is_identified && i->prefix_id == -1 && i->suffix_id != -1) {
			return (int)(price * 1.5);
		}
		else if (i->is_identified && i->prefix_id != -1 && i->suffix_id == -1) {
			return (int)(price * 1.5);
		}
		else {
			return (int)(price * 2.0);
		}

	}
	if (i->item_class == ItemConsts::SCROLL_CLASS || i->item_class == ItemConsts::POTION_CLASS) {
		return (int)price;
	}

	return 0;
}

//----------------------------------------------------------------------------
// Puts the museum artifacts into a map (for faster access, hopefully)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void init_museum_artifacts() {
	for (int i = 0; i < NUM_ARTIFACTS; ++i) {
		std::pair<int, int> p = std::make_pair(g_museum_artifact_list[i].x, g_museum_artifact_list[i].y);
		g_museum_artifacts[p] = i;
	}
}

// The positions of each artifact in the museum.  When entering the museum,
// each artifact position will be checked and drawn if at least one artifact of that
// type is present
const ArtifactPos g_museum_artifact_list[NUM_ARTIFACTS] = {
	{ 2, 19},
	{ 4, 19},
	{ 6, 19},
	{ 8, 19},
	{10, 19},
	{12, 19},
	{14, 19},
	{18, 19},
	{ 2, 17},
	{ 4, 17},
	{ 6, 17},
	{ 8, 17},
	{10, 17},
	{12, 17},
	{16, 17},
	{18, 17},
	{ 2, 15},
	{ 4, 15},
	{ 6, 15},
	{ 8, 15},
	{10, 15},
	{14, 15},
	{16, 15},
	{18, 15},
	{ 2, 13},
	{ 4, 13},
	{ 6, 13},
	{ 8, 13},
	{10, 13},
	{12, 13},
	{14, 13},
	{16, 13},
	{18, 13},
	{ 3,  9},
	{ 5,  9},
	{ 9,  9},
	{11,  9},
	{13,  9},
	{17,  9},
	{ 2,  8},
	{ 4,  8},
	{ 8,  8},
	{10,  8},
	{12,  8},
	{14,  8},
	{16,  8},
	{18,  8},
	{ 3,  4},
	{ 5,  4},
	{ 7,  4},
	{ 9,  4},
	{11,  4},
	{13,  4},
	{15,  4},
	{17,  4},
	{ 2,  3},
	{ 4,  3},
	{ 6,  3},
	{ 8,  3},
	{10,  3},
	{12,  3},
	{14,  3},
	{16,  3},
	{16, 19},
	{14, 17},
    {12, 15},
	{ 7,  9},
	{15,  9},
	{ 6,  8},
	{18,  3}
};

// A map of museum artifact positions to the artifact ID.
// Hopefully this will make searches faster
std::map<std::pair<int, int>, int> g_museum_artifacts;

// Vectors to hold item values for the
std::vector<int> g_equipment_shop_item_values;
std::vector<int> g_item_shop_item_values;
std::vector<int> g_equipment_shop_item_sell_values;
std::vector<int> g_item_shop_item_sell_values;
