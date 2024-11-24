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
#include "globals.h"

void process_movement_flags(void) {
	g_state_flags.update_maze_area = true;
	if (g_state_flags.text_log_extended) {
		g_state_flags.update_text_dialog = true;
	}
	g_state_flags.update_display = true;
}

void process_inventory_substate(int key) {

}

void process_map_substate(int key) {
    switch (key) {
        case KEY_M:
    		g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;

            // Redraw the maze area, and the extended log if enabled
		    g_state_flags.update_maze_area = true;
		    if (g_state_flags.text_log_extended) {
    		    g_state_flags.update_text_dialog = true;
		    }
            g_state_flags.update_display = true;
            break;
    } 
}

void process_game_state(int key) {
    if (g_state_flags.cur_substate == GAME_SUBSTATE_MAP) {
        process_map_substate(key);
    }
    else if (g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY) {
        process_inventory_substate(key);
    }
    else {
        if (key == KEY_ESC) {
		    g_state_flags.exit_game = true;
	    }

	    if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN) 
	    {
    		// If the player is currently in a room, keep track of that room ID so we can darken
		    // the room if the player leaves it on move
		    g_player.set_last_room_entered(g_maze->get_room_id_at(g_player.x_pos, g_player.y_pos));
		    // Darken the current space around the player if not in a room
		    if (g_player.get_last_room_entered() == -1) {
    			g_maze->change_lit_status_around(g_player.x_pos, g_player.y_pos, false);
		    }
	    }
	    if (key == KEY_LEFT) {
    		if (g_maze->is_carved(g_player.x_pos-1, g_player.y_pos) == true) {
			    g_player.x_pos = g_player.x_pos -1;
			    process_movement_flags();
			    add_items_at_player_to_log();
		    }
	    }
	    if (key == KEY_RIGHT) {
    		if (g_maze->is_carved(g_player.x_pos+1, g_player.y_pos) == true) {			
			    g_player.x_pos = g_player.x_pos + 1;
			    process_movement_flags();
			    add_items_at_player_to_log();
		    }
	    }
	    if (key == KEY_UP) {
    		if (g_maze->is_carved(g_player.x_pos, g_player.y_pos-1) == true) {
			    g_player.y_pos = g_player.y_pos - 1;
			    process_movement_flags();
			    add_items_at_player_to_log();
		    }
	    }
	    if (key == KEY_DOWN) {
    		if (g_maze->is_carved(g_player.x_pos, g_player.y_pos+1) == true)
		    {
    			g_player.y_pos = g_player.y_pos + 1;
			    process_movement_flags();
			    add_items_at_player_to_log();
		    }
	    }
	    if (key == KEY_M) {
            g_state_flags.cur_substate = GAME_SUBSTATE_MAP;
		    g_state_flags.update_display = true;
	    }

	    if (key == KEY_TILDE && g_state_flags.input_disabled == false) {
    		if (g_state_flags.text_log_extended) {
			    g_state_flags.text_log_extended = false;
		    }
		    else {
    			g_state_flags.text_log_extended = true;
		    }
		    g_state_flags.update_text_dialog = true;
		    g_state_flags.update_maze_area = true;
		    g_state_flags.update_status_dialog = true;
		    g_state_flags.update_display = true;
	    }
    }
}

void process_input(void) {
	int key = (readkey() >> 8);

    switch(g_state_flags.cur_state) {
        case STATE_MAIN_GAME:
            process_game_state(key);
            break;
    }
}