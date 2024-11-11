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

// A collection of flags relevant to the game loop.  The game loop will want
// to farm tasks out to other functions; this provides a way to have them all
// in one place to make them easy to query, while keeping things manageable. 
struct StateFlags {
    // Graphics state
    bool update_display;        // Is the screen ready to be redrawn?
    bool map_displayed;         // Is the map currently on the screen?
    bool update_text_dialog;    // Should the text dialog be redrawn?
    bool update_status_dialog;  // Should the status display be redrawn?
    bool update_map_dialog;     // Should the map screen be redrawn?
    bool update_maze_area;      // Should the maze area be redrawn?
    
    // Input state
    bool input_disabled;      // Is keyboard input currently disabled?

    // Miscellaneous state
    bool exit_game;           // Did the player choose to exit the game?
};

#endif