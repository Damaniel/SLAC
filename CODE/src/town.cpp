
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
void unlock_dungeon(int dungeon) {
	if (dungeon == MARBLE_HALLS && g_game_flags.can_enter_marble_halls && !g_game_flags.has_unlocked_marble_halls) {
		g_town_tile_data[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::MARBLE_HALLS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::MARBLE_HALLS_GATE_X] = 1;
		g_game_flags.has_unlocked_marble_halls = true;
	}

	if (dungeon == CRYSTAL_DEPTHS && g_game_flags.can_enter_crystal_depths && !g_game_flags.has_unlocked_crystal_depths) {
		g_town_tile_data[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = TownConsts::UNLOCKED_GATE_TILE;
		g_town_movability[TownConsts::CRYSTAL_DEPTHS_GATE_Y * TownConsts::TOWN_SIZE + TownConsts::CRYSTAL_DEPTHS_GATE_X] = 1;
		g_game_flags.has_unlocked_crystal_depths = true;
	}

	// Redraw the maze area in case the locked door is on the screen
	g_state_flags.update_maze_area = true;
	g_state_flags.update_display = true;
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