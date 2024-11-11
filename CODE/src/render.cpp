//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2021 Shaun Brandt / Holy Meatgoat Software
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
#include <allegro.h>
#include <vector>
#include <cstdio>
#include "globals.h"
#include "render.h"

//==================================================================================
// Constructors
//==================================================================================
Render::Render() {

}

//==================================================================================
// Private methods
//==================================================================================

//----------------------------------------------------------------------------------
// render_actors
//
// Renders all non-static dungeon elements.  This includes the player and all
// enemies.  
//
// Notes:
//   maze_x and maze_y represent the maze tile position in the upper left corner of 
//   the play area
//----------------------------------------------------------------------------------
void Render::render_actors(BITMAP *destination, int maze_x, int maze_y) {
	BITMAP *bpc = (BITMAP *)g_game_data[DAMRL_PLAYER_SPRITES].dat;
	// For now, just draw the player
	masked_blit(bpc, destination, PLAYER_TILE_OFFSET * TILE_PIXEL_WIDTH, 0, 
	            PLAYER_PLAY_AREA_X * TILE_PIXEL_WIDTH, PLAYER_PLAY_AREA_Y * TILE_PIXEL_HEIGHT,
		        TILE_PIXEL_WIDTH, TILE_PIXEL_HEIGHT);
}

//----------------------------------------------------------------------------------
// render_base_tile
//
// Draws the specified base tile (that is, wall, floor, or darkness) at the tile
// location (x,y) relative to the top of the play area
//----------------------------------------------------------------------------------
void Render::render_base_tile(BITMAP *destination, int tileId, int x, int y) {
	blit((BITMAP *)g_game_data[DAMRL_MAZE_BASE_TILES_1].dat, 
	     destination,
	     tileId * TILE_PIXEL_WIDTH, 
		 0, 
		 x * TILE_PIXEL_WIDTH,
		 y * TILE_PIXEL_HEIGHT,
		 TILE_PIXEL_WIDTH,
		 TILE_PIXEL_HEIGHT);	
}

//----------------------------------------------------------------------------------
// render_statics
//
// Renders all non-actor, non-architectural dungeon elements.  This includes 
// items, traps, money, doors, and so on.
//
// Notes:
//   maze_x and maze_y represent the maze tile position in the upper left corner of 
//   the play area
//----------------------------------------------------------------------------------
void Render::render_statics(BITMAP *destination, int maze_x, int maze_y) {
	
}

//==================================================================================
// Public methods
//==================================================================================

//----------------------------------------------------------------------------------
// initialize_map_bitmap
//
// Clears the entire backround of the map area to the 'fog of war' color.
// Called every time the player enters a new maze.
//
// I could cheat and just blit the fog of war color, but for now I want to do it
// the same way that the update map function does.
//----------------------------------------------------------------------------------
void Render::initialize_map_bitmap(Maze m) {
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
    map_maze_xoffset = MAP_AREA_VMEM_X + ((m.get_width() / 2) + 1) * MAP_DOT_WIDTH;
	map_maze_yoffset = MAP_AREA_VMEM_Y + ((m.get_height() / 2) + 1) * MAP_DOT_HEIGHT;
}

//----------------------------------------------------------------------------------
// add_area_to_map_bitmap
//
// Debug function (for now).  TODO: investigate a better way to do this
//
// Adds small squares to the map bitmap corresponding to the area in the 
// immediate vicinity of the location specified by (x, y)
//
// Notes:
//   This method will probably change dramatically since many features are 
//   missing and this function can be pretty slow.
//  
//   - Currently, walls and floors will be redrawn even if they've been drawn 
//     previously - keeping track of what's already done can reduce the blitting
//   - xOff and yOff should be precomputed somewhere since it only changes once
//     per generated maze
//   - A 3x3 area centered on the player is always used.  The player may have
//     a larger light radius than that
//   - Non-player static objects (like items and stairs) aren't currently drawn
//
//----------------------------------------------------------------------------------
void Render::add_area_to_map_bitmap(Maze m, int x, int y) {
	for(int i=x-1; i<=x+1; i++) {
		for(int j=y-1; j<=y+1; j++) {
			if(i >=0 && i < m.get_width() && j >=0 && j < m.get_height()) {
				if (m.is_carved(i, j) == false) {
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

	// If the player is in a room and hasn't been in the room before, 
	// draw the room to the map area
	int room = m.get_room_id_at(x, y);
	if(room != -1) {
		Room r = m.get_room(room);
		if (r.hasBeenEntered == false) {
			for(int i = r.x - 1; i < r.x + r.w + 1; i++) {
				for (int j = r.y - 1; j < r.y + r.h + 1; j++) {
					if(m.is_carved(i, j) == false) {
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
	}
}

//----------------------------------------------------------------------------------
// copy_data_to_offscreen_vram
//
// Takes any bitmap data that we plan to stuff in unused video RAM and load it
// into a free spot
//
// Notes:
//   The only bitmap data being put into video memory right now is the map dialog.
//   The map will be constructed as the player explores, and by doing this as 
//   exploration occurs, there's no need to generate it at the time the map is
//   displayed (which would be a very slow operation).
//----------------------------------------------------------------------------------
void Render::copy_data_to_offscreen_vram(void) {
	BITMAP *b = (BITMAP *)g_game_data[DAMRL_MAIN_MAP].dat;	
	blit(b, screen, 0, 0, MAP_VMEM_X, MAP_VMEM_Y, MAP_VMEM_WIDTH, MAP_VMEM_HEIGHT);
}

//----------------------------------------------------------------------------------
// render_fixed_text
//
// Writes a string to the screen in the specified location using the specified color
// using a fixed width font.
//
// Notes: 
//   The font bitmap contains all characters in the ASCII range 32-128.  To find the
//   correct offset into the bitmap, the ASCII value needs to be subtracted by 32.
//----------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------
// render_map
//
// Displays the map dialog in the play area.
//
// Notes: 
//   The map dialog is stored in otherwise unused VGA memory.
//----------------------------------------------------------------------------------
void Render::render_map(BITMAP *destination, Maze m) {

	// Blit the base map
	blit(screen, destination, MAP_VMEM_X, MAP_VMEM_Y, MAP_X_POS, MAP_Y_POS, 
	     MAP_VMEM_WIDTH, MAP_VMEM_HEIGHT);

	// Draw the player's position on the map
	blit((BITMAP *)g_game_data[DAMRL_MAP_DOTS].dat, 
	     destination, 
         MAP_DOT_PLAYER*MAP_DOT_WIDTH,
		 0, 
		 map_maze_xoffset + (g_player.x_pos*MAP_DOT_WIDTH),
		 map_maze_yoffset + (g_player.y_pos*MAP_DOT_HEIGHT), 
		 MAP_DOT_WIDTH,MAP_DOT_HEIGHT);

	// TODO - Draw actual relevant text.  Needs game state to do this.
	render_fixed_text(destination, "Cave 1", 55, 30, FONT_YELLOW);
	render_fixed_text(destination, "Floor 3", 130, 30, FONT_YELLOW);
	render_fixed_text(destination, "X:25", 74, 171, FONT_YELLOW);
	render_fixed_text(destination, "Y:18", 137, 171, FONT_YELLOW);
}

//----------------------------------------------------------------------------------
// render_prop_text
//
// Writes a string to the screen in the specified location using the specified color
// using a proportional font.
//
// Notes: 
//   The font bitmap contains all characters in the ASCII range 32-128.  To find the
//   correct offset into the bitmap, the ASCII value needs to be subtracted by 32.
//----------------------------------------------------------------------------------
void Render::render_prop_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx) {
	int x = x_pos;
	int y = y_pos;
	int offset;
	char *cur = text;

	while (*cur != 0) {
		offset = (*cur++) - 32;
		masked_blit((BITMAP *)g_game_data[DAMRL_PROP_FONT].dat, destination, prop_font_offset[offset],
		     font_idx * prop_font_height, x, y, prop_font_width[offset], prop_font_height);
		x += prop_font_width[offset] + 1;
	}
}

//----------------------------------------------------------------------------------
// render_status_base
//
// Draws the status background graphic to the screen.
//----------------------------------------------------------------------------------
void Render::render_status_base(BITMAP *destination) {
	BITMAP *b = (BITMAP *)g_game_data[DAMRL_MAIN_STATUS].dat;
	blit(b, destination, 0, 0, STATUS_AREA_X, STATUS_AREA_Y, b->w, b->h);
}

//----------------------------------------------------------------------------------
// render_text_base
//
// Draws the text area graphic to the screen.
//
// Note:
//   If extended is true, the larger extended text dialog will be used.
//----------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------
// render_world_at
//
// Render the world with the tile at screen position (0, 0) position equal to (maze_x, maze_y).  
//
// Notes:
//   Negative values for maze_x and maze_y are allowed, as are values outside of the 
//   positive end of the range - maze tiles just won't be drawn for invalid locations	
//   Also note that the code that draws the floor (that is, where is_carved == true),
//   checks tiles to the left and above it when deciding what to draw.  There isn't 
//   any check done to see if those tiles are valid, but the default Maze class will 
//   always have a valid tile to the left and above any carved tile, so this shouldn't
//   cause a problem.  If weird crashes happen, try looking here.
//----------------------------------------------------------------------------------
void Render::render_world_at(BITMAP *destination, Maze m, int maze_x, int maze_y) {
	for (int screen_x = 0; screen_x < PLAY_AREA_TILE_WIDTH; screen_x++) {
		for (int screen_y = 0; screen_y < PLAY_AREA_TILE_HEIGHT; screen_y++) {
			int tile_to_render_x = maze_x + screen_x;
			int tile_to_render_y = maze_y + screen_y;
			int tileToUse;
			bool carvedLeft = m.is_carved(tile_to_render_x -1, tile_to_render_y);
			bool carvedUp = m.is_carved(tile_to_render_x, tile_to_render_y - 1);
			
			if(tile_to_render_x >=0 && tile_to_render_y >=0 && tile_to_render_x < m.get_width() && tile_to_render_y < m.get_height()) {
				int stairs = m.stairs_here(tile_to_render_x, tile_to_render_y);				
				// Before checking any other status, draw darkness if the square isn't lit
				if (m.is_square_lit(tile_to_render_x, tile_to_render_y) == false) { 
					// If the square has previously been seen and isn't carved, draw a darker wall
					if (m.is_carved(tile_to_render_x, tile_to_render_y) == false && m.was_seen(tile_to_render_x, tile_to_render_y) == true) {
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
				else if (m.is_carved(tile_to_render_x, tile_to_render_y) == true) {
					if (carvedLeft == false && carvedUp == true) {
						tileToUse = TILE_FLOOR_LEFT_HIGHLIGHT;
					}
					else if (carvedLeft == true && carvedUp == false) {
						tileToUse = TILE_FLOOR_TOP_HIGHLIGHT;
					}
					else if (carvedLeft == false && carvedUp == false) {
						tileToUse = TILE_FLOOR_BOTH_HIGHLIGHT;
					}
					else {
						tileToUse = TILE_FLOOR;
					}
					render_base_tile(destination, tileToUse, screen_x, screen_y);
				} else {
					render_base_tile(destination, TILE_WALL, screen_x, screen_y);
				}		
			} else {
				// Draw an empty space since it's outside of the map
				render_base_tile(destination, TILE_DARK, screen_x, screen_y);
			}						 
		}
	}
	
	// Render the other world components
	render_statics(destination, maze_x, maze_y);
	render_actors(destination, maze_x, maze_y);
}

//----------------------------------------------------------------------------------
// render_world_at_player
//
// Equivalent to render_world_at, but renders using the player's location as the
// center of the play area rather than (0, 0) as the top left of the play area.
// This way, all rendering is done relative to the player, who sits in a fixed
// location on the screen.
//----------------------------------------------------------------------------------
void Render::render_world_at_player(BITMAP *destination, Maze m, int maze_x, int maze_y) {
	// Render the world with the tile at the player's position (7,6) equal to (maze_x, maze_y)
	render_world_at(destination, m, maze_x - PLAYER_PLAY_AREA_X, maze_y - PLAYER_PLAY_AREA_Y);
}