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

// The current maze.
// TODO: This will be part of a larger dungeon state object later on.
Maze      *g_maze;

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
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void create_new_maze_floor(void) {
	if (g_maze != NULL) {
		delete g_maze;
	}

	g_maze = new Maze(30, 30);
	g_maze->generate();

	//std::cout << "main: generate() completed" << std::endl;
	g_render.initialize_map_bitmap(g_maze);
	//std::cout << "Map bitmap is initialized" << std::endl;
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

	// TODO: some things in here shouldn't be handled by the main state
	// initialization.  We're just doing it for now.

	// Make a new maze floor
	create_new_maze_floor();

	// Place the player on a random set of up stairs
	std::pair<int, int> stairLoc = g_maze->get_random_stair(STAIRS_UP);

	// Create a new player at the stair location
	g_player = Player(stairLoc.first, stairLoc.second);
	
	// Hack to force lighting in the initial room the player is in
	int initial_room = g_maze->get_room_id_at(g_player.x_pos, g_player.y_pos);
	g_player.set_last_room_entered(initial_room);	
	if (initial_room != -1) {
		// double hack to mark the room as seen so that the map renderer can
		// display it
		g_maze->change_room_lit_status(initial_room, false);		
		g_maze->change_room_lit_status(initial_room, true);			
	}
	
	// Loop until done.  Right now, 'done' = pressing Esc
	g_state_flags.exit_game = false;
	// Does the display need to be refreshed?
	g_state_flags.update_display = true;
	
	// Tell the renderer to draw these first thing.
	g_state_flags.update_maze_area = true;
	g_state_flags.update_status_dialog = true;
	g_state_flags.update_text_dialog = true;

	// Is the player locked out from keypresses due to a dialog being displayed?
	g_state_flags.input_disabled = false;

	g_state_flags.text_log_extended = false;

	// Force an explicit display update so the user can see the world right away
	update_display();
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
	int item_count = g_maze->get_num_items_at(g_player.x_pos, g_player.y_pos);
	int idx = 0;

	if (item_count > 0) {
		std::list<Item *> items = g_maze->get_items_at(g_player.x_pos, g_player.y_pos);
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

	g_maze = NULL;
	g_inventory = new Inventory();

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

	unload_resources();
	set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

	delete g_maze;
	delete g_inventory;

	return 0;
}
