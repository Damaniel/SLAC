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
#ifndef __MAIN_H__
#define __MAIN_H__

// States for the state machine god.  This is a first shot at some; there will
// be more.  He must feed.

enum {
    STATE_LOGO_SCREEN,
    STATE_TITLE_SCREEN,
    STATE_NEW_GAME,
    STATE_CONTINUE_GAME,
    STATE_MAIN_GAME,
    STATE_DEAD,
    STATE_EXIT
};

enum {
    GAME_SUBSTATE_DEFAULT,
    GAME_SUBSTATE_MAP,
    GAME_SUBSTATE_INVENTORY
};

enum {
    DUSTY_TUNNELS,
    MARBLE_HALLS,
    CRYSTAL_DEPTHS
};

// The maximum depth of each of the 3 dungeons
const int g_max_dungeon_depths[3] = {50, 100, 150};
const int g_dungeon_sizes[3] = {48, 48, 64};

#endif