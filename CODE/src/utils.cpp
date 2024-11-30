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

// Non-class update functions.  They might go into the class eventually

void update_main_game_display(void) {
	if (g_state_flags.cur_substate == GAME_SUBSTATE_MAP) {
		g_render.render_map(g_back_buffer);
	}
	else if (g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY || g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
		g_render.render_inventory(g_back_buffer);
	}
	else {		
		if (g_state_flags.update_maze_area == true) {
			// Add the areas around the player to the map bitmap
			//std::cout << "update_display: adding area to map bitmap" << std::endl;
			g_render.add_area_to_map_bitmap(g_dungeon.maze, g_player.get_x_pos(), g_player.get_y_pos());
			//std::cout << "update_display: Added area to map bitmap" << std::endl;
			// Light the space around the player
			g_dungeon.maze->change_lit_status_around(g_player.get_x_pos(), g_player.get_y_pos(), true);
			//std::cout << "update_display: Changed lit status" << std::endl;
			// Check what room the player is in, if any
			int room_to_light = g_dungeon.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos());
			int last_player_room = g_player.get_last_room_entered();
			//std::cout << "update_display: Got last room player was in" << std::endl;
			// If the player was in a room but no longer is, then darken the room
			if(last_player_room != -1 && room_to_light == -1) {
				g_dungeon.maze->change_room_lit_status(last_player_room, false);
			}
			// If the player wasn't in a room but now is, then light up the room
			if(last_player_room == -1 && room_to_light != -1) {
				g_dungeon.maze->change_room_lit_status(room_to_light, true);
				// TODO: restructure this!
				// Mark the room itself as visited so rendering the map will
				// show the room even at the start of the game
				g_dungeon.maze->set_room_as_entered(room_to_light);
			}
			//std::cout << "update_display: Finished processing lighting" << std::endl;

			// Draw the world display area
			g_render.render_world_at_player(g_back_buffer, g_dungeon.maze, g_player.get_x_pos(), g_player.get_y_pos());
			//std::cout << "update_display: rendered world" << std::endl;
			g_state_flags.update_maze_area = false;
		}
	}

	if(g_state_flags.update_status_dialog == true) {
		g_render.render_status_base(g_back_buffer);
		g_render.render_status_ui(g_back_buffer);
		g_state_flags.update_status_dialog = false;
	}

	if(g_state_flags.update_text_dialog == true) {
		g_render.render_text_base(g_back_buffer, g_state_flags.text_log_extended);
		g_render.render_text_log(g_back_buffer, g_state_flags.text_log_extended);
		g_state_flags.update_text_dialog = false;
	}
}

//------------------------------------------------------------------------------
// Updates the main display for the current state
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//
// TODO: Move this to render.cpp
//------------------------------------------------------------------------------
void update_display(void) {
	switch (g_state_flags.cur_state) {
		case STATE_MAIN_GAME:
			update_main_game_display();
			break;
	}

	// Now actually put the image on the visible part of the screen
	vsync();
	blit(g_back_buffer, screen, 0, 0, 0, 0, 320, 240);	
	
	// Display is updated - we don't want to do it again right now.
	g_state_flags.update_display = false;
}

//------------------------------------------------------------------------------
// Retreives the name of the dungeon specified by the given ID
//
// Arguments:
//   dungeon - the id of the dungeon
//
// Returns:
//   A string containing the name of the dungeon
//------------------------------------------------------------------------------
std::string get_dungeon_name(int dungeon, bool abbrev) {
	if (abbrev) {
		switch (dungeon) {
			case DUSTY_TUNNELS:
				return "D. Tunnels";
				break;
			case MARBLE_HALLS:
				return "M. Halls";
				break;
			case CRYSTAL_DEPTHS:
				return "C. Depths";
				break;
			default:
				return "Huh?";
				break;
		}

	} 
	else {
		switch (dungeon) {
			case DUSTY_TUNNELS:
				return "Dusty Tunnels";
				break;
			case MARBLE_HALLS:
				return "Marble Halls";
				break;
			case CRYSTAL_DEPTHS:
				return "Crystal Depths";
				break;
			default:
				return "Huh?";
				break;
		}
	}
}

//------------------------------------------------------------------------------
// Returns a string representation of a generation designator (i.e. '3rd' or
// '17th')
//
// Arguments:
//   generation - the generation to make the string for
//
// Returns:
//   A string containing the generational designator.
//------------------------------------------------------------------------------
std::string get_generation_string(int generation) {
	int suffix = generation % 100;
	char gen_string[16];

	switch (suffix) {
		case 1:
			sprintf(gen_string, "Senior");
			break;
		case 2:
			sprintf(gen_string, "Junior");
			break;
		case 21:
		case 31:
		case 41:
		case 51:
		case 61:
		case 71:
		case 81:
		case 91:
			sprintf(gen_string, "%dst", generation);
			break;
		case 22:
		case 32:
		case 42:
		case 52:
		case 62:
		case 72:
		case 82:
		case 92:
			sprintf(gen_string, "%dnd", generation);
			break;
		case 3:
		case 23:
		case 33:
		case 43:
		case 53:
		case 63:
		case 73:
		case 83:
		case 93:
			sprintf(gen_string, "%drd", generation);
			break;
		default:
			sprintf(gen_string, "%dth", generation);
            break;
	}

	return std::string(gen_string);
}

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
//   d - a reference to a DungeonFloor that will contain the new floor
//   level - the dungeon level to generate (affects iLevel)
//   stairs_from - the kind of stairs the player came from 
//
// Returns:
//   Nothing
//
// Notes:
//   stairs_from is used to place the player on the correct kind of stairs
//   corresponding to the floor they came from (up stairs if the player went
//   down, and down stairs if the player went up)
//------------------------------------------------------------------------------
void generate_new_dungeon_floor(DungeonFloor &d, int level, int stairs_from) {
	if (d.maze != NULL) {
		delete d.maze;
	}

	//std::cout << "generate_new_dungeon_floor: Generating floor " << level << "..." << std::endl;

	d.depth = level;

	// Set the maximum depth and size for the current dungeon
	// Yes, this is done every floor when it doesn't need to be, but fine.
	d.max_depth = g_max_dungeon_depths[d.maze_id];
	d.width = g_dungeon_sizes[d.maze_id];
	d.height = g_dungeon_sizes[d.maze_id];

	// Set the current ilevel based on the dungeon the player is in and the
	// floor they're on
	// switch (d.maze_id) {
	// 	case DUSTY_TUNNELS:
	// 		d.ilevel = level / 2;
	// 		if (d.ilevel < 1 ) d.ilevel = 1;
	// 		if (d.ilevel > 25) d.ilevel = 25;
	// 		break;
	// 	case MARBLE_HALLS:
	// 		d.ilevel = 20 + (level / 2);
	// 		if (d.ilevel < 20 ) d.ilevel = 20;
	// 		if (d.ilevel > 70) d.ilevel = 70;
	// 		break;
	// 	case CRYSTAL_DEPTHS:
	// 		d.ilevel = 30 + (level / 2);
	// 		if (d.ilevel < 30 ) d.ilevel = 30;
	// 		if (d.ilevel > 100) d.ilevel = 100;
	// 		break;
	// 	default:
	// 		d.ilevel = 100;
	// 		break;
	// }

	// TODO: remove this after testing
	d.ilevel = 100;

	d.maze = new Maze(d.width, d.height, d.ilevel);

	// If we're at the bottom, direct the maze generator to omit down stairs
	if(d.depth >= d.max_depth)
		d.maze->set_stair_gen_behavior(MazeConsts::GENERATE_NO_DOWN_STAIRS);

	d.maze->generate();

	std::pair<int, int> stairLoc;
	// Place the player on a random set of stairs based on where they came from
	if (stairs_from == MazeConsts::STAIRS_DOWN)
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_UP);
	else
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_DOWN);

	// Place the player at the stair location
	g_player.set_position(stairLoc.first, stairLoc.second);
	
	// Hack to force lighting in the initial room the player is in
	int initial_room = d.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos());
	g_player.set_last_room_entered(initial_room);	
	if (initial_room != -1) {
		// double hack to mark the room as seen so that the map renderer can
		// display it
		d.maze->change_room_lit_status(initial_room, false);		
		d.maze->change_room_lit_status(initial_room, true);			
	}
	
	// Does the display need to be refreshed?
	g_state_flags.update_display = true;
	
	// Tell the renderer to draw these first thing.
	g_state_flags.update_maze_area = true;
	g_state_flags.update_status_dialog = true;
	g_state_flags.update_text_dialog = true;

	// Use the short text log by default
	g_state_flags.text_log_extended = false;

	// Clear the map bitmap
	g_render.initialize_map_bitmap(g_dungeon.maze);

	// Force an explicit display update so the user can see the world right away
	update_display();
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
	if (g_dungeon.maze != NULL) {
		delete g_dungeon.maze;
		g_dungeon.maze = NULL;
	}

	// Create a new dungeon floor (first floor, coming down from surface)
	generate_new_dungeon_floor(g_dungeon, 1, MazeConsts::STAIRS_DOWN);

	// create a new inventory (TODO - move to an earlier state)
	g_inventory = new Inventory();
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
	int item_count = g_dungeon.maze->get_num_items_at(g_player.get_x_pos(), g_player.get_y_pos());
	int idx = 0;

	if (item_count > 0) {
		std::list<Item *> items = g_dungeon.maze->get_items_at(g_player.get_x_pos(), g_player.get_y_pos());
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

//----------------------------------------------------------------------------
// Drops an item (throwing it on the ground)
//
// Arguments:
//   i - the item to drop
//   x, y - the location on the ground to drop it
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void drop_item_at(Item *i, int x, int y) {
	bool dropped = false;

	if(g_dungeon.maze->stairs_here(x, y) != MazeConsts::NO_STAIRS) {
		g_text_log.put_line("Unable to drop an item onto stairs.");
	}
	else {
		if (i != NULL) {
			g_text_log.put_line("Dropped the " + i->get_full_name() + ".");
			g_dungeon.maze->add_item(x, y, i);
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_description = true;
		}
	}
	g_state_flags.update_text_dialog = true;
	g_state_flags.update_display = true;

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
// Do the action associated with the selected inventory context menu item.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void perform_inventory_menu_action(void) {
	// Get the item under the cursor
	int slot = g_ui_globals.inv_cursor_y * UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_cursor_x;
    Item *i = g_inventory->get_item_in_slot(slot);
	
	// Determine if the action can be done by the item
	switch (g_ui_globals.sel_item_option) {
		case UiConsts::ITEM_OPTION_USE:
			// If the item can be used, use it
			if (i->can_be_used()) {
				// Use the item.  Take one from the stack, or delete the item if there was only 1
				i->use();
				i->adjust_quantity(-1);
				if (i->get_quantity() <= 0) {
					// The item was used and there are none left, get rid of it
					//std::cout << "perform_inventory_menu_action: stack is depleted, deleting item" << std::endl;
					g_inventory->delete_item_in_slot(slot);
				}
			}
			break;
		case UiConsts::ITEM_OPTION_EQUIP:
			// If it can be equipped and isn't, have the player equip it
			if (i->can_be_equipped() && !i->is_it_equipped()) {
				//std::cout << "perform_inventory_menu_action: equipping item" << std::endl;
				g_player.equip(i);
			}
			break;
		case UiConsts::ITEM_OPTION_UNEQUIP:
			// If it can be equipped and currently is, have the player unequip it
			if (i->can_be_equipped() && i->is_it_equipped()) {
				//std::cout << "perform_inventory_menu_action: unequipping item" << std::endl;
				g_player.unequip(i);
			}
			break;
		case UiConsts::ITEM_OPTION_DROP:
			// If the item can be dropped, and currently isn't equipped, drop it on the ground
			if (i->can_be_dropped() && !i->is_it_equipped()) {
				//std::cout << "perform_inventory_menu_action: dropping item" << std::endl;
				drop_item_at(i, g_player.get_x_pos(), g_player.get_y_pos());
				g_inventory->remove_item_in_slot(slot);
			}
			break;
		case UiConsts::ITEM_OPTION_DESTROY:
			// If the item can be dropped and currently isn't equipped, destroy it
			if (i->can_be_dropped() && !i->is_it_equipped()) {
				// Delete the item; it will delete the entire stack
				//std::cout << "perform_inventory_menu_action: deleting item(s)" << std::endl;
				g_inventory->delete_item_in_slot(slot);
			}
			break;
		default:
			break;
	} 
}

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
// Applies a modifier based on a mode (absolute or relative) to the 
// specified locations
//
// Arguments:
//   mode - the magnifier mode (0 = relative, 1 = fixed)
//	 value - the value to set
//   fixed - the variable to hold the fixed value
//   multiplicative - the variable to hold the multiplicative value
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void apply_modifier_value(ModifierMagType m, float *fixed, float *multiplicative, std::vector<ModifierMagType> &mods) {
	//std::cout << "apply_modifier_value: fixed = " << *fixed << ", mult = " << *multiplicative << ", value = " << value << std::endl;
	if (m.modifier_mode == 0)					// Relative increase
		*multiplicative += (m.magnitude - 1.0);
	else if (m.modifier_mode == 1)				// Absolute increase
		*fixed += m.magnitude;
	else if (m.modifier_mode == 2)  			// Increase one stat by another
		mods.push_back(m);

	//std::cout << "apply_modifier_value: after - fixed = " << *fixed << ", mult = " << *multiplicative << ", value = " << value << std::endl;
}

void apply_mode_2_modifier_value(ModifierMagType m) {
	float *from_val, *to_val;

	// Determine where the value comes from 
	switch (m.modifier_id) {
		case ItemConsts::MODIFIER_STR:		// STR
			std::cout << "apply_mode_2_modifier_value: source stat = STR" << std::endl;
			from_val = &(g_player.actual.str);
			break;
		case ItemConsts::MODIFIER_CON:		// CON
			std::cout << "apply_mode_2_modifier_value: source stat = CON" << std::endl;
			from_val = &(g_player.actual.con);
			break;
		case ItemConsts::MODIFIER_DEX:		// DEX
			std::cout << "apply_mode_2_modifier_value: source stat = DEX" << std::endl;
			from_val = &(g_player.actual.dex);
			break;
		case ItemConsts::MODIFIER_ATK:		// ATK
			std::cout << "apply_mode_2_modifier_value: source stat = ATK" << std::endl;
			from_val = &(g_player.actual.atk);
			break;
		case ItemConsts::MODIFIER_DEF:		// DEF
			std::cout << "apply_mode_2_modifier_value: source stat = DEF" << std::endl;
			from_val = &(g_player.actual.def);
			break;
		case ItemConsts::MODIFIER_SPD:		// SPD
			std::cout << "apply_mode_2_modifier_value: source stat = SPD" << std::endl;
			from_val = &(g_player.actual.spd);
			break;
		case ItemConsts::MODIFIER_FATK:		// FAtk
			std::cout << "apply_mode_2_modifier_value: source stat = FAtk" << std::endl;
			from_val = &(g_player.actual.f_atk);
			break;
		case ItemConsts::MODIFIER_IATK:		// IAtk
			std::cout << "apply_mode_2_modifier_value: source stat = IAtk" << std::endl;
			from_val = &(g_player.actual.i_atk);
			break;
		case ItemConsts::MODIFIER_LATK:		// LAtk
			std::cout << "apply_mode_2_modifier_value: source stat = LAtk" << std::endl;
			from_val = &(g_player.actual.l_atk);
			break;
		case ItemConsts::MODIFIER_FDEF:		// FDef
			std::cout << "apply_mode_2_modifier_value: source stat = FDef" << std::endl;
			from_val = &(g_player.actual.f_def);
			break;
		case ItemConsts::MODIFIER_IDEF:		// IDef
			std::cout << "apply_mode_2_modifier_value: source stat = IDef" << std::endl;
			from_val = &(g_player.actual.i_def);
			break;
		case ItemConsts::MODIFIER_LDEF:		// LDef
			std::cout << "apply_mode_2_modifier_value: source stat = LDef" << std::endl;
			from_val = &(g_player.actual.l_def);
			break;
		case ItemConsts::MODIFIER_APT:		// APT
			std::cout << "apply_mode_2_modifier_value: source stat = APT" << std::endl;
			from_val = &(g_player.actual.apt);
			break;
		case ItemConsts::MODIFIER_MAX_HP:	// Max HP
			std::cout << "apply_mode_2_modifier_value: source stat = MAX HP" << std::endl;
			from_val = &(g_player.actual.max_hp);
			break;
		case ItemConsts::MODIFIER_FDMG:		// FDmg
			std::cout << "apply_mode_2_modifier_value: source stat = FDmg" << std::endl;
			from_val = &(g_player.actual.f_dmg);
			break;
		case ItemConsts::MODIFIER_IDMG:		// IDmg
			std::cout << "apply_mode_2_modifier_value: source stat = IDmg" << std::endl;
			from_val = &(g_player.actual.i_dmg);
			break;
		case ItemConsts::MODIFIER_LDMG:		// LDmg
			std::cout << "apply_mode_2_modifier_value: source stat = LDmg" << std::endl;
			from_val = &(g_player.actual.l_dmg);
			break;
		case ItemConsts::MODIFIER_POIS:		// Poison
			// This modifier doesn't have this option
			return;
			break;
		case ItemConsts::MODIFIER_BLOCK:		// Block
			std::cout << "apply_mode_2_modifier_value: source stat = Block" << std::endl;
			from_val = &(g_player.actual.block);
			break;
		case ItemConsts::MODIFIER_ADMG:			// ADmg
			std::cout << "apply_mode_2_modifier_value: source stat = ADmg" << std::endl;
			from_val = &(g_player.actual.a_dmg);
			break;
	}

	// Determine where the value goes
	switch (m.secondary_id) {
		case ItemConsts::MODIFIER_STR:		// STR
			std::cout << "apply_mode_2_modifier_value: dest stat = STR" << std::endl;
			to_val = &(g_player.actual.str);
			break;
		case ItemConsts::MODIFIER_CON:		// CON
			std::cout << "apply_mode_2_modifier_value: dest stat = CON" << std::endl;
			to_val = &(g_player.actual.con);
			break;
		case ItemConsts::MODIFIER_DEX:		// DEX
			std::cout << "apply_mode_2_modifier_value: dest stat = DEX" << std::endl;
			to_val = &(g_player.actual.dex);
			break;
		case ItemConsts::MODIFIER_ATK:		// ATK
			std::cout << "apply_mode_2_modifier_value: dest stat = ATK" << std::endl;
			to_val = &(g_player.actual.atk);
			break;
		case ItemConsts::MODIFIER_DEF:		// DEF
			std::cout << "apply_mode_2_modifier_value: dest stat = DEF" << std::endl;
			to_val = &(g_player.actual.def);
			break;
		case ItemConsts::MODIFIER_SPD:		// SPD
			std::cout << "apply_mode_2_modifier_value: dest stat = SPD" << std::endl;
			to_val = &(g_player.actual.spd);
			break;
		case ItemConsts::MODIFIER_FATK:		// FAtk
			std::cout << "apply_mode_2_modifier_value: dest stat = FAtk" << std::endl;
			to_val = &(g_player.actual.f_atk);
			break;
		case ItemConsts::MODIFIER_IATK:		// IAtk
			std::cout << "apply_mode_2_modifier_value: dest stat = IAtk" << std::endl;
			to_val = &(g_player.actual.i_atk);
			break;
		case ItemConsts::MODIFIER_LATK:		// LAtk
			std::cout << "apply_mode_2_modifier_value: dest stat = LAtk" << std::endl;
			to_val = &(g_player.actual.l_atk);
			break;
		case ItemConsts::MODIFIER_FDEF:		// FDef
			std::cout << "apply_mode_2_modifier_value: dest stat = FDef" << std::endl;
			to_val = &(g_player.actual.f_def);
			break;
		case ItemConsts::MODIFIER_IDEF:		// IDef
			std::cout << "apply_mode_2_modifier_value: dest stat = IDef" << std::endl;
			to_val = &(g_player.actual.i_def);
			break;
		case ItemConsts::MODIFIER_LDEF:		// LDef
			std::cout << "apply_mode_2_modifier_value: dest stat = LDef" << std::endl;
			to_val = &(g_player.actual.l_def);
			break;
		case ItemConsts::MODIFIER_APT:		// APT
			std::cout << "apply_mode_2_modifier_value: dest stat = APT" << std::endl;
			to_val = &(g_player.actual.apt);
			break;
		case ItemConsts::MODIFIER_MAX_HP:	// Max HP
			std::cout << "apply_mode_2_modifier_value: dest stat = Max HP" << std::endl;
			to_val = &(g_player.actual.max_hp);
			break;
		case ItemConsts::MODIFIER_FDMG:		// FDmg
			std::cout << "apply_mode_2_modifier_value: dest stat = FDmg" << std::endl;
			to_val = &(g_player.actual.f_dmg);
			break;
		case ItemConsts::MODIFIER_IDMG:		// IDmg
			std::cout << "apply_mode_2_modifier_value: dest stat = IDmg" << std::endl;
			to_val = &(g_player.actual.i_dmg);
			break;
		case ItemConsts::MODIFIER_LDMG:		// LDmg
			std::cout << "apply_mode_2_modifier_value: dest stat = LDmg" << std::endl;
			to_val = &(g_player.actual.l_dmg);
			break;
		case ItemConsts::MODIFIER_POIS:		// Poison
			// This modifier doesn't have this option
			return;
			break;
		case ItemConsts::MODIFIER_BLOCK:		// Block
			std::cout << "apply_mode_2_modifier_value: dest stat = Block" << std::endl;
			to_val = &(g_player.actual.block);
			break;
		case ItemConsts::MODIFIER_ADMG:			// ADmg
			std::cout << "apply_mode_2_modifier_value: dest stat = ADmg" << std::endl;
			to_val = &(g_player.actual.a_dmg);
			break;
	}

	std::cout << "apply_mode_2_modifier_value: magnitude = " << m.magnitude << std::endl;

	// Apply the value
	*to_val += *from_val * m.magnitude;
}

//----------------------------------------------------------------------------
// Applies a single modifier to the multiplicative and fixed value lists
//
// Arguments:
//   m - the modifier to adjust
//   fixed - the fixed values structure
//   multiplicative - the multiplicative values structure
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void apply_single_modifier(ModifierMagType m, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods) {
// This function is Ug. Ly.  I think this could be managed better by function pointers that do the
// application of the values directly.  But for now, I'm doing this to get something in place.
	switch (m.modifier_id) {
		case ItemConsts::MODIFIER_STR:		// STR
			//std::cout << "apply_single_modifier: Adjusting STR - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->str << ", mult = " << multiplicative->str << std::endl;
			apply_modifier_value(m, &(fixed->str), &(multiplicative->str), mods);
			break;
		case ItemConsts::MODIFIER_CON:		// CON
			//std::cout << "apply_single_modifier: Adjusting CON - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->con << ", mult = " << multiplicative->con << std::endl;
			apply_modifier_value(m, &(fixed->con), &(multiplicative->con), mods);
			break;
		case ItemConsts::MODIFIER_DEX:		// DEX
			//std::cout << "apply_single_modifier: Adjusting DEX - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->dex << ", mult = " << multiplicative->dex << std::endl;
			apply_modifier_value(m, &(fixed->dex), &(multiplicative->dex), mods);
			break;
		case ItemConsts::MODIFIER_ATK:		// ATK
			//std::cout << "apply_single_modifier: Adjusting ATK - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->atk << ", mult = " << multiplicative->atk << std::endl;
			apply_modifier_value(m, &(fixed->atk), &(multiplicative->atk), mods);
			break;
		case ItemConsts::MODIFIER_DEF:		// DEF
			//std::cout << "apply_single_modifier: Adjusting DEF - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->def << ", mult = " << multiplicative->def << std::endl;
			apply_modifier_value(m, &(fixed->def), &(multiplicative->def), mods);
			break;
		case ItemConsts::MODIFIER_SPD:		// SPD
			//std::cout << "apply_single_modifier: Adjusting SPD - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->spd << ", mult = " << multiplicative->spd << std::endl;
			apply_modifier_value(m, &(fixed->spd), &(multiplicative->spd), mods);
			break;
		case ItemConsts::MODIFIER_FATK:		// FAtk
			//std::cout << "apply_single_modifier: Adjusting FAtk - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			//std::cout << "apply_single_modifier: Fixed = " << fixed->f_atk << ", mult = " << multiplicative->f_atk << std::endl;
			apply_modifier_value(m, &(fixed->f_atk), &(multiplicative->f_atk), mods);
			break;
		case ItemConsts::MODIFIER_IATK:		// IAtk
			//std::cout << "apply_single_modifier: Adjusting IAtk - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->i_atk), &(multiplicative->i_atk), mods);
			break;
		case ItemConsts::MODIFIER_LATK: 	// LAtk
			//std::cout << "apply_single_modifier: Adjusting LAtk - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->l_atk), &(multiplicative->l_atk), mods);
			break;
		case ItemConsts::MODIFIER_FDEF:		// FDef
			//std::cout << "apply_single_modifier: Adjusting FDef - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->f_def), &(multiplicative->f_def), mods);
			break;
		case ItemConsts::MODIFIER_IDEF:	// IDef
			//std::cout << "apply_single_modifier: Adjusting IDef - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->i_def), &(multiplicative->i_def), mods);
			break;
		case ItemConsts::MODIFIER_LDEF:	// LDef
			//std::cout << "apply_single_modifier: Adjusting LDef - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->l_def), &(multiplicative->l_def), mods);
			break;
		case ItemConsts::MODIFIER_APT:	// Attacks per turn
			//std::cout << "apply_single_modifier: Adjusting APT - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->apt), &(multiplicative->apt), mods);
			break;
		case ItemConsts::MODIFIER_MAX_HP:	// Max HP
			//std::cout << "apply_single_modifier: Adjusting Max HP - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->max_hp), &(multiplicative->max_hp), mods);
			break;
		case ItemConsts::MODIFIER_FDMG:	// Fire damage taken
			//std::cout << "apply_single_modifier: Adjusting FDmg  - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->f_dmg), &(multiplicative->f_dmg), mods);
			break;
		case ItemConsts::MODIFIER_IDMG:	// Ice damage taken
			//std::cout << "apply_single_modifier: Adjusting IDmg - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->i_dmg), &(multiplicative->i_dmg), mods);
			break;
		case ItemConsts::MODIFIER_LDMG:	// Lightning damage taken
			//std::cout << "apply_single_modifier: Adjusting LDmg - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->l_dmg), &(multiplicative->l_dmg), mods);
			break;
		case ItemConsts::MODIFIER_POIS:	// Poisoned
			//std::cout << "apply_single_modifier: Turning on equipment poison" << std::endl;
			g_player.is_equip_poisoned = true;
			break;
		case ItemConsts::MODIFIER_BLOCK:	// Chance to block
			//std::cout << "apply_single_modifier: Adjusting Block - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->block), &(multiplicative->block), mods);
			break;
		case ItemConsts::MODIFIER_ADMG: 	// All damage taken
			//std::cout << "apply_single_modifier: Adjusting ADmg - mode " << (int)m.modifier_mode << ", value " << m.magnitude << std::endl;
			apply_modifier_value(m, &(fixed->a_dmg), &(multiplicative->a_dmg), mods);
			break;
	}
}

//----------------------------------------------------------------------------
// Gets the base stats and mods for an item, determine what stats the mods
// affect, and adjust the fixed and mulitplicative stats accordingly
//
// Arguments:
//   i - the item to process
//   fixed - a set of stats to apply fixed increases/decreases to
//   multiplicative - a set of stats to apply multiplicative 
//                    increases/decreases to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void apply_item_values_to_stats(Item *i, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods) {
	if (i->get_item_class() == ItemConsts::WEAPON_CLASS) {
		//std::cout << "apply_item_values_to_stats: attack was " << fixed->atk << std::endl;
		fixed->atk += i->get_attack();
		//std::cout << "apply_item_values_to_stats: attack is now " << fixed->atk << std::endl;
	}
	if (i->get_item_class() == ItemConsts::ARMOR_CLASS) {
		//std::cout << "apply_item_values_to_stats: defense was " << fixed->def << std::endl;
		fixed->def += i->get_defense();
		//std::cout << "apply_item_values_to_stats: defense is now " << fixed->def << std::endl;
	}

	int idx;
	if(i->get_prefix() != -1) {
		ItemPrefixType p;
		int prefix = i->get_prefix();
		if (i->is_it_cursed()) {
			p = g_cursed_item_prefix_ids[prefix];
		}
		else {
			p = g_item_prefix_ids[prefix];
		}
		//std::cout << "apply_item_values_to_stats: name: " << p.name << ", num mods = " << (int)p.num_modifiers << std::endl;
		for (idx=0; idx < p.num_modifiers; idx++) {
			//std::cout << "apply_item_values_to_stats: applying prefix id " << idx << std::endl;
			apply_single_modifier(p.modifiers[idx], fixed, multiplicative, mods);
		}
	}
	if(i->get_suffix() != -1) {
		ItemSuffixType p;
		int suffix = i->get_suffix();
		if (i->is_it_cursed()) {
			p = g_cursed_item_suffix_ids[suffix];
		}
		else {
			p = g_item_suffix_ids[suffix];
		}
		//std::cout << "apply_item_values_to_stats: name: " << p.name << ", num mods = " << (int)p.num_modifiers << std::endl;
		for (idx=0; idx < p.num_modifiers; idx++) {
			//std::cout << "apply_item_values_to_stats: applying suffix id " << idx << std::endl;
			apply_single_modifier(p.modifiers[idx], fixed, multiplicative, mods);
		}
	}
}