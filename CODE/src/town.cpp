
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

void unlock_dungeons() {
	if (g_player.can_enter_marble_halls) {
		g_town_tile_data[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = 1;
	}

	if (g_player.can_enter_crystal_depths) {
		g_town_tile_data[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = 1;
	}
}