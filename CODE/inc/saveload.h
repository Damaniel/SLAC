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
#ifndef __SAVELOAD_H__
#define __SAVELOAD_H__

namespace SaveLoadConsts {
    const int FILE_VERSION = 0x01;

    const int PLAYER_DATA_OFFSET = 128;
    const int INVENTORY_DATA_OFFSET = 409;
    const int ARTIFACT_DATA_OFFSET = 14381;
    const int DUNGEON_DATA_OFFSET = 14665;
    const int GAME_FLAGS_OFFSET = 14693;
    const int POTION_SCRAMBLINGS_OFFSET = 14727;
    const int SCROLL_SCRAMBLINGS_OFFSET = 14771;
    const int ID_POTIONS_OFFSET = 14819;
    const int ID_SCROLLS_OFFSET = 14833;
}

int write_initial_header(FILE *f);
int write_player_data(FILE *f);
int write_inventory_data(FILE *f);
int write_artifact_data(FILE *f);
int write_dungeon_data(FILE *f);
int write_game_flags(FILE *f);
int write_potion_scramble_data(FILE *f);
int write_scroll_scramble_data(FILE *f);
int write_identified_potions(FILE *f);
int write_identified_scrolls(FILE *f);

bool load_game(std::string filename);
bool save_game(std::string filename);

#endif