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
// 'Uses' a set of stairs - adjusts floor, generates new maze, etc
//
// Arguments:
//   x, y - the position to check for stairs
//
// Returns:
//   Nothing
//
// Notes:
//   Does nothing if there are no stairs in the provided location
//----------------------------------------------------------------------------
void use_stairs(int x, int y) {
    int stairs = g_dungeon.maze->stairs_here(x, y);
    int depth;

    // If there aren't actually any stairs, then do nothing
    if (stairs == MazeConsts::NO_STAIRS)
        return;

    // If the stairs are down stairs, the new floor should be
    // one greater than the current one (with a limit of the 
    // maximum floor value for the current dungeon)
    if (stairs == MazeConsts::STAIRS_DOWN) {
        depth = g_dungeon.depth + 1;
        if (depth > g_dungeon.max_depth)
            depth = g_dungeon.max_depth;
    }

    // If the stairs are up stairs, the new floor should be
    // one less than the current one (with a limit of 1).
    // Eventually, if the floor is 0, it will transition to
    // town instead of generating floor 1 again.
    if (stairs == MazeConsts::STAIRS_UP) {
        depth = g_dungeon.depth - 1;
        if (depth < 1) 
            depth = 1;
    }

    // Generate a new dungeon with the new floor value
    generate_new_dungeon_floor(g_dungeon, depth, stairs); 
}

//----------------------------------------------------------------------------
// 'Picks up' an item (adding it to the inventory or gold total, removing it
// from the ground)
//
// Arguments:
//   x, y - the position to check for items
//
// Returns:
//   Nothing
//
// Notes:
//   Does nothing if there are no items in the provided location
//----------------------------------------------------------------------------
void pick_up_item_at(int x, int y) {
    bool picked_up = false;
    std::string item_name;

    // Check for items.  Only do something if there are.
    if (g_dungeon.maze->get_num_items_at(x, y) <= 0) {
        return;
    } 
    else {
        // Get the item list and process the one at the end 
        // (which is the one that the player can see)
        std::list<Item *> items = g_dungeon.maze->get_items_at(x, y);

        // Get the item name.  Currency items and stackable items
        // will be deleted before the end of the function so we'll 
        // grab it for all items and use it instead of accidentally 
        //trying to blit a deleted item.
        Item *i = items.back();
        item_name = i->get_full_name();

        // For currency, add the value to the player's gold directly
        // Also, delete the currency item because it's going away
        // (not on the floor, not in the inventory)
        if (i->get_item_class() == ItemConsts::CURRENCY_CLASS) {
            g_player.add_gold(i->get_quantity());
		    delete i;
            g_state_flags.update_status_dialog = true;
            picked_up = true;
        }
        else {
            // If it's a stackable item, get any item slot existing
            // items are in
            int stackable_slot = g_inventory->get_stackable_item_slot(i);

            // If an existing item is found, increase the quantity of the
            // item in the existing slot, then delete the picked up one
            if (stackable_slot != -1) {
                Item *si = g_inventory->get_item_in_slot(stackable_slot);
                si->adjust_quantity(1);
                delete i;
                picked_up = true;
            }
            else {
                // Otherwise, add it to the inventory (if there's room)
                if (!g_inventory->inventory_is_full()) {
                    g_inventory->add_at_first_empty(i);
                    picked_up = true;
                }
                else {
                    // If there wasn't room, tell the player and do nothing.
                    g_text_log.put_line("You have no room to pick that up.");
                }
            }
        }
        
        // If an item was picked up, tell the player.
        if (picked_up) {
            g_dungeon.maze->remove_item_from_end_at(x, y);
            g_text_log.put_line("Picked up " + item_name + ".");
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
                    g_state_flags.cur_substate = GAME_SUBSTATE_INVENTORY;
                    g_state_flags.update_inventory_dialog = true;
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