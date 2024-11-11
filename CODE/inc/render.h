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
#ifndef __RENDER_H__
#define __RENDER_H__

// System includes
#include <allegro.h>

// Game-specific includes
#include "globals.h"
#include "maze.h"

// Number of characters defined in each instance of a font
#define FONT_ENTRIES       96

// A copy of the map bitmap is stored at this location in video memory.
#define MAP_VMEM_X	0
#define MAP_VMEM_Y	480

// The size of the map bitmap in offscreen memory
#define MAP_VMEM_WIDTH   144
#define MAP_VMEM_HEIGHT  160

#define MAP_X_POS		  48
#define MAP_Y_POS		  24

// The offset of the actual map portion of the map screen stored in offscreen
// memory
#define MAP_AREA_VMEM_X  (MAP_VMEM_X + 7)
#define MAP_AREA_VMEM_Y  (MAP_VMEM_Y + 16)

//  The size of a dungeon tile in pixels
#define TILE_PIXEL_WIDTH		  16
#define TILE_PIXEL_HEIGHT	      16

// The size of the visible play area (in tiles)
// PLAY_AREA_TILE_HEIGHT_EXT measures the height in tiles when the extended message
// log is displayed.
#define PLAY_AREA_TILE_WIDTH   		15
#define PLAY_AREA_TILE_HEIGHT  		13
#define PLAY_AREA_TILE_HEIGHT_EXT	10

// The location on the screen (in pixels) where the status area is placed
#define STATUS_AREA_X			   240
#define STATUS_AREA_Y				 0

// The location on the screen (in pixels) where the normal text area is placed
#define TEXT_AREA_STD_X			     0
#define TEXT_AREA_STD_Y			   208

// The location on the screen (in pixels) where the extended text area is placed
#define TEXT_AREA_EXT_X              0
#define TEXT_AREA_EXT_Y			   160

// The offset (in tiles) into the player graphic where the player is.  
// TODO: This will eventually include different characters, but this one is a placeholder.
#define PLAYER_TILE_OFFSET			 9

// The offset (in tiles) into the play area where the player graphic is placed.  The player
// will always be centered in the play area.
#define PLAYER_PLAY_AREA_X			 7
#define PLAYER_PLAY_AREA_Y			 6

// The size (in pixels) of a single map dot.
#define MAP_DOT_WIDTH				 2
#define MAP_DOT_HEIGHT				 2

// The maximum width and height of the map area in dots. This is the maximum
// amount of displayable area inside the map.  Currently, the maze can be
// no larger than these values below, but can be smaller.
#define MAP_NUM_X_DOTS				64
#define MAP_NUM_Y_DOTS				64

// Each font has 5 different versions in different colors.  These are used to grab the correct
// color font from the bitmaps
enum {
	FONT_YELLOW,
	FONT_BLUE,
	FONT_GREEN,
	FONT_RED,
	FONT_GRAY
};

// The base tiles that make up the fixed portions of a dungeon level
// They map to tile offsets in the dungeon world tiles
enum {
	TILE_DARK,
	TILE_DARKER_WALL,
	TILE_WALL,
	TILE_FLOOR,
	TILE_FLOOR_TOP_HIGHLIGHT,
	TILE_FLOOR_LEFT_HIGHLIGHT,
	TILE_FLOOR_BOTH_HIGHLIGHT,
	TILE_UP_STAIRS,
	TILE_DOWN_STAIRS,
	TILE_DOOR
};

// An enum containing entries for each of the 16 colors of 'map dots' sitting
// in the datafile.  Some of them aren't used on the minimap, but those that
// are will have a name describing what they're used for (for example, 
// MAP_DOT_FLOOR is used for unoccupied floor spaces)
enum {
	MAP_DOT_FLOOR,
	MAP_DOT_FOG_OF_WAR,
	MAP_DOT_2,
	MAP_DOT_3,
	MAP_DOT_4,
	MAP_DOT_UP_STAIRS,
	MAP_DOT_DOWN_STAIRS,
	MAP_DOT_7,
	MAP_DOT_8,
	MAP_DOT_9,
	MAP_DOT_PLAYER,
	MAP_DOT_11,
	MAP_DOT_12,
	MAP_DOT_13,
	MAP_DOT_14,
	MAP_DOT_WALL
};

// Width and height of all characters from ASCII values 32 to 127 in the standard 
// proportional font
const int prop_font_width[FONT_ENTRIES] = {
	6, 2, 6, 7, 6, 6, 7, 2, 4, 4, 5, 5, 2, 6, 2, 6, 
	7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 5, 6, 5, 6, 
	8, 8, 7, 7, 7, 7, 7, 7, 8, 4, 7, 8, 7, 8, 8, 7, 
	7, 7, 8, 7, 6, 8, 8, 8, 8, 8, 6, 4, 6, 4, 5, 8, 
	3, 7, 7, 6, 7, 6, 5, 7, 8, 4, 6, 7, 4, 8, 8, 6, 
	7, 7, 7, 6, 4, 7, 8, 7, 6, 6, 6, 4, 2, 4, 7, 7  
};
const int prop_font_height = 8;

// Offsets into the font bitmap for each character (based on the character widths
// defined in prop_font_width)
const int prop_font_offset[FONT_ENTRIES] = {
	0,    6,    8,  14,  21,  27,  33,  40,  42,  46,  50,  55,  60,  62,  68,  70, 
	76,  83,   87,  94, 101, 108, 115, 122, 129, 136, 143, 145, 147, 152, 158, 163, 
	169, 177, 185, 192, 199, 206, 213, 220, 227, 235, 239, 246, 254, 261, 269, 277,
	284, 291, 298, 306, 313, 319, 327, 335, 343, 351, 359, 365, 369, 375, 379, 384, 
	392, 395, 402, 409, 415, 422, 428, 433, 440, 448, 452, 458, 465, 469, 477, 485, 
	491, 498, 505, 512, 518, 522, 529, 537, 544, 550, 556, 562, 566, 568, 572, 579
};	

// Width and height of all characters in the standard fixed font
const int fixed_font_width = 8;
const int fixed_font_height = 8;

//----------------------------------------------------------------------------
// Render class definition
//----------------------------------------------------------------------------
class Render {
	private:	
		// Used to center the maze inside the map region
		int map_maze_xoffset;
		int map_maze_yoffset;

		void render_actors(BITMAP *destination, int maze_x, int maze_y);
		void render_base_tile(BITMAP *destination, int tileId, int x, int y);
		void render_statics(BITMAP *destination, int maze_x, int maze_y);
		
	public:
		Render();
		void initialize_map_bitmap(Maze m);
		void add_area_to_map_bitmap(Maze m, int x, int y);
		void copy_data_to_offscreen_vram(void);		
		void render_fixed_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx);		
		void render_map(BITMAP *destination, Maze m);		
		void render_prop_text(BITMAP *destination, char *text, int x_pos, int y_pos, int font_idx);
		void render_status_base(BITMAP *destination);		
		void render_text_base(BITMAP *destination, bool extended);		
		void render_world_at(BITMAP *destination, Maze m, int maze_x, int maze_y);
		void render_world_at_player(BITMAP *destination, Maze m, int maze_x, int maze_y);
};
 
#endif	
	
	
	
	