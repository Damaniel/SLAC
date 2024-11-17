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

// Game-specific include files
#include "globals.h"

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
Maze      g_maze;

//----------------------------------------------------------------------------------
// load_resources
//
// Loads and processes all game resources.  Most are stored in the global 
// datafile, so that's all that gets loaded right now.
//----------------------------------------------------------------------------------
int load_resources(void) {
	
	g_game_data = load_datafile("game.dat");
	if(g_game_data == NULL) {
		printf("Unable to open game data file.  Is it in the right place?\n");
		return 1;
	}		
	return 0;
}

//----------------------------------------------------------------------------------
// init_resources
//
// Perform any initializtion tasks that need to be done with game data.
//----------------------------------------------------------------------------------
void init_resources(Render r) {	
	r.copy_data_to_offscreen_vram();	
	set_palette((RGB *)g_game_data[DAMRL_DB16].dat);		
	g_back_buffer = create_sub_bitmap(screen, 0, 240, 320, 240);
}

//----------------------------------------------------------------------------------
// unload_resources
//
// Free up any game related resources.
//----------------------------------------------------------------------------------
void unload_resources(void) {
	unload_datafile(g_game_data);
}

void update_display(void) {
	if (g_state_flags.map_displayed == true) {
		g_render.render_map(g_back_buffer, g_maze);
	}
	else {		
		if (g_state_flags.update_maze_area == true) {
			// TODO: move elsewhere
			// Add the areas around the player to the map bitmap
			g_render.add_area_to_map_bitmap(g_maze, g_player.x_pos, g_player.y_pos);

			// Light the space around the player
			g_maze.change_lit_status_around(g_player.x_pos, g_player.y_pos, true);

			// Check what room the player is in, if any
			int room_to_light = g_maze.get_room_id_at(g_player.x_pos, g_player.y_pos);
			int last_player_room = g_player.get_last_room_entered();
			
			// If the player was in a room but no longer is, then darken the room
			if(last_player_room != -1 && room_to_light == -1) {
				g_maze.change_room_lit_status(last_player_room, false);
			}
			// If the player wasn't in a room but now is, then light up the room
			if(last_player_room == -1 && room_to_light != -1) {
				g_maze.change_room_lit_status(room_to_light, true);
				// TODO: restructure this!
				// Mark the room itself as visited so rendering the map will
				// show the room even at the start of the game
				g_maze.set_room_as_entered(room_to_light);
			}
			
			// Draw the world display area
			g_render.render_world_at_player(g_back_buffer, g_maze, g_player.x_pos, g_player.y_pos);
			g_state_flags.update_maze_area = false;
		}
	}

	if(g_state_flags.update_status_dialog == true) {
		g_render.render_status_base(g_back_buffer);
		g_state_flags.update_status_dialog = false;
	}

	if(g_state_flags.update_text_dialog == true) {
		g_render.render_text_base(g_back_buffer, false);
		g_state_flags.update_text_dialog = false;
	}

	// Now actually put the image on the visible part of the screen
	vsync();
	blit(g_back_buffer, screen, 0, 0, 0, 0, 320, 240);	
	
	// Display is updated - we don't want to do it again right now.
	g_state_flags.update_display = false;
}

// TODO:
// Clean up hacks here... eventually.
void initialize_state(void) {
	// Place the player on a random set of up stairs
	std::vector<int> stairLoc = g_maze.get_random_stair(STAIRS_UP);

	// Create a new player at the stair location
	g_player = Player(stairLoc[0], stairLoc[1]);
	
	// Hack to force lighting in the initial room the player is in
	int initial_room = g_maze.get_room_id_at(g_player.x_pos, g_player.y_pos);
	g_player.set_last_room_entered(initial_room);	
	if (initial_room != -1) {
		// double hack to mark the room as seen so that the map renderer can
		// display it
		g_maze.change_room_lit_status(initial_room, false);		
		g_maze.change_room_lit_status(initial_room, true);			
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
	// Is the map currently displayed?
	g_state_flags.map_displayed = false;

	// Force an explicit display update so the user can see the world right away
	update_display();

}

void process_input(void) {
	int key = (readkey() >> 8);

	if (key == KEY_ESC) {
		g_state_flags.exit_game = true;
	}

	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN) 
	{
		// If the player is currently in a room, keep track of that room ID so we can darken
		// the room if the player leaves it on move
		g_player.set_last_room_entered(g_maze.get_room_id_at(g_player.x_pos, g_player.y_pos));
		// Darken the current space around the player if not in a room
		if (g_player.get_last_room_entered() == -1) {
			g_maze.change_lit_status_around(g_player.x_pos, g_player.y_pos, false);
		}
	}
	if (key == KEY_LEFT && g_state_flags.input_disabled == false) {
		if (g_maze.is_carved(g_player.x_pos-1, g_player.y_pos) == true) {
			g_player.x_pos = g_player.x_pos -1;
			g_state_flags.update_maze_area = true;
			g_state_flags.update_display = true;
		}
	}
	if (key == KEY_RIGHT && g_state_flags.input_disabled == false) {
		if (g_maze.is_carved(g_player.x_pos+1, g_player.y_pos) == true) {			
			g_player.x_pos = g_player.x_pos + 1;
			g_state_flags.update_maze_area = true;
			g_state_flags.update_display = true;
		}
	}
	if (key == KEY_UP && g_state_flags.input_disabled == false) {
		if (g_maze.is_carved(g_player.x_pos, g_player.y_pos-1) == true) {
			g_player.y_pos = g_player.y_pos - 1;
			g_state_flags.update_maze_area = true;
			g_state_flags.update_display = true;
		}
	}
	if (key == KEY_DOWN && g_state_flags.input_disabled == false) {
		if (g_maze.is_carved(g_player.x_pos, g_player.y_pos+1) == true)
		{
			g_player.y_pos = g_player.y_pos + 1;
			g_state_flags.update_maze_area = true;
			g_state_flags.update_display = true;
		}
	}
	if (key == KEY_M) {
		if (g_state_flags.map_displayed == true) {
			g_state_flags.map_displayed = false;
			g_state_flags.update_maze_area = true;
			g_state_flags.input_disabled = false;
		} else {
			g_state_flags.map_displayed = true;
			g_state_flags.input_disabled = true;
		}
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
	
	// allegro_init();
	// install_timer();
	// install_keyboard();

	// int mode_result = set_gfx_mode(GFX_MODEX, 320, 240, 320, 640);
	// if (mode_result != 0) {
	// 	set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
	// 	printf("Unable to set graphics mode!\n");
	// }

	// clear(screen);
	
	// int res_result = load_resources();
	// if(res_result != 0) {
	// 	printf("Failure while loading resources!\n");
	// 	return 1;
	// }
	// init_resources(g_render);

	// g_maze = Maze(30,30);
	// g_maze.generate();

	// // TODO: Should be done on a per-floor basis!
	// g_render.initialize_map_bitmap(g_maze);

	// initialize_state();

	// // Main game loop
	// do {
		
	// 	// Handle all input
	// 	process_input();

	// 	// Process all non-input actions
	// 	// process_non_player_actions();

	// 	// update the display
	// 	if (g_state_flags.update_display == true) {
	// 		update_display();					
	// 	}
	// } while (g_state_flags.exit_game == false);

	// unload_resources();
	// set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

	Item *it;
	for (int i=0; i < 10; i++) {
		std::cout << std::endl;
		it = ItemGenerator::generate();
		if (it != NULL) { 
			std::cout << "Roll " << (i+1) << ", item is now " << it->get_full_name() << std::endl;
			it->dump_item();
			delete it;
		}
		else {
			std::cout << "Roll " << (i+1) << ", <not defined yet>" << std::endl;
		}
	}

	// g_inventory = new Inventory();

	// Item *w = new Weapon(2);
	// w->add_prefix(0);
	// w->add_suffix(0);
	// Item *a = new Armor(&(g_armor_base_ids[7]));
	// a->add_prefix(1);
	// a->add_suffix(0);
	
	// int first_empty = g_inventory->get_first_empty_slot();
	// std::cout << std::endl;
	// if(first_empty >= 0) {
	// 	g_inventory->add_at_slot(w, first_empty);
	// 	g_inventory->get_item_in_slot(first_empty)->dump_item();
	// }

	// std::cout << std::endl;
	// int slot_used = g_inventory->add_at_first_empty(a);
	// std::cout << std::endl;
	// if(slot_used >=0)
	// 	g_inventory->get_item_in_slot(slot_used)->dump_item();

	// std::cout << std::endl << "Slots in use = " << g_inventory->get_num_slots_in_use() << std::endl;
	// delete g_inventory;

	return 0;
}