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
DATAFILE  	  *g_game_data;
BITMAP    	  *g_back_buffer;
Player 	   	   g_player;
StateFlags 	   g_state_flags;
GameFlags      g_game_flags;
Render         g_render;
DungeonFloor   g_dungeon;
HallOfChampionsEntry g_hall_of_champions[UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES];

/*=============================================================================
 * process_timing_stuff
 *============================================================================*/
void process_per_frame() {

	if (g_state_flags.cur_state == STATE_MAIN_GAME &&
	    g_state_flags.cur_substate != GAME_SUBSTATE_PLAYER_JUST_DIED) {
		g_state_flags.time_to_update_elapsed -= 1;
		if (g_state_flags.time_to_update_elapsed <= 0) {
			g_game_flags.elapsed_time += 1;
			g_state_flags.time_to_update_elapsed = FRAME_RATE;
			g_state_flags.update_status_elapsed_time = true;
			g_state_flags.update_display = true;
		}
	}
}

/*=============================================================================
 * int_handler
 *============================================================================*/
void int_handler() {
  /* do animation stuff here */
  g_state_flags.frame_counter++;
  g_state_flags.next_frame = 1;
}
END_OF_FUNCTION(int_handler);

//----------------------------------------------------------------------------
// Does required startup tasks (init/load graphics, set graphics mode,
// set game flags)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void init_game() {
	// Set up the RNG
	srand(time(NULL));

	// Initialize graphics and input subsystem
	allegro_init();
	install_timer();
	install_keyboard();

  	install_int(int_handler, 1000/FRAME_RATE);

	// Set graphics mode
	int mode_result = set_gfx_mode(GFX_MODEX, 320, 240, 320, 640);
	if (mode_result != 0) {
		set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Unable to set graphics mode!\n");
		shut_down_game();
		exit(1);
	}
	clear(screen);

	// Load the graphics datafile
	int res_result = load_resources();
	if(res_result != 0) {
		printf("Failure while loading graphics data!\n");
		shut_down_game();
		exit(1);
	}

	// Initializes some extra graphics stuff (the map bitmap, the palette,
	// etc)
	init_resources(g_render);

	// Reset the global game flags
	reset_game_flags();

	// Populate the museum artifact map
	init_museum_artifacts();

	// Null out the inventory
	g_inventory = NULL;

	// Create the player
	g_player = Player();

	// Make the game loop until 'done' (right now, mainly by pressing ESC)
	g_state_flags.exit_game = false;

	g_state_flags.loading_save = false;
	g_state_flags.save_loaded = false;

	// Timer related stuff
	g_state_flags.frame_counter = 0;
	g_state_flags.next_frame = 1;
	g_game_flags.elapsed_time = 0;
	g_state_flags.time_to_update_elapsed = FRAME_RATE;

	// Check to see if the hall of champions file exists
	// If not, blank out the data
	if (slac_file_exists(SaveLoadConsts::hoc_file)) {
		load_hall_of_champions();
	}
	else {
		init_hall_of_champions_entries();
	}
}

//----------------------------------------------------------------------------
// Does cleanup on game exit (deallocates resources, resets video mode, etc)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void shut_down_game() {
	// Save the hall of champions file
	save_hall_of_champions();

	// Delete the inventory and all items in it
	if (g_inventory != NULL)
		delete g_inventory;

	// If any existing equipment or item shop inventories exist, delete them
	if (g_weapon_shop_inventory != NULL) {
		delete g_weapon_shop_inventory;
	}

	if (g_item_shop_inventory != NULL) {
		delete g_item_shop_inventory;
	}

	// Delete the maze
	if (g_dungeon.maze != NULL)
		delete g_dungeon.maze;

	// Delete all items/enemies that were associated with the maze
	g_dungeon.clear_lists();

	// Unload graphics and reset the video mode
	unload_resources();
	set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
}

//----------------------------------------------------------------------------------
// MAIN
//----------------------------------------------------------------------------------
int main(void) {
	std::cout << "Loading game..." << std::endl;

	init_game();
	change_state(STATE_TITLE_SCREEN);

	// Main game loop
	do {
		process_input();
		if (g_state_flags.next_frame) {
			process_per_frame();
			g_state_flags.next_frame = 0;
		}
		if (g_state_flags.update_display == true) {
			update_display();
		}
	} while (g_state_flags.exit_game == false);

	shut_down_game();
	return 0;
}
