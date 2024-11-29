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

UiGlobals g_ui_globals;

//------------------------------------------------------------------------------
// Render::Render
//
// Constructor.
//------------------------------------------------------------------------------
Render::Render() {
	// Set the inventory cursor to the first position of the inventory.
	g_ui_globals.inv_cursor_x = 0;
	g_ui_globals.inv_cursor_y = 0;

	g_ui_globals.prev_inv_cursor_x = 0;
	g_ui_globals.prev_inv_cursor_y = 0;

	g_ui_globals.inv_menu_active = false;
	g_ui_globals.sel_item_option = 0;
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
	masked_blit(bpc, destination, UiConsts::PLAYER_TILE_OFFSET * UiConsts::TILE_PIXEL_WIDTH, 0, 
	            UiConsts::PLAYER_PLAY_AREA_X * UiConsts::TILE_PIXEL_WIDTH, 
				UiConsts::PLAYER_PLAY_AREA_Y * UiConsts::TILE_PIXEL_HEIGHT,
		        UiConsts::TILE_PIXEL_WIDTH, UiConsts::TILE_PIXEL_HEIGHT);
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
	     tile_id * UiConsts::TILE_PIXEL_WIDTH, 
		 0, 
		 x * UiConsts::TILE_PIXEL_WIDTH,
		 y * UiConsts::TILE_PIXEL_HEIGHT,
		 UiConsts::TILE_PIXEL_WIDTH,
		 UiConsts::TILE_PIXEL_HEIGHT);	
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
	int tilex = gid % UiConsts::ITEM_TILE_ENTRY_WIDTH;
	int tiley = gid / UiConsts::ITEM_TILE_ENTRY_WIDTH;

	masked_blit((BITMAP *)g_game_data[DAMRL_ITEMS].dat, 
	     destination,
	     tilex * UiConsts::TILE_PIXEL_WIDTH, 
		 tiley * UiConsts::TILE_PIXEL_HEIGHT, 
		 x * UiConsts::TILE_PIXEL_WIDTH,
		 y * UiConsts::TILE_PIXEL_HEIGHT,
		 UiConsts::TILE_PIXEL_WIDTH,
		 UiConsts::TILE_PIXEL_HEIGHT);	
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
	for (int y=0; y <= UiConsts::MAP_NUM_Y_DOTS; y++) {
		for (int x=0; x <= UiConsts::MAP_NUM_X_DOTS; x++) {
			blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
			screen,
			UiConsts::MAP_DOT_FOG_OF_WAR * UiConsts::MAP_DOT_WIDTH,
			0,
			UiConsts::MAP_AREA_VMEM_X + (x * UiConsts::MAP_DOT_WIDTH),
			UiConsts::MAP_AREA_VMEM_Y + (y * UiConsts::MAP_DOT_HEIGHT),
			UiConsts::MAP_DOT_WIDTH,
			UiConsts::MAP_DOT_HEIGHT);			
		}
	}	

	// Calculate the center point for the maze on the map (so everything is
	// nice and centered)
	// The center location is map_x + (((the whole map width) - (2 * maze_width)) / 2)
    g_ui_globals.map_maze_xoffset = UiConsts::MAP_AREA_VMEM_X + ((UiConsts::MAP_PIXEL_WIDTH - m->get_width() * UiConsts::MAP_DOT_WIDTH) / 2);
	g_ui_globals.map_maze_yoffset = UiConsts::MAP_AREA_VMEM_Y + ((UiConsts::MAP_PIXEL_HEIGHT - m->get_height() * UiConsts::MAP_DOT_HEIGHT) / 2);
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
					 	UiConsts::MAP_DOT_WALL * UiConsts::MAP_DOT_WIDTH,
					 	0,
					 	g_ui_globals.map_maze_xoffset + (i * UiConsts::MAP_DOT_WIDTH),
					 	g_ui_globals.map_maze_yoffset + (j * UiConsts::MAP_DOT_HEIGHT),
					 	UiConsts::MAP_DOT_WIDTH,
					 	UiConsts::MAP_DOT_HEIGHT);
				} else {
					//std::cout << "  add_area_to_map_bitmap: carved" << std::endl;
					blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
				     	screen,
					 	UiConsts::MAP_DOT_FLOOR * UiConsts::MAP_DOT_WIDTH,
					 	0,
					 	g_ui_globals.map_maze_xoffset + (i * UiConsts::MAP_DOT_WIDTH),
					 	g_ui_globals.map_maze_yoffset + (j * UiConsts::MAP_DOT_HEIGHT),
					 	UiConsts::MAP_DOT_WIDTH,
					 	UiConsts::MAP_DOT_HEIGHT);			
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
					 		UiConsts::MAP_DOT_WALL * UiConsts::MAP_DOT_WIDTH,
					 		0,
					 		g_ui_globals.map_maze_xoffset + (i * UiConsts::MAP_DOT_WIDTH),
					 		g_ui_globals.map_maze_yoffset + (j * UiConsts::MAP_DOT_HEIGHT),
					 		UiConsts::MAP_DOT_WIDTH,
					 		UiConsts::MAP_DOT_HEIGHT);
					} else {
						blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
					     	screen,
					 		UiConsts::MAP_DOT_FLOOR * UiConsts::MAP_DOT_WIDTH,
					 		0,
					 		g_ui_globals.map_maze_xoffset + (i * UiConsts::MAP_DOT_WIDTH),
					 		g_ui_globals.map_maze_yoffset + (j * UiConsts::MAP_DOT_HEIGHT),
					 		UiConsts::MAP_DOT_WIDTH,
					 		UiConsts::MAP_DOT_HEIGHT);
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
	render_ui_box(screen, UiConsts::MAP_VMEM_X + 1, UiConsts::MAP_VMEM_Y + 1, 
				  UiConsts::MAP_VMEM_X + UiConsts::MAP_VMEM_WIDTH - 2,
				  UiConsts::MAP_VMEM_Y + UiConsts::MAP_VMEM_HEIGHT - 2);
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
		masked_blit((BITMAP *)g_game_data[DAMRL_FIXED_FONT].dat, destination, offset * FontConsts::fixed_font_width, 
		     font_idx * FontConsts::fixed_font_height, x, y, FontConsts::fixed_font_width, FontConsts::fixed_font_height);
		x += 8;
	}
}

//------------------------------------------------------------------------------
// Draws a line of text in the a proportional font to the screen
//
// Arguments:
//   destination - the place to render the text to
//   text - the text to write
//   x_pos, y_pos - the upper left corner of the location to place the text
//   font_idx     - which color offet (0-4) to use 
//   style - standard or narrow
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_prop_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx, int style) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;

	while (*cur != 0) {
		offset = (*cur++) - 32;
		if (style == FontConsts::FONT_NARROW_PROPORTIONAL) {
			masked_blit((BITMAP *)g_game_data[DAMRL_PROP_FONT_NARROW].dat, destination, 
			            (int)FontConsts::prop_narrow_font_offset[offset], font_idx * FontConsts::prop_narrow_font_height, 
						x, y, (int)FontConsts::prop_narrow_font_width[offset], FontConsts::prop_narrow_font_height);
			x += (int)FontConsts::prop_narrow_font_width[offset] + 1;
		}
		else {
			masked_blit((BITMAP *)g_game_data[DAMRL_PROP_FONT].dat, destination, (int)FontConsts::prop_font_offset[offset],
		    	 font_idx * FontConsts::prop_font_height, x, y, (int)FontConsts::prop_font_width[offset], FontConsts::prop_font_height);
			x += (int)FontConsts::prop_font_width[offset] + 1;			
		}
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

	std::string dungeon;
	char text[32];

	// Blit the base map
	blit(screen, destination, UiConsts::MAP_VMEM_X, UiConsts::MAP_VMEM_Y, 
	     UiConsts::MAP_X_POS, UiConsts::MAP_Y_POS, UiConsts::MAP_VMEM_WIDTH, UiConsts::MAP_VMEM_HEIGHT);

	// Draw the player's position on the map
	blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat, 
	     destination, 
         UiConsts::MAP_DOT_PLAYER * UiConsts::MAP_DOT_WIDTH,
		 0, 
		 UiConsts::MAP_X_POS + g_ui_globals.map_maze_xoffset - UiConsts::MAP_VMEM_X + (g_player.get_x_pos() * UiConsts::MAP_DOT_WIDTH),
		 UiConsts::MAP_Y_POS + g_ui_globals.map_maze_yoffset - UiConsts::MAP_VMEM_Y + (g_player.get_y_pos() * UiConsts::MAP_DOT_HEIGHT), 
		 UiConsts::MAP_DOT_WIDTH, UiConsts::MAP_DOT_HEIGHT);

	// Draw the dungeon name
	dungeon = get_dungeon_name(g_dungeon.maze_id, false);
	sprintf(text, "%s, Floor %d", (char *)dungeon.c_str(), g_dungeon.depth);
	render_text(destination, text, UiConsts::MAP_AREA_DUNGEON_X, UiConsts::MAP_AREA_DUNGEON_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_CENTERED);

	// Draw the player's position
	sprintf(text, "Position: (%d, %d)", g_player.get_x_pos(), g_player.get_y_pos());
	render_text(destination, text, UiConsts::MAP_AREA_POSITION_X, UiConsts::MAP_AREA_POSITION_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_CENTERED);
  }

//------------------------------------------------------------------------------
// Draws the submenu for the item under the cursor, with the appropriate
// context items highlighted or grayed out.
//
// Arguments:
//   b - the BITMAP to render to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_item_submenu(BITMAP *destination) {

	int inv_menu_x;
	int inv_menu_selection_y;

	// Determine the x position of the menu
	if (g_ui_globals.inv_cursor_x < 6) {
	 	inv_menu_x = UiConsts::INVENTORY_ITEMS_X + 
		             (g_ui_globals.inv_cursor_x + 1) * (UiConsts::INVENTORY_CURSOR_SIZE - 1);
	}
	else {
	 	inv_menu_x = UiConsts::INVENTORY_ITEMS_X + 
		             ((g_ui_globals.inv_cursor_x * (UiConsts::INVENTORY_CURSOR_SIZE - 1))) -
					 UiConsts::INVENTORY_MENU_WIDTH;		
	}

	// Create the box interior
	rectfill(destination, inv_menu_x + 3, UiConsts::INVENTORY_MENU_Y + 3, 
	         (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 3),
			 (UiConsts::INVENTORY_MENU_Y + UiConsts::INVENTORY_MENU_HEIGHT - 3 - 1),
			 23);

	// Create the common borders
	rect(destination, inv_menu_x, UiConsts::INVENTORY_MENU_Y, 
	     (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH),
		 (UiConsts::INVENTORY_MENU_Y + UiConsts::INVENTORY_MENU_HEIGHT - 1), 30);

	// { 103 }
	// Create the interior borders
	rect(destination, inv_menu_x + 2, UiConsts::INVENTORY_MENU_Y + 2,
	     (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 2),
		 (UiConsts::INVENTORY_MENU_Y + 48), 19);

	rect(destination, inv_menu_x + 1, UiConsts::INVENTORY_MENU_Y + 1,
	     (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 1),
		 (UiConsts::INVENTORY_MENU_Y + 49), 16);

	rect(destination, inv_menu_x + 2 , UiConsts::INVENTORY_MENU_Y + 52,
	     (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 2),
		 (UiConsts::INVENTORY_MENU_Y + UiConsts::INVENTORY_MENU_HEIGHT - 2 - 1), 19);

	rect(destination, inv_menu_x + 1 , UiConsts::INVENTORY_MENU_Y + 51,
	     (inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 1),
		 (UiConsts::INVENTORY_MENU_Y + UiConsts::INVENTORY_MENU_HEIGHT - 1 - 1), 16);

	// Create the separator
	hline(destination, inv_menu_x , UiConsts::INVENTORY_MENU_Y + 50,
	      inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH, 30);

	// Draw the highlight over what will be the selected text option
	switch (g_ui_globals.sel_item_option) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			inv_menu_selection_y = UiConsts::INVENTORY_MENU_Y + 3 + (g_ui_globals.sel_item_option * 9);
			break;
		case 5:
			inv_menu_selection_y = UiConsts::INVENTORY_MENU_Y + 53;
			break;
	}

	rectfill(destination, inv_menu_x + 3, inv_menu_selection_y,
	         inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 3, 
			 inv_menu_selection_y + 8, 29);

	// Get the item at the highlighed slot
	Item *i = g_inventory->get_item_in_slot(g_ui_globals.inv_cursor_y * 
                UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_cursor_x);

	// Fill in the text in the menu

	// The use option
	int text_color;
	if (i->can_be_used()) 
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Use", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 1, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// The equip/unequip options
	// TODO - get player equip/unequip stuff figured out.  For now, gray them out
	text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Equip", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 10, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);
	render_text(destination, "Unequip", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 19, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);	

	// The drop / destroy options
	if (i->can_be_dropped())
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Drop", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 28, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);
	render_text(destination, "Destroy", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 37, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);	

	// The close option
	render_text(destination, "Close", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 51, 
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_LEFT_JUSTIFIED);	

	// Done

}

//------------------------------------------------------------------------------
// Draws all non-name description fields for an item, based on the item
// type.
//
// Arguments:
//   i - the item to use as the reference
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_description_fields(BITMAP *destination, Item *it) {
	char text[24];
	
	int item_class = it->get_item_class();

	// This value will increment by 10 every time we put a new line on the screen
	int text_y = UiConsts::INVENTORY_ITEM_NAME_Y + 10;

	// Show quantity for stackable items
	if (it->can_it_stack()) {
		sprintf(text, "Quantity: %d", it->get_quantity());
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X, 
					text_y, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, 
					FontConsts::TEXT_LEFT_JUSTIFIED);	
		text_y += 10;
	}

	// Show attack or defense rating for equipment
	if (item_class == ItemConsts::WEAPON_CLASS) {
		sprintf(text, "Attack Rating: %d", it->get_attack());
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X, 
					text_y, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, 
					FontConsts::TEXT_LEFT_JUSTIFIED);	
		text_y += 10;		
	}
	else if (item_class == ItemConsts::ARMOR_CLASS) {
		sprintf(text, "Defense Rating: %d", it->get_defense());
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X, 
					text_y, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, 
					FontConsts::TEXT_LEFT_JUSTIFIED);	
		text_y += 10;				
	}

	// Show description for identified items (or for any artifact)
	if (item_class == ItemConsts::ARTIFACT_CLASS || (it->is_it_identified() && (item_class == ItemConsts::POTION_CLASS || item_class == ItemConsts::SCROLL_CLASS))) {
		render_text(destination, (char *)it->get_description().c_str(), UiConsts::INVENTORY_ITEM_NAME_X, 
					text_y, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, 
					FontConsts::TEXT_LEFT_JUSTIFIED);	
		text_y += 10;
	}
	else if (!it->is_it_identified() && (item_class == ItemConsts::POTION_CLASS || item_class == ItemConsts::SCROLL_CLASS)) {
		render_text(destination, "(This item is unidentified)", UiConsts::INVENTORY_ITEM_NAME_X, 
					text_y, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, 
					FontConsts::TEXT_LEFT_JUSTIFIED);	
		text_y += 10;		
	}

	else if (item_class == ItemConsts::WEAPON_CLASS || item_class == ItemConsts::ARMOR_CLASS) {
		if (it->is_it_identified()) {
			std::string description;
			if (it->get_prefix() != -1) {
				description = g_item_prefix_ids[it->get_prefix()].description;
				render_text(destination, (char *)description.c_str(), UiConsts::INVENTORY_ITEM_NAME_X, 
							text_y, FontConsts::FONT_YELLOW, 
							FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);	
				text_y += 10;
			}
			if (it->get_suffix() != -1) {
				description = g_item_suffix_ids[it->get_suffix()].description;
				render_text(destination, (char *)description.c_str(), UiConsts::INVENTORY_ITEM_NAME_X, 
							text_y, FontConsts::FONT_YELLOW, 
							FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);	
				text_y += 10;
			}
		}
		else {
				render_text(destination, "(This item is unidentified)", UiConsts::INVENTORY_ITEM_NAME_X, 
							text_y, FontConsts::FONT_YELLOW, 
							FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);	
				text_y += 10;			
		}
	}
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
	if (g_state_flags.update_inventory_items) {
		// Draw the items
		for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
			int x = i % UiConsts::INVENTORY_ITEMS_PER_ROW;
			int y = i / UiConsts::INVENTORY_ITEMS_PER_ROW;
			Item *it = g_inventory->get_item_in_slot(i);
			if (it != NULL) {
				int gid = it->get_gid();
				int tilex = gid % UiConsts::ITEM_TILE_ENTRY_WIDTH;
				int tiley = gid / UiConsts::ITEM_TILE_ENTRY_WIDTH;

				masked_blit((BITMAP *)g_game_data[DAMRL_ITEMS].dat, 
	     			    	destination,
	     					tilex * UiConsts::TILE_PIXEL_WIDTH, 
		 					tiley * UiConsts::TILE_PIXEL_HEIGHT, 
		 					(x * (UiConsts::TILE_PIXEL_WIDTH + 1)) + UiConsts::INVENTORY_ITEMS_X + 1,
		 					(y * (UiConsts::TILE_PIXEL_HEIGHT + 1)) + UiConsts::INVENTORY_ITEMS_Y + 1,
		 					UiConsts::TILE_PIXEL_WIDTH,
		 					UiConsts::TILE_PIXEL_HEIGHT);	
			}
		}
		g_state_flags.update_inventory_items = false;
	}

	// Draw the active item cursor (if any)
	if (g_state_flags.update_inventory_cursor) {
		// Draw a square around the old location in the standard border color
		int x1 = UiConsts::INVENTORY_ITEMS_X + (g_ui_globals.prev_inv_cursor_x * (UiConsts::INVENTORY_CURSOR_SIZE - 1));
		int y1 = UiConsts::INVENTORY_ITEMS_Y + (g_ui_globals.prev_inv_cursor_y * (UiConsts::INVENTORY_CURSOR_SIZE - 1));
		int x2 = x1 + (UiConsts::INVENTORY_CURSOR_SIZE - 1);
		int y2 = y1 + (UiConsts::INVENTORY_CURSOR_SIZE - 1);
		rect(destination, x1, y1, x2, y2, 19);

		// Draw a square around the new location in the standard border color
		x1 = UiConsts::INVENTORY_ITEMS_X + (g_ui_globals.inv_cursor_x * (UiConsts::INVENTORY_CURSOR_SIZE - 1));
		y1 = UiConsts::INVENTORY_ITEMS_Y + (g_ui_globals.inv_cursor_y * (UiConsts::INVENTORY_CURSOR_SIZE - 1));
		x2 = x1 + (UiConsts::INVENTORY_CURSOR_SIZE - 1);
		y2 = y1 + (UiConsts::INVENTORY_CURSOR_SIZE - 1);
		rect(destination, x1, y1, x2, y2, 30);

		g_state_flags.update_inventory_cursor = false;
	}

	// Draw the active item description
	if (g_state_flags.update_inventory_description) {
		// Clear the old description
		rectfill(destination, UiConsts::INVENTORY_DESC_AREA_X, UiConsts::INVENTORY_DESC_AREA_Y,
				 UiConsts::INVENTORY_DESC_AREA_X + UiConsts::INVENTORY_DESC_AREA_W - 1,
				 UiConsts::INVENTORY_DESC_AREA_Y + UiConsts::INVENTORY_DESC_AREA_H - 1,
				 23);
				 
		// Get the item we are writing the description of
		int item_index = (g_ui_globals.inv_cursor_y  * UiConsts::INVENTORY_ITEMS_PER_ROW) + g_ui_globals.inv_cursor_x;
		Item *it = g_inventory->get_item_in_slot(item_index);
		if (it != NULL) {
			// Render the item name
			render_text(destination, (char *)it->get_full_name().c_str(), 
		    	        UiConsts::INVENTORY_ITEM_NAME_X, UiConsts::INVENTORY_ITEM_NAME_Y, 
						FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, 
						FontConsts::TEXT_LEFT_JUSTIFIED);
			render_description_fields(destination, it);
		}
		g_state_flags.update_inventory_description = false;
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
	// This used to be drawn as a bitmap, but the UI is now much simpler so
	// I'm rendering it using graphics primitives.  That makes the code below
	// look pretty ugly, but I shouldn't have to touch it.

	// Draw the background
	if (g_state_flags.update_inventory_dialog) {
		// the main window
		rectfill(destination, UiConsts::INVENTORY_DIALOG_X + 4, UiConsts::INVENTORY_DIALOG_Y + 4,
				 UiConsts::INVENTORY_DIALOG_X2 - 4,
				 UiConsts::INVENTORY_DIALOG_Y2 - 4,
				 23);

		//the common borders
		rect(destination, UiConsts::INVENTORY_DIALOG_X, UiConsts::INVENTORY_DIALOG_Y,
		   	 UiConsts::INVENTORY_DIALOG_X2, UiConsts::INVENTORY_DIALOG_Y2, 16);
	    rect(destination, UiConsts::INVENTORY_DIALOG_X + 1, UiConsts::INVENTORY_DIALOG_Y + 1,
		 	 UiConsts::INVENTORY_DIALOG_X2 - 1, UiConsts::INVENTORY_DIALOG_Y2 - 1, 30);

		// The top borders
		rect(destination, UiConsts::INVENTORY_DIALOG_X + 2, UiConsts::INVENTORY_DIALOG_Y + 2,
		 	 UiConsts::INVENTORY_TOP_X2 - 2, UiConsts::INVENTORY_TOP_Y2 - 1, 16);
		rect(destination, UiConsts::INVENTORY_DIALOG_X + 3, UiConsts::INVENTORY_DIALOG_Y + 3,
		 	 UiConsts::INVENTORY_TOP_X2 - 3, UiConsts::INVENTORY_TOP_Y2 - 2, 19);		

		// The bottom borders	
		rect(destination, UiConsts::INVENTORY_DIALOG_X + 2, UiConsts::INVENTORY_TOP_Y2 + 1,
		 	 UiConsts::INVENTORY_TOP_X2 - 2, UiConsts::INVENTORY_DIALOG_Y2 - 2, 16);
		rect(destination, UiConsts::INVENTORY_DIALOG_X + 3, UiConsts::INVENTORY_TOP_Y2 + 2,
		 	 UiConsts::INVENTORY_TOP_X2 - 3, UiConsts::INVENTORY_DIALOG_Y2 - 3, 19);	

		// the separating line
		hline(destination, UiConsts::INVENTORY_DIALOG_X + 1, UiConsts::INVENTORY_TOP_Y2,
			  UiConsts::INVENTORY_DIALOG_X2 - 1, 30);
		
		// The item text
		render_text(destination, "Inventory", (UiConsts::INVENTORY_DIALOG_X + UiConsts::INVENTORY_DIALOG_X2) / 2,
					UiConsts::INVENTORY_DIALOG_Y + 7, FontConsts::FONT_YELLOW, 
					FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

		// The item grid
		rectfill(destination, UiConsts::INVENTORY_ITEMS_X - 1, UiConsts::INVENTORY_ITEMS_Y - 1,
			 UiConsts::INVENTORY_ITEMS_X2 + 1, UiConsts::INVENTORY_ITEMS_Y2 + 1, 16);
		rect(destination, UiConsts::INVENTORY_ITEMS_X, UiConsts::INVENTORY_ITEMS_Y,
			 UiConsts::INVENTORY_ITEMS_X2, UiConsts::INVENTORY_ITEMS_Y2, 19);
		for (int i = 1; i < UiConsts::INVENTORY_ROWS; i++) {
			hline(destination, UiConsts::INVENTORY_ITEMS_X, 
				  UiConsts::INVENTORY_ITEMS_Y + ((UiConsts::INVENTORY_CURSOR_SIZE - 1) * i),
				  UiConsts::INVENTORY_ITEMS_X2, 19);
		}
		for (int i = 1; i < UiConsts::INVENTORY_ITEMS_PER_ROW; i++) {
			vline(destination, UiConsts::INVENTORY_ITEMS_X + ((UiConsts::INVENTORY_CURSOR_SIZE - 1) * i), 
				  UiConsts::INVENTORY_ITEMS_Y, UiConsts::INVENTORY_ITEMS_Y2, 19);
		}			 
		g_state_flags.update_inventory_dialog = false;
	}

	render_inventory_content(destination);

	if(g_state_flags.update_inventory_submenu) {
		render_item_submenu(destination);
		g_state_flags.update_inventory_submenu = false;
	}
}

//------------------------------------------------------------------------------
// Draws a generic UI bitmap to the specified location on the target BITMAP.
//
// Arguments:
//   destination - the BITMAP to render to
//   x1, y1, x2, y2 - the extents of the box to be rendered
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_ui_box(BITMAP *destination, int x1, int y1, int x2, int y2) {
	rectfill(destination, x1 + 3, y1 + 3, x2 - 3, y2 - 3, 23);
	rect(destination, x1 + 2, y1 + 2, x2 - 2, y2 - 2, 19);
	rect(destination, x1 + 1, y1 + 1, x2 - 1, y2 - 1, 16);
	rect(destination, x1, y1, x2, y2, 30);
}

//------------------------------------------------------------------------------
// Draws the contents of the status area (Name/Level/HP/EXP/gold) to the screen
//
// Arguments:
//   destination - the bitmap to write to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_status_ui(BITMAP *destination) {
	char text[32];

	// Name
	render_text(destination, (char *)g_player.name.c_str(), UiConsts::NAME_TEXT_X, UiConsts::NAME_TEXT_Y,
			    FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	// Generation
	sprintf(text, "(%s)", get_generation_string(g_player.generation).c_str());
	render_text(destination, text, UiConsts::GENERATION_TEXT_X, UiConsts::GENERATION_TEXT_Y,
			    FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	// Level
	sprintf(text, "Level %d", g_player.level);
	render_text(destination, text, UiConsts::LEVEL_TEXT_X, UiConsts::LEVEL_TEXT_Y,
			    FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	// HP status bar
	render_text(destination, "HP:", UiConsts::HP_TEXT_X, UiConsts::HP_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	masked_blit((BITMAP *)g_game_data[DAMRL_STATUS_BAR].dat,
				destination, 0, 0, UiConsts::HP_BAR_X, UiConsts::HP_BAR_Y, 
				UiConsts::HP_EXP_BAR_WIDTH, UiConsts::HP_EXP_BAR_HEIGHT);

	// EXP status bar
	render_text(destination, "EXP:", UiConsts::EXP_TEXT_X, UiConsts::EXP_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	masked_blit((BITMAP *)g_game_data[DAMRL_STATUS_BAR].dat,
				destination, 0, 0, UiConsts::EXP_BAR_X, UiConsts::EXP_BAR_Y,
				UiConsts::HP_EXP_BAR_WIDTH, UiConsts::HP_EXP_BAR_HEIGHT);

	// Area text
	render_text(destination, "Area:", UiConsts::DUNGEON_TEXT_X, UiConsts::DUNGEON_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	render_text(destination, (char *)get_dungeon_name(g_dungeon.maze_id, true).c_str(), UiConsts::DUNGEON_NAME_X,
	  			UiConsts::DUNGEON_NAME_Y, FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);

	render_text(destination, "Floor:", UiConsts::FLOOR_TEXT_X, UiConsts::FLOOR_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d of %d", g_dungeon.depth, g_dungeon.max_depth);
	render_text(destination, text, UiConsts::FLOOR_VALUE_X, UiConsts::FLOOR_VALUE_Y, 
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// Gold text
	render_text(destination, "Gold:", UiConsts::GOLD_TEXT_X, UiConsts::GOLD_TEXT_Y, 
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", g_player.get_gold());
	render_text(destination, text, UiConsts::GOLD_VALUE_X, UiConsts::GOLD_VALUE_Y, 
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, 
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// Status icons (TBD)
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
	render_ui_box(destination, UiConsts::STATUS_AREA_X1, UiConsts::STATUS_AREA_Y1,
				  UiConsts::STATUS_AREA_X2, UiConsts::STATUS_AREA_Y2);
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
	int x1, y1;

	if(extended == true) {
		x1 = UiConsts::TEXT_AREA_EXT_X1;
		y1 = UiConsts::TEXT_AREA_EXT_Y1;
	}
	else {
		x1 = UiConsts::TEXT_AREA_STD_X1;
		y1 = UiConsts::TEXT_AREA_STD_Y1;
	}

	render_ui_box(destination, x1, y1, UiConsts::TEXT_AREA_X2, UiConsts::TEXT_AREA_Y2);
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
		size = UiConsts::TEXT_AREA_EXT_NUM_LINES;
		x_off = UiConsts::TEXT_AREA_EXT_X1 + UiConsts::TEXT_AREA_LINE_X_OFFSET;
		y_off = UiConsts::TEXT_AREA_EXT_Y1 + UiConsts::TEXT_AREA_LINE_Y_OFFSET;
		log_start = 0;
 	} 
	else {
		size = UiConsts::TEXT_AREA_NORMAL_NUM_LINES;
		x_off = UiConsts::TEXT_AREA_STD_X1 + UiConsts::TEXT_AREA_LINE_X_OFFSET;
		y_off = UiConsts::TEXT_AREA_STD_Y1 + (2 * UiConsts::TEXT_AREA_LINE_Y_OFFSET);
		if (lines_to_draw > size) {
			log_start = lines_to_draw - size;
		} 
		else {
			log_start = 0;
		}
	}

	for(int idx = log_start; idx < lines_to_draw; ++idx) {
		render_text(destination, (char *)g_text_log.get_line(idx).c_str(),
					x_off, y_off + ((FontConsts::prop_font_height + 1) * (idx-log_start)),
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
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
	int num_y_tiles;

	// If the extended text dialog is up, don't draw the last 3 rows of tiles
	if (g_state_flags.text_log_extended) {
		num_y_tiles = UiConsts::PLAY_AREA_TILE_HEIGHT - UiConsts::TEXT_AREA_EXT_MAZE_ROWS_OBSCURED;
	}
	else {
		num_y_tiles = UiConsts::PLAY_AREA_TILE_HEIGHT;
	}

	for (int screen_x = 0; screen_x < UiConsts::PLAY_AREA_TILE_WIDTH; screen_x++) {
		for (int screen_y = 0; screen_y < num_y_tiles; screen_y++) {
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
						render_base_tile(destination, UiConsts::TILE_DARKER_WALL, screen_x, screen_y);
					} else {
						// Otherwise, draw darkness
						render_base_tile(destination, UiConsts::TILE_DARK, screen_x, screen_y);
					}
				}
				// Render stairs if present
				else if (stairs == MazeConsts::STAIRS_UP) {
					render_base_tile(destination, UiConsts::TILE_UP_STAIRS, screen_x, screen_y);
				}
				else if (stairs == MazeConsts::STAIRS_DOWN) {
					render_base_tile(destination, UiConsts::TILE_DOWN_STAIRS, screen_x, screen_y);
				}
				// Render floor if present.  There are 4 different floor tiles - one with no
				// highlighting and 3 with different types of highlighting
				// If the location is a wall, render that instead.
				else if (m->is_carved(tile_to_render_x, tile_to_render_y) == true) {
					if (carved_left == false && carved_up == true) {
						tile_to_use = UiConsts::TILE_FLOOR_LEFT_HIGHLIGHT;
					}
					else if (carved_left == true && carved_up == false) {
						tile_to_use = UiConsts::TILE_FLOOR_TOP_HIGHLIGHT;
					}
					else if (carved_left == false && carved_up == false) {
						tile_to_use = UiConsts::TILE_FLOOR_BOTH_HIGHLIGHT;
					}
					else {
						tile_to_use = UiConsts::TILE_FLOOR;
					}
					render_base_tile(destination, tile_to_use, screen_x, screen_y);
					// Get any items at the location and draw the first on the list
					int num_items_here = m->get_num_items_at(tile_to_render_x, tile_to_render_y);
					if (num_items_here > 0) {
						std::list<Item *> items = m->get_items_at(tile_to_render_x, tile_to_render_y);
						Item *it = items.back();
						render_item(destination, it->get_gid(), screen_x, screen_y);
					}
				} else {
					render_base_tile(destination, UiConsts::TILE_WALL, screen_x, screen_y);
				}		
			} else {
				// Draw an empty space since it's outside of the map
				render_base_tile(destination, UiConsts::TILE_DARK, screen_x, screen_y);
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
	render_world_at(destination, m, maze_x - UiConsts::PLAYER_PLAY_AREA_X, maze_y - UiConsts::PLAYER_PLAY_AREA_Y);
}

//------------------------------------------------------------------------------
// Writes a string in the specified location on the screen, with specified
// font, width, color and justification.
////
// Arguments:
//   dest - the bitmap to render to
//   text - the string to render
//   x_pos - the x position of the string  
//   y_pos  - the y position of the string
//   font_idx - the color of the string
//   type   - fixed, proportional or narrow proportional
//   alignment - left, center, or right justified
//
// Returns:
//   Nothing
//
// Notes:
//   For 'x_pos', this specifies the left edge of the text in left-justified 
//   mode, the center in centered mode, and the right edge of the text in 
//   right justified mode
//------------------------------------------------------------------------------
void Render::render_text(BITMAP *dest, char *text, int x_pos, int y_pos, int font_idx, int style, int alignment) {
	int width;
	int x_offset;

	// Get the text width
	switch (style) {
		case FontConsts::FONT_FIXED:
			width = strlen(text) * FontConsts::fixed_font_width;
			break;
		case FontConsts::FONT_NARROW_PROPORTIONAL:
		case FontConsts::FONT_PROPORTIONAL:
			width = get_prop_text_width(text, style);
			break;
	}

	// Get the text alignment
	switch (alignment) {
		case FontConsts::TEXT_LEFT_JUSTIFIED:
			x_offset = x_pos;
			break;
		case FontConsts::TEXT_CENTERED:
			x_offset = x_pos - (width / 2);
			break;
		case FontConsts::TEXT_RIGHT_JUSTIFIED:
			x_offset = x_pos - width;
			break;
	}

	// Render the text itself
	switch (style) {
		case FontConsts::FONT_FIXED:
			render_fixed_text(dest, text, x_offset, y_pos, font_idx);
			break;
		case FontConsts::FONT_NARROW_PROPORTIONAL:
		case FontConsts::FONT_PROPORTIONAL:
			render_prop_text(dest, text, x_offset, y_pos, font_idx, style);
			break;
	}
}


//------------------------------------------------------------------------------
// Gets the width of a text in the proportional font.
//
// Arguments:
//   text - the text to be rendered
//   style - standard or narrow
//
// Returns:
//   The width of the text in pixels
//------------------------------------------------------------------------------
int Render::get_prop_text_width(char *text, int style) {
	int width, offset;
	char *cur;

	cur = text;
	width = 0;
	while (*cur != 0) {
		offset = (*cur) - 32;
		if (style == FontConsts::FONT_NARROW_PROPORTIONAL)
			width += (int)FontConsts::prop_narrow_font_width[offset] + 1;
		else
			width += (int)FontConsts::prop_font_width[offset] + 1;
    	cur++;
	}

	return width;
}