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

// Game-specific include files
#include "globals.h"
#include <map>
#include <list>

// Some Allegro defines to remove unused graphics and joystick modes
BEGIN_GFX_DRIVER_LIST
	GFX_DRIVER_MODEX
END_GFX_DRIVER_LIST

BEGIN_COLOR_DEPTH_LIST
	COLOR_DEPTH_8
END_COLOR_DEPTH_LIST

BEGIN_JOYSTICK_DRIVER_LIST
END_JOYSTICK_DRIVER_LIST

// Globals used to hold game state.  External defines are in globals.h
DATAFILE  	*g_game_data;
BITMAP    	*g_back_buffer;
Player 	   	 g_player;
StateFlags 	 g_state_flags;
Render       g_render;

// The current dungeon.
DungeonFloor   g_dungeon;

//------------------------------------------------------------------------------
// Retreives the name of the dungeon specified by the given ID
//
// Arguments:
//   dungeon - the id of the dungeon
//
// Returns:
//   A string containing the name of the dungeon
//------------------------------------------------------------------------------
std::string get_dungeon_name(int dungeon, bool abbrev) {
	if (abbrev) {
		switch (dungeon) {
			case DUSTY_TUNNELS:
				return "D. Tunnels";
				break;
			case MARBLE_HALLS:
				return "M. Halls";
				break;
			case CRYSTAL_DEPTHS:
				return "C. Depths";
				break;
			default:
				return "Huh?";
				break;
		}

	} 
	else {
		switch (dungeon) {
			case DUSTY_TUNNELS:
				return "Dusty Tunnels";
				break;
			case MARBLE_HALLS:
				return "Marble Halls";
				break;
			case CRYSTAL_DEPTHS:
				return "Crystal Depths";
				break;
			default:
				return "Huh?";
				break;
		}
	}
}

std::string get_generation_string(int generation) {
	int suffix = generation % 100;
	char gen_string[16];

	switch (suffix) {
		case 1:
			sprintf(gen_string, "Senior");
			break;
		case 2:
			sprintf(gen_string, "Junior");
			break;
		case 21:
		case 31:
		case 41:
		case 51:
		case 61:
		case 71:
		case 81:
		case 91:
			sprintf(gen_string, "%dst", generation);
			break;
		case 22:
		case 32:
		case 42:
		case 52:
		case 62:
		case 72:
		case 82:
		case 92:
			sprintf(gen_string, "%dnd", generation);
			break;
		case 3:
		case 23:
		case 33:
		case 43:
		case 53:
		case 63:
		case 73:
		case 83:
		case 93:
			sprintf(gen_string, "%drd", generation);
			break;
		default:
			sprintf(gen_string, "%dth", generation);
	}

	return std::string(gen_string);
}

//------------------------------------------------------------------------------
// Loads and prepares all game resources from the data file
//
// Arguments:
//   None
//
// Returns:
//   0 if data was loaded successfully, non-zero otherwise
//------------------------------------------------------------------------------
int load_resources(void) {
	
	g_game_data = load_datafile("game.dat");
	if(g_game_data == NULL) {
		printf("Unable to open game data file.  Is it in the right place?\n");
		return 1;
	}		
	return 0;
}

//------------------------------------------------------------------------------
// Perform any initializtion tasks that need to be done with game data.
// 
// Arguments:
//   r - a reference to the Render object to init
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void init_resources(Render &r) {	
	r.copy_data_to_offscreen_vram();	
	set_palette((RGB *)g_game_data[DAMRL_DB16].dat);		
	g_back_buffer = create_sub_bitmap(screen, 0, 240, 320, 240);
}

//----------------------------------------------------------------------------------
// Free up any game related resources.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void unload_resources(void) {
	unload_datafile(g_game_data);
}

//------------------------------------------------------------------------------
// Creates a new maze floor, deleting any existing one first.
//
// Arguments:
//   d - a reference to a DungeonFloor that will contain the new floor
//   level - the dungeon level to generate (affects iLevel)
//   stairs_from - the kind of stairs the player came from 
//
// Returns:
//   Nothing
//
// Notes:
//   stairs_from is used to place the player on the correct kind of stairs
//   corresponding to the floor they came from (up stairs if the player went
//   down, and down stairs if the player went up)
//------------------------------------------------------------------------------
void generate_new_dungeon_floor(DungeonFloor &d, int level, int stairs_from) {
	if (d.maze != NULL) {
		delete d.maze;
	}

	//std::cout << "generate_new_dungeon_floor: Generating floor " << level << "..." << std::endl;

	d.depth = level;

	// Set the maximum depth and size for the current dungeon
	// Yes, this is done every floor when it doesn't need to be, but fine.
	d.max_depth = g_max_dungeon_depths[d.maze_id];
	d.width = g_dungeon_sizes[d.maze_id];
	d.height = g_dungeon_sizes[d.maze_id];

	// Set the current ilevel based on the dungeon the player is in and the
	// floor they're on
	switch (d.maze_id) {
		case DUSTY_TUNNELS:
			d.ilevel = level / 2;
			if (d.ilevel < 1 ) d.ilevel = 1;
			if (d.ilevel > 25) d.ilevel = 25;
			break;
		case MARBLE_HALLS:
			d.ilevel = 20 + (level / 2);
			if (d.ilevel < 20 ) d.ilevel = 20;
			if (d.ilevel > 70) d.ilevel = 70;
			break;
		case CRYSTAL_DEPTHS:
			d.ilevel = 30 + (level / 2);
			if (d.ilevel < 30 ) d.ilevel = 30;
			if (d.ilevel > 100) d.ilevel = 100;
			break;
		default:
			d.ilevel = 100;
			break;
	}

	d.maze = new Maze(d.width, d.height, d.ilevel);

	// If we're at the bottom, direct the maze generator to omit down stairs
	if(d.depth >= d.max_depth)
		d.maze->set_stair_gen_behavior(MazeConsts::GENERATE_NO_DOWN_STAIRS);

	d.maze->generate();

	std::pair<int, int> stairLoc;
	// Place the player on a random set of stairs based on where they came from
	if (stairs_from == MazeConsts::STAIRS_DOWN)
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_UP);
	else
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_DOWN);

	// Place the player at the stair location
	g_player.set_position(stairLoc.first, stairLoc.second);
	
	// Hack to force lighting in the initial room the player is in
	int initial_room = d.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos());
	g_player.set_last_room_entered(initial_room);	
	if (initial_room != -1) {
		// double hack to mark the room as seen so that the map renderer can
		// display it
		d.maze->change_room_lit_status(initial_room, false);		
		d.maze->change_room_lit_status(initial_room, true);			
	}
	
	// Does the display need to be refreshed?
	g_state_flags.update_display = true;
	
	// Tell the renderer to draw these first thing.
	g_state_flags.update_maze_area = true;
	g_state_flags.update_status_dialog = true;
	g_state_flags.update_text_dialog = true;

	// Use the short text log by default
	g_state_flags.text_log_extended = false;

	// Clear the map bitmap
	g_render.initialize_map_bitmap(g_dungeon.maze);

	// Force an explicit display update so the user can see the world right away
	update_display();
}

//------------------------------------------------------------------------------
// Do any initialization tasks required when moving into the new game state
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void initialize_main_game_state(void) {
	if (g_dungeon.maze != NULL) {
		delete g_dungeon.maze;
		g_dungeon.maze = NULL;
	}

	// Create a new dungeon floor (first floor, coming down from surface)
	generate_new_dungeon_floor(g_dungeon, 1, MazeConsts::STAIRS_DOWN);

	// create a new inventory (TODO - move to an earlier state)
	g_inventory = new Inventory();
}

//------------------------------------------------------------------------------
// Moves the state machine to a new state and initializes accordingly
//
// Arguments:
//   new_state - the state to change to
//
// Returns:
//   Nothing.
//------------------------------------------------------------------------------
void change_state(int new_state) {
    g_state_flags.prev_state = g_state_flags.cur_state;
    g_state_flags.cur_state = new_state;
    g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;

    switch (g_state_flags.cur_state) {
        case STATE_MAIN_GAME:
			initialize_main_game_state();
			break;
    }
}

//------------------------------------------------------------------------------
// Adds log entries for any item(s) sitting at the player's current position
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void add_items_at_player_to_log(void) {
	int item_count = g_dungeon.maze->get_num_items_at(g_player.get_x_pos(), g_player.get_y_pos());
	int idx = 0;

	if (item_count > 0) {
		std::list<Item *> items = g_dungeon.maze->get_items_at(g_player.get_x_pos(), g_player.get_y_pos());
		for (std::list<Item *>::iterator it = items.begin(); it != items.end(); ++ it) {
			if (idx == 0)
				g_text_log.put_line("You see " + (*it)->get_full_name() + ".");
			else
				g_text_log.put_line("You also see " + (*it)->get_full_name() + ".");
			++idx;
		}
		g_state_flags.update_text_dialog = true;
		g_state_flags.update_display = true;
	}
}

//----------------------------------------------------------------------------------
// MAIN
//
// Notes:
//   Most of the code in here is just testing stuff.  There's no official game
//   loop of any kind yet, and stuff in here is subject to change and/or removal.
//----------------------------------------------------------------------------------
int main(void) {

	srand(time(NULL));
	
	allegro_init();
	install_timer();
	install_keyboard();

	int mode_result = set_gfx_mode(GFX_MODEX, 320, 240, 320, 640);
	if (mode_result != 0) {
		set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Unable to set graphics mode!\n");
	}

	clear(screen);
	
	int res_result = load_resources();
	if(res_result != 0) {
		printf("Failure while loading resources!\n");
		return 1;
	}
	init_resources(g_render);

	g_player = Player();

	// Loop until done.  Right now, 'done' = pressing Esc
	g_state_flags.exit_game = false;

	change_state(STATE_MAIN_GAME);

	//std::cout << "State initialized" << std::endl;

	// Main game loop
	do {
		// Handle all input
		process_input();

		// Process all non-input actions
		// process_non_player_actions();

		// update the display
		if (g_state_flags.update_display == true) {
			update_display();					
		}
	} while (g_state_flags.exit_game == false);

	//std::cout << "main: deleting inventory" << std::endl;
	delete g_inventory;

	//std::cout << "main: deleting maze" << std::endl;
	if (g_dungeon.maze != NULL) {
		delete g_dungeon.maze;
	}
	
	unload_resources();
	set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

	return 0;
}
