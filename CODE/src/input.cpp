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
// Handles common tasks required after the inventory cursor is moved
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_inventory_movement_flags(void) {
    g_state_flags.update_inventory_cursor = true;
    g_state_flags.update_inventory_description = true;
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Handles all input for the inventory submenu substate.
//
// Arguments:
//   key - the key that was pressed.
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_inventory_menu_substate(int key) {
    switch(key) {
        case KEY_UP:
            g_ui_globals.sel_item_option -= 1;
            if (g_ui_globals.sel_item_option < 0) {
                g_ui_globals.sel_item_option = UiConsts::NUM_ITEM_SUBMENU_OPTIONS - 1;
            }
            g_state_flags.update_inventory_submenu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_DOWN:
            g_ui_globals.sel_item_option += 1;
            if (g_ui_globals.sel_item_option >= UiConsts::NUM_ITEM_SUBMENU_OPTIONS) {
                g_ui_globals.sel_item_option = 0;
            }
            g_state_flags.update_inventory_submenu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ENTER:
            // If 'Close' is selected, exit the inventory menu
            if (g_ui_globals.sel_item_option == UiConsts::NUM_ITEM_SUBMENU_OPTIONS - 1) {
                g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                g_state_flags.update_inventory_dialog = true;
                g_state_flags.update_inventory_cursor = true;
                g_state_flags.update_inventory_items = true;
                g_state_flags.update_inventory_description = true;
                g_state_flags.update_display = true;               
            } 
            else {
                // Do the thing that the selected menu option does, if valid
            }
            break;
        case KEY_ESC:
            g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
            g_state_flags.update_inventory_dialog = true;
            g_state_flags.update_inventory_cursor = true;
            g_state_flags.update_inventory_items = true;
            g_state_flags.update_inventory_description = true;
            g_state_flags.update_display = true;
            break;
    }
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
        // If an arrow key is pressed, move the cursor around
        case KEY_UP:
            g_ui_globals.prev_inv_cursor_x = g_ui_globals.inv_cursor_x;
            g_ui_globals.prev_inv_cursor_y = g_ui_globals.inv_cursor_y;
            g_ui_globals.inv_cursor_y = g_ui_globals.inv_cursor_y - 1;
            if (g_ui_globals.inv_cursor_y < 0) 
                g_ui_globals.inv_cursor_y = UiConsts::INVENTORY_ROWS - 1;
            process_inventory_movement_flags();
            break;
        case KEY_DOWN:
            g_ui_globals.prev_inv_cursor_x = g_ui_globals.inv_cursor_x;
            g_ui_globals.prev_inv_cursor_y = g_ui_globals.inv_cursor_y;
            g_ui_globals.inv_cursor_y = g_ui_globals.inv_cursor_y + 1;
            if (g_ui_globals.inv_cursor_y >= UiConsts::INVENTORY_ROWS) 
                g_ui_globals.inv_cursor_y = 0;
            process_inventory_movement_flags();
            break;
        case KEY_LEFT:
            g_ui_globals.prev_inv_cursor_x = g_ui_globals.inv_cursor_x;
            g_ui_globals.prev_inv_cursor_y = g_ui_globals.inv_cursor_y;
            g_ui_globals.inv_cursor_x = g_ui_globals.inv_cursor_x - 1;
            if (g_ui_globals.inv_cursor_x < 0) 
                g_ui_globals.inv_cursor_x = UiConsts::INVENTORY_ITEMS_PER_ROW - 1;
            process_inventory_movement_flags();
            break;
        case KEY_RIGHT:
            g_ui_globals.prev_inv_cursor_x = g_ui_globals.inv_cursor_x;
            g_ui_globals.prev_inv_cursor_y = g_ui_globals.inv_cursor_y;
            g_ui_globals.inv_cursor_x = g_ui_globals.inv_cursor_x + 1;
            if (g_ui_globals.inv_cursor_x >= UiConsts::INVENTORY_ITEMS_PER_ROW) 
                g_ui_globals.inv_cursor_x = 0;
            process_inventory_movement_flags();
            break;
        // If Enter is pressed, bring up the inventory submenu, but only if there's an item
        // in the slot.
        case KEY_ENTER:
            {
                Item *i = g_inventory->get_item_in_slot(g_ui_globals.inv_cursor_y * 
                                       UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_cursor_x);
                if (i != NULL) {    
                    g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY_MENU;
                    g_state_flags.update_inventory_submenu = true;
                    g_state_flags.update_display = true;
                    g_ui_globals.sel_item_option = 0;
                }
            }
            break;
        // If I is pressed, exit the inventory screen
        // If Esc is pressed, exit the inventory screen or the
        // inventory submenu
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
        case GAME_SUBSTATE_INVENTORY_MENU:
            process_inventory_menu_substate(key);
            break;
        case GAME_SUBSTATE_DEFAULT:
            // Handle lighting status for the current room.
            // TODO: Maybe figure out if this is really the best place for this.
		    g_player.set_last_room_entered(g_dungeon.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos()));
		    // Darken the current space around the player if not in a room
		    if (g_player.get_last_room_entered() == -1) {
    		    g_dungeon.maze->change_lit_status_around(g_player.get_x_pos(), g_player.get_y_pos(), false);
		    }            
            switch (key) {
                case KEY_ESC:
            	    g_state_flags.exit_game = true;
                    break;
                case KEY_LEFT:
        		    if (g_dungeon.maze->is_carved(g_player.get_x_pos()-1, g_player.get_y_pos()) == true) {
			            g_player.set_x_pos(g_player.get_x_pos() - 1);
			            process_movement_flags();
			            add_items_at_player_to_log();
		            }
                    break;           
	            case KEY_RIGHT:
            		if (g_dungeon.maze->is_carved(g_player.get_x_pos()+1, g_player.get_y_pos()) == true) {			
	    		        g_player.set_x_pos(g_player.get_x_pos() + 1);
		    	        process_movement_flags();
			            add_items_at_player_to_log();
		            }
                    break;
    	        case KEY_UP:
        	    	if (g_dungeon.maze->is_carved(g_player.get_x_pos(), g_player.get_y_pos()-1) == true) {
    			        g_player.set_y_pos(g_player.get_y_pos() - 1);
	    		        process_movement_flags();
		    	        add_items_at_player_to_log();
		            }
                    break;
                case KEY_DOWN:
            		if (g_dungeon.maze->is_carved(g_player.get_x_pos(), g_player.get_y_pos()+1) == true)
	    	        {
        	    		g_player.set_y_pos(g_player.get_y_pos() + 1);
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
                    // Reset the cursor position to the top left
                    g_ui_globals.inv_cursor_x = 0;
                    g_ui_globals.inv_cursor_y = 0;
                    g_ui_globals.inv_menu_active = false;
                    g_ui_globals.sel_item_option = 0;
                    // Change to the inventory substate
                    g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                    // Update the graphics
                    g_state_flags.update_inventory_dialog = true;
                    g_state_flags.update_inventory_cursor = true;
                    g_state_flags.update_inventory_description = true;
                    g_state_flags.update_inventory_items = true;
                    g_state_flags.update_display = true;
                    break;
                case KEY_G:
                    pick_up_item_at(g_player.get_x_pos(), g_player.get_y_pos());    
                    break;
                case KEY_COMMA:
                case KEY_STOP:
                    use_stairs(g_player.get_x_pos(), g_player.get_y_pos());
                    break;
                case KEY_SPACE:
                case KEY_ENTER:
                    // attempt to perform all context sensitive actions in turn.
                    // Each is only designed to do something if the relevant
                    // condition is met anyway, so we can do them all in turn
                    // and the ones for non-valid actions become no-ops.

                    // Use the stairs.  This will only do something if there's
                    // a set of stairs at the player's feet.
                    use_stairs(g_player.get_x_pos(), g_player.get_y_pos());

                    // Pick up an item.  This will only do something if there's
                    // an item to actually pick up.
                    pick_up_item_at(g_player.get_x_pos(), g_player.get_y_pos());    
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