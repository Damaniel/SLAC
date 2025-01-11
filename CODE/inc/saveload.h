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

    // The save file format uses fixed field sizes for everything
    // in version 1, so the offsets are fixed and known.
    // In future versions, if these values need to become dynamic,
    // they'll cease to be constants.
    const int PLAYER_DATA_OFFSET = 128;
    const int INVENTORY_DATA_OFFSET = 409;
    const int ARTIFACT_DATA_OFFSET = 14285;
    const int DUNGEON_DATA_OFFSET = 14569;
    const int GAME_FLAGS_OFFSET = 14597;
    const int POTION_SCRAMBLINGS_OFFSET = 14631;
    const int SCROLL_SCRAMBLINGS_OFFSET = 14675;
    const int ID_POTIONS_OFFSET = 14723;
    const int ID_SCROLLS_OFFSET = 14737;

    const int INVENTORY_ITEM_SIZE = 289;
}

void equip_items_back_on_player(int *slots);
void create_item_from_save_data(FILE *f, int slot);
bool finish_other_load_tasks(void);

bool process_player_data(FILE *f, int *slots);
bool process_inventory_data(FILE *f);
bool process_artifact_data(FILE *f);
bool process_dungeon_data(FILE *f);
bool process_game_flags(FILE *f);
bool process_potion_scramble_data(FILE *f);
bool process_scroll_scramble_data(FILE *f);
bool process_ided_potion_data(FILE *f);
bool process_ided_scroll_data(FILE *f);
bool finish_other_load_tasks(void);

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