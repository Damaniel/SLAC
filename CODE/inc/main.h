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
#ifndef __MAIN_H__
#define __MAIN_H__

// The base frame rate for the game (updates and such)
const int FRAME_RATE = 20;

// States for the state machine god.
enum {
    STATE_LOGO_SCREEN,
    STATE_TITLE_SCREEN,
    STATE_MAIN_GAME,
    STATE_DEAD,
    STATE_HALL_OF_CHAMPIONS,
    STATE_EXIT
};

// Substates of the title screen state
enum {
    TITLE_SUBSTATE_DEFAULT,        // The main part of the title screen
    TITLE_SUBSTATE_MENU,           // The menu
    TITLE_SUBSTATE_NEW,            // When 'New Legacy' is selected
    TITLE_SUBSTATE_DELETE,         // When 'Delete Legacy' is selected
    TITLE_SUBSTATE_LEGACY_DELETED  // When the player confirms they want to delete
};

// Substates of the main game state.  The difference between a main state and a substate
// is that substates can only transition into other substates, and are generally associated
// with a primary state.  Since these are processed from the code that controls the main state 
// machine, the state handler should hand control off to the relevant substate functions
enum {
    GAME_SUBSTATE_DEFAULT,
    GAME_SUBSTATE_MAP,
    GAME_SUBSTATE_INVENTORY,
    GAME_SUBSTATE_INVENTORY_MENU,        // The item context menu
    GAME_SUBSTATE_USE_ON_ITEM,           // Used when selecting an item to use another item on 
    GAME_SUBSTATE_STATS,
    GAME_SUBSTATE_STORE,                 // In a shop in town           
    GAME_SUBSTATE_PLAYER_JUST_DIED,      // Player just hit 0 HP - allows a key to be pressed before transitioning
    GAME_SUBSTATE_HALL_OF_CHAMPIONS,
    GAME_SUBSTATE_CONFIRM_EXIT           // Displays the 'Are you sure you want to quit? menu'
};

enum {
    DUSTY_TUNNELS,
    MARBLE_HALLS,
    CRYSTAL_DEPTHS
};

// The maximum depth of each of the 3 dungeons
const int g_max_dungeon_depths[3] = {25, 50, 100};
const int g_dungeon_sizes[3] = {48, 48, 64};

void int_handler();
void init_game();
void shut_down_game();

#endif