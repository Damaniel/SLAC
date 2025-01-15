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
#ifndef __TOWN_H__
#define __TOWN_H__

#include "invntory.h"
#include <string>

typedef struct {
    int x;
    int y;
    std::string text;
} NPCInfoType;

typedef struct {
    short x;
    short y;
} ArtifactPos;

namespace TownConsts {
    // How many NPCs and signs that say something exist in town
    const int NUM_NPC_TEXTS = 28;

    // The Dusty Tunnels portal
    const int DUSTY_TUNNELS_X = 44;
    const int DUSTY_TUNNELS_Y = 14;

    // The Marble Halls portal
    const int MARBLE_HALLS_X = 4;
    const int MARBLE_HALLS_Y = 3;

    // The Crystal Depths portal
    const int CRYSTAL_DEPTHS_X = 44;
    const int CRYSTAL_DEPTHS_Y = 43;

    // The Marble Halls (locked) gate
    const int MARBLE_HALLS_GATE_X = 4;
    const int MARBLE_HALLS_GATE_Y = 5;

    // The Crystal Depths (locked) gate
    const int CRYSTAL_DEPTHS_GATE_X = 40;
    const int CRYSTAL_DEPTHS_GATE_Y = 38;

    // The Dusty Tunnels recall circle
    const int DT_RECALL_X = 45;
    const int DT_RECALL_Y = 19;

    // The Marble Halls recall circle
    const int MH_RECALL_X = 2;
    const int MH_RECALL_Y = 11;

    // The Crystal Depths recall circle
    const int CD_RECALL_X = 43;
    const int CD_RECALL_Y = 41;

    // The weapon shop
    const int WEAPON_SHOP_X = 32;
    const int WEAPON_SHOP_Y = 16;

    // The item shop
    const int ITEM_SHOP_X = 12;
    const int ITEM_SHOP_Y = 16;

    // The museum
    const int MUSEUM_X = 22;
    const int MUSEUM_Y = 12;

    // The length (and width) of the town in tiles
    const int TOWN_SIZE = 48;

    // The length and width of the museum
    const int MUSEUM_WIDTH = 21;
    const int MUSEUM_HEIGHT = 24;

    // The length and width of the item and weapon shops
    const int SHOPS_WIDTH = 9;
    const int SHOPS_HEIGHT = 20;

    // The y offset into the map for the upper left corner of each shop
    const int WEAPON_SHOP_Y_OFF = 0;
    const int ITEM_SHOP_Y_OFF = 14;

    // The square corresponding to the exit from the weapon shop
    const int WEAPON_SHOP_EXIT_X = 4;
    const int WEAPON_SHOP_EXIT_Y = 4;

    // The square corresponding to the exit from the item shop
    const int ITEM_SHOP_EXIT_X = 4;
    const int ITEM_SHOP_EXIT_Y = 18;

    // The square corresponding to the exit from the museum
    const int MUSEUM_EXIT_X = 10;
    const int MUSEUM_EXIT_Y = 22;

    // The square corresponding to the location where the soul
    // orb must be taken
    const int END_GAME_LOC_X = 2;
    const int END_GAME_LOC_Y = 40;

    // The location of the equipment shop NPC
    const int WEAPON_SHOP_NPC_X = 4;
    const int WEAPON_SHOP_NPC_Y = 2;

    // The location of the item shop NPC
    const int ITEM_SHOP_NPC_X = 4;
    const int ITEM_SHOP_NPC_Y = 16;

    // The tile id to draw when a gate is open
    const int UNLOCKED_GATE_TILE = 40;
}

extern const ArtifactPos g_museum_artifact_list[];
extern std::map<std::pair<int, int>, int> g_museum_artifacts;
extern std::vector<int> g_equipment_shop_item_values;
extern std::vector<int> g_item_shop_item_values;
extern std::vector<int> g_equipment_shop_item_sell_values;
extern std::vector<int> g_item_shop_item_sell_values;

void check_and_process_npc_here(int x, int y);
void check_and_process_town_entrances(int x, int y);
void check_for_active_area(int x, int y);
void enter_dungeon(int floor);
void unlock_dungeon(int dungeon, bool loading_save);
void init_museum_artifacts();
void populate_shop_inventory();

int get_item_price(Item *i);
int get_item_sell_price(Item *i);

#endif
