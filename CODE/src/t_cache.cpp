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
#include "t_cache.h"

TileCache::TileCache() {
    initialize();
}

void TileCache::initialize() {
    // Reset the tile cache positions
    old_x = 0;
    old_y = 0;
    new_x = 0;
    new_y = 0;
    // Reset the tile map data
    for (int i=0; i < UiConsts::PLAY_AREA_TILE_WIDTH; ++i) {
        for (int j = 0; j < UiConsts::PLAY_AREA_TILE_HEIGHT; ++j) {
            old_tiles[i][j] = -1;
            new_tiles[i][j] = UiConsts::TILE_DARK;
        }
    }

    // Remove any dirty squares
    clear_dirty();

    // Invalidate the cache
    invalidate();
}

void TileCache::invalidate() {
    valid = false;
}

void TileCache::set_valid() {
    valid = true;
}

void TileCache::update(short **tile_data, int world_x, int world_y) {
    old_x = new_x;
    old_y = new_y;
    new_x = world_x;
    new_y = world_y;
    for (int i = 0; i < UiConsts::PLAY_AREA_TILE_WIDTH; ++i) {
        for (int j = 0; j < UiConsts::PLAY_AREA_TILE_HEIGHT; ++j) {
            old_tiles[i][j] = new_tiles[i][j];
            new_tiles[i][j] = tile_data[i][j];
        }
    }
}

std::pair<short, short> TileCache::get_old_world_position(int screen_x, int screen_y) {
    return std::make_pair<short, short>(screen_x + old_x, screen_y + old_y);
}

std::pair<short, short> TileCache::get_new_world_position(int screen_x, int screen_y) {
    return std::make_pair<short, short>(screen_x + new_x, screen_y + new_y);
}

std::pair<short, short> TileCache::get_old_screen_position(int world_x, int world_y) {
    return std::make_pair<short, short>(world_x - old_x, world_y - old_y);
}

std::pair<short, short> TileCache::get_new_screen_position(int world_x, int world_y) {
    return std::make_pair<short, short>(world_x - new_x, world_y - new_y);
}

void TileCache::clear_dirty() {
    dirty.clear();
}

void TileCache::add_dirty(int world_x, int world_y) {
    dirty.push_back(std::make_pair<short, short>(world_x, world_y));
}

bool TileCache::is_tile_same(int screen_x, int screen_y) {
    return (old_tiles[screen_x][screen_y] == new_tiles[screen_x][screen_y]);
}

bool TileCache::is_old_location_on_screen(int world_x, int world_y) {
    int dx = world_x - old_x;
    int dy = world_y - old_y;
    if (dx < 0 || dy < 0 || dx >= UiConsts::PLAY_AREA_TILE_WIDTH || dy >= UiConsts::PLAY_AREA_TILE_HEIGHT)
        return false;
    return true;
}

bool TileCache::is_new_location_on_screen(int world_x, int world_y) {
    int dx = world_x - new_x;
    int dy = world_y - new_y;
    if (dx < 0 || dy < 0 || dx >= UiConsts::PLAY_AREA_TILE_WIDTH || dy >= UiConsts::PLAY_AREA_TILE_HEIGHT)
        return false;
    return true;
}

void TileCache::dump_old_tiles() {
    std::cout << "= old tile data ======================" << std::endl;
    std::cout << "World position at (0,0) is (" << old_x << ", " << old_y << ")" << std::endl;
    for (int j = 0; j < UiConsts::PLAY_AREA_TILE_HEIGHT; ++j) {
        for (int i = 0; i < UiConsts::PLAY_AREA_TILE_WIDTH; ++i) {
            std::cout << old_tiles[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "= end old tile data ==================" << std::endl;
}

void TileCache::dump_new_tiles() {
    std::cout << "= new tile data ======================" << std::endl;
    std::cout << "World position at (0,0) is (" << new_x << ", " << new_y << ")" << std::endl;
    for (int j = 0; j < UiConsts::PLAY_AREA_TILE_HEIGHT; ++j) {
        for (int i = 0; i < UiConsts::PLAY_AREA_TILE_WIDTH; ++i) {
            std::cout << new_tiles[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "= end new tile data ==================" << std::endl;
}

void TileCache::dump_dirty_squares() {
    std::cout << "= dirty square data ==================" << std::endl;
    if (dirty.size() > 0) {
        for (int i = 0; i < dirty.size(); ++i) {
            std::cout << "  (" << dirty[i].first << ", " << dirty[i].second << ")" << std::endl;
        }
    }
    else {
        std::cout << "  (No entries in the table)" << std::endl;
    }
    std::cout << "= end dirty square data ==============" << std::endl;

}
