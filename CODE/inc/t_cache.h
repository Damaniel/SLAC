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
#ifndef __T_CACHE_H__
#define __T_CACHE_H__

struct TileCache;

#include "globals.h"
#include "render.h"

struct TileCache {
	bool valid;
	short old_tiles[UiConsts::PLAY_AREA_TILE_WIDTH][UiConsts::PLAY_AREA_TILE_HEIGHT];
	int old_x, old_y;
	short new_tiles[UiConsts::PLAY_AREA_TILE_WIDTH][UiConsts::PLAY_AREA_TILE_HEIGHT];
	int new_x, new_y;
	std::vector<std::pair<short, short> > dirty;

	// Functions
    TileCache();
	void initialize();
	void invalidate();
    void set_valid();
	void update(short tile_data[UiConsts::PLAY_AREA_TILE_WIDTH][UiConsts::PLAY_AREA_TILE_HEIGHT], int world_x, int world_y);
	std::pair<short, short>get_old_world_position(int screen_x, int screen_y);
	std::pair<short, short>get_new_world_position(int screen_x, int screen_y);
	std::pair<short, short>get_old_screen_position(int world_x, int world_y);
	std::pair<short, short>get_new_screen_position(int world_x, int world_y);
    void clear_dirty();
	void add_dirty(int world_x, int world_y);
	bool is_tile_same(int screen_x, int screen_y);
	bool is_old_location_on_screen(int world_x, int world_y);
    bool is_new_location_on_screen(int world_x, int world_y);
    void dump_old_tiles();
    void dump_new_tiles();
    void dump_dirty_squares();
};

#endif
