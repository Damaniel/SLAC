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

	// Default the inventory menu to sane defaults
	g_ui_globals.inv_menu_active = false;
	g_ui_globals.sel_item_option = UiConsts::ITEM_OPTION_CLOSE;
}

//------------------------------------------------------------------------------
// Renders the player on the screen.  They're always in a fixed location.
//
// Arguments:
//   destination - the bitmap to render to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_player(BITMAP *destination) {
	BITMAP *bpc = (BITMAP *)g_game_data[DAMRL_PLAYER_SPRITES].dat;

	// Draw the player.  He's always centered in the play area.
	masked_blit(bpc, destination, UiConsts::PLAYER_TILE_OFFSET * UiConsts::TILE_PIXEL_WIDTH, 0,
	            UiConsts::PLAYER_PLAY_AREA_X * UiConsts::TILE_PIXEL_WIDTH,
				UiConsts::PLAYER_PLAY_AREA_Y * UiConsts::TILE_PIXEL_HEIGHT,
		        UiConsts::TILE_PIXEL_WIDTH, UiConsts::TILE_PIXEL_HEIGHT);
}

//------------------------------------------------------------------------------
// Renders all non-static dungeon elements.  This includes the player and all
// visible enemies.
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

	// Draw the player
	render_player(destination);

	// Iterate through the (sorted) monster list, and calculate/render each monster until
	// the distance of the next monster is further than the render limit
	std::list<Enemy *>::iterator enemy_it = g_dungeon.enemies.begin();
	bool done = false;
	while (enemy_it != g_dungeon.enemies.end() && !done) {
		if ((*enemy_it)->get_distance() <= UiConsts::MAXIMUM_ENEMY_RENDER_DISTANCE) {
			// Get the enemy position and tile id
			int ex = (*enemy_it)->get_x_pos();
			int ey = (*enemy_it)->get_y_pos();
			int eid = (*enemy_it)->get_gid();
			//std::cout << "  maze_x = " << maze_x << ", maze_y = " << maze_y << std::endl;
			//std::cout << "  ex = " << ex << ", ey = " << ey << ", px = " << ex - maze_x << ", py = " << ey - maze_y << std::endl;
			// If the enemy is on a square that's currently lit, then draw it
			if (g_dungeon.maze->is_square_lit(ex, ey)) {
				//std::cout << "  Enemy is on a lit square" << std::endl;
				// Get the on-screen position of the enemy
				int px = ex - maze_x;
				int py = ey - maze_y;
				// Since the enemy we're considering may be slightly off-screen, we'll check for that and skip
				// drawing those enemies
				if (px >= 0 && py >= 0 && px < UiConsts::PLAY_AREA_TILE_WIDTH && py < UiConsts::PLAY_AREA_TILE_HEIGHT) {
					int tx = eid % UiConsts::ENEMY_TILE_ENTRY_WIDTH;
					int ty = eid / UiConsts::ENEMY_TILE_ENTRY_WIDTH;
					//std::cout << "  tx = " << tx << ", ty = " << ty << std::endl;
					masked_blit((BITMAP *)g_game_data[DAMRL_ENEMIES].dat,
								destination,
								tx * UiConsts::TILE_PIXEL_WIDTH,
								ty * UiConsts::TILE_PIXEL_HEIGHT,
								px * UiConsts::TILE_PIXEL_WIDTH,
								py * UiConsts::TILE_PIXEL_WIDTH,
								UiConsts::TILE_PIXEL_WIDTH,
								UiConsts::TILE_PIXEL_HEIGHT);
				}
			}

			//std::cout << "Render enemy - distance is " << (*enemy_it)->get_distance() << std::endl;
			//std::cout << "  Enemy position is (" << (*enemy_it)->get_x_pos() << ", " << (*enemy_it)->get_y_pos() << ")" << std::endl;
		}
		else {
			// Every other enemy is too far away; we're done
			done = true;
		}
		++enemy_it;
	}

	//std::cout << "=============================" << std::endl;


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
void Render::render_base_tile(BITMAP *destination, int tile_id, int dungeon_id, int x, int y) {
	blit((BITMAP *)g_game_data[DAMRL_MAZE_BASE_TILES_1].dat,
	     destination,
	     tile_id * UiConsts::TILE_PIXEL_WIDTH,
		 dungeon_id * UiConsts::TILE_PIXEL_HEIGHT,
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
void Render::initialize_map_bitmap(DungeonFloor *f) {
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
    g_ui_globals.map_maze_xoffset = UiConsts::MAP_AREA_VMEM_X + ((UiConsts::MAP_PIXEL_WIDTH - f->maze->get_width() * UiConsts::MAP_DOT_WIDTH) / 2);
	g_ui_globals.map_maze_yoffset = UiConsts::MAP_AREA_VMEM_Y + ((UiConsts::MAP_PIXEL_HEIGHT - f->maze->get_height() * UiConsts::MAP_DOT_HEIGHT) / 2);
}

//------------------------------------------------------------------------------
// Marks the selected square on the map as a wall or empty space
//
// Arguments:
//   f - the dungeon to use to determine what squares to draw
//   x, y - the position in the maze to draw
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::fill_in_map_square(DungeonFloor *f, int x, int y) {
	if (f->maze->was_seen(x, y)) {
		if (f->maze->is_carved(x, y) == false) {
			blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
				screen,
				UiConsts::MAP_DOT_WALL * UiConsts::MAP_DOT_WIDTH,
				0,
				g_ui_globals.map_maze_xoffset + (x * UiConsts::MAP_DOT_WIDTH),
				g_ui_globals.map_maze_yoffset + (y * UiConsts::MAP_DOT_HEIGHT),
				UiConsts::MAP_DOT_WIDTH,
				UiConsts::MAP_DOT_HEIGHT);
		} else {
			blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat,
				screen,
				UiConsts::MAP_DOT_FLOOR * UiConsts::MAP_DOT_WIDTH,
				0,
				g_ui_globals.map_maze_xoffset + (x * UiConsts::MAP_DOT_WIDTH),
				g_ui_globals.map_maze_yoffset + (y * UiConsts::MAP_DOT_HEIGHT),
				UiConsts::MAP_DOT_WIDTH,
				UiConsts::MAP_DOT_HEIGHT);
		}
	}
}

//------------------------------------------------------------------------------
// Exposes the entire map into the map bitmap
//
// Arguments:
//   f - the dungeon to use to determine what squares to draw
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::fill_in_entire_map(DungeonFloor *f) {
	for(int i = 0; i < f->maze->get_width(); i++) {
		for(int j = 0; j < f->maze->get_height(); j++) {
			fill_in_map_square(f, i, j);
		}
	}
}

//------------------------------------------------------------------------------
// Adds small squares to the map bitmap corresponding to the area in the
// immediate vicinity of the location specified by (x, y)
//
// Arguments:
//   f- the dungeon to use to determine what squares to draw
//   x, y - the 'center' of the portion of the dungeon to render on the map
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::add_area_to_map_bitmap(DungeonFloor *f, int x, int y) {
	// Fill in the squares immediately surrounding the player
	for(int i=x-1; i<=x+1; i++) {
		for(int j=y-1; j<=y+1; j++) {
			//std::cout << "add_area_to_map_bitmap: processing (" << i << ", " << j << ")" << std::endl;
			if(i >=0 && i < f->maze->get_width() && j >=0 && j < f->maze->get_height()) {
				fill_in_map_square(f, i, j);
			}
		}
	}

	// If the player is in a room and hasn't been in the room before,
	// draw the room to the map area
	int room = f->maze->get_room_id_at(x, y);
	//std::cout << "add_area_to_map_bitmap: room id = " << room << std::endl;
	if(room != -1) {
		Room r = f->maze->get_room(room);
		//std::cout << "  add_area_to_map_bitmap: Got room" << std::endl;
		if (r.has_been_entered == false) {
			for(int i = r.x - 1; i < r.x + r.w + 1; i++) {
				for (int j = r.y - 1; j < r.y + r.h + 1; j++) {
					//std::cout << "  add_area_to_map_bitmap: Processing room at (" << i << ", " << j << ")" << std::endl;
					if(f->maze->is_carved(i, j) == false) {
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
// Draws a line of text in the tiny font to the screen
//
// Arguments:
//   destination - the place to render the text to
//   text - the text to write
//   x_pos, y_pos - the upper left corner of the location to place the text
//   font_idx     - which color offet (0-4) to use
//
// Returns:
//   Nothing
//
// Notes:
//   The following characters can't be drawn in this font:
//     $, &, @
//------------------------------------------------------------------------------
void Render::render_tiny_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;

	if (font_idx > 0)
		font_idx = 0;

	while (*cur != 0) {
		offset = (*cur++) - 32;
			masked_blit((BITMAP *)g_game_data[DAMRL_TINY_FONT].dat, destination,
			            (int)FontConsts::tiny_font_offset[offset], font_idx * FontConsts::tiny_font_height,
						x, y, (int)FontConsts::tiny_font_width[offset], FontConsts::tiny_font_height);
			x += (int)FontConsts::tiny_font_width[offset] + 1;
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
		case UiConsts::ITEM_OPTION_USE:
		case UiConsts::ITEM_OPTION_EQUIP:
		case UiConsts::ITEM_OPTION_UNEQUIP:
		case UiConsts::ITEM_OPTION_DROP:
		case UiConsts::ITEM_OPTION_DESTROY:
			inv_menu_selection_y = UiConsts::INVENTORY_MENU_Y + 3 + (g_ui_globals.sel_item_option * 9);
			break;
		case UiConsts::ITEM_OPTION_CLOSE:
			inv_menu_selection_y = UiConsts::INVENTORY_MENU_Y + 53;
			break;
	}

	rectfill(destination, inv_menu_x + 3, inv_menu_selection_y,
	         inv_menu_x + UiConsts::INVENTORY_MENU_WIDTH - 3,
			 inv_menu_selection_y + 8, 25);

	// Get the item at the highlighed slot
	Item *i = g_inventory->get_item_in_slot(g_ui_globals.inv_cursor_y *
                UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_cursor_x);

	// Fill in the text in the menu

	// The use option
	int text_color;
	if (i->can_use)
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Use", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 1,
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// The equip/unequip options
	if(i->can_equip && !i->is_equipped)
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Equip", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 10,
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// Allow the item to be unequipped if it's equipped and not cursed
	if(i->can_equip && i->is_equipped && !i->is_cursed)
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Unequip", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 19,
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// The drop / destroy options
	if (g_state_flags.in_dungeon && i->can_drop && !i->is_equipped)
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Drop", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 28,
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// The drop / destroy options
	if (i->can_drop && !i->is_equipped)
		text_color = FontConsts::FONT_YELLOW;
	else
		text_color = FontConsts::FONT_GRAY;
	render_text(destination, "Destroy", inv_menu_x + 4, UiConsts::INVENTORY_MENU_Y + 3 + 37,
	            text_color, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);

	// The close option
	text_color = FontConsts::FONT_YELLOW;
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

	int item_class = it->item_class;

	// This value will increment by 10 every time we put a new line on the screen
	int text_y = UiConsts::INVENTORY_ITEM_NAME_Y + 10;

	// Show quantity for stackable items
	if (it->can_stack) {
		sprintf(text, "Quantity: %d", it->quantity);
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X,
					text_y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_LEFT_JUSTIFIED);
		text_y += 10;
	}

	// Show attack or defense rating for equipment
	if (item_class == ItemConsts::WEAPON_CLASS) {
		sprintf(text, "Attack Rating: %d", it->attack);
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X,
					text_y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_LEFT_JUSTIFIED);
		text_y += 10;
	}
	else if (item_class == ItemConsts::ARMOR_CLASS) {
		sprintf(text, "Defense Rating: %d", it->defense);
		render_text(destination, text, UiConsts::INVENTORY_ITEM_NAME_X,
					text_y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_LEFT_JUSTIFIED);
		text_y += 10;
	}

	// Show description for identified items (or for any artifact)
	if (item_class == ItemConsts::ARTIFACT_CLASS || (it->is_identified && (item_class == ItemConsts::POTION_CLASS || item_class == ItemConsts::SCROLL_CLASS))) {
		render_text(destination, (char *)it->description.c_str(), UiConsts::INVENTORY_ITEM_NAME_X,
					text_y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_LEFT_JUSTIFIED);
		text_y += 10;
	}
	else if (!it->is_identified && (item_class == ItemConsts::POTION_CLASS || item_class == ItemConsts::SCROLL_CLASS)) {
		render_text(destination, "(This item is unidentified)", UiConsts::INVENTORY_ITEM_NAME_X,
					text_y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_LEFT_JUSTIFIED);
		text_y += 10;
	}

	else if (item_class == ItemConsts::WEAPON_CLASS || item_class == ItemConsts::ARMOR_CLASS) {
		if (it->is_identified) {
			std::string description;
			if (it->prefix_id != -1) {
				if (it->is_cursed) {
					description = g_cursed_item_prefix_ids[it->prefix_id].description;
				}
				else {
					description = g_item_prefix_ids[it->prefix_id].description;
				}
				render_text(destination, (char *)description.c_str(), UiConsts::INVENTORY_ITEM_NAME_X,
							text_y, FontConsts::FONT_YELLOW,
							FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
				text_y += 10;
			}
			if (it->suffix_id != -1) {
				if (it->is_cursed) {
					description = g_cursed_item_suffix_ids[it->suffix_id].description;
				}
				else {
					description = g_item_suffix_ids[it->suffix_id].description;
				}
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
				// If a potion or scroll, get the GID from the scrambled
				// icon table to ensure the correct scrambled icon
				// is drawn
				int gid = get_tile_to_render(it);
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
				// Draw the equipped icon if the item is equipped
				if (it->is_equipped) {
					masked_blit((BITMAP *)g_game_data[DAMRL_EQUIPPED].dat,
								destination,
								0, 0,
								(x * (UiConsts::TILE_PIXEL_WIDTH + 1)) + UiConsts::INVENTORY_ITEMS_X + 13,
		 					    (y * (UiConsts::TILE_PIXEL_HEIGHT + 1)) + UiConsts::INVENTORY_ITEMS_Y + 11,
								3, 5);
				}
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
// Draws filled rectangles to represent the HP and EXP bar
//
// Arguments:
//   destination - the BITMAP to render to
//   x1, y1, x2, y2 - the extents of the box to be rendered
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_hp_exp_bar(BITMAP *destination) {
	int width;

	// HP bar
	// clear the entire bar
	rectfill(destination, UiConsts::HP_BAR_X + 3, UiConsts::HP_BAR_Y + 5,
			 UiConsts::HP_BAR_X + 3 + UiConsts::HP_EXP_BAR_WIDTH - 1,
			 UiConsts::HP_BAR_Y + UiConsts::HP_EXP_BAR_HEIGHT - 1,
			 16);
	// fill in the HP bar
	width = (int)(((float)g_player.hp / (float)g_player.actual.max_hp) * (UiConsts::HP_EXP_BAR_WIDTH));
	if (width > 0) {
		rectfill(destination, UiConsts::HP_BAR_X + 3, UiConsts::HP_BAR_Y + 5,
				 UiConsts::HP_BAR_X + 3 + width - 1, UiConsts::HP_BAR_Y + UiConsts::HP_EXP_BAR_HEIGHT - 1, 22);
	}

	// EXP bar
	width = (int)(g_player.pct_exp_to_next_level() * (UiConsts::HP_EXP_BAR_WIDTH));
	if (width > 0) {
		rectfill(destination, UiConsts::EXP_BAR_X + 3, UiConsts::EXP_BAR_Y + 5,
				 UiConsts::EXP_BAR_X + 3 + width - 1, UiConsts::EXP_BAR_Y + UiConsts::HP_EXP_BAR_HEIGHT - 1, 29);
	}
}

//------------------------------------------------------------------------------
// Draws the elapsed time
//
// Arguments:
//   destination - the BITMAP to render to
//   x1, y1, x2, y2 - the extents of the box to be rendered
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_elapsed_time(BITMAP *destination) {
	// clear the time area
	rectfill(destination, UiConsts::ELAPSED_TEXT_X, UiConsts::ELAPSED_VALUE_Y,
	         UiConsts::ELAPSED_VALUE_X, UiConsts::ELAPSED_VALUE_Y + 10, 23);

	// Render the elapsed time
	char elapsed[20];
	int etime = g_game_flags.elapsed_time;
	int hours = etime / 3600;
	int minutes = (etime - (hours * 3600)) / 60;
	int seconds = (etime - (hours * 3600)) % 60;

    if (hours >= 1000)
    	sprintf(elapsed, "999:59:59");
    else if(hours >= 100)
    	sprintf(elapsed, "%03d:%02d:%02d", hours, minutes, seconds);
  	else
    	sprintf(elapsed, "%02d:%02d:%02d", hours, minutes, seconds);

	render_text(destination, elapsed, UiConsts::ELAPSED_VALUE_X, UiConsts::ELAPSED_VALUE_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_RIGHT_JUSTIFIED);
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
	sprintf(text, "(%s)", get_generation_string(g_game_flags.generation).c_str());
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
				UiConsts::HP_EXP_BAR_AREA_WIDTH, UiConsts::HP_EXP_BAR_AREA_HEIGHT);

	// EXP status bar
	render_text(destination, "EXP:", UiConsts::EXP_TEXT_X, UiConsts::EXP_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	masked_blit((BITMAP *)g_game_data[DAMRL_STATUS_BAR].dat,
				destination, 0, 0, UiConsts::EXP_BAR_X, UiConsts::EXP_BAR_Y,
				UiConsts::HP_EXP_BAR_AREA_WIDTH, UiConsts::HP_EXP_BAR_AREA_HEIGHT);

	// Area text
	render_text(destination, "Area:", UiConsts::DUNGEON_TEXT_X, UiConsts::DUNGEON_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);\
	if (g_state_flags.in_dungeon) {
		render_text(destination, (char *)get_dungeon_name(g_dungeon.maze_id, true).c_str(), UiConsts::DUNGEON_NAME_X,
		  			UiConsts::DUNGEON_NAME_Y, FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_RIGHT_JUSTIFIED);
	}
	else {
		render_text(destination, "Town", UiConsts::DUNGEON_NAME_X,
		  			UiConsts::DUNGEON_NAME_Y, FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_RIGHT_JUSTIFIED);
	}

	render_text(destination, "Floor:", UiConsts::FLOOR_TEXT_X, UiConsts::FLOOR_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
	if (g_state_flags.in_dungeon) {
		sprintf(text, "%d of %d", g_dungeon.depth, g_dungeon.max_depth);
	}
	else {
		sprintf(text, "- Surface -");
	}
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

	// Elapsed time text
	render_text(destination, "Elapsed Time:", UiConsts::ELAPSED_TEXT_X, UiConsts::ELAPSED_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_LEFT_JUSTIFIED);
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
// Draws the stats screen.
//
// Arguments:
//   destination - the bitmap to write to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_stats_screen(BITMAP *destination) {
	char text[32];

	// The main window
	render_ui_box(destination, UiConsts::STATS_SCREEN_X1, UiConsts::STATS_SCREEN_Y1,
				   UiConsts::STATS_SCREEN_X2, UiConsts::STATS_SCREEN_Y2);

	// Stats header
	render_text(destination, "Stats", UiConsts::STATS_HEADER_X, UiConsts::STATS_HEADER_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);

	// HP
	sprintf(text, "HP: %d / %d", g_player.hp, (int)g_player.actual.max_hp);
	render_text(destination, text, UiConsts::STATS_HP_X, UiConsts::STATS_HP_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
	// EXP
	sprintf(text, "EXP: %d", g_player.exp);
	render_text(destination, text, UiConsts::STATS_EXP_X, UiConsts::STATS_EXP_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);

 	// EXP
	sprintf(text, "To next: %d", PlayerConsts::g_player_exp_table[g_player.level] - g_player.exp);
	render_text(destination, text, UiConsts::STATS_NEXT_X, UiConsts::STATS_NEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);

	// STR
	render_text(destination, "STR:", UiConsts::STATS_STR_TEXT_X, UiConsts::STATS_STR_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.str);
	render_text(destination, text, UiConsts::STATS_STR_VAL_X, UiConsts::STATS_STR_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// CON
	render_text(destination, "CON:", UiConsts::STATS_CON_TEXT_X, UiConsts::STATS_CON_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.con);
	render_text(destination, text, UiConsts::STATS_CON_VAL_X, UiConsts::STATS_CON_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// DEX
	render_text(destination, "DEX:", UiConsts::STATS_DEX_TEXT_X, UiConsts::STATS_DEX_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.dex);
	render_text(destination, text, UiConsts::STATS_DEX_VAL_X, UiConsts::STATS_DEX_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// ATK
	render_text(destination, "ATK:", UiConsts::STATS_ATK_TEXT_X, UiConsts::STATS_ATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.atk);
	render_text(destination, text, UiConsts::STATS_ATK_VAL_X, UiConsts::STATS_ATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// DEF
	render_text(destination, "DEF:", UiConsts::STATS_DEF_TEXT_X, UiConsts::STATS_DEF_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.def);
	render_text(destination, text, UiConsts::STATS_DEF_VAL_X, UiConsts::STATS_DEF_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// SPD
	render_text(destination, "SPD:", UiConsts::STATS_SPD_TEXT_X, UiConsts::STATS_SPD_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.spd);
	render_text(destination, text, UiConsts::STATS_SPD_VAL_X, UiConsts::STATS_SPD_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FRes
	render_text(destination, "FRes:", UiConsts::STATS_FRES_TEXT_X, UiConsts::STATS_FRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.f_def);
	render_text(destination, text, UiConsts::STATS_FRES_VAL_X, UiConsts::STATS_FRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IRes
	render_text(destination, "IRes:", UiConsts::STATS_IRES_TEXT_X, UiConsts::STATS_IRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.i_def);
	render_text(destination, text, UiConsts::STATS_IRES_VAL_X, UiConsts::STATS_IRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// LRes
	render_text(destination, "LRes:", UiConsts::STATS_LRES_TEXT_X, UiConsts::STATS_LRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.l_def);
	render_text(destination, text, UiConsts::STATS_LRES_VAL_X, UiConsts::STATS_LRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FAtk
	render_text(destination, "FAtk:", UiConsts::STATS_FATK_TEXT_X, UiConsts::STATS_FATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.f_atk);
	render_text(destination, text, UiConsts::STATS_FATK_VAL_X, UiConsts::STATS_FATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IAtk
	render_text(destination, "IAtk:", UiConsts::STATS_IATK_TEXT_X, UiConsts::STATS_IATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.i_atk);
	render_text(destination, text, UiConsts::STATS_IATK_VAL_X, UiConsts::STATS_IATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FAtk
	render_text(destination, "LAtk:", UiConsts::STATS_LATK_TEXT_X, UiConsts::STATS_LATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.l_atk);
	render_text(destination, text, UiConsts::STATS_LATK_VAL_X, UiConsts::STATS_LATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FDmg
	render_text(destination, "FDmg:", UiConsts::STATS_FDMG_TEXT_X, UiConsts::STATS_FDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.f_dmg * 100));
	render_text(destination, text, UiConsts::STATS_FDMG_VAL_X, UiConsts::STATS_FDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IDmg
	render_text(destination, "IDmg:", UiConsts::STATS_IDMG_TEXT_X, UiConsts::STATS_IDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.i_dmg * 100));
	render_text(destination, text, UiConsts::STATS_IDMG_VAL_X, UiConsts::STATS_IDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// LDmg
	render_text(destination, "LDmg:", UiConsts::STATS_LDMG_TEXT_X, UiConsts::STATS_LDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.l_dmg * 100));
	render_text(destination, text, UiConsts::STATS_LDMG_VAL_X, UiConsts::STATS_LDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// ADmg
	render_text(destination, "ADmg:", UiConsts::STATS_ADMG_TEXT_X, UiConsts::STATS_ADMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.a_dmg * 100));
	render_text(destination, text, UiConsts::STATS_ADMG_VAL_X, UiConsts::STATS_ADMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// APT
	render_text(destination, "APT:", UiConsts::STATS_APT_TEXT_X, UiConsts::STATS_APT_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.apt);
	render_text(destination, text, UiConsts::STATS_APT_VAL_X, UiConsts::STATS_APT_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// Block
	render_text(destination, "Block:", UiConsts::STATS_BLOCK_TEXT_X, UiConsts::STATS_BLOCK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%.0f%%", (g_player.actual.block * 100));
	render_text(destination, text, UiConsts::STATS_BLOCK_VAL_X, UiConsts::STATS_BLOCK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);
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
		y_off = UiConsts::TEXT_AREA_STD_Y1 + UiConsts::TEXT_AREA_LINE_Y_OFFSET;
		if (lines_to_draw > size) {
			log_start = lines_to_draw - size;
		}
		else {
			log_start = 0;
		}
	}

	for(int idx = log_start; idx < lines_to_draw; ++idx) {
		render_text(destination, (char *)g_text_log.get_line(idx).c_str(),
					x_off, y_off + ((FontConsts::tiny_font_height + 1) * (idx-log_start)),
					FontConsts::FONT_YELLOW, FontConsts::FONT_TINY, FontConsts::TEXT_LEFT_JUSTIFIED);
	}
}

//------------------------------------------------------------------------------
// Render the world with the tile at screen position (0, 0) position equal to
// (maze_x, maze_y).
//
// Arguments:
//  destination - the bitmap to draw to
//  f - the dungeon floor to draw
//  maze_x, maze_y - the maze position corresponding to the upper left corner
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Render::render_world_at(BITMAP *destination, DungeonFloor *f, int maze_x, int maze_y) {
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
			bool carved_left = f->maze->is_carved(tile_to_render_x -1, tile_to_render_y);
			bool carved_up = f->maze->is_carved(tile_to_render_x, tile_to_render_y - 1);

			if(tile_to_render_x >=0 && tile_to_render_y >=0 && tile_to_render_x < f->maze->get_width() && tile_to_render_y < f->maze->get_height()) {
				int stairs = f->maze->stairs_here(tile_to_render_x, tile_to_render_y);
				// Before checking any other status, draw darkness if the square isn't lit
				if (f->maze->is_square_lit(tile_to_render_x, tile_to_render_y) == false) {
					// If the square has previously been seen and isn't carved, draw a darker wall
					if (f->maze->is_carved(tile_to_render_x, tile_to_render_y) == false && f->maze->was_seen(tile_to_render_x, tile_to_render_y) == true) {
						render_base_tile(destination, UiConsts::TILE_DARKER_WALL, g_dungeon.maze_id, screen_x, screen_y);
					} else {
						// Otherwise, draw darkness
						render_base_tile(destination, UiConsts::TILE_DARK, g_dungeon.maze_id, screen_x, screen_y);
					}
				}
				// Render stairs if present
				else if (stairs == MazeConsts::STAIRS_UP) {
					render_base_tile(destination, UiConsts::TILE_UP_STAIRS, g_dungeon.maze_id, screen_x, screen_y);
				}
				else if (stairs == MazeConsts::STAIRS_DOWN) {
					render_base_tile(destination, UiConsts::TILE_DOWN_STAIRS, g_dungeon.maze_id, screen_x, screen_y);
				}
				// Render floor if present.  There are 4 different floor tiles - one with no
				// highlighting and 3 with different types of highlighting
				// If the location is a wall, render that instead.
				else if (f->maze->is_carved(tile_to_render_x, tile_to_render_y) == true) {
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
					render_base_tile(destination, tile_to_use, g_dungeon.maze_id, screen_x, screen_y);
					// Get any items at the location and draw the first on the list
					int num_items_here = f->get_num_items_at(tile_to_render_x, tile_to_render_y);
					if (num_items_here > 0) {
						std::list<Item *> items = f->get_items_at(tile_to_render_x, tile_to_render_y);
						Item *it = items.back();
						int gid = get_tile_to_render(it);
						render_item(destination, gid, screen_x, screen_y);
					}
				} else {
					render_base_tile(destination, UiConsts::TILE_WALL, g_dungeon.maze_id, screen_x, screen_y);
				}
			} else {
				// Draw an empty space since it's outside of the map
				render_base_tile(destination, UiConsts::TILE_DARK, g_dungeon.maze_id, screen_x, screen_y);
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
//   f - the dungeon floor to render
//   maze_x, maze_y - the position of the maze at the player's current location
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_world_at_player(BITMAP *destination, DungeonFloor *f, int maze_x, int maze_y) {
	// Render the world with the tile at the player's position (7,6) equal to (maze_x, maze_y)
	render_world_at(destination, f, maze_x - UiConsts::PLAYER_PLAY_AREA_X, maze_y - UiConsts::PLAYER_PLAY_AREA_Y);
}

//----------------------------------------------------------------------------------
// Render the town (or a shop in it) with the tile at screen position (0, 0)
// position equal to (x, y).
//
// Arguments:
//   destination - the bitmap to draw to
//   x, y - the town position corresponding to the upper left part of the screen
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_town_at(BITMAP *destination, int x, int y) {
	int num_y_tiles;
	std::map<std::pair<int, int>, int>::iterator it;

	if (g_state_flags.text_log_extended) {
		num_y_tiles = UiConsts::PLAY_AREA_TILE_HEIGHT - UiConsts::TEXT_AREA_EXT_MAZE_ROWS_OBSCURED;
	}
	else {
		num_y_tiles = UiConsts::PLAY_AREA_TILE_HEIGHT;
	}

	int x_limit, y_limit, tile_block;
	unsigned short *tile_index_data;

	// Determine which data to use to draw, depending on where the player is
	if (g_state_flags.in_weapon_shop || g_state_flags.in_item_shop) {
		x_limit = TownConsts::SHOPS_WIDTH;
		y_limit = TownConsts::SHOPS_HEIGHT;
		tile_block = DAMRL_SHOP_TILES;
		tile_index_data = g_shops_tile_data;
	}
	else if (g_state_flags.in_museum) {
		x_limit = TownConsts::MUSEUM_WIDTH;
		y_limit = TownConsts::MUSEUM_HEIGHT;
		tile_block = DAMRL_SHOP_TILES;
		tile_index_data = g_museum_tile_data;
	}
	else {
		x_limit = TownConsts::TOWN_SIZE;
		y_limit = TownConsts::TOWN_SIZE;
		tile_block = DAMRL_TOWN_TILES;
		tile_index_data = g_town_tile_data;
	}

	for (int screen_x = 0; screen_x < UiConsts::PLAY_AREA_TILE_WIDTH; screen_x++) {
		for (int screen_y = 0; screen_y < num_y_tiles; screen_y++) {
			int tile_to_render_x = x + screen_x;
			int tile_to_render_y = y + screen_y;

			if (tile_to_render_x >=0 && tile_to_render_y >=0 && tile_to_render_x < x_limit && tile_to_render_y < y_limit) {
				int tile_index_to_render = tile_index_data[tile_to_render_y * x_limit + tile_to_render_x];
				int tile_offset_x = tile_index_to_render % UiConsts::TOWN_TILE_ENTRY_WIDTH;
				int tile_offset_y = tile_index_to_render / UiConsts::TOWN_TILE_ENTRY_WIDTH;

				blit((BITMAP *)g_game_data[tile_block].dat,
		     		destination,
	    	 		tile_offset_x * UiConsts::TILE_PIXEL_WIDTH,
		 			tile_offset_y * UiConsts::TILE_PIXEL_HEIGHT,
		 			screen_x * UiConsts::TILE_PIXEL_WIDTH,
 		 		 	screen_y * UiConsts::TILE_PIXEL_HEIGHT,
			 		UiConsts::TILE_PIXEL_WIDTH,
			 		UiConsts::TILE_PIXEL_HEIGHT);

				if (g_state_flags.in_museum) {
					it = g_museum_artifacts.find(std::make_pair(tile_to_render_x, tile_to_render_y));
					if (it != g_museum_artifacts.end() && g_active_artifacts[it->second] > 0) {
						int it_x = g_artifact_ids[it->second].gid % UiConsts::ITEM_TILE_ENTRY_WIDTH;
						int it_y = g_artifact_ids[it->second].gid / UiConsts::ITEM_TILE_ENTRY_WIDTH;
						masked_blit((BITMAP *)g_game_data[DAMRL_ITEMS].dat,
		     						 destination,
	    	 						 it_x * UiConsts::TILE_PIXEL_WIDTH,
		 							 it_y * UiConsts::TILE_PIXEL_HEIGHT,
		 							 screen_x * UiConsts::TILE_PIXEL_WIDTH,
 		 		 					 screen_y * UiConsts::TILE_PIXEL_HEIGHT - 1,  // Push it up just a bit
			 						 UiConsts::TILE_PIXEL_WIDTH,
			 						 UiConsts::TILE_PIXEL_HEIGHT);
					}
				}
			}
			else {
				// Draw darkness
				render_base_tile(destination, UiConsts::TILE_DARK, g_dungeon.maze_id, screen_x, screen_y);
			}
		}
	}

	// Draw the player
	render_player(destination);
}

//----------------------------------------------------------------------------------
// Equivalent to render_town_at, but renders using the player's location at the
// center of the play area (rather than (0, 0)) as the top left of the play area.
//
// Arguments:
//   destination - the bitmap to draw to
//   x, y - the position of town at the player's current location
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_town_at_player(BITMAP *destination, int x, int y) {
	render_town_at(destination, x - UiConsts::PLAYER_PLAY_AREA_X, y - UiConsts::PLAYER_PLAY_AREA_Y);
}

//----------------------------------------------------------------------------------
// Draws the dialog showing the base stats for the next generation of player
//
// Arguments:
//   destination - the bitmap to draw to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_death_dialog(BITMAP *destination) {
	char text[40];

	// The main window
	render_ui_box(destination, UiConsts::DEATH_SCREEN_X1, UiConsts::DEATH_SCREEN_Y1,
				   UiConsts::DEATH_SCREEN_X2, UiConsts::DEATH_SCREEN_Y2);

	// Initial paragraphs
	render_text(destination, "While *you* may be dead...", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P1_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
	render_text(destination, "...your adventure continues!", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P1_Y + 9,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
	render_text(destination, "Thanks to your artifacts,", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P2_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
	render_text(destination, "your heir will start with the", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P2_Y + 9,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
	render_text(destination, "following base stats:", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P2_Y + 18,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);

	// Stats
	// STR
	render_text(destination, "STR:", UiConsts::NEXT_GEN_STR_TEXT_X, UiConsts::NEXT_GEN_STR_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.str);
	render_text(destination, text, UiConsts::NEXT_GEN_STR_VAL_X, UiConsts::NEXT_GEN_STR_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// CON
	render_text(destination, "CON:", UiConsts::NEXT_GEN_CON_TEXT_X, UiConsts::NEXT_GEN_CON_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.con);
	render_text(destination, text, UiConsts::NEXT_GEN_CON_VAL_X, UiConsts::NEXT_GEN_CON_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// DEX
	render_text(destination, "DEX:", UiConsts::NEXT_GEN_DEX_TEXT_X, UiConsts::NEXT_GEN_DEX_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.dex);
	render_text(destination, text, UiConsts::NEXT_GEN_DEX_VAL_X, UiConsts::NEXT_GEN_DEX_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// ATK
	render_text(destination, "ATK:", UiConsts::NEXT_GEN_ATK_TEXT_X, UiConsts::NEXT_GEN_ATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.atk);
	render_text(destination, text, UiConsts::NEXT_GEN_ATK_VAL_X, UiConsts::NEXT_GEN_ATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// DEF
	render_text(destination, "DEF:", UiConsts::NEXT_GEN_DEF_TEXT_X, UiConsts::NEXT_GEN_DEF_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.def);
	render_text(destination, text, UiConsts::NEXT_GEN_DEF_VAL_X, UiConsts::NEXT_GEN_DEF_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// SPD
	render_text(destination, "SPD:", UiConsts::NEXT_GEN_SPD_TEXT_X, UiConsts::NEXT_GEN_SPD_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.spd);
	render_text(destination, text, UiConsts::NEXT_GEN_SPD_VAL_X, UiConsts::NEXT_GEN_SPD_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FRes
	render_text(destination, "FRes:", UiConsts::NEXT_GEN_FRES_TEXT_X, UiConsts::NEXT_GEN_FRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.f_def);
	render_text(destination, text, UiConsts::NEXT_GEN_FRES_VAL_X, UiConsts::NEXT_GEN_FRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IRes
	render_text(destination, "IRes:", UiConsts::NEXT_GEN_IRES_TEXT_X, UiConsts::NEXT_GEN_IRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.i_def);
	render_text(destination, text, UiConsts::NEXT_GEN_IRES_VAL_X, UiConsts::NEXT_GEN_IRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// LRes
	render_text(destination, "LRes:", UiConsts::NEXT_GEN_LRES_TEXT_X, UiConsts::NEXT_GEN_LRES_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.l_def);
	render_text(destination, text, UiConsts::NEXT_GEN_LRES_VAL_X, UiConsts::NEXT_GEN_LRES_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FAtk
	render_text(destination, "FAtk:", UiConsts::NEXT_GEN_FATK_TEXT_X, UiConsts::NEXT_GEN_FATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.f_atk);
	render_text(destination, text, UiConsts::NEXT_GEN_FATK_VAL_X, UiConsts::NEXT_GEN_FATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IAtk
	render_text(destination, "IAtk:", UiConsts::NEXT_GEN_IATK_TEXT_X, UiConsts::NEXT_GEN_IATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.i_atk);
	render_text(destination, text, UiConsts::NEXT_GEN_IATK_VAL_X, UiConsts::NEXT_GEN_IATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// LAtk
	render_text(destination, "LAtk:", UiConsts::NEXT_GEN_LATK_TEXT_X, UiConsts::NEXT_GEN_LATK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.l_atk);
	render_text(destination, text, UiConsts::NEXT_GEN_LATK_VAL_X, UiConsts::NEXT_GEN_LATK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FDmg
	render_text(destination, "FDmg:", UiConsts::NEXT_GEN_FDMG_TEXT_X, UiConsts::NEXT_GEN_FDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.f_dmg * 100));
	render_text(destination, text, UiConsts::NEXT_GEN_FDMG_VAL_X, UiConsts::NEXT_GEN_FDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// IDmg
	render_text(destination, "IDmg:", UiConsts::NEXT_GEN_IDMG_TEXT_X, UiConsts::NEXT_GEN_IDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.i_dmg * 100));
	render_text(destination, text, UiConsts::NEXT_GEN_IDMG_VAL_X, UiConsts::NEXT_GEN_IDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// FDmg
	render_text(destination, "LDmg:", UiConsts::NEXT_GEN_LDMG_TEXT_X, UiConsts::NEXT_GEN_LDMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.l_dmg * 100));
	render_text(destination, text, UiConsts::NEXT_GEN_LDMG_VAL_X, UiConsts::NEXT_GEN_LDMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// ADmg
	render_text(destination, "ADmg:", UiConsts::NEXT_GEN_ADMG_TEXT_X, UiConsts::NEXT_GEN_ADMG_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)(g_player.actual.a_dmg * 100));
	render_text(destination, text, UiConsts::NEXT_GEN_ADMG_VAL_X, UiConsts::NEXT_GEN_ADMG_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// APT
	render_text(destination, "APT:", UiConsts::NEXT_GEN_APT_TEXT_X, UiConsts::NEXT_GEN_APT_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.apt);
	render_text(destination, text, UiConsts::NEXT_GEN_APT_VAL_X, UiConsts::NEXT_GEN_APT_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// Block
	render_text(destination, "Block:", UiConsts::NEXT_GEN_BLOCK_TEXT_X, UiConsts::NEXT_GEN_BLOCK_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d%%", (int)g_player.actual.block);
	render_text(destination, text, UiConsts::NEXT_GEN_BLOCK_VAL_X, UiConsts::NEXT_GEN_BLOCK_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// Max HP
	render_text(destination, "Max HP:", UiConsts::NEXT_GEN_MAX_HP_TEXT_X, UiConsts::NEXT_GEN_MAX_HP_TEXT_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_LEFT_JUSTIFIED);
	sprintf(text, "%d", (int)g_player.actual.max_hp);
	render_text(destination, text, UiConsts::NEXT_GEN_MAX_HP_VAL_X, UiConsts::NEXT_GEN_MAX_HP_VAL_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_RIGHT_JUSTIFIED);

	// End text
	render_text(destination, "Press ENTER to be reborn!", UiConsts::DEATH_TEXT_X, UiConsts::DEATH_TEXT_P3_Y,
	            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
				FontConsts::TEXT_CENTERED);
}

//----------------------------------------------------------------------------------
// Draws the dialog showing the Hall of Champions
//
// Arguments:
//   destination - the bitmap to draw to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_hall_of_champions(BITMAP *destination) {
	// The main window
	render_ui_box(destination, UiConsts::HOC_SCREEN_X1, UiConsts::HOC_SCREEN_Y1,
				   UiConsts::HOC_SCREEN_X2, UiConsts::HOC_SCREEN_Y2);

	render_text(destination, "** Hall of Champions **", UiConsts::HOC_SCREEN_TITLE_X, UiConsts::HOC_SCREEN_TITLE_Y,
	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
			FontConsts::TEXT_CENTERED);

	render_text(destination, "Rank", UiConsts::HOC_RANK_HEADER_X, UiConsts::HOC_RANK_HEADER_Y,
	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
			FontConsts::TEXT_CENTERED);

	render_text(destination, "Name", UiConsts::HOC_NAME_HEADER_X, UiConsts::HOC_NAME_HEADER_Y,
	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
			FontConsts::TEXT_CENTERED);

	render_text(destination, "Time", UiConsts::HOC_TIME_HEADER_X, UiConsts::HOC_TIME_HEADER_Y,
	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
			FontConsts::TEXT_CENTERED);

	render_text(destination, "Gen", UiConsts::HOC_GEN_HEADER_X, UiConsts::HOC_GEN_HEADER_Y,
	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
			FontConsts::TEXT_CENTERED);

	for (int i = 0; i < UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES; ++i) {
		char val[10];
		int color;

		int offset = UiConsts::HOC_FIRST_ENTRY_Y + (i * UiConsts::HOC_ENTRY_Y_OFFSET);
		sprintf(val, "%d", (i + 1));
		render_text(destination, val, UiConsts::HOC_RANK_HEADER_X, offset,
		            FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
					FontConsts::TEXT_CENTERED);
		if (g_hall_of_champions[i].has_entry) {
			// Fill in the rest of the entry
			render_text(destination, (char *)g_hall_of_champions[i].name.c_str(), UiConsts::HOC_NAME_HEADER_X, offset,
		      	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
						FontConsts::TEXT_CENTERED);

			int hours = g_hall_of_champions[i].elapsed / 3600;
			int minutes = (g_hall_of_champions[i].elapsed - (hours * 3600)) / 60;
			int seconds = (g_hall_of_champions[i].elapsed - (hours * 3600)) % 60;
		    if (hours >= 1000)
    			sprintf(val, "999:59:59");
    		else if(hours >= 100)
    			sprintf(val, "%03d:%02d:%02d", hours, minutes, seconds);
  			else
    			sprintf(val, "%02d:%02d:%02d", hours, minutes, seconds);
			render_text(destination, val, UiConsts::HOC_TIME_HEADER_X, offset,
		      	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
						FontConsts::TEXT_CENTERED);

			sprintf(val, "%d", g_hall_of_champions[i].generation);
			render_text(destination, val, UiConsts::HOC_GEN_HEADER_X, offset,
		      	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
						FontConsts::TEXT_CENTERED);

			// Draw the brackets for the new entry (if needed)
			if (i == g_state_flags.hall_of_champions_ranking) {
				render_text(destination, ">>", UiConsts::HOC_LEFT_BRACKETS_X, offset,
			      	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
							FontConsts::TEXT_LEFT_JUSTIFIED);
				render_text(destination, "<<", UiConsts::HOC_RIGHT_BRACKETS_X, offset,
			      	        FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL,
							FontConsts::TEXT_LEFT_JUSTIFIED);

			}
		}
	}
}

//----------------------------------------------------------------------------------
// Draws the main portion of the title screen
//
// Arguments:
//   destination - the bitmap to draw to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_title_background(BITMAP *destination) {
	int tile_index_to_render;
	int tile_offset_x;
	int tile_offset_y;

	clear_to_color(destination, 16);

	// draw the main box
	render_ui_box(destination, UiConsts::TITLE_BOX_X1, UiConsts::TITLE_BOX_Y1,
	              UiConsts::TITLE_BOX_X2, UiConsts::TITLE_BOX_Y2);

	// Draw the borders for the interior box
	rect(destination, UiConsts::TITLE_BG_X - 1, UiConsts::TITLE_BG_Y - 1,
		 UiConsts::TITLE_BG_X2 + 1, UiConsts::TITLE_BG_Y2 + 1, 30);
	rect(destination, UiConsts::TITLE_BG_X - 2, UiConsts::TITLE_BG_Y - 2,
		 UiConsts::TITLE_BG_X2 + 2, UiConsts::TITLE_BG_Y2 + 2, 16);
	rect(destination, UiConsts::TITLE_BG_X - 3, UiConsts::TITLE_BG_Y - 3,
		 UiConsts::TITLE_BG_X2 + 3, UiConsts::TITLE_BG_Y2 + 3, 19);

	// Draw the copyright and press enter text
	render_text(destination, "Copyright 2025 Shaun Brandt / Holy Meatgoat Productions",
	            UiConsts::TITLE_COPYRIGHT_X, UiConsts::TITLE_COPYRIGHT_Y, FontConsts::FONT_YELLOW,
				FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	render_text(destination, "-- Press ENTER to play --",
	            UiConsts::TITLE_PRESS_ENTER_X, UiConsts::TITLE_PRESS_ENTER_Y, FontConsts::FONT_YELLOW,
				FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	// Draw the tiles inside the interior box
	for (int j = 0; j < UiConsts::TITLE_BG_TILE_HEIGHT; ++j) {
		for (int i = 0; i < UiConsts::TITLE_BG_TILE_WIDTH; ++i) {
			tile_index_to_render = g_town_tile_data[(j + UiConsts::TITLE_BG_TILE_Y) * TownConsts::TOWN_SIZE + i + UiConsts::TITLE_BG_TILE_X];
			tile_offset_x = tile_index_to_render % UiConsts::TOWN_TILE_ENTRY_WIDTH;
			tile_offset_y = tile_index_to_render / UiConsts::TOWN_TILE_ENTRY_WIDTH;
			blit((BITMAP *)g_game_data[DAMRL_TOWN_TILES].dat,
		     	 destination,
	    	 	 tile_offset_x * UiConsts::TILE_PIXEL_WIDTH,
		 		 tile_offset_y * UiConsts::TILE_PIXEL_HEIGHT,
		 		 UiConsts::TITLE_BG_X + (i * UiConsts::TILE_PIXEL_WIDTH),
 		 		 UiConsts::TITLE_BG_Y + (j * UiConsts::TILE_PIXEL_HEIGHT),
			 	 UiConsts::TILE_PIXEL_WIDTH,
			 	 UiConsts::TILE_PIXEL_HEIGHT);
		}
	}

	// Draw the title over that
	draw_sprite(destination, (BITMAP *)g_game_data[DAMRL_TITLE].dat, UiConsts::TITLE_NAME_X, UiConsts::TITLE_NAME_Y);

}

//----------------------------------------------------------------------------------
// Draws the exit game confirmation dialog
//
// Arguments:
//   destination - the bitmap to draw to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_confirm_exit_dialog(BITMAP *destination) {
	render_ui_box(destination, UiConsts::CONFIRM_EXIT_DIALOG_X1, UiConsts::CONFIRM_EXIT_DIALOG_Y1,
	              UiConsts::CONFIRM_EXIT_DIALOG_X2, UiConsts::CONFIRM_EXIT_DIALOG_Y2);

	// Render the text
	render_text(destination, "Are you sure you want",
	            UiConsts::CONFIRM_EXIT_TEXT_LINE_X, UiConsts::CONFIRM_EXIT_TEXT_LINE_1_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	render_text(destination, "to quit?",
	            UiConsts::CONFIRM_EXIT_TEXT_LINE_X, UiConsts::CONFIRM_EXIT_TEXT_LINE_2_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	render_text(destination, "(Game will be saved.)",
	            UiConsts::CONFIRM_EXIT_TEXT_LINE_X, UiConsts::CONFIRM_EXIT_TEXT_LINE_3_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	// Render the Yes/No options
	render_text(destination, "(Y)es",
	            UiConsts::CONFIRM_EXIT_YES_TEXT_X, UiConsts::CONFIRM_EXIT_OPTION_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	render_text(destination, "(N)o",
	            UiConsts::CONFIRM_EXIT_NO_TEXT_X, UiConsts::CONFIRM_EXIT_OPTION_TEXT_Y,
				FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

}

//----------------------------------------------------------------------------------
// Draws the title menu
//
// Arguments:
//   destination - the bitmap to draw to
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------------
void Render::render_title_menu(BITMAP *destination) {
	// Draw the menu box
	rectfill(destination, UiConsts::TITLE_MENU_BOX_X1, UiConsts::TITLE_MENU_BOX_Y1,
	         UiConsts::TITLE_MENU_BOX_X2, UiConsts::TITLE_MENU_BOX_Y2, 16);
	rect(destination, UiConsts::TITLE_MENU_BOX_X1 - 1, UiConsts::TITLE_MENU_BOX_Y1 - 1,
	         UiConsts::TITLE_MENU_BOX_X2 + 1, UiConsts::TITLE_MENU_BOX_Y2 + 1, 30);
	rect(destination, UiConsts::TITLE_MENU_BOX_X1 - 2, UiConsts::TITLE_MENU_BOX_Y1 - 2,
	         UiConsts::TITLE_MENU_BOX_X2 + 2, UiConsts::TITLE_MENU_BOX_Y2 + 2, 19);

	if (g_state_flags.cur_substate == TITLE_SUBSTATE_MENU) {
		// Draw the menu text
		render_text(destination, "New Legacy",
	            	UiConsts::TITLE_MENU_OPTIONS_X, UiConsts::TITLE_MENU_OPTIONS_Y, FontConsts::FONT_YELLOW,
					FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		// Pick the color to use for 'Continue Legacy' and 'Delete Legacy' options depending on whether the save file exists
		int color;
		if (slac_file_exists(SaveLoadConsts::save_file)) {
			color = FontConsts::FONT_YELLOW;
		}
		else {
			color = FontConsts::FONT_GRAY;
		}
		render_text(destination, "Continue Legacy",
	            	UiConsts::TITLE_MENU_OPTIONS_X, UiConsts::TITLE_MENU_OPTIONS_Y + UiConsts::TITLE_MENU_OPTION_Y_OFFSET,
					color, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "Delete Legacy",
	            	UiConsts::TITLE_MENU_OPTIONS_X, UiConsts::TITLE_MENU_OPTIONS_Y + (UiConsts::TITLE_MENU_OPTION_Y_OFFSET * 2),
					color, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

		// Draw the brackets by the selected menu options
		rectfill(destination, 101, 174, 111, 211, 16);
		rectfill(destination, 208, 174, 218, 211, 16);

		render_text(destination, ">>", UiConsts::TITLE_MENU_LEFT_BRACKET_X,
	            	UiConsts::TITLE_MENU_OPTIONS_Y + (g_state_flags.title_menu_index * UiConsts::TITLE_MENU_OPTION_Y_OFFSET),
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		// Draw the brackets by the selected menu options
		render_text(destination, "<<", UiConsts::TITLE_MENU_RIGHT_BRACKET_X,
	            	UiConsts::TITLE_MENU_OPTIONS_Y + (g_state_flags.title_menu_index * UiConsts::TITLE_MENU_OPTION_Y_OFFSET),
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	}
	else if(g_state_flags.cur_substate == TITLE_SUBSTATE_DELETE) {
		render_text(destination, "Are you sure that you",
	            	UiConsts::TITLE_MENU_CONFIRM_DELETE_X, UiConsts::TITLE_MENU_CONFIRM_DELETE_LINE_1_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "want to delete your",
	            	UiConsts::TITLE_MENU_CONFIRM_DELETE_X, UiConsts::TITLE_MENU_CONFIRM_DELETE_LINE_2_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "legacy PERMANENTLY?",
	            	UiConsts::TITLE_MENU_CONFIRM_DELETE_X, UiConsts::TITLE_MENU_CONFIRM_DELETE_LINE_3_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "(Y)es",
	            	UiConsts::TITLE_MENU_CONFIRM_DELETE_YES_X, UiConsts::TITLE_MENU_CONFIRM_DELETE_OPTION_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "(N)o",
	            	UiConsts::TITLE_MENU_CONFIRM_DELETE_NO_X, UiConsts::TITLE_MENU_CONFIRM_DELETE_OPTION_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	}
	else if (g_state_flags.cur_substate == TITLE_SUBSTATE_LEGACY_DELETED) {
		render_text(destination, "Your legacy has been",
	            	UiConsts::TITLE_MENU_ERASED_FOREVER_X, UiConsts::TITLE_MENU_ERASED_FOREVER_LINE_1_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "erased forever...",
	            	UiConsts::TITLE_MENU_ERASED_FOREVER_X, UiConsts::TITLE_MENU_ERASED_FOREVER_LINE_2_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "-- Press ENTER --",
	            	UiConsts::TITLE_MENU_ERASED_FOREVER_X, UiConsts::TITLE_MENU_ERASED_FOREVER_LINE_3_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	}
	else if (g_state_flags.cur_substate == TITLE_SUBSTATE_NEW) {
		render_text(destination, "Enter your name:",
	            	UiConsts::TITLE_MENU_NEW_X, UiConsts::TITLE_MENU_NEW_LINE_1_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "Press ENTER when done",
	            	UiConsts::TITLE_MENU_NEW_X, UiConsts::TITLE_MENU_NEW_LINE_2_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, g_state_flags.character_name,
	            	UiConsts::TITLE_MENU_NEW_X, UiConsts::TITLE_MENU_NEW_NAME_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);

	}
	else if (g_state_flags.cur_substate == TITLE_SUBSTATE_CONFIRM_EXIT) {
		render_text(destination, "Are you sure that you",
	            	UiConsts::TITLE_CONFIRM_EXIT_X, UiConsts::TITLE_CONFIRM_EXIT_LINE_1_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "want to exit to DOS?",
	            	UiConsts::TITLE_CONFIRM_EXIT_X, UiConsts::TITLE_CONFIRM_EXIT_LINE_2_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "(Y)es",
	            	UiConsts::TITLE_CONFIRM_EXIT_YES_TEXT_X, UiConsts::TITLE_CONFIRM_EXIT_OPTION_TEXT_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
		render_text(destination, "(N)o",
	            	UiConsts::TITLE_CONFIRM_EXIT_NO_TEXT_X, UiConsts::TITLE_CONFIRM_EXIT_OPTION_TEXT_Y,
					FontConsts::FONT_YELLOW, FontConsts::FONT_NARROW_PROPORTIONAL, FontConsts::TEXT_CENTERED);
	}
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
		case FontConsts::FONT_NARROW_PROPORTIONAL:
		case FontConsts::FONT_PROPORTIONAL:
		case FontConsts::FONT_TINY:
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
		case FontConsts::FONT_NARROW_PROPORTIONAL:
		case FontConsts::FONT_PROPORTIONAL:
			render_prop_text(dest, text, x_offset, y_pos, font_idx, style);
			break;
		case FontConsts::FONT_TINY:
			render_tiny_text(dest, text, x_offset, y_pos, font_idx);
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
		else if (style == FontConsts::FONT_PROPORTIONAL)
			width += (int)FontConsts::prop_font_width[offset] + 1;
		else
			width += (int)FontConsts::tiny_font_width[offset] + 1;
    	cur++;
	}

	return width;
}

//------------------------------------------------------------------------------
// Forces an on-screen update of everything
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void force_update_screen(void) {
	g_state_flags.update_maze_area = true;
	g_state_flags.update_text_dialog = true;
	g_state_flags.update_status_dialog = true;
	g_state_flags.update_status_hp_exp = true;
	g_state_flags.update_status_elapsed_time = true;
	g_state_flags.update_display = true;
	update_display();
}