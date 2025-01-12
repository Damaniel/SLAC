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
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// Used for the Allegro definitions
#include <allegro.h>

// C++ includes
#include <vector>
#include <string>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <stack>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>

// Header for the datafile
#include "dat.h"

// Other includes
#include "town.h"
#include "input.h"
#include "textlog.h"
#include "invntory.h"
#include "player.h"
#include "enemy.h"
#include "itemgen.h"
#include "item_use.h"
#include "maze.h"
#include "utils.h"
#include "saveload.h"
#include "gen_data.h"
#include "render.h"
#include "main.h"

// The datafile - contains all sprite, font and sound data.
// -- Defined in main.cpp
extern DATAFILE *g_game_data;

// A memory buffer to render to - it will be blitted to the display in one shot.
// -- Defined in main.cpp
extern BITMAP   *g_back_buffer;

// -- Defined in main.cpp
extern Player 	  g_player;

// Flags that hold state of interest to the game loop.  Other objects exist to
// hold the state of things like the current maze, enemies, and such - these flags
// are used to track what elements to render on the current iteration of the game
// loop, what menus or screens should be displayed, whether keyboard input should
// be disabled by a dialog, and so on.
extern StateFlags   g_state_flags;

// Flags that hold the state of the game itself - whether the player has unlocked
// certain dungeons or beaten bosses, for example
extern GameFlags g_game_flags;

// Holds flags and functionality related to drawing the screen
extern Render g_render;

// Holds information about the current dungeon floor (the maze, ilevel, depth, etc)
extern DungeonFloor g_dungeon;

// Holds dynamic UI global information (like cursor positions and such)
extern UiGlobals g_ui_globals;

// Holds the hall of champions
extern HallOfChampionsEntry g_hall_of_champions[UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES];

// Static tile data (town, shops, etc)
extern unsigned short g_town_tile_data[TownConsts::TOWN_SIZE * TownConsts::TOWN_SIZE];
extern unsigned char g_town_movability[TownConsts::TOWN_SIZE * TownConsts::TOWN_SIZE];
extern unsigned short g_museum_tile_data[TownConsts::MUSEUM_WIDTH * TownConsts::MUSEUM_HEIGHT];
extern unsigned char g_museum_movability[TownConsts::MUSEUM_WIDTH * TownConsts::MUSEUM_HEIGHT];
extern unsigned short g_shops_tile_data[TownConsts::SHOPS_WIDTH * TownConsts::SHOPS_HEIGHT];
extern unsigned char g_shops_movability[TownConsts::SHOPS_WIDTH * TownConsts::SHOPS_HEIGHT];

#endif
