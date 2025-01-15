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
// Handles common tasks related to moving the shop item cursor around
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_store_menu_common_tasks(int key) {
    // Get the old cursor position
    g_ui_globals.prev_shop_inv_cursor_x = g_ui_globals.shop_inv_cursor_x;
    g_ui_globals.prev_shop_inv_cursor_y = g_ui_globals.shop_inv_cursor_y;

    // Set the new cursor position
    switch (key) {
        case KEY_UP:
            g_ui_globals.shop_inv_cursor_y = g_ui_globals.shop_inv_cursor_y - 1;
            break;
        case KEY_DOWN:
            g_ui_globals.shop_inv_cursor_y = g_ui_globals.shop_inv_cursor_y + 1;
            break;
        case KEY_LEFT:
            g_ui_globals.shop_inv_cursor_x = g_ui_globals.shop_inv_cursor_x - 1;
            break;
        case KEY_RIGHT:
            g_ui_globals.shop_inv_cursor_x = g_ui_globals.shop_inv_cursor_x + 1;
            break;
    }

    // Wrap the cursor around if necessary
    if (g_ui_globals.shop_inv_cursor_x < 0)
        g_ui_globals.shop_inv_cursor_x = UiConsts::INVENTORY_ITEMS_PER_ROW - 1;
    if (g_ui_globals.shop_inv_cursor_x >= UiConsts::INVENTORY_ITEMS_PER_ROW)
        g_ui_globals.shop_inv_cursor_x = 0;
    if (g_ui_globals.shop_inv_cursor_y < 0)
        g_ui_globals.shop_inv_cursor_y = UiConsts::INVENTORY_ROWS - 1;
    if (g_ui_globals.shop_inv_cursor_y >= UiConsts::INVENTORY_ROWS)
        g_ui_globals.shop_inv_cursor_y = 0;

    // Redraw the inventory cursor and description areas
    g_state_flags.update_shop_inventory_cursor = true;
    g_state_flags.update_shop_inventory_description = true;
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Handles all input for the store substate (that is, when the stats are
// on screen)
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_store_substate(int key) {
    switch(key) {
        case KEY_ESC:
            g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;
            g_state_flags.is_shopping = false;
            break;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            process_store_menu_common_tasks(key);
            break;
        case KEY_SPACE:
            if (g_state_flags.in_weapon_shop) {
                g_state_flags.weapon_shop_in_buy_mode = !g_state_flags.weapon_shop_in_buy_mode;
            }
            if (g_state_flags.in_item_shop) {
                g_state_flags.item_shop_in_buy_mode = !g_state_flags.item_shop_in_buy_mode;
            }
            g_state_flags.update_shop_inventory_dialog = true;
            g_state_flags.update_shop_inventory_description = true;
            g_state_flags.update_shop_inventory_items = true;;
            g_state_flags.update_shop_inventory_cursor = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ENTER:
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
            g_state_flags.recently_died = true;
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
        case GAME_SUBSTATE_STORE:
            process_store_substate(key);
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
                    g_state_flags.update_display = true;
                    change_state(STATE_DEAD);
                    break;
            }
            break;
        case GAME_SUBSTATE_CONFIRM_EXIT:
            process_confirm_exit_substate(key);
            break;
        case GAME_SUBSTATE_HALL_OF_CHAMPIONS:
            switch (key) {
                case KEY_ENTER:
                    change_state(STATE_HALL_OF_CHAMPIONS);
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
            	    g_state_flags.cur_substate = GAME_SUBSTATE_CONFIRM_EXIT;
                    g_state_flags.update_display = true;
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
                    // magic key for testing stuff
                    break;
                case KEY_S:
                    save_game(SaveLoadConsts::save_file);
                    g_text_log.put_line("-- Your game was saved. --");
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
                    g_state_flags.update_status_elapsed_time = true;
		            g_state_flags.update_display = true;
                    break;
	        }
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the title screen menu substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_title_screen_menu_substate(int key) {
    switch (key) {
        case KEY_ESC:
            g_state_flags.cur_substate = TITLE_SUBSTATE_DEFAULT;
            g_state_flags.update_title_background = true;
            g_state_flags.update_display = true;
            break;
        case KEY_DOWN:
            g_state_flags.title_menu_index += 1;
            if (g_state_flags.title_menu_index >= UtilConsts::NUM_TITLE_MENU_ENTRIES)
                g_state_flags.title_menu_index = 0;
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_UP:
            g_state_flags.title_menu_index -= 1;
            if (g_state_flags.title_menu_index < 0)
                g_state_flags.title_menu_index = UtilConsts::NUM_TITLE_MENU_ENTRIES - 1;
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ENTER:
            switch (g_state_flags.title_menu_index) {
                case 0:
                    g_state_flags.cur_substate = TITLE_SUBSTATE_NEW;
                    // Put the character cursor in the correct position, reset the name
                    // and clear the character text box
                    g_state_flags.new_game_char_text_index = 0;
                    g_state_flags.character_name[0] = '\0';
                    g_state_flags.update_title_menu = true;
                    g_state_flags.update_display = true;
                    break;
                case 1:
                    if(slac_file_exists(SaveLoadConsts::save_file)) {
                        g_state_flags.save_loaded = true;
                        change_state(STATE_MAIN_GAME);
                        load_game(SaveLoadConsts::save_file);
                        g_state_flags.save_loaded = false;
                        g_text_log.put_line("Welcome back to Secret Legacy of the Ancient caves!");
                        force_update_screen();
                    }
                    break;
                case 2:
                    if(slac_file_exists(SaveLoadConsts::save_file)) {
                        g_state_flags.cur_substate = TITLE_SUBSTATE_DELETE;
                        g_state_flags.update_title_menu = true;
                        g_state_flags.update_display = true;
                    }
                    break;
            }
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the title screen new substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_title_screen_new_substate(int key) {
    // In this case only, we care about both the scancode and the ASCII value
    int ascii_val = key & 0xff;
    int scancode = key >> 8;

    switch (scancode) {
        case KEY_ESC:
            g_state_flags.cur_substate = TITLE_SUBSTATE_MENU;
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        // These are all of the valid name values (letters, digits, dash, underscore)
        case KEY_A:
        case KEY_B:
        case KEY_C:
        case KEY_D:
        case KEY_E:
        case KEY_F:
        case KEY_G:
        case KEY_H:
        case KEY_I:
        case KEY_J:
        case KEY_K:
        case KEY_L:
        case KEY_M:
        case KEY_N:
        case KEY_O:
        case KEY_P:
        case KEY_Q:
        case KEY_R:
        case KEY_S:
        case KEY_T:
        case KEY_U:
        case KEY_V:
        case KEY_W:
        case KEY_X:
        case KEY_Y:
        case KEY_Z:
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_MINUS:
            if (!(g_state_flags.new_game_char_text_index >= UtilConsts::MAX_CHARACTER_NAME_LENGTH)) {
                g_state_flags.character_name[g_state_flags.new_game_char_text_index] = ascii_val;
                g_state_flags.new_game_char_text_index += 1;
                g_state_flags.character_name[g_state_flags.new_game_char_text_index] = '\0';
            }
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_BACKSPACE:
            if (!(g_state_flags.new_game_char_text_index < 0)) {
                g_state_flags.new_game_char_text_index -= 1;
                if (g_state_flags.new_game_char_text_index < 0)
                    g_state_flags.new_game_char_text_index = 0;
                g_state_flags.character_name[g_state_flags.new_game_char_text_index] = '\0';
            }
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ENTER:
            reset_game_flags();
            // Set the player's name (or NoName if blank)
            if (strlen(g_state_flags.character_name) > 0) {
                g_state_flags.character_name[g_state_flags.new_game_char_text_index] = '\0';
            }
            else {
                strncpy(g_state_flags.character_name, "NoName", 6);
                g_state_flags.character_name[6] = '\0';
            }
            g_player.name = g_state_flags.character_name;
            change_state(STATE_MAIN_GAME);
            g_text_log.put_line("After many years of adventuring, you've decided to settle down in a town rumored");
            g_text_log.put_line("to harbor a secret legacy.  Whispers of unspeakable beasts far below the town");
            g_text_log.put_line("reach your ears.  One day, you decide that now is the time to discover this secret");
            g_text_log.put_line("for yourself, no matter how long it takes you (or your heirs)!");
            force_update_screen();
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the title screen delete substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_title_screen_delete_substate(int key) {
    switch (key) {
        case KEY_Y:
            // Delete the save file
            remove((SaveLoadConsts::save_file).c_str());
            g_state_flags.cur_substate = TITLE_SUBSTATE_LEGACY_DELETED;
            // Highlight the 'new' option
            g_state_flags.title_menu_index = 0;
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
        case KEY_ESC:
        case KEY_N:
            g_state_flags.cur_substate = TITLE_SUBSTATE_MENU;
            g_state_flags.update_title_menu = true;
            g_state_flags.update_display = true;
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the title screen, plus any current substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_title_screen_state(int key) {
    switch (g_state_flags.cur_substate) {
        case TITLE_SUBSTATE_DEFAULT:
            switch (key >> 8) {
                case KEY_ENTER:
                    g_state_flags.cur_substate = TITLE_SUBSTATE_MENU;
                    g_state_flags.update_title_menu = true;
                    g_state_flags.update_display = true;
                    break;
                case KEY_ESC:
                    g_state_flags.cur_substate = TITLE_SUBSTATE_CONFIRM_EXIT;
                    g_state_flags.update_title_menu = true;
                    g_state_flags.update_display = true;
                    break;
            }
            break;
        case TITLE_SUBSTATE_MENU:
            process_title_screen_menu_substate(key >> 8);
            break;
        case TITLE_SUBSTATE_NEW:
            process_title_screen_new_substate(key);
            break;
        case TITLE_SUBSTATE_DELETE:
            process_title_screen_delete_substate(key >> 8);
            break;
        case TITLE_SUBSTATE_CONFIRM_EXIT:
            switch (key >> 8) {
                case KEY_Y:
                    change_state(STATE_EXIT);
                    break;
                case KEY_N:
                case KEY_ESC:
                    g_state_flags.cur_substate = TITLE_SUBSTATE_DEFAULT;
                    g_state_flags.update_title_background = true;
                    g_state_flags.update_display = true;
                    break;
            }
        case TITLE_SUBSTATE_LEGACY_DELETED:
            // The only valid key here is ENTER, to return to the main menu
            switch (key >> 8) {
                case KEY_ENTER:
                    g_state_flags.cur_substate = TITLE_SUBSTATE_MENU;
                    g_state_flags.update_title_menu = true;
                    g_state_flags.update_display = true;
                    break;
            }
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the hall of champions
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_hall_of_champions_state(int key) {

    switch (key) {
        // The only valid key is Enter, which returns to the title screen
        // Esc is only for testing right now
        case KEY_ESC:
            change_state(STATE_EXIT);
            break;
        case KEY_ENTER:
            // Save the updated Hall of Champions data
            save_hall_of_champions();
            // Go back to the title screen
            change_state(STATE_TITLE_SCREEN);
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
    if (!keypressed())
        return;

	int key = readkey();
    int scancode = key >> 8;

    switch(g_state_flags.cur_state) {
        // Title screen gets the raw key value since we need specifically
        // to extract ASCII values from the key
        case STATE_TITLE_SCREEN:
            process_title_screen_state(key);
            break;
        case STATE_MAIN_GAME:
            process_game_state(scancode);
            break;
        case STATE_DEAD:
            process_dead_state(scancode);
            break;
        case STATE_HALL_OF_CHAMPIONS:
            process_hall_of_champions_state(scancode);
            break;
    }
}

//----------------------------------------------------------------------------
// Handles all input for the confirm exit substate
//
// Arguments:
//   key - the key that was pressed
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void process_confirm_exit_substate(int key) {
    switch (key) {
        case KEY_ESC:
        case KEY_N:
            g_state_flags.cur_substate = GAME_SUBSTATE_DEFAULT;
            force_update_screen();
            break;
        case KEY_Y:
            save_game(SaveLoadConsts::save_file);
            change_state(STATE_TITLE_SCREEN);
            break;
    }
}