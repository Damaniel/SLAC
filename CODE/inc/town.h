#ifndef __TOWN_H__
#define __TOWN_H__

#include <string>

typedef struct {
    int x;
    int y;
    std::string text;
} NPCInfoType;

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

}

void check_and_process_npc_here(int x, int y);
void check_and_process_town_entrances(int x, int y);
void check_for_active_area(int x, int y);
void enter_dungeon(int floor);

#endif
