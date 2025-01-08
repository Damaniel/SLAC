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
// Handles common tasks required after the inventory cursor is moved
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_inventory_common_tasks(int key) {
    // Get the old cursor position
    g_ui_globals.prev_inv_cursor_x = g_ui_globals.inv_cursor_x;
    g_ui_globals.prev_inv_cursor_y = g_ui_globals.inv_cursor_y;

    // Set the new cursor position
    switch (key) {
        case KEY_UP:
            g_ui_globals.inv_cursor_y = g_ui_globals.inv_cursor_y - 1;
            break;
        case KEY_DOWN:
            g_ui_globals.inv_cursor_y = g_ui_globals.inv_cursor_y + 1;
            break;
        case KEY_LEFT:
            g_ui_globals.inv_cursor_x = g_ui_globals.inv_cursor_x - 1;
            break;
        case KEY_RIGHT:
            g_ui_globals.inv_cursor_x = g_ui_globals.inv_cursor_x + 1;
            break;
    }

    // Wrap the cursor around if necessary
    if (g_ui_globals.inv_cursor_x < 0) 
        g_ui_globals.inv_cursor_x = UiConsts::INVENTORY_ITEMS_PER_ROW - 1;
    if (g_ui_globals.inv_cursor_x >= UiConsts::INVENTORY_ITEMS_PER_ROW) 
        g_ui_globals.inv_cursor_x = 0;
    if (g_ui_globals.inv_cursor_y < 0) 
        g_ui_globals.inv_cursor_y = UiConsts::INVENTORY_ROWS - 1;
    if (g_ui_globals.inv_cursor_y >= UiConsts::INVENTORY_ROWS) 
        g_ui_globals.inv_cursor_y = 0;

    // Redraw the inventory cursor and description areas
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
                g_ui_globals.sel_item_option = UiConsts::NUM_ITEM_OPTIONS - 1;
            }
            g_state_flags.update_inventory_submenu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_DOWN:
            g_ui_globals.sel_item_option += 1;
            if (g_ui_globals.sel_item_option >= UiConsts::NUM_ITEM_OPTIONS) {
                g_ui_globals.sel_item_option = 0;
            }
            g_state_flags.update_inventory_submenu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ENTER:
            // If 'Close' is selected, exit the inventory menu
            if (g_ui_globals.sel_item_option == UiConsts::NUM_ITEM_OPTIONS - 1) {
                g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                g_state_flags.update_inventory_dialog = true;
                g_state_flags.update_inventory_cursor = true;
                g_state_flags.update_inventory_items = true;
                g_state_flags.update_inventory_description = true;
                g_state_flags.update_display = true;    
            } 
            else {
                // Do the thing that the selected menu option does, if valid
                perform_inventory_menu_action();
                // If the menu action didn't trigger another substate, return to the
                // main inventory screen
                if (g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
                    g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                    g_state_flags.update_inventory_dialog = true;
                    g_state_flags.update_inventory_cursor = true;
                    g_state_flags.update_inventory_items = true;
                    g_state_flags.update_inventory_description = true;
                    g_state_flags.update_display = true;    
                }
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
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            process_inventory_common_tasks(key);
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
                    // Highlight 'close' by default
                    g_ui_globals.sel_item_option = UiConsts::NUM_ITEM_OPTIONS - 1;
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
// Handles all input for the stats substate (that is, when the stats are
// on screen)
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_stats_substate(int key) {
    switch (key) {
        // If C or ESC is pressed, exit the stats screen
        case KEY_C:
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
// Handles all input for the dead state
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_dead_state(int key) {
    // The only key that does anything is Enter.   When pressed,
    // create a new player with the appropriate base stats, reset everything,
    // and restart in town
    switch (key) {
        case KEY_ENTER:
            change_state(STATE_MAIN_GAME);
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
        case GAME_SUBSTATE_STATS:
            process_stats_substate(key);
            break;
        case GAME_SUBSTATE_PLAYER_JUST_DIED:
            switch (key) {
                case KEY_ENTER:
                    g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;
                    change_state(STATE_DEAD);
                    break;
            }
            break;
        case GAME_SUBSTATE_DEFAULT:
            // Only process lighting if the player is in the dungeon
            if (g_state_flags.in_dungeon) {
                // Handle lighting status for the current room.
		        g_player.set_last_room_entered(g_dungeon.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos()));
    		    // Darken the current space around the player if not in a room
	    	    if (g_player.get_last_room_entered() == -1) {
    	    	    g_dungeon.maze->change_lit_status_around(g_player.get_x_pos(), g_player.get_y_pos(), false);
		        }
            }            
            switch (key) {
                case KEY_ESC:
            	    g_state_flags.exit_game = true;
                    break;
                case KEY_LEFT:
                    process_move(std::make_pair(g_player.get_x_pos() - 1, g_player.get_y_pos()));
                    break;           
	            case KEY_RIGHT:
                    process_move(std::make_pair(g_player.get_x_pos() + 1, g_player.get_y_pos()));                
                    break;
    	        case KEY_UP:
                    process_move(std::make_pair(g_player.get_x_pos(), g_player.get_y_pos() - 1));
                    break;
                case KEY_DOWN:
                    process_move(std::make_pair(g_player.get_x_pos(), g_player.get_y_pos() + 1));
                    break;
                case KEY_HOME:   // Up and left
                    process_move(std::make_pair(g_player.get_x_pos() - 1, g_player.get_y_pos() - 1));
                    break;
                case KEY_PGUP:   // Up and right
                    process_move(std::make_pair(g_player.get_x_pos() + 1, g_player.get_y_pos() - 1));
                    break;         
                case KEY_END:   // Down and left
                    process_move(std::make_pair(g_player.get_x_pos() - 1, g_player.get_y_pos() + 1));
                    break;                         
                case KEY_PGDN:  // Down and right
                    process_move(std::make_pair(g_player.get_x_pos() + 1, g_player.get_y_pos() + 1));
                    break;        
                case KEY_DEL: // Do nothing (sit in place)
                    process_move(std::make_pair(g_player.get_x_pos(), g_player.get_y_pos()));
                    break;
                case KEY_C:
                    g_state_flags.cur_substate = GAME_SUBSTATE_STATS;
                    g_state_flags.update_stats_screen = true;
                    g_state_flags.update_display = true;
                    break;
	            case KEY_M:
                    if (g_state_flags.in_dungeon) {
                        g_state_flags.cur_substate = GAME_SUBSTATE_MAP;
                        g_state_flags.update_map_dialog = true;
	        	        g_state_flags.update_display = true;
                    }
                    break;
                case KEY_H:
                    g_game_flags.can_enter_crystal_depths = true;
                    g_game_flags.can_enter_marble_halls = true;
                    // g_player.actual.max_hp = 10000;
                    // g_player.hp = 10000;
                    // g_player.actual.atk = 255;
                    unlock_dungeons();
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
                    if (g_state_flags.in_dungeon) {
                        pick_up_item_at(g_player.get_x_pos(), g_player.get_y_pos());    
                    }
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
                    if (g_state_flags.in_dungeon) {
                        pick_up_item_at(g_player.get_x_pos(), g_player.get_y_pos());
                    }
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
                    g_state_flags.update_status_hp_exp = true;
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
        case STATE_DEAD:
            process_dead_state(key);
            break;
    }
}