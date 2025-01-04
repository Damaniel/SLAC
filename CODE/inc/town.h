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
}
#endif
