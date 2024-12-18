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
DATAFILE  	  *g_game_data;
BITMAP    	  *g_back_buffer;
Player 	   	   g_player;
StateFlags 	   g_state_flags;
Render         g_render;
DungeonFloor   g_dungeon;

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
	
	//std::cout << "main: clearing remaining items/enemies" << std::endl;
	g_dungeon.clear_lists();
	
	unload_resources();
	set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);

	return 0;
}
