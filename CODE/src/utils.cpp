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

//------------------------------------------------------------------------------
// Deallocates memory used by the item and enemies lists.
//
// Arguments:
//	 None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void DungeonFloor::clear_lists() {
	// An iterator for the entire map structure
	std::map <std::pair<int, int>, std::list<Item*> >::iterator it;
	// An iterator for a list in the structure
	std::list<Item *>::iterator list_it;

	// Iterate through the item map and remove individual sublists found
	for (it = items.begin(); it != items.end(); ++it) {
		//std::cout << "Found a list" << std::endl;
		// Iterate through the found list and delete any items found in it
		for (list_it = it->second.begin(); list_it != it->second.end(); ++list_it) {
			if (*list_it != NULL) {
				//std::cout << "  Found an Item" << std::endl;
				delete *list_it;
			}
		}
	}	

	// Deallocate any remaining Enemies in the list before clearing it
	std::list<Enemy *>::iterator enemy_it;
	for (enemy_it = enemies.begin(); enemy_it != enemies.end(); ++enemy_it) {
		if (*enemy_it != NULL) {
			delete *enemy_it;
		}
	}

	// Reset the actual maps/lists
	items.clear();
	enemies.clear();
}

//------------------------------------------------------------------------------
// Populates the maze with a quantity of generated enemies of appropriate enemy 
// level.
//
// Arguments:
//	 min_enemies - the minimum number of enemies to create
//   max_enemies - the maximum number of enemies to create
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void DungeonFloor::generate_enemies(int min_enemies, int max_enemies) {
	// Pick a number of enemies
	// For each number
	//	 - Create an enemy
	// Loop:
	//   - Pick a location
	//   - Check existing enemies to see if an enemy already sits there
	//      - If so, pick another location, repeat loop
	//      - if not
	//        - Add the enemy to the list of enemies
	//        - Mark done with iteration
	
	int num_enemies = (rand() % (max_enemies - min_enemies)) + min_enemies;
	bool is_placed;
	for (int i = 0; i < num_enemies; ++i) {
		is_placed = false;
		do {
			int x = rand() % maze->get_width();
			int y = rand() % maze->get_height();
			// Only place an enemy on a carved square with no stairs
			if (maze->is_carved(x, y) && maze->stairs_here(x, y) == MazeConsts::NO_STAIRS) {
				// Check to see if this space is already taken by an enemy
				if (true) {
					// If not, create one and put it here
					Enemy *e = EnemyGenerator::generate(ilevel);
					add_enemy(x, y, e);
					is_placed = true;
				}
			}
		} while (!is_placed);
	}

}

//------------------------------------------------------------------------------
// Adds an enemy to the maze at the specified location
//
// Arguments:
//	 x, y - the coordinates of the location of the enemy
//   e - the enemy to add
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void DungeonFloor::add_enemy(int x, int y, Enemy *e) {
	e->set_pos(x, y);
	enemies.push_back(e);
}


//------------------------------------------------------------------------------
// Populates the maze with a quantity of generated items of appropriate item
// level.
//
// Arguments:
//	 min_items - the minimum number of items to create
//   max_items - the maximum number of items to create
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void DungeonFloor::generate_items(int min_items, int max_items) {
	int num_items = (rand() % (max_items - min_items)) + min_items;
	bool is_placed;
	//std::cout << "maze_generator: Adding " << num_items << " items..." << std::endl;

	for (int i = 0; i < num_items; ++i) {
		is_placed = false;
		do {
			int x = rand() % maze->get_width();
			int y = rand() % maze->get_height();
			if (maze->is_carved(x, y) && maze->stairs_here(x, y) == MazeConsts::NO_STAIRS) {
				std::pair<int, int> p = std::make_pair(x, y);
				Item *item = ItemGenerator::generate(ilevel);
				add_item(x, y, item);
				//std::cout << "maze_generator: Added item " << item->get_full_name() << " at position (" << x << ", " << y << ")" << std::endl;
				is_placed = true;
			}
		} while (!is_placed);
	}
	//std::cout << "maze_generator:  Finished adding items" << std::endl;
}

//------------------------------------------------------------------------------
// Adds an item to the maze at the specified location
//
// Arguments:
//	 x, y - the coordinates of the location of the item
//   i - the item to add
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void DungeonFloor::add_item(int x, int y, Item *i) {
	std::pair<int, int> p = std::make_pair(x, y);
	items[p].push_back(i);
}

//------------------------------------------------------------------------------
// Gets a list of items at the specified location
//
// Arguments:
//   x, y - the coordinates of the location to retreive items
//
// Returns:
//   A list of Item* containing any items at that location.  Returns
//   an empty list if there are no items.
//------------------------------------------------------------------------------
std::list<Item *> DungeonFloor::get_items_at(int x, int y) {
	std::list<Item *> item_list;
	std::map <std::pair<int, int>, std::list<Item*> >::iterator it;

	std::pair<int, int> p = std::make_pair(x, y);
	it = items.find(p);
	if (it != items.end()) {
		//std::cout << "get_items_at: Found a list!" << std::endl;
		item_list = it->second;
	}
	else {
		//std::cout << "get_items_at: Didn't find a list, will return the default" << std::endl;
	}

	return item_list;
}

//------------------------------------------------------------------------------
// Gets the number of items sitting at the specified location
//
// Arguments:
//   x, y - the coordinates of the item to check
//
// Returns:
//   The number of items at the location
//------------------------------------------------------------------------------
int DungeonFloor::get_num_items_at(int x, int y) {
	std::list<Item *> item_list = get_items_at(x, y);
	return item_list.size();
}

//------------------------------------------------------------------------------
// Removes the last item from the item list for the specified spot in the maze
//
// Arguments:
//   x, y - the coordinates of the location to process
// 
// Returns:
//   nothing
//
// Notes:
//   When picking up an item, it's always pulled from the back of the list,
//   so there's no equivalent (remove_item_from_front_at) function.
//------------------------------------------------------------------------------

void DungeonFloor::remove_item_from_end_at(int x, int y) {
	Item *i;
	int num_items = get_num_items_at(x, y);
	if (num_items > 0) {
		//std::cout << "Number of items was " << num_items << std::endl;
		std::pair<int, int> p = std::make_pair(x, y);

		// Remove the pointer from the list
		items[p].pop_back();

		num_items = get_num_items_at(x, y);
		//std::cout << "Number of items is now " << num_items << std::endl;
	}
}

//------------------------------------------------------------------------------
// Updates the main display for the main game state
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void update_main_game_display(void) {
	// Update the maze area if requested
	if (g_state_flags.update_maze_area == true) {
		if (g_state_flags.in_dungeon) {
			// Add the areas around the player to the map bitmap
			//std::cout << "update_display: adding area to map bitmap" << std::endl;
			g_render.add_area_to_map_bitmap(&g_dungeon, g_player.get_x_pos(), g_player.get_y_pos());
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
				g_dungeon.maze->set_room_entered_state(room_to_light, true);
			}
			//std::cout << "update_display: Finished processing lighting" << std::endl;

			// Draw the world display area
			g_render.render_world_at_player(g_back_buffer, &g_dungeon, g_player.get_x_pos(), g_player.get_y_pos());
			//std::cout << "update_display: rendered world" << std::endl;
		}
		else {
			// Draw the appropriate part of the town
			g_render.render_town_at_player(g_back_buffer, g_player.get_x_pos(), g_player.get_y_pos());
		}
		g_state_flags.update_maze_area = false;
	}

	// Update the status area if requested
	if(g_state_flags.update_status_dialog == true) {
		g_render.render_status_base(g_back_buffer);
		g_render.render_status_ui(g_back_buffer);
		g_state_flags.update_status_dialog = false;
	}

	// Update the HP and exp bars if requested
	if(g_state_flags.update_status_hp_exp == true) {
		g_render.render_hp_exp_bar(g_back_buffer);
		g_state_flags.update_status_hp_exp = false;
	}

	// Update the text dialog if requested
	if(g_state_flags.update_text_dialog == true) {
		g_render.render_text_base(g_back_buffer, g_state_flags.text_log_extended);
		g_render.render_text_log(g_back_buffer, g_state_flags.text_log_extended);
		g_state_flags.update_text_dialog = false;
	}

	// If we're in a substate, render on top of everything else as needed
	switch (g_state_flags.cur_substate) {
		case GAME_SUBSTATE_MAP:
			g_render.render_map(g_back_buffer);
			break;
		case GAME_SUBSTATE_INVENTORY:
		case GAME_SUBSTATE_INVENTORY_MENU:
			g_render.render_inventory(g_back_buffer);
			break;
		case GAME_SUBSTATE_STATS:
			g_render.render_stats_screen(g_back_buffer);
			break;
		default:
			break;
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

	// Clear the enemies and items lists
	d.clear_lists();

	//std::cout << "generate_new_dungeon_floor: Generating floor " << level << "..." << std::endl;
	d.depth = level;

	// Set the maximum depth and size for the current dungeon
	// Yes, this is done every floor when it doesn't need to be, but fine.
	d.max_depth = g_max_dungeon_depths[d.maze_id];
	d.width = g_dungeon_sizes[d.maze_id];
	d.height = g_dungeon_sizes[d.maze_id];

	// Set the current ilevel based on the dungeon the player is in and the
	// floor they're on
	switch (d.maze_id) {
		case DUSTY_TUNNELS:
			d.ilevel = level / 2;
			if (d.ilevel < 1 ) d.ilevel = 1;
			if (d.ilevel > 25) d.ilevel = 25;
			break;
		case MARBLE_HALLS:
			d.ilevel = 20 + (level / 2);
			if (d.ilevel < 20 ) d.ilevel = 20;
			if (d.ilevel > 70) d.ilevel = 70;
			break;
		case CRYSTAL_DEPTHS:
			d.ilevel = 30 + (level / 2);
			if (d.ilevel < 30 ) d.ilevel = 30;
			if (d.ilevel > 100) d.ilevel = 100;
			break;
		default:
			d.ilevel = 100;
			break;
	}

	d.maze = new Maze(d.width, d.height, d.ilevel);

	// If we're at the bottom, direct the maze generator to omit down stairs
	if(d.depth >= d.max_depth)
		d.maze->set_stair_gen_behavior(MazeConsts::GENERATE_NO_DOWN_STAIRS);

	// Generate the maze structure itself
	d.maze->generate();

	// Generate a few items on the ground
	d.generate_items(10, 30);

	// Populate the maze with an assortment of enemies
	d.generate_enemies(10, 20);

	std::pair<int, int> stairLoc;
	// Place the player on a random set of stairs based on where they came from
	if (stairs_from == MazeConsts::STAIRS_DOWN)
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_UP);
	else
		stairLoc = d.maze->get_random_stair(MazeConsts::STAIRS_DOWN);

	// Place the player at the stair location
	g_player.set_position(stairLoc.first, stairLoc.second);

	// Light the room and mark it as visited	
	int initial_room = d.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos());
	g_player.set_last_room_entered(initial_room);	
	if (initial_room != -1) {
		//d.maze->change_room_lit_status(initial_room, false);		
		d.maze->change_room_lit_status(initial_room, true);			
	}

	// Update the distance from the player to each enemy and sort
	get_enemy_distances(d.enemies, g_player.get_x_pos(), g_player.get_y_pos());

	// Process initial vision for the enemies
	process_enemy_vision(d.enemies);

	// Use the short text log by default
	g_state_flags.text_log_extended = false;

	// Clear the map bitmap
	g_render.initialize_map_bitmap(&g_dungeon);

	// Force an explicit display update so the user can see the world right away
	force_update_screen();
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

	// Scramble the potions and scrolls
	scramble_potion_icons();
	scramble_scroll_icons();

	g_identified_potions.clear();
	g_identified_scrolls.clear();

	// Reset the identified state for all scrolls and potions
	for (int i = 0; i < ItemConsts::NUM_POTIONS; ++i) {
		g_identified_potions.push_back(false);
	}
	for (int i = 0; i < ItemConsts::NUM_SCROLLS; ++i) {
		g_identified_scrolls.push_back(false);
	}

	// The 'default' dungeon is Dusty Tunnels
	g_dungeon.maze_id = DUSTY_TUNNELS;

	// create a new inventory (TODO - move to an earlier state)
	g_inventory = new Inventory();

	// Put the player in the place they start a new game
	g_player.place_in_town_start();

	// Set initial flags to render stuff like the UI
	force_update_screen();
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
			g_state_flags.in_dungeon = false;
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
	int item_count = g_dungeon.get_num_items_at(g_player.get_x_pos(), g_player.get_y_pos());
	int idx = 0;

	if (item_count > 0) {
		std::list<Item *> items = g_dungeon.get_items_at(g_player.get_x_pos(), g_player.get_y_pos());
		for (std::list<Item *>::iterator it = items.begin(); it != items.end(); ++ it) {
			if (idx == 0)
				g_text_log.put_line("You see " + (*it)->get_full_name() + ".");
			else
				g_text_log.put_line("You also see " + (*it)->get_full_name() + ".");
			++idx;
		}
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
			g_dungeon.add_item(x, y, i);
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_items = true;
			g_state_flags.update_inventory_description = true;
		}
	}
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
    if (g_dungeon.get_num_items_at(x, y) <= 0) {
        return;
    } 
    else {
        // Get the item list and process the one at the end 
        // (which is the one that the player can see)
        std::list<Item *> items = g_dungeon.get_items_at(x, y);

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
			g_state_flags.update_status_hp_exp = true;
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
            g_dungeon.remove_item_from_end_at(x, y);
            g_text_log.put_line("Picked up " + item_name + ".");
            g_state_flags.update_maze_area = true;
            g_state_flags.update_display = true;
        }

		// TODO - remove this once enemies have been added
		// Add some experience when the player picks a thing up
		if (picked_up) {
			g_state_flags.update_status_hp_exp = true;
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
				// If the item was a potion or scroll, using it identifies all items of that kind until
				// the current gen of player dies.  The 'identify' function works for the current 
				// stack in the inventory; g_identified_<XYZ> ensures future items are auto-identified
				if (i->get_item_class() == ItemConsts::POTION_CLASS || i->get_item_class() == ItemConsts::SCROLL_CLASS) {
					perform_identification_action(i, true);
				} 
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
				Item **equip_slot = g_player.get_item_slot_by_type(i->get_type_id());
				g_player.unequip(equip_slot);
			}
			break;
		case UiConsts::ITEM_OPTION_DROP:
			// If the item can be dropped, and currently isn't equipped, drop it on the ground
			if (g_state_flags.in_dungeon && i->can_be_dropped() && !i->is_it_equipped()) {
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
    int stairs; 
    int depth;

	if (g_state_flags.in_dungeon) {
		stairs = g_dungeon.maze->stairs_here(x, y);

	    // If there aren't actually any stairs, then do nothing
	    if (stairs == MazeConsts::NO_STAIRS)
        	return;

	    // If the stairs are down stairs, the new floor should be
	    // one greater than the current one (with a limit of the 
	    // maximum floor value for the current dungeon)
	    if (stairs == MazeConsts::STAIRS_DOWN) {
			if (g_state_flags.in_dungeon)
				depth = g_dungeon.depth + 1;
			else
		        depth = 1;
        	if (depth > g_dungeon.max_depth)
	            depth = g_dungeon.max_depth;
	    }

		// If the stairs are up stairs, move up.  If on the first
		// floor, transition to town.
	    if (stairs == MazeConsts::STAIRS_UP) {
    	    depth = g_dungeon.depth - 1;
	        if (depth < 1) {
				exit_dungeon(false);
				return;
			}
    	}

    	// Generate a new dungeon with the new floor value
    	generate_new_dungeon_floor(g_dungeon, depth, stairs); 
	}
	else {
		// Check to see if we're sitting on one of the dungeon
		// entrances, and enter the correct dungeon from the
		// first floor
		check_and_process_town_entrances(x, y);
	}
}

//----------------------------------------------------------------------------
// Processes the transition from the dungeon to town
//
// Arguments:
//   used_recall - was a scroll of recall used to exit?
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void exit_dungeon(bool used_recall) {
    g_state_flags.in_dungeon = false;
	// Place the player in the correct spot for the dungeon
	// they're leaving
	switch(g_dungeon.maze_id) {
		case DUSTY_TUNNELS:
			if(used_recall) {
				g_player.x_pos = TownConsts::DT_RECALL_X;
				g_player.y_pos = TownConsts::DT_RECALL_Y;
			}
			else {
				g_player.x_pos = TownConsts::DUSTY_TUNNELS_X;
				g_player.y_pos = TownConsts::DUSTY_TUNNELS_Y;
			}
			break;
		case MARBLE_HALLS:
			if (used_recall) {
				g_player.x_pos = TownConsts::MH_RECALL_X;
				g_player.y_pos = TownConsts::MH_RECALL_Y;
			}
			else {
				g_player.x_pos = TownConsts::MARBLE_HALLS_X;
				g_player.y_pos = TownConsts::MARBLE_HALLS_Y;
			}
			break;
		case CRYSTAL_DEPTHS:
			if (used_recall) {
				g_player.x_pos = TownConsts::CD_RECALL_X;
				g_player.y_pos = TownConsts::CD_RECALL_Y;
			}	
			else {
				g_player.x_pos = TownConsts::CRYSTAL_DEPTHS_X;
				g_player.y_pos = TownConsts::CRYSTAL_DEPTHS_Y;
			}
			break;
	}
	force_update_screen();
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

//----------------------------------------------------------------------------
// Applies a mode 2 modifier (% of A as B) to the player's stats
//
// Arguments:
//	 m - a ModifierMagType that holds the source+destintaion stat + amount
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void apply_mode_2_modifier_value(ModifierMagType m) {
	float *from_val, *to_val;

	// Determine where the value comes from 
	switch (m.modifier_id) {
		case ItemConsts::MODIFIER_STR:		// STR
			//std::cout << "apply_mode_2_modifier_value: source stat = STR" << std::endl;
			from_val = &(g_player.actual.str);
			break;
		case ItemConsts::MODIFIER_CON:		// CON
			//std::cout << "apply_mode_2_modifier_value: source stat = CON" << std::endl;
			from_val = &(g_player.actual.con);
			break;
		case ItemConsts::MODIFIER_DEX:		// DEX
			//std::cout << "apply_mode_2_modifier_value: source stat = DEX" << std::endl;
			from_val = &(g_player.actual.dex);
			break;
		case ItemConsts::MODIFIER_ATK:		// ATK
			//std::cout << "apply_mode_2_modifier_value: source stat = ATK" << std::endl;
			from_val = &(g_player.actual.atk);
			break;
		case ItemConsts::MODIFIER_DEF:		// DEF
			//std::cout << "apply_mode_2_modifier_value: source stat = DEF" << std::endl;
			from_val = &(g_player.actual.def);
			break;
		case ItemConsts::MODIFIER_SPD:		// SPD
			//std::cout << "apply_mode_2_modifier_value: source stat = SPD" << std::endl;
			from_val = &(g_player.actual.spd);
			break;
		case ItemConsts::MODIFIER_FATK:		// FAtk
			//std::cout << "apply_mode_2_modifier_value: source stat = FAtk" << std::endl;
			from_val = &(g_player.actual.f_atk);
			break;
		case ItemConsts::MODIFIER_IATK:		// IAtk
			//std::cout << "apply_mode_2_modifier_value: source stat = IAtk" << std::endl;
			from_val = &(g_player.actual.i_atk);
			break;
		case ItemConsts::MODIFIER_LATK:		// LAtk
			//std::cout << "apply_mode_2_modifier_value: source stat = LAtk" << std::endl;
			from_val = &(g_player.actual.l_atk);
			break;
		case ItemConsts::MODIFIER_FDEF:		// FDef
			//std::cout << "apply_mode_2_modifier_value: source stat = FDef" << std::endl;
			from_val = &(g_player.actual.f_def);
			break;
		case ItemConsts::MODIFIER_IDEF:		// IDef
			//std::cout << "apply_mode_2_modifier_value: source stat = IDef" << std::endl;
			from_val = &(g_player.actual.i_def);
			break;
		case ItemConsts::MODIFIER_LDEF:		// LDef
			//std::cout << "apply_mode_2_modifier_value: source stat = LDef" << std::endl;
			from_val = &(g_player.actual.l_def);
			break;
		case ItemConsts::MODIFIER_APT:		// APT
			//std::cout << "apply_mode_2_modifier_value: source stat = APT" << std::endl;
			from_val = &(g_player.actual.apt);
			break;
		case ItemConsts::MODIFIER_MAX_HP:	// Max HP
			//std::cout << "apply_mode_2_modifier_value: source stat = MAX HP" << std::endl;
			from_val = &(g_player.actual.max_hp);
			break;
		case ItemConsts::MODIFIER_FDMG:		// FDmg
			//std::cout << "apply_mode_2_modifier_value: source stat = FDmg" << std::endl;
			from_val = &(g_player.actual.f_dmg);
			break;
		case ItemConsts::MODIFIER_IDMG:		// IDmg
			//std::cout << "apply_mode_2_modifier_value: source stat = IDmg" << std::endl;
			from_val = &(g_player.actual.i_dmg);
			break;
		case ItemConsts::MODIFIER_LDMG:		// LDmg
			//std::cout << "apply_mode_2_modifier_value: source stat = LDmg" << std::endl;
			from_val = &(g_player.actual.l_dmg);
			break;
		case ItemConsts::MODIFIER_POIS:		// Poison
			// This modifier doesn't have this option
			return;
			break;
		case ItemConsts::MODIFIER_BLOCK:		// Block
			//std::cout << "apply_mode_2_modifier_value: source stat = Block" << std::endl;
			from_val = &(g_player.actual.block);
			break;
		case ItemConsts::MODIFIER_ADMG:			// ADmg
			//std::cout << "apply_mode_2_modifier_value: source stat = ADmg" << std::endl;
			from_val = &(g_player.actual.a_dmg);
			break;
	}

	// Determine where the value goes
	switch (m.secondary_id) {
		case ItemConsts::MODIFIER_STR:		// STR
			//std::cout << "apply_mode_2_modifier_value: dest stat = STR" << std::endl;
			to_val = &(g_player.actual.str);
			break;
		case ItemConsts::MODIFIER_CON:		// CON
			//std::cout << "apply_mode_2_modifier_value: dest stat = CON" << std::endl;
			to_val = &(g_player.actual.con);
			break;
		case ItemConsts::MODIFIER_DEX:		// DEX
			//std::cout << "apply_mode_2_modifier_value: dest stat = DEX" << std::endl;
			to_val = &(g_player.actual.dex);
			break;
		case ItemConsts::MODIFIER_ATK:		// ATK
			//std::cout << "apply_mode_2_modifier_value: dest stat = ATK" << std::endl;
			to_val = &(g_player.actual.atk);
			break;
		case ItemConsts::MODIFIER_DEF:		// DEF
			//std::cout << "apply_mode_2_modifier_value: dest stat = DEF" << std::endl;
			to_val = &(g_player.actual.def);
			break;
		case ItemConsts::MODIFIER_SPD:		// SPD
			//std::cout << "apply_mode_2_modifier_value: dest stat = SPD" << std::endl;
			to_val = &(g_player.actual.spd);
			break;
		case ItemConsts::MODIFIER_FATK:		// FAtk
			//std::cout << "apply_mode_2_modifier_value: dest stat = FAtk" << std::endl;
			to_val = &(g_player.actual.f_atk);
			break;
		case ItemConsts::MODIFIER_IATK:		// IAtk
			//std::cout << "apply_mode_2_modifier_value: dest stat = IAtk" << std::endl;
			to_val = &(g_player.actual.i_atk);
			break;
		case ItemConsts::MODIFIER_LATK:		// LAtk
			//std::cout << "apply_mode_2_modifier_value: dest stat = LAtk" << std::endl;
			to_val = &(g_player.actual.l_atk);
			break;
		case ItemConsts::MODIFIER_FDEF:		// FDef
			//std::cout << "apply_mode_2_modifier_value: dest stat = FDef" << std::endl;
			to_val = &(g_player.actual.f_def);
			break;
		case ItemConsts::MODIFIER_IDEF:		// IDef
			//std::cout << "apply_mode_2_modifier_value: dest stat = IDef" << std::endl;
			to_val = &(g_player.actual.i_def);
			break;
		case ItemConsts::MODIFIER_LDEF:		// LDef
			//std::cout << "apply_mode_2_modifier_value: dest stat = LDef" << std::endl;
			to_val = &(g_player.actual.l_def);
			break;
		case ItemConsts::MODIFIER_APT:		// APT
			//std::cout << "apply_mode_2_modifier_value: dest stat = APT" << std::endl;
			to_val = &(g_player.actual.apt);
			break;
		case ItemConsts::MODIFIER_MAX_HP:	// Max HP
			//std::cout << "apply_mode_2_modifier_value: dest stat = Max HP" << std::endl;
			to_val = &(g_player.actual.max_hp);
			break;
		case ItemConsts::MODIFIER_FDMG:		// FDmg
			//std::cout << "apply_mode_2_modifier_value: dest stat = FDmg" << std::endl;
			to_val = &(g_player.actual.f_dmg);
			break;
		case ItemConsts::MODIFIER_IDMG:		// IDmg
			//std::cout << "apply_mode_2_modifier_value: dest stat = IDmg" << std::endl;
			to_val = &(g_player.actual.i_dmg);
			break;
		case ItemConsts::MODIFIER_LDMG:		// LDmg
			//std::cout << "apply_mode_2_modifier_value: dest stat = LDmg" << std::endl;
			to_val = &(g_player.actual.l_dmg);
			break;
		case ItemConsts::MODIFIER_POIS:		// Poison
			// This modifier doesn't have this option
			return;
			break;
		case ItemConsts::MODIFIER_BLOCK:		// Block
			//std::cout << "apply_mode_2_modifier_value: dest stat = Block" << std::endl;
			to_val = &(g_player.actual.block);
			break;
		case ItemConsts::MODIFIER_ADMG:			// ADmg
			//std::cout << "apply_mode_2_modifier_value: dest stat = ADmg" << std::endl;
			to_val = &(g_player.actual.a_dmg);
			break;
	}

	//std::cout << "apply_mode_2_modifier_value: magnitude = " << m.magnitude << std::endl;

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

//----------------------------------------------------------------------------
// Generates a scrambled list of potion tiles, so the player can't recognize
// unidentified potions.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void scramble_potion_icons(void) {
	g_scrambled_potion_icons.clear();

	for (int i = ItemConsts::FIRST_POTION_GID; i <= ItemConsts::LAST_POTION_GID; ++i) {
		g_scrambled_potion_icons.push_back(i);
	}
	std::random_shuffle(g_scrambled_potion_icons.begin(), g_scrambled_potion_icons.end());

}

//----------------------------------------------------------------------------
// Generates a scrambled list of scroll tiles, so the player can't recognize
// unidentified scrolls
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void scramble_scroll_icons(void) {
	g_scrambled_scroll_icons.clear();

	for (int i = ItemConsts::FIRST_SCROLL_GID; i <= ItemConsts::LAST_SCROLL_GID; ++i) {
		g_scrambled_scroll_icons.push_back(i);
	}
	std::random_shuffle(g_scrambled_scroll_icons.begin(), g_scrambled_scroll_icons.end());
}

//----------------------------------------------------------------------------
// Gets the tile ID of the item to be rendered.  For most items, this is just
// the GID.  For scrolls and potions, the offset is stored in a list of
// scrambled tile IDs.
//
// Arguments:
//   i - the item to get the tile ID of
//
// Returns:
//   the tile ID
//----------------------------------------------------------------------------
int get_tile_to_render(Item *i) {

	int i_class = i->get_item_class();
	int i_id = i->get_id();

	if (i_class == ItemConsts::POTION_CLASS) {
		return g_scrambled_potion_icons[i_id];
	}
	else if (i_class == ItemConsts::SCROLL_CLASS) {
		return g_scrambled_scroll_icons[i_id];	
	}
	else {
		return i->get_gid();
	}
}

//----------------------------------------------------------------------------
// For any items sitting at the player's feet, identify them if they're a
// potion or scroll that has previously been identified
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void identify_previously_known_items_at_player() {
	int item_count = g_dungeon.get_num_items_at(g_player.get_x_pos(), g_player.get_y_pos());

	if (item_count > 0) {
		std::list<Item *> items = g_dungeon.get_items_at(g_player.get_x_pos(), g_player.get_y_pos());
		for (std::list<Item *>::iterator it = items.begin(); it != items.end(); ++ it) {
			identify_if_previously_known((*it));
		}
	}
}

//----------------------------------------------------------------------------
// If the specified item type (potion or scroll) has been previously 
// identified, identify it automatically
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void identify_if_previously_known(Item *i) {
    // If the item is a potion or scroll and has been previously identified, 
    // mark it as such
    if(i->get_item_class() == ItemConsts::POTION_CLASS){
        if (g_identified_potions[i->get_id()] == true)
            i->identify();
    }        
    if(i->get_item_class() == ItemConsts::SCROLL_CLASS)
    {
        if (g_identified_scrolls[i->get_id()] == true) {
            i->identify();
        }
    }
}

//----------------------------------------------------------------------------
// Do all tasks related to identification.  This includes marking the 
// item as identified, marking all potions and scrolls of the identified type
// as identified, and optionally displaying a message to the log
//
// Arguments:
//   i - the item to identify
//   log - log to game log if true, don't log otherwise
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void perform_identification_action(Item *i, bool log) {
	std::string old_name = i->get_full_name();
                
	i->identify();
	if (i->get_item_class() == ItemConsts::POTION_CLASS)
		g_identified_potions[i->get_id()] = true;
	if (i->get_item_class() == ItemConsts::SCROLL_CLASS)
		g_identified_scrolls[i->get_id()] = true;
    if (log) {
        g_text_log.put_line(old_name + " is " + i->get_full_name() + ".");
    }
}

//----------------------------------------------------------------------------
// Generates a random item index from the given pool
//
// Arguments:
//  pool - the pool to draw from
//  pool_size - the number of elements in the pool to consider
//  max_val - the highest possible value in the pool
//
// Returns:
//  The index from the pool selected, or 0 (the default item) if something
//  went wrong
//----------------------------------------------------------------------------
int roll_from_pool(const int *pool, int pool_size, int max_val) {
    int val = rand() % max_val;
    for (int i = 0; i < pool_size; ++i) {
        if (val < pool[i]) {
            return i;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
// Get the Chebyshev distance between two points.  Not as efficient as the
// octile distance would be, but it doesn't use any square roots
//
// Arguments:
//   x1, y1 - the first point 
//   x2, y2 - the second point
//
// Returns:
//   The distance
//----------------------------------------------------------------------------
int get_diagonal_distance_between(int x1, int y1, int x2, int y2) {
	return max(abs(x2 - x1), abs(y2 - y1));
}

//----------------------------------------------------------------------------
// Get the Manhattan distance between two points.  Not as accurate as the
// Pythagorean method, but much faster
//
// Arguments:
//   x1, y1 - the first point 
//   x2, y2 - the second point
//
// Returns:
//   The distance
//----------------------------------------------------------------------------
int get_manhattan_distance_between(int x1, int y1, int x2, int y2) {
	return (abs(x2 - x1) + abs(y2 - y1));
}

//----------------------------------------------------------------------------
// Get the Euclidian distance between two points.  The most accurate method,
// but the square root makes it slower
//
// Arguments:
//   x1, y1 - the first point 
//   x2, y2 - the second point
//
// Returns:
//   The distance
//----------------------------------------------------------------------------
int get_distance_between(int x1, int y1, int x2, int y2) {
	int a = abs(x2 - x1);
	int b = abs(y2 - y1);
	return (int)sqrt((a * a) + (b *b));
}

//----------------------------------------------------------------------------
// A utility function used to assist with sorting the enemy list - this
// function assists with sorting by distance
//
// Arguments:
//	first, second - the enemies to compare
//
// Returns:
//  true if the first is lower, false otherwise
//----------------------------------------------------------------------------
bool enemy_distance_sort(Enemy *first, Enemy *second) {
	return (first->get_distance() < second->get_distance());
}

//----------------------------------------------------------------------------
// Sorts a list of enemies by distance, from closest to furthest
//
// Arguments:
//	el - the list to sort
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void sort_enemy_list(std::list<Enemy *> &el) {
	el.sort(enemy_distance_sort);
}

//----------------------------------------------------------------------------
// Calculates the distance from an arbitrary point to each enemy and
// sorts the resulting list by distance
//
// Arguments:
//	el - the enemy list
//  x, y - the point
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void get_enemy_distances(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), x, y);
		(*enemy_it)->set_distance(distance);
	}

	sort_enemy_list(el);
}

//----------------------------------------------------------------------------
// For any sufficiently close enemies, check to see if they can see the 
// player.
//
// Arguments:
//	el - the enemy list
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void process_enemy_vision(std::list<Enemy *> &el) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->has_seen_the_player()) {
			//std::cout << "process_enemy_vision: the " << (*enemy_it)->get_name() << " has already seen player" << std::endl;
		} 
		else {
			//std::cout << "process_enemy_vision: processing the " << (*enemy_it)->get_name() << std::endl;
			int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), g_player.get_x_pos(), g_player.get_y_pos());
			if (distance <= UtilConsts::MAXIMUM_ENEMY_AI_DISTANCE_FAR && (*enemy_it)->has_seen_the_player() == false) {
				bool seen = (*enemy_it)->check_if_can_see(g_player.get_x_pos(), g_player.get_y_pos());
				if (seen) {
					(*enemy_it)->mark_has_seen_player(true);
				}	
			}
			else {
				//std::cout << "  - enemy is too far away to care" << std::endl;
			}
		}
	}
}

//----------------------------------------------------------------------------
// Marks every enemy too far from the player as having forgotten that the 
// player exists. 
//
// Arguments:
//	el - the enemy list
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void process_enemy_forgetting_player(std::list<Enemy *> &el) {
	int px = g_player.get_x_pos();
	int py = g_player.get_y_pos();
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->has_seen_the_player()) {
			int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), px, py);
			if (distance >= UtilConsts::MAXIMUM_ENEMY_REMEMBER_DISTANCE) {
				(*enemy_it)->mark_has_seen_player(false);
				//std::cout << "process_enemy_forgetting_player: the " << (*enemy_it)->get_name() << " has forgotten the player" << std::endl;
			}
		}
	}
}

//----------------------------------------------------------------------------
// Checks if an enemy is located in the specified position
//
// Arguments:
//	el - the enemy list
//  x, y - the point
//
// Returns:
//	True if an enemy is located there, false otherwise
//----------------------------------------------------------------------------
bool is_enemy_here(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->get_x_pos() == x && (*enemy_it)->get_y_pos() == y)
			return true;
	}

	return false;
}

//----------------------------------------------------------------------------
// Returns the Enemy at the specified position, if there is one
//
// Arguments:
//  x, y - the position
//
// Returns:
//	A pointer to the Enemy if present, NULL otherwise.
//----------------------------------------------------------------------------
Enemy* get_enemy_at(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->get_x_pos() == x && (*enemy_it)->get_y_pos() == y)
			return (*enemy_it);
	}

	return NULL;
}

//----------------------------------------------------------------------------
// Goes through the enemy list and deletes any marked as dead
//
// Arguments:
//  el - the enemy list
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void delete_dead_enemies(std::list<Enemy *> &el) {
	std::list<Enemy *>::iterator enemy_it;

	for (enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->is_it_alive() == false) {
			std::list<Enemy *>::iterator it = enemy_it;
			//std::cout << "delete_dead_enemies: deleting " << (*it)->get_name() << std::endl;
			delete *enemy_it;
			enemy_it = el.erase(it);
		}
	}

	// Now that enemies are dead, we need to update the maze area to
	// remove them from the screen
	g_state_flags.update_maze_area = true;
}

//----------------------------------------------------------------------------
// Checks if the specified location is a place an enemy can be
//
// Arguments:
//  x, y - the point
//
// Returns:
//	True if an enemy can be there, false otherwise
//----------------------------------------------------------------------------
bool is_valid_enemy_position(int x, int y) {
	// Is the square a floor?
	if (!g_dungeon.maze->is_carved(x,y))
		return false;
	// Does the square already contain an enemy?
	if (is_enemy_here(g_dungeon.enemies, x, y))
		return false;

	// If neither are true, the enemy can be here.
	return true;
}

//----------------------------------------------------------------------------
// Determines the direction an enemy should move on its turn
//
// Arguments:
//  e - the enemy
//
// Returns:
//   Nothing.  This function directly moves the enemy.
//----------------------------------------------------------------------------
void perform_enemy_action(Enemy *e) {
	// Does the following :
	//   - Check to see if the player is adjacent.  
	//      - If so, attack the player
	//   - Otherwise, for each of the 8 directions
	//      - If the position can be moved to (no wall, no enemy, no player)
	//          - calculate the distance from the player
	//          - push a pair <direction, distance> to a vector
	//	 - With the resulting vector:
	//   - Make a pass, find the lowest distance and add each one
	//   - Pick a random element from the second vector
	//   - Use the direction component of the selected element to move the enemy

	// Being greedy, this will lead to non-optimal behavior (enemies getting stuck
	// behind walls, and such), but non-optimal behavior is much better than the
	// cost and complexity of A*, and behavior in more open spaces will be just fine.
	int x = e->get_x_pos();
	int y = e->get_y_pos();
	int px = g_player.get_x_pos();
	int py = g_player.get_y_pos();

	// If the enemy is 0 or 1 away from the player in both the x and y direction, they're 'adjacent',
	// and should attack the player
	//std::cout << "perform_enemy_action: abs(px-x) = " << abs(px-x) << ", abs(py-y) = " << abs(py-y) << std::endl;
	if (abs(px-x) <= 1 && abs(py-y) <= 1) {
		g_text_log.put_line("The " + e->get_name() + " attacks you!");
		perform_enemy_combat(e);
		if (g_player.hp <= 0) {
			g_text_log.put_line("You are defeated!");
		}
		// TODO: Deal with player death
		return;
	}

	std::vector<std::pair<int, int> > directions;
	std::vector<int> lowest;

	if (is_valid_enemy_position(x - 1, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTHWEST, get_diagonal_distance_between(x - 1, y - 1, px, py)));
	if (is_valid_enemy_position(x, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTH, get_diagonal_distance_between(x, y - 1, px, py)));
	if (is_valid_enemy_position(x + 1, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTHEAST, get_diagonal_distance_between(x + 1, y - 1, px, py)));
	if (is_valid_enemy_position(x - 1, y))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_WEST, get_diagonal_distance_between(x - 1, y, px, py)));
	if (is_valid_enemy_position(x + 1, y))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_EAST, get_diagonal_distance_between(x + 1, y, px, py)));
	if (is_valid_enemy_position(x - 1, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTHWEST, get_diagonal_distance_between(x - 1, y + 1, px, py)));
	if (is_valid_enemy_position(x, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTH, get_diagonal_distance_between(x, y + 1, px, py)));
	if (is_valid_enemy_position(x + 1, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTHEAST, get_diagonal_distance_between(x + 1, y + 1, px, py)));

	// The enemy can't move in any direction; return
	if (directions.size() == 0) {
		//std::cout << "  Enemy can't move" << std::endl;
		return;
	}

	int lowest_distance = 1000;
	// Loop through, find the lowest distance
	for (std::vector<std::pair<int, int> >::iterator it = directions.begin(); it != directions.end(); ++it) {
		if ((*it).second <= lowest_distance)
			lowest_distance = (*it).second;
	}

	// Loop through again, pull out all that have the lowest distance
	for (std::vector<std::pair<int, int> >::iterator it = directions.begin(); it != directions.end(); ++it) {
		if ((*it).second == lowest_distance)
			lowest.push_back((*it).first);
	}

	//std::cout << "Number of lowest values = " << lowest.size() << std::endl;

	int dir = rand() % lowest.size();
	switch (lowest[dir]) {
		case MazeConsts::DIRECTION_NORTHWEST:
			//std::cout << "  Enemy moves northwest" << std::endl;
			e->set_pos(x - 1, y - 1);
			break;
		case MazeConsts::DIRECTION_NORTH:
			//std::cout << "  Enemy moves north" << std::endl;
			e->set_pos(x, y - 1);
			break;
		case MazeConsts::DIRECTION_NORTHEAST:
			//std::cout << "  Enemy moves northeast" << std::endl;
			e->set_pos(x + 1, y - 1);
			break;
		case MazeConsts::DIRECTION_WEST:
			//std::cout << "  Enemy moves west" << std::endl;
			e->set_pos(x - 1, y);
			break;
		case MazeConsts::DIRECTION_EAST:
			//std::cout << "  Enemy moves east" << std::endl;
			e->set_pos(x + 1, y);
			break;
		case MazeConsts::DIRECTION_SOUTHWEST:
			//std::cout << "  Enemy moves southwest" << std::endl;
			e->set_pos(x - 1, y + 1);
			break;
		case MazeConsts::DIRECTION_SOUTH:
			//std::cout << "  Enemy moves south" << std::endl;
			e->set_pos(x, y + 1);
			break;
		case MazeConsts::DIRECTION_SOUTHEAST:
			//std::cout << "  Enemy moves southeast" << std::endl;
			e->set_pos(x + 1, y + 1);
			break;
		default:
			//std::cout << "  Enemy doesn't move" << std::endl;
			break;
	}
}

//----------------------------------------------------------------------------
// 'Attacks' the player, doing all required damage calculations and
// adjusting player/enemy health
//
// Arguments:
//   e - the enemy performing the attack
//
// Returns:
//   Nothing.  The enemy and player health will be adjusted accordingly
//----------------------------------------------------------------------------
void perform_enemy_combat(Enemy *e) {
	for (int attack = 0; attack < e->get_apt(); ++attack) {
		// Calculate physical base damage
		int base_physical_damage = (int)((e->get_atk() + (0.2 * e->get_str())) * ((rand() % 50) + 75) / 100);
		//std::cout << "perform_enemy_combat: enemy base phys = " << base_physical_damage << std::endl;

		// Calculate elemental base damage
		int base_fire_damage = 0;
		int base_ice_damage = 0;
		int base_lightning_damage = 0;
		bool fire_attack_done = false;
		bool ice_attack_done = false;
		bool lightning_attack_done = false;
		if (e->get_fatk() > 0) {
			base_fire_damage = (int)((e->get_fatk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			fire_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base fire = " << base_fire_damage << std::endl;
		}
		if (e->get_iatk() > 0) {
			base_ice_damage = (int)((e->get_iatk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			ice_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base fire = " << base_ice_damage << std::endl;
		}
		if (e->get_latk() > 0) {
			base_lightning_damage = (int)((e->get_latk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			lightning_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base lightning = " << base_lightning_damage << std::endl;
		}		

		// Check for critical hit
		bool attack_crits = false;
		int chance_of_crit = 2 + (int)(e->get_str() / 10);
		if (chance_of_crit > 90)
			chance_of_crit = 90;
		if (rand() % 100 < chance_of_crit) {
			attack_crits = true;
			//std::cout << "perform_enemy_combat: attack crits!" << std::endl;
		}	

		int player_base_damage_taken;
		// Calculate actual base damage
		if (rand() % 100 < (2 + g_player.actual.block)) {
			player_base_damage_taken = 0;
		}
		else {
			player_base_damage_taken = (int)((base_physical_damage - (g_player.actual.def + 0.2 * g_player.actual.con) * (rand() % 50 + 75) / 100));
		}
		//std::cout << "perform_enemy_combat: player base damage taken = " << player_base_damage_taken << std::endl;
		if (player_base_damage_taken < 1)
			player_base_damage_taken = 1;
		//std::cout << "perform_enemy_combat: actual base damage taken = " << player_base_damage_taken << std::endl;

		// Calculate actual elemental damage
		float fire_resist = g_player.actual.f_def / 100;
		float ice_resist = g_player.actual.i_def / 100;
		float lightning_resist = g_player.actual.l_def / 100;
		int player_fire_damage_taken = (int)(base_fire_damage * g_player.actual.f_def * (1.0 - fire_resist) * (rand() % 50 + 75) / 100);
		int player_ice_damage_taken = (int)(base_ice_damage * g_player.actual.i_def * (1.0 - ice_resist) * (rand() % 50 + 75) / 100);
		int player_lightning_damage_taken = (int)(base_lightning_damage * g_player.actual.l_def * (1.0 - lightning_resist) * (rand() % 50 + 75) / 100);
		if (fire_attack_done && player_fire_damage_taken < 1)
			player_fire_damage_taken = 1;
		if (ice_attack_done && player_ice_damage_taken < 1)
			player_ice_damage_taken = 1;
		if (lightning_attack_done && player_lightning_damage_taken < 1)
			player_lightning_damage_taken = 1;
		//std::cout << "perform_enemy_combat: fire damage taken = " << player_fire_damage_taken << std::endl;
		//std::cout << "perform_enemy_combat: ice damage taken = " << player_ice_damage_taken << std::endl;
		//std::cout << "perform_enemy_combat: lightning damage taken = " << player_lightning_damage_taken << std::endl;

		// Sum up all damage
		int total_damage_taken = player_base_damage_taken + player_fire_damage_taken + player_ice_damage_taken + player_lightning_damage_taken;		
		if (attack_crits) {
			g_text_log.put_line("Critical hit!");
			int prevent_chance = (int)(g_player.actual.con / 2);
			if (prevent_chance > 90)
				prevent_chance = 90;
			if (rand() % 100 < prevent_chance) {
				if (rand() % 100 < 50) {
					//std::cout << "perform_enemy_combat: crit missed, no damage taken" << std::endl;
					total_damage_taken = 0;
				}
				//else {
					//std::cout << "perform_enemy_combat: crit missed, standard damage taken" << std::endl;
				//}
			}
			else {
				total_damage_taken = total_damage_taken * 2;
				//std::cout << "perform_enemy combat: crit landed, player takes 2x damage" << std::endl;
			}
		}

		// Subtract player HP
		g_player.hp = g_player.hp - total_damage_taken;

		// Log the damage done to the game log
		//std::cout << "perform_enemy_combat: player takes " << total_damage_taken << " damage." << std::endl;
		//std::cout << "  perform_enemy_combat: player hp remaining = " << g_player.hp << std::endl;
		char text[80];
		sprintf(text, "You take %d damage!", total_damage_taken);
		g_text_log.put_line(text);
	}
}

//----------------------------------------------------------------------------
// 'Attacks' an enemy, doing all required damage calculations and
// adjusting player/enemy health
//
// Arguments:
//  target - the enemy to attack
//
// Returns:
//   Nothing.  The enemy and player health will be adjusted accordingly
//----------------------------------------------------------------------------
void perform_player_combat(Enemy *target) {
	for (int attack = 0; attack < g_player.actual.apt; ++attack) {

		// Calculate physical base damage
		int base_physical_damage = (int)((g_player.actual.atk + (0.2 * g_player.actual.str)) * ((rand() % 50) + 75) / 100);
		//std::cout << "perform_player_combat: player base phys = " << base_physical_damage << std::endl;

		// Calculate elemental base damage
		int base_fire_damage = 0;
		int base_ice_damage = 0;
		int base_lightning_damage = 0;
		bool fire_attack_done = false;
		bool ice_attack_done = false;
		bool lightning_attack_done = false;
		if (g_player.actual.f_atk > 0) {
			base_fire_damage = (int)((g_player.actual.f_atk + (0.1 * g_player.actual.str)) * ((rand() % 50) + 75) / 100);
			fire_attack_done = true;
			//std::cout << "peform_player_combat: player base fire = " << base_fire_damage << std::endl;
		}
		if (g_player.actual.i_atk > 0) {
			base_ice_damage = (int)((g_player.actual.i_atk + (0.1 * g_player.actual.str)) * ((rand() % 50) + 75) / 100);
			ice_attack_done = true;
			//std::cout << "peform_player_combat: player base ice = " << base_ice_damage << std::endl;
		}
		if (g_player.actual.l_atk > 0) {
			base_lightning_damage = (int)((g_player.actual.l_atk + (0.1 * g_player.actual.str)) * ((rand() % 50) + 75) / 100);
			lightning_attack_done = true;
			//std::cout << "peform_player_combat: player base lightning = " << base_lightning_damage << std::endl;
		}

		// Check for critical hit
		bool attack_crits = false;
		int chance_of_crit = 2 + (int)(g_player.actual.str / 10);
		if (chance_of_crit > 90)
			chance_of_crit = 90;
		if (rand() % 100 < chance_of_crit) {
			attack_crits = true;
			//std::cout << "perform_player_combat: attack crits!" << std::endl;
		}

		// Calculate actual base damage
		int enemy_base_damage_taken = (int)((base_physical_damage - target->get_def()) * (rand() % 50 + 75) / 100);
		//std::cout << "perform_player_combat: enemy base damage taken = " << enemy_base_damage_taken << std::endl;
		if (enemy_base_damage_taken < 1)
			enemy_base_damage_taken = 1;
		//std::cout << "perform_player_combat: actual base damage taken = " << enemy_base_damage_taken << std::endl;

		// Calculate actual elemental damage
		float fire_resist = target->get_fdef() / 100;
		float ice_resist = target->get_idef() / 100;
		float lightning_resist = target->get_ldef() / 100;
		int enemy_fire_damage_taken = (int)(base_fire_damage * (1.0 - fire_resist) * (rand() % 50 + 75) / 100);
		int enemy_ice_damage_taken = (int)(base_ice_damage * (1.0 - ice_resist) * (rand() % 50 + 75) / 100);
		int enemy_lightning_damage_taken = (int)(base_lightning_damage * (1.0 - lightning_resist) * (rand() % 50 + 75) / 100);
		if (fire_attack_done && enemy_fire_damage_taken < 1)
			enemy_fire_damage_taken = 1;
		if (ice_attack_done && enemy_ice_damage_taken < 1)
			enemy_ice_damage_taken = 1;
		if (lightning_attack_done && enemy_lightning_damage_taken < 1)
			enemy_lightning_damage_taken = 1;
		//std::cout << "perform_player_combat: fire damage taken = " << enemy_fire_damage_taken << std::endl;
		//std::cout << "perform_player_combat: ice damage taken = " << enemy_ice_damage_taken << std::endl;
		//std::cout << "perform_player_combat: lightning damage taken = " << enemy_lightning_damage_taken << std::endl;

		// Sum up all damage
		int total_damage_taken = enemy_base_damage_taken + enemy_fire_damage_taken + enemy_ice_damage_taken + enemy_lightning_damage_taken;		
		if (attack_crits) {
			g_text_log.put_line("Critical hit!");
			total_damage_taken = total_damage_taken * 2;
		}

		// Subtract enemy HP
		target->set_hp(target->get_hp() - total_damage_taken);

		// Log the damage done to the game log
		//std::cout << "perform_player_combat: enemy takes " << total_damage_taken << " damage." << std::endl;
		//std::cout << "  perform_player_combat: enemy hp remaining = " << target->get_hp() << std::endl;
		char text[80];
		sprintf(text, "The %s takes %d damage!", target->get_name().c_str(), total_damage_taken);
		g_text_log.put_line(text);
	}
}

//----------------------------------------------------------------------------
// Does the things required to enter the dungeon
//
// Arguments:
//  floor - the floor to enter at
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void enter_dungeon(int floor) {
	// Change the player to in the dungeon
	g_state_flags.in_dungeon = true;

	// Turn off any active scroll of recall
	g_player.recall_active = false;

	// Make a new dungeon floor
	generate_new_dungeon_floor(g_dungeon, floor, MazeConsts::STAIRS_DOWN);
	force_update_screen();
}

//----------------------------------------------------------------------------
// Checks to see if the player is on a dungeon entrance, and enters it if so.
//
// Arguments:
//  x, y - the position to check
//
// Returns:
//   Nothing
//
// Notes:
//   This function is called from an input function that already checked to
//   see if the player used the stairs.
//----------------------------------------------------------------------------
void check_and_process_town_entrances(int x, int y) {
	bool enter = false;
	if (x == TownConsts::DUSTY_TUNNELS_X && y == TownConsts::DUSTY_TUNNELS_Y)
	{
		g_dungeon.maze_id = DUSTY_TUNNELS;
		enter = true;
	}
	if (x == TownConsts::MARBLE_HALLS_X && y == TownConsts::MARBLE_HALLS_Y)
	{
		g_dungeon.maze_id = MARBLE_HALLS;
		enter = true;
	}
	if (x == TownConsts::CRYSTAL_DEPTHS_X && y == TownConsts::CRYSTAL_DEPTHS_Y)
	{
		g_dungeon.maze_id = CRYSTAL_DEPTHS;
		enter = true;
	}

	// If entering a dungeon, generate a new floor and turn off any active
	// scroll of recall
	if (enter) {
		enter_dungeon(1);
	}
}

//----------------------------------------------------------------------------
// Checks the location for a NPC or sign, and if so, display their message.
//
// Arguments:
//  x, y - the location to check
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void check_and_process_npc_here(int x, int y) {
	for (int i = 0; i < TownConsts::NUM_NPC_TEXTS; ++i) {
		if (g_npc_info[i].x == x && g_npc_info[i].y == y) {
			g_text_log.put_line(g_npc_info[i].text);
			g_state_flags.update_text_dialog = true;
			g_state_flags.update_display = true;
			return;
		}
	} 
}

//----------------------------------------------------------------------------
// Processes the proposed movement of the player (and any enemies, depending
// on where the player is)
//
// Arguments:
//  proposed_location - the place the player wants to move to
//
// Returns:
//   Nothing.  This function directly moves the player (and enemies, if 
//   present)
//----------------------------------------------------------------------------
void process_move(std::pair<int, int> proposed_location) {
	if (g_state_flags.in_dungeon)
		process_dungeon_move(proposed_location);
	else
		process_town_move(proposed_location);
}

//----------------------------------------------------------------------------
// Looks to see if the current location is an 'active' square (the entrance
// to a shop or an active recall circle) and do the thing
//
// Arguments:
//  x, y - the place to check
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void check_for_active_area(int x, int y) {
	bool enter = false;
	// Return the player to the dungeon if they step on the appropriate circle with a scroll active
	if (g_player.recall_active) {
		if (x == TownConsts::DT_RECALL_X && y == TownConsts::DT_RECALL_Y && g_dungeon.maze_id == DUSTY_TUNNELS)
			enter = true;
		if (x == TownConsts::MH_RECALL_X && y == TownConsts::MH_RECALL_Y && g_dungeon.maze_id == MARBLE_HALLS)
			enter = true;
		if (x == TownConsts::CD_RECALL_X && y == TownConsts::CD_RECALL_Y && g_dungeon.maze_id == CRYSTAL_DEPTHS)
			enter = true;
		if (enter) {
			g_text_log.put_line("You re-enter the dungeon as the magic fades away...");
			enter_dungeon(g_player.recall_floor);
		}
	}
	// Check to see if the player is on the weapon shop

	// Check to see if the player is on the item shop

	// Check to see if the player is on the museum
}

//----------------------------------------------------------------------------
// Processes the proposed movement of the player and any enemies within
// range of the player while in town
//
// Arguments:
//  proposed_location - the place the player wants to move to
//
// Returns:
//   Nothing.  This function directly moves the player
//----------------------------------------------------------------------------
void process_town_move(std::pair<int, int> proposed_location) {
	// Do town movement stuff
	int x = proposed_location.first;
	int y = proposed_location.second;
	int passable = g_town_movability[y * TOWN_SIZE + x];
	if (passable == 1) {
		g_player.set_x_pos(x);
		g_player.set_y_pos(y);
		g_state_flags.update_maze_area = true;
		g_state_flags.update_text_dialog = true;
		g_state_flags.update_display = true;
	}
	else {
		// Check to see if the obstruction is a NPC.  If so,
		// get their text and put it in the log
		check_and_process_npc_here(x, y);
	}

	// Check to see if the new position corresponds to a shop,
	// dungeon entrance, or a recall point that's active,
	// and do the correct thing
	check_for_active_area(x, y);
}

//----------------------------------------------------------------------------
// Processes the proposed movement of the player and any enemies within
// range of the player while in the dungeon
//
// Arguments:
//  proposed_location - the place the player wants to move to
//
// Returns:
//   Nothing.  This function directly moves the player/enemies.
//----------------------------------------------------------------------------
void process_dungeon_move(std::pair<int, int> proposed_location) {
	// Eventually:
	//  - Put together a queue of enemy and player actions based
	//    on relative speed
	//  - Execute each action (move, attack) in turn
	//  - Store any fractions of a turn not executed in the 
	//    enemy or player structure
	//  - If the player moved, describe items on the ground
	//  - Mark things to be updated

	// Relative speed:
	//   The player's and enemy's speed is a value (100 by default for the player but
	//   can increase or decrease with gear; varied by enemy) that determines how
	//   many move(s) can be made.  A 'move' costs 100 points.
	//
	//   For each turn that an actor can act:
	//     - Take any residual value from the pool and add the SPD value to it
	//     - Execute a turn
	//     - Save the residual for the next turn
	//
	//   For example, if there is a player and an enemy, and the player has 125
	//   speed while the enemy has 110 speed:
	//     Turn 1: Player gets 125 to pool, spends 100, has 25 remainder
	//			   Enemy gets 110 to pool, spends 100, has 10 remainder
	//     Turn 2: Player gets 125 to pool + 25 remainder, spends 100, has 50 remainder
	//             Enemy gets 110 to pool + 10 remainder, spends 100, has 20 remainder
	//     Turn 3: Player gets 125 to pool + 50 remainder, spends 100, has 75 remainder
	//			   Enemy gets 110 to pool + 20 remainder, spends 100, has 30 remainder
	//     Turn 4: Player gets 125 to pool + 75 remainder, spends 100, has 100 remainder
	//             Enemy (and all other with less than 100 remainder) gets no turn
	//	   Turn 5: Player gets no additional to pool + 100 remainder, spends 100, has 0 remainder
	//             Enemy gets 110 to pool + 30 remainder, spends 100, has 40 remainder
	//	   And so on...
	// 
	//   The net result is that the player gets an additional turn every 4th turn, so compared
	//   to an enemy with a base speed of 100, the player gets 5 turns to the enemy's 4.	

	// The queue consists of a single player turn and any enemy turns that go along with it,
	// and is executed in order.  It's possible that a queue will have one player move and
	// zero enemy moves, or one player move and multiple moves from one or more enemies -
	// and the player and/or enemies can be queued anywhere in the turn depending on 
	// relative pool size (generally, if both a player and enemy have an extra turn coming,
	// the one to move first will be the one with the highest residual).

	// Queueing rules
	//  - If the player has 100 or greater residual:
	//       If any enemies do as well, queue the player and then the enemy (or enemies)
	//       with >100 residual and queue no others.  The player is added to
    //       the queue once, even if they have 200+ residual, 
	//       but enemies will be queued in turn until their excess residual is spent. 
	//       Nobody gets additional speed to their pool this turn.
	//  
	//    Example:  given a player with 120 residual, and enemies A and B with 210 and 140 residuals,
	//              the resulting queue would be A, B, player, A
	//
	//	- If the player has less than 100 residual:
	//       - If one or more enemies have >100, queue them first until they have less than 100,
	//         then the player, then all enemies by distance.  The enemies with >100 
	//         residual get no extra in their pool at the time of their turn, but get that extra
	//         after all their overage turns have completed and they run from the rest of the
	//         queue
	//       - If no enemies have >100, the player is queued first, then all enemies sorted by
	//         distance.  The player and all enemies get speed added to their pools

	// The list that holds player and enemy actions.  The first item in the pair is an enum value
	// (either PLAYER or ENEMY).  The second item in the pair is the offset into the enemy list
	// of the enemy to take the action.  For PLAYER, the second value has no meaning.
	std::vector<std::pair<int, int> > actions;
	std::vector<Enemy *> enemies;

	// get a list of enemies that are close enough to be processed
	// For enemies that haven't seen the player, it's MAXIMUM_ENEMY_AI_DISTANCE
	// For enemies that have seen the player, it's 2 x MAXIMUM_ENEMY_AI_DISTANCE
    std::list<Enemy *>::iterator enemy_it = g_dungeon.enemies.begin();
	bool done = false;
	while (enemy_it != g_dungeon.enemies.end() && !done) {
		int distance = (*enemy_it)->get_distance();
		if (((*enemy_it)->has_seen_the_player() && distance <= UtilConsts::MAXIMUM_ENEMY_AI_DISTANCE_FAR) ||
		    (!(*enemy_it)->has_seen_the_player() && distance  <= UtilConsts::MAXIMUM_ENEMY_AI_DISTANCE_NEAR)) {
            enemies.push_back(*enemy_it);
		}
		else {
			// Every other enemy is too far away; we're done
			done = true;
		}
		++enemy_it;
	}	

	//std::cout << "process_move: " << enemies.size() << " enemies are being processed" << std::endl;

	// Assemble the queue
	// If the player is due an extra turn...
	if (g_player.get_action_residual() >= 100) {
		//std::cout << "process_move:  player has action residual of " << g_player.get_action_residual() << std::endl;
		// Queue player move
	 	actions.push_back(std::make_pair(UtilConsts::ACTION_PLAYER_DEFER_SPEED, 0));
		//std::cout << "  process_move:  queued player action (deferred speed)" << std::endl;
		// Check to see if any of the enemies also have over 100 residual.
		// If so, queue their moves until they'll have less than 100 residual
		for (int i=0; i < enemies.size(); ++i) {
			int e_res = enemies[i]->get_action_residual();
			if (e_res >= 100) {
				//std::cout << "  process_move: enemy has an action residual of " << e_res << std::endl;
				while (e_res >= 100) {
					actions.push_back(std::make_pair(UtilConsts::ACTION_ENEMY_DEFER_SPEED, i));
					//std::cout << "    process_move: queued enemy action (deferred speed)" << std::endl;
					e_res -= 100;
				}
			}
		}
	}
	else {
		// Check to see if any of the enemies have over 100 residual.
		// If so, queue their moves until they have less than 100 residual
		//std::cout << "process_move: player has action residual of < 100" << std::endl;
		for (int i=0; i < enemies.size(); ++i) {
			int e_res = enemies[i]->get_action_residual();
			if (e_res >= 100) {
				//std::cout << "  process_move: enemy has an action residual of " << e_res << std::endl;
				while (e_res >= 100) {
					//std::cout << "    process_move: queued enemy action (deferred speed)" << std::endl;
					actions.push_back(std::make_pair(UtilConsts::ACTION_ENEMY_DEFER_SPEED, i));
					e_res -= 100;
				}
			}
		}

		// Queue the player move
	 	actions.push_back(std::make_pair(UtilConsts::ACTION_PLAYER, 0));
		//std::cout << "  process_move: queued player action" << std::endl;

		// Now append all enemy moves in non-deferred state
		for (int i = 0; i < enemies.size(); ++i) {
			actions.push_back(std::make_pair(UtilConsts::ACTION_ENEMY, i));
			//std::cout << "  process_move: queued action for enemy " << i << std::endl;
		}
	}

	// Execute the queue
	// For each entry in the queue
	//  - If non-deferred, add the total SPD to the entity's residual
	//  - If deferred, or non-deferred and residual >= 100
	//     - If player, perform the player movement action
	//       (or combat action - TBD)
	//     - If enemy, perform the enemy movement action
	//       (or combat action - TBD)
	for (int i = 0; i < actions.size(); ++i) {
		//std::cout << "process_move: performing action " << (i+1) << "..." << std::endl;
		int act = actions[i].first;
		int target = actions[i].second;
		// If non-deferred, add speed
		if (act == UtilConsts::ACTION_PLAYER) {
			g_player.set_action_residual(g_player.get_action_residual() + (int)g_player.actual.spd);
			//std::cout << "  process_move: adding non-deferred speed to player action pool" << std::endl;
			//std::cout << "    process_move: player action pool is now " << g_player.get_action_residual() << std::endl;
		}
		if (act == UtilConsts::ACTION_ENEMY) {
			enemies[target]->set_action_residual(enemies[target]->get_action_residual() + enemies[target]->get_spd());
			//std::cout << "  process_move: adding non-deferred speed to enemy " << target << std::endl;
			//std::cout << "    process:_move: enemy action pool is now " << enemies[target]->get_action_residual() << std::endl;
		}
		// If a player action, do the player thing
		if (act == UtilConsts::ACTION_PLAYER || act == UtilConsts::ACTION_PLAYER_DEFER_SPEED) {
			if (g_player.get_action_residual() >= 100) {
				//std::cout << "  process_move: attempting to perform player action" << std::endl;
				int x = proposed_location.first;
				int y = proposed_location.second;

				if (g_player.get_x_pos() == x && g_player.get_y_pos() == y) {
					//std::cout << "Player is sitting still" << std::endl;
				}
				else if (is_enemy_here(g_dungeon.enemies, x, y)) {
					Enemy *to_attack = get_enemy_at(g_dungeon.enemies, x, y);
					// Do attack stuff
					g_text_log.put_line("You attack the " + to_attack->get_name() + "!");
					perform_player_combat(to_attack);
					if (to_attack->get_hp() <= 0) {
						to_attack->mark_alive_status(false);
						g_text_log.put_line("You defeated the " + to_attack->get_name() + "!");
						int exp = to_attack->get_exp();
						// Subtract 10% experience per elevel lower than the player level, to a minimum of 10%
						if (g_player.level > to_attack->get_elevel()) {
							float adj = 1.0 - ((g_player.level - to_attack->get_elevel()) * 0.1);
							if (adj < 0.1)
								adj = 0.1;
							exp = (int)(ceil((float)exp * adj));
						}
						else if (g_player.level < to_attack->get_elevel()) {
							float adj = 1.0 + ((to_attack->get_elevel() - g_player.level) * 0.1);
							exp = (int)(ceil((float)exp * adj));
						}
						g_player.apply_experience(exp);
						// TODO:
						//  - Drop items
					}
				}
    			else if (g_dungeon.maze->is_carved(x, y)) {
					// Move the player
					g_player.set_x_pos(x);
					g_player.set_y_pos(y);

    				// Identify known (but not yet identified) potions and scrolls on the ground
    				// to ensure any stragglers on the current floor are dealt with
    				identify_previously_known_items_at_player();

					// Show the items on the ground in the player log
					add_items_at_player_to_log();
				}
				// Subtract the action points from the player
				g_player.set_action_residual(g_player.get_action_residual() - 100);
				//std::cout << "    process_move: player residual is now " << g_player.get_action_residual() << std::endl;
			}

		}
		// If an enemy action, do the enemy thing for the current enemy
		if (act == UtilConsts::ACTION_ENEMY || act == UtilConsts::ACTION_ENEMY_DEFER_SPEED) {
			Enemy *e = enemies[target];
			// The enemy only gets to go if it hasn't been killed yet
			if (e->is_it_alive() == true) {
				if (e->get_action_residual() >= 100) {
					//std::cout << "  process_move: attempting to perform enemy action" << std::endl;
					perform_enemy_action(e);
					e->set_action_residual(e->get_action_residual() - 100);
					//std::cout << "    process_move: enemy residual is now " << e->get_action_residual() << std::endl;
				}
			}
		}

	}

	// For any enemies marked as dead this turn, delete them.
	delete_dead_enemies(g_dungeon.enemies);

	// Recalculate enemy distances
	get_enemy_distances(g_dungeon.enemies, g_player.get_x_pos(), g_player.get_y_pos());

	// Process enemy vision
	process_enemy_vision(g_dungeon.enemies);

	// Update whether enemies remember the player or not
	process_enemy_forgetting_player(g_dungeon.enemies);

	// If the player has a scroll of recall active, subtract the count and if the count
	// becomes zero, send the player to town
	if (g_player.recall_active && g_state_flags.in_dungeon) {
		--g_player.recall_count;
		if (g_player.recall_count <= 0) {
			g_text_log.put_line("The magical energy whisks you away!");
			exit_dungeon(true);
		}
	}
    // Redraw the maze area
	g_state_flags.update_maze_area = true;
	g_state_flags.update_text_dialog = true;

	// Redraw the player health
	g_state_flags.update_status_hp_exp = true;

    // Tell the game to do the redraw
	g_state_flags.update_display = true;
} 