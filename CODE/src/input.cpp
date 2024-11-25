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
#include "globals.h"

void pick_up_item_at(int x, int y) {
    if (g_maze->get_num_items_at(x, y) > 0) {

        // Add it to the inventory
        if (!g_inventory->inventory_is_full()) {
            std::list<Item *> items = g_maze->get_items_at(x, y);
            g_inventory->add_at_first_empty(items.back());
            g_text_log.put_line("Picked up " + items.back()->get_full_name() + ".");
            g_maze->remove_item_from_end_at(x, y);
            // TODO: I may want to remove this maze area update...
            g_state_flags.update_maze_area = true;
            g_state_flags.update_text_dialog = true;
            g_state_flags.update_display = true;
        }
    }
}
//----------------------------------------------------------------------------
// Handles common tasks required after the player moves into a new square
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_movement_flags(void) {
    // Redraw the maze area
	g_state_flags.update_maze_area = true;
    // Redraw the log if the text log is in extended mode (as it
    // will be overdrawn by the maze if this isn't done)
	if (g_state_flags.text_log_extended) {
		g_state_flags.update_text_dialog = true;
	}
    // Tell the game to do the redraw
	g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Handles all input for the inventory substate (that is, when the inventory
// is on screen)
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_inventory_substate(int key) {
    switch (key) {
        // If I or ESC is pressed, exit the inventory screen
        case KEY_I:
        case KEY_ESC:
            g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;

            g_state_flags.update_maze_area = true;
            if (g_state_flags.text_log_extended) {
                g_state_flags.update_text_dialog = true;
            }
            g_state_flags.update_display = true;
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the map substate (that is, when the map is on screen)
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_map_substate(int key) {
    switch (key) {
        // If M or ESC is pressed, exit the map screen
        case KEY_M:
        case KEY_ESC:
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

//----------------------------------------------------------------------------
// Handles all input for the main game state, plus any current substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_game_state(int key) {
    switch (g_state_flags.cur_substate) {
        case GAME_SUBSTATE_MAP:
            process_map_substate(key);
            break;
        case GAME_SUBSTATE_INVENTORY:
            process_inventory_substate(key);
            break;
        case GAME_SUBSTATE_DEFAULT:
            // Handle lighting status for the current room.
            // TODO: Maybe figure out if this is really the best place for this.
		    g_player.set_last_room_entered(g_maze->get_room_id_at(g_player.x_pos, g_player.y_pos));
		    // Darken the current space around the player if not in a room
		    if (g_player.get_last_room_entered() == -1) {
    		    g_maze->change_lit_status_around(g_player.x_pos, g_player.y_pos, false);
		    }            
            switch (key) {
                case KEY_ESC:
            	    g_state_flags.exit_game = true;
                    break;
                case KEY_LEFT:
        		    if (g_maze->is_carved(g_player.x_pos-1, g_player.y_pos) == true) {
			            g_player.x_pos = g_player.x_pos -1;
			            process_movement_flags();
			            add_items_at_player_to_log();
		            }
                    break;           
	            case KEY_RIGHT:
            		if (g_maze->is_carved(g_player.x_pos+1, g_player.y_pos) == true) {			
	    		        g_player.x_pos = g_player.x_pos + 1;
		    	        process_movement_flags();
			            add_items_at_player_to_log();
		            }
                    break;
    	        case KEY_UP:
        	    	if (g_maze->is_carved(g_player.x_pos, g_player.y_pos-1) == true) {
    			        g_player.y_pos = g_player.y_pos - 1;
	    		        process_movement_flags();
		    	        add_items_at_player_to_log();
		            }
                    break;
                case KEY_DOWN:
            		if (g_maze->is_carved(g_player.x_pos, g_player.y_pos+1) == true)
	    	        {
        	    		g_player.y_pos = g_player.y_pos + 1;
			            process_movement_flags();
			            add_items_at_player_to_log();
		            }
                    break;
	            case KEY_M:
                    g_state_flags.cur_substate = GAME_SUBSTATE_MAP;
                    g_state_flags.update_map_dialog = true;
	    	        g_state_flags.update_display = true;
                    break;
                case KEY_I:
                    g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                    g_state_flags.update_inventory_dialog = true;
                    g_state_flags.update_display = true;
                    break;
                case KEY_G:
                    pick_up_item_at(g_player.x_pos, g_player.y_pos);    
                    break;
	            case KEY_TILDE:
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
                    break;
	        }
            break;
    }
}

//----------------------------------------------------------------------------
// Handles keyboard input for all game states, delegating as needed
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_input(void) {
	int key = (readkey() >> 8);

    switch(g_state_flags.cur_state) {
        case STATE_MAIN_GAME:
            process_game_state(key);
            break;
    }
}