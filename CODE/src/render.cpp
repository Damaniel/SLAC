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
// Render::Render
//
// Constructor.
//------------------------------------------------------------------------------
Render::Render() {

}

//------------------------------------------------------------------------------
// Renders all non-static dungeon elements.  This includes the player and all
// enemies.  
//
// Arguments:
//   destination - the bitmap to render to
//   maze_x, maze_y - the position to draw from
//  
// Returns:
//   Nothing
//
// Notes:
//   maze_x and maze_y represent the maze tile position in the upper left 
//   cornerof the play area
//------------------------------------------------------------------------------
void Render::render_actors(BITMAP *destination, int maze_x, int maze_y) {
	BITMAP *bpc = (BITMAP *)g_game_data[DAMRL_PLAYER_SPRITES].dat;

	// For now, just draw the player.  He's always centered in the play area.
	masked_blit(bpc, destination, PLAYER_TILE_OFFSET * TILE_PIXEL_WIDTH, 0, 
	            PLAYER_PLAY_AREA_X * TILE_PIXEL_WIDTH, PLAYER_PLAY_AREA_Y * TILE_PIXEL_HEIGHT,
		        TILE_PIXEL_WIDTH, TILE_PIXEL_HEIGHT);
}

//------------------------------------------------------------------------------
// Draws the specified base tile (that is, wall, floor, or darkness) at the 
// specified position relative to the top of the play area
//
// Arguments:
//   destination - the bitmap to render to
//   tile_id - the index of the ground tile to draw
//   x, y - the position to draw the tile
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_base_tile(BITMAP *destination, int tile_id, int x, int y) {
	blit((BITMAP *)g_game_data[DAMRL_MAZE_BASE_TILES_1].dat, 
	     destination,
	     tile_id * TILE_PIXEL_WIDTH, 
		 0, 
		 x * TILE_PIXEL_WIDTH,
		 y * TILE_PIXEL_HEIGHT,
		 TILE_PIXEL_WIDTH,
		 TILE_PIXEL_HEIGHT);	
}

//------------------------------------------------------------------------------
// Draws the specified item tile (specified by the Item value in 'gid') at the 
// tile location (x,y) relative to the top of the play area
//
// Arguments:
//   destination - the bitmap to render to
//   gid - the tile id of the item
//   x, y - the position to draw the tile
//------------------------------------------------------------------------------
void Render::render_item(BITMAP *destination, int gid, int x, int y) {
	int tilex = gid % ITEM_TILE_ENTRY_WIDTH;
	int tiley = gid / ITEM_TILE_ENTRY_WIDTH;

	masked_blit((BITMAP *)g_game_data[DAMRL_ITEMS].dat, 
	     destination,
	     tilex * TILE_PIXEL_WIDTH, 
		 tiley * TILE_PIXEL_HEIGHT, 
		 x * TILE_PIXEL_WIDTH,
		 y * TILE_PIXEL_HEIGHT,
		 TILE_PIXEL_WIDTH,
		 TILE_PIXEL_HEIGHT);	
}

//------------------------------------------------------------------------------
// Clears the entire backround of the map area to the 'fog of war' color.
//
// Arguments:
//   None
//
// Returns:
//   
//------------------------------------------------------------------------------
void Render::initialize_map_bitmap(Maze *m) {
	for (int y=0; y <= MAP_NUM_Y_DOTS; y++) {
		for (int x=0; x <= MAP_NUM_X_DOTS; x++) {
			blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
			screen,
			MAP_DOT_FOG_OF_WAR * MAP_DOT_WIDTH,
			0,
			MAP_AREA_VMEM_X + (x * MAP_DOT_WIDTH),
			MAP_AREA_VMEM_Y + (y * MAP_DOT_HEIGHT),
			MAP_DOT_WIDTH,
			MAP_DOT_HEIGHT);			
		}
	}	

	// Calculate the center point for the maze on the map (so everything is
	// nice and centered)
	// The center location is map_x + (((the whole map width) - (2 * maze_width)) / 2)
    map_maze_xoffset = MAP_AREA_VMEM_X + ((MAP_PIXEL_WIDTH - m->get_width() * MAP_DOT_WIDTH) / 2);
	map_maze_yoffset = MAP_AREA_VMEM_Y + ((MAP_PIXEL_HEIGHT - m->get_height() * MAP_DOT_HEIGHT) / 2);
}

//------------------------------------------------------------------------------
// Adds small squares to the map bitmap corresponding to the area in the 
// immediate vicinity of the location specified by (x, y)
//
// Arguments:
//   m - the maze to use to determine what squares to draw
//   x, y - the 'center' of the portion of the maze to render on the map
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::add_area_to_map_bitmap(Maze *m, int x, int y) {
	for(int i=x-1; i<=x+1; i++) {
		for(int j=y-1; j<=y+1; j++) {
			//std::cout << "add_area_to_map_bitmap: processing (" << i << ", " << j << ")" << std::endl;
			if(i >=0 && i < m->get_width() && j >=0 && j < m->get_height()) {
				if (m->is_carved(i, j) == false) {
					//std::cout << "  add_area_to_map_bitmap: not carved" << std::endl;
					blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
				     	screen,
					 	MAP_DOT_WALL * MAP_DOT_WIDTH,
					 	0,
					 	map_maze_xoffset + (i * MAP_DOT_WIDTH),
					 	map_maze_yoffset + (j * MAP_DOT_HEIGHT),
					 	MAP_DOT_WIDTH,
					 	MAP_DOT_HEIGHT);
				} else {
					//std::cout << "  add_area_to_map_bitmap: carved" << std::endl;
					blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
				     	screen,
					 	MAP_DOT_FLOOR * MAP_DOT_WIDTH,
					 	0,
					 	map_maze_xoffset + (i * MAP_DOT_WIDTH),
					 	map_maze_yoffset + (j * MAP_DOT_HEIGHT),
					 	MAP_DOT_WIDTH,
					 	MAP_DOT_HEIGHT);			
				}
			}
		}
	}

	// If the player is in a room and hasn't been in the room before, 
	// draw the room to the map area
	int room = m->get_room_id_at(x, y);
	//std::cout << "add_area_to_map_bitmap: room id = " << room << std::endl; 
	if(room != -1) {
		Room r = m->get_room(room);
		//std::cout << "  add_area_to_map_bitmap: Got room" << std::endl;
		if (r.has_been_entered == false) {
			for(int i = r.x - 1; i < r.x + r.w + 1; i++) {
				for (int j = r.y - 1; j < r.y + r.h + 1; j++) {
					//std::cout << "  add_area_to_map_bitmap: Processing room at (" << i << ", " << j << ")" << std::endl;
					if(m->is_carved(i, j) == false) {
						blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
					     	screen,
					 		MAP_DOT_WALL * MAP_DOT_WIDTH,
					 		0,
					 		map_maze_xoffset + (i * MAP_DOT_WIDTH),
					 		map_maze_yoffset + (j * MAP_DOT_HEIGHT),
					 		MAP_DOT_WIDTH,
					 		MAP_DOT_HEIGHT);
					} else {
						blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
					     	screen,
					 		MAP_DOT_FLOOR * MAP_DOT_WIDTH,
					 		0,
					 		map_maze_xoffset + (i * MAP_DOT_WIDTH),
					 		map_maze_yoffset + (j * MAP_DOT_HEIGHT),
					 		MAP_DOT_WIDTH,
					 		MAP_DOT_HEIGHT);
					}
				}	
			}
		}	
	} else {
		//std::cout << "  add_area_to_map_bitmap: not in a room" << std::endl;
	}
	//std::cout << "add_area_to_map_bitmap: finished" << std::endl;
}

//------------------------------------------------------------------------------
// Takes any bitmap data that we plan to stuff in unused video RAM and loads it
// into a free spot
//
// Arguments:
//   None
// 
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::copy_data_to_offscreen_vram(void) {
	//   The only bitmap data being put into video memory right now is the map dialog.
	//   The map will be constructed as the player explores, and by doing this as 
	//   exploration occurs, there's no need to generate it at the time the map is
	//   displayed (which would be a very slow operation).
	BITMAP *b = (BITMAP *)g_game_data[DAMRL_MAIN_MAP].dat;	
	blit(b, screen, 0, 0, MAP_VMEM_X, MAP_VMEM_Y, MAP_VMEM_WIDTH, MAP_VMEM_HEIGHT);
}

//------------------------------------------------------------------------------
// Writes a string to the screen in the specified location using the specified 
// color (0-4) using a fixed width font.
//
// Arguments:
//   destination - the bitmap to draw to
//   text - the text to render
//   x_pos, y_pos - the location to render the text
//   font_idx - the 'color (0-4) to use for the text
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_fixed_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;
	
	// This isn't a library, so we'll assume strings are terminated.  That should end well...
	while(*cur != 0) {
		offset = (*cur++) - 32;
		masked_blit((BITMAP *)g_game_data[DAMRL_FIXED_FONT].dat, destination, offset * fixed_font_width, 
		     font_idx * fixed_font_height, x, y, fixed_font_width, fixed_font_height);
		x += 8;
	}
}

//------------------------------------------------------------------------------
// Displays the map dialog in the play area.
//
// Arguments:
//   destination - the bitmap to draw the map dialog to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_map(BITMAP *destination) {

	// Blit the base map
	blit(screen, destination, MAP_VMEM_X, MAP_VMEM_Y, MAP_X_POS, MAP_Y_POS, 
	     MAP_VMEM_WIDTH, MAP_VMEM_HEIGHT);

	// Draw the player's position on the map
	blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat, 
	     destination, 
         MAP_DOT_PLAYER*MAP_DOT_WIDTH,
		 0, 
		 MAP_X_POS + map_maze_xoffset - MAP_VMEM_X + (g_player.get_x_pos()*MAP_DOT_WIDTH),
		 MAP_Y_POS + map_maze_yoffset - MAP_VMEM_Y + (g_player.get_y_pos()*MAP_DOT_HEIGHT), 
		 MAP_DOT_WIDTH, MAP_DOT_HEIGHT);

	// TODO - Draw actual relevant text.  Needs game state to do this.
	render_fixed_text(destination, "Cave 1", 55, 30, FONT_YELLOW);
	render_fixed_text(destination, "Floor 3", 130, 30, FONT_YELLOW);
	render_fixed_text(destination, "X:25", 74, 171, FONT_YELLOW);
	render_fixed_text(destination, "Y:18", 137, 171, FONT_YELLOW);
}

//------------------------------------------------------------------------------
// Draws inventory content (the items, descriptions, etc) on the inventory 
// screen
//
// Arguments:
//   destination - the place to draw the inventory
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_inventory_content(BITMAP *destination) {
	// Draw the items
	for (int i = 0; i < INVENTORY_SIZE; ++i) {
		int x = i % INVENTORY_ITEMS_PER_ROW;
		int y = i / INVENTORY_ITEMS_PER_ROW;
		Item *it = g_inventory->get_item_in_slot(i);
		if (it != NULL) {
			int gid = it->get_gid();
			int tilex = gid % ITEM_TILE_ENTRY_WIDTH;
			int tiley = gid / ITEM_TILE_ENTRY_WIDTH;

			masked_blit((BITMAP *)g_game_data[DAMRL_ITEMS].dat, 
	     			    destination,
	     				tilex * TILE_PIXEL_WIDTH, 
		 				tiley * TILE_PIXEL_HEIGHT, 
		 				(x * (TILE_PIXEL_WIDTH + 1)) + INVENTORY_DIALOG_X + INVENTORY_ITEMS_X,
		 				(y * (TILE_PIXEL_HEIGHT + 1)) + INVENTORY_DIALOG_Y + INVENTORY_ITEMS_Y,
		 				TILE_PIXEL_WIDTH,
		 				TILE_PIXEL_HEIGHT);	
		}
	}

	// Draw the active item cursor (if any)

	// Draw the active item description
	Item *it = g_inventory->get_item_in_slot(0);
	if (it != NULL) {
		render_prop_narrow_text(destination, (char *)it->get_full_name().c_str(), 15, 135, 0);
	}
}

//------------------------------------------------------------------------------
// Draws the inventory screen
//
// Arguments:
//   destination - the place to draw the inventory
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_inventory(BITMAP *destination) {
	// Draw the background
	blit((BITMAP *)g_game_data[DAMRL_INVENTORY].dat,
	     destination, 0, 0, INVENTORY_DIALOG_X, INVENTORY_DIALOG_Y, 
		 INVENTORY_DIALOG_WIDTH, INVENTORY_DIALOG_HEIGHT);

	render_inventory_content(destination);
}

//------------------------------------------------------------------------------
// Writes a string to the screen in the specified location using the specified 
// color (0-4) using a proportional font.
//
// Arguments:
//   destination - the bitmap to write the text to
//   text - the text to write
//   x_pos, y_pos - the location to place the text
//   font_idx - the 'color' (0-4) to draw the text with
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_prop_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;

	while (*cur != 0) {
		offset = (*cur++) - 32;
		masked_blit((BITMAP *)g_game_data[DAMRL_PROP_FONT].dat, destination, (int)prop_font_offset[offset],
		     font_idx * prop_font_height, x, y, (int)prop_font_width[offset], prop_font_height);
		x += (int)prop_font_width[offset] + 1;
	}
}

//------------------------------------------------------------------------------
// Draws a line of text in the narrow proportional font to the screen
//
// Arguments:
//   destination - the place to render the text to
//   text - the text to write
//   x_pos, y_pos - the upper left corner of the location to place the text
//   font_idx     - which color offet (0-4) to use 
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_prop_narrow_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;

	while (*cur != 0) {
		offset = (*cur++) - 32;
		masked_blit((BITMAP *)g_game_data[DAMRL_PROP_FONT_NARROW].dat, destination, (int)prop_narrow_font_offset[offset],
		     font_idx * prop_narrow_font_height, x, y, (int)prop_narrow_font_width[offset], prop_narrow_font_height);
		x += (int)prop_narrow_font_width[offset] + 1;
	}
}

//------------------------------------------------------------------------------
// Draws the status background graphic to the screen.
//
// Arguments:
//   destination - the bitmap to write to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_status_base(BITMAP *destination) {
	BITMAP *b = (BITMAP *)g_game_data[DAMRL_MAIN_STATUS].dat;
	blit(b, destination, 0, 0, STATUS_AREA_X, STATUS_AREA_Y, b->w, b->h);
}

//------------------------------------------------------------------------------
// Draws the text area graphic to the screen.
//
// Arguments:
//	 destination - the bitmap to write to
//   extended - if true, draws the 7 line version of the dialog
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_text_base(BITMAP *destination, bool extended) {
	BITMAP *bstd = (BITMAP *)g_game_data[DAMRL_MAIN_TEXT].dat;
	BITMAP *bext = (BITMAP *)g_game_data[DAMRL_MAIN_TEXT_EXT].dat;
	
	if(extended == true) {
		blit(bext, destination, 0, 0, TEXT_AREA_EXT_X, TEXT_AREA_EXT_Y, bext->w, bext->h);
	}
	else {
		blit(bstd, destination, 0, 0, TEXT_AREA_STD_X, TEXT_AREA_STD_Y, bstd->w, bstd->h);		
	}
}

//------------------------------------------------------------------------------
// Renders the contents of the text log to the log area.
//
// Arguments:
//	 destination - the bitmap to write to
//   extended - if true, use the 7 line version of the dialog
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_text_log(BITMAP *destination, bool extended) {
	int size, x_off, y_off, lines_to_draw, log_start;

	// Notes:
	// - For both regular and extended, the first line offset is based on the position of the window
	// - Number of lines to draw
	//     - If extended, the number of lines in the log
	//     - If regular, the number of lines in the log or the size of the window, whichever is smaller
	// - Log offset
	//     - If extended, 0
	//     - If regular:
	//          If number of lines <= size of the window, then 0
	//          If the number of lines > size of the window, then (length of log - size of window)   

	lines_to_draw = g_text_log.get_num_lines();

	if (extended) {
		size = TEXT_AREA_EXT_NUM_LINES;
		x_off = TEXT_AREA_EXT_X + 4;
		y_off = TEXT_AREA_EXT_Y + prop_font_height;
		log_start = 0;
 	} 
	else {
		size = TEXT_AREA_NORMAL_NUM_LINES;
		x_off = TEXT_AREA_STD_X + 4;
		y_off = TEXT_AREA_STD_Y + prop_font_height;
		if (lines_to_draw > size) {
			log_start = lines_to_draw - size;
		} 
		else {
			log_start = 0;
		}
	}

	for(int idx = log_start; idx < lines_to_draw; ++idx) {
		render_prop_narrow_text(destination, (char *)g_text_log.get_line(idx).c_str(), x_off, y_off + ((prop_font_height + 1) * (idx-log_start)), 0);
	}
}

//------------------------------------------------------------------------------
// Render the world with the tile at screen position (0, 0) position equal to 
// (maze_x, maze_y).  
//
// Arguments:
//  destination - the bitmap to draw to
//  m - the maze to draw
//  maze_x, maze_y - the maze position corresponding to the upper left corner
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_world_at(BITMAP *destination, Maze *m, int maze_x, int maze_y) {
	// Notes:
	//   Negative values for maze_x and maze_y are allowed, as are values outside of the 
	//   positive end of the range - maze tiles just won't be drawn for invalid locations	
	//   Also note that the code that draws the floor (that is, where is_carved == true),
	//   checks tiles to the left and above it when deciding what to draw.  There isn't 
	//   any check done to see if those tiles are valid, but the default Maze class will 
	//   always have a valid tile to the left and above any carved tile, so this shouldn't
	//   cause a problem.  If weird crashes happen, try looking here.
	for (int screen_x = 0; screen_x < PLAY_AREA_TILE_WIDTH; screen_x++) {
		for (int screen_y = 0; screen_y < PLAY_AREA_TILE_HEIGHT; screen_y++) {
			int tile_to_render_x = maze_x + screen_x;
			int tile_to_render_y = maze_y + screen_y;
			int tile_to_use;
			bool carved_left = m->is_carved(tile_to_render_x -1, tile_to_render_y);
			bool carved_up = m->is_carved(tile_to_render_x, tile_to_render_y - 1);
			
			if(tile_to_render_x >=0 && tile_to_render_y >=0 && tile_to_render_x < m->get_width() && tile_to_render_y < m->get_height()) {
				int stairs = m->stairs_here(tile_to_render_x, tile_to_render_y);				
				// Before checking any other status, draw darkness if the square isn't lit
				if (m->is_square_lit(tile_to_render_x, tile_to_render_y) == false) { 
					// If the square has previously been seen and isn't carved, draw a darker wall
					if (m->is_carved(tile_to_render_x, tile_to_render_y) == false && m->was_seen(tile_to_render_x, tile_to_render_y) == true) {
						render_base_tile(destination, TILE_DARKER_WALL, screen_x, screen_y);
					} else {
						// Otherwise, draw darkness
						render_base_tile(destination, TILE_DARK, screen_x, screen_y);
					}
				}
				// Render stairs if present
				else if (stairs == STAIRS_UP) {
					render_base_tile(destination, TILE_UP_STAIRS, screen_x, screen_y);
				}
				else if (stairs == STAIRS_DOWN) {
					render_base_tile(destination, TILE_DOWN_STAIRS, screen_x, screen_y);
				}
				// Render floor if present.  There are 4 different floor tiles - one with no
				// highlighting and 3 with different types of highlighting
				// If the location is a wall, render that instead.
				else if (m->is_carved(tile_to_render_x, tile_to_render_y) == true) {
					if (carved_left == false && carved_up == true) {
						tile_to_use = TILE_FLOOR_LEFT_HIGHLIGHT;
					}
					else if (carved_left == true && carved_up == false) {
						tile_to_use = TILE_FLOOR_TOP_HIGHLIGHT;
					}
					else if (carved_left == false && carved_up == false) {
						tile_to_use = TILE_FLOOR_BOTH_HIGHLIGHT;
					}
					else {
						tile_to_use = TILE_FLOOR;
					}
					render_base_tile(destination, tile_to_use, screen_x, screen_y);
					// Get any items at the location and draw the first on the list
					int num_items_here = m->get_num_items_at(tile_to_render_x, tile_to_render_y);
					if (num_items_here > 0) {
						std::list<Item *> items = m->get_items_at(tile_to_render_x, tile_to_render_y);
						Item *it = items.front();
						render_item(destination, it->get_gid(), screen_x, screen_y);
					}
				} else {
					render_base_tile(destination, TILE_WALL, screen_x, screen_y);
				}		
			} else {
				// Draw an empty space since it's outside of the map
				render_base_tile(destination, TILE_DARK, screen_x, screen_y);
			}						 
		}
	}
	
	// Render the player and any enemies
	render_actors(destination, maze_x, maze_y);
}

//----------------------------------------------------------------------------------
// Equivalent to render_world_at, but renders using the player's location at the
// center of the play area (rather than (0, 0)) as the top left of the play area.
//
// Arguments:
//   destination - the bitmap to draw to
//   m - the maze to render
//   maze_x, maze_y - the position of the maze at the player's current location
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_world_at_player(BITMAP *destination, Maze *m, int maze_x, int maze_y) {
	// Render the world with the tile at the player's position (7,6) equal to (maze_x, maze_y)
	render_world_at(destination, m, maze_x - PLAYER_PLAY_AREA_X, maze_y - PLAYER_PLAY_AREA_Y);
}

// Non-class update functions.  They might go into the class eventually
void update_main_game_display(void) {
	if (g_state_flags.cur_substate == GAME_SUBSTATE_MAP) {
		g_render.render_map(g_back_buffer);
	}
	else if (g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY) {
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