#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "globals.h"

typedef struct {
    // Ids for different things
    int id;         // Offset into the enemy array
    std::string name;
    int gid;        // The tile index
    int bid;        // An index into AI behavior types
    // Stats
    unsigned short hp;
    unsigned short str;
    unsigned short atk;
    unsigned short def;
    unsigned short spd;
    unsigned short apt;
    unsigned short f_atk;       // Elemental attack
    unsigned short i_atk;
    unsigned short l_atk;
    unsigned short f_def;       // Elemental resist
    unsigned short i_def;
    unsigned short l_def;
    // rewards
    unsigned short exp;         // Experience on kill
    unsigned short elevel;      // enemy level (for average dungeon floor)
    unsigned short rarity;      // relative rarity of the enemy
    unsigned short ilevel;      // ilevel for item drops
    unsigned short max_items;   // maximum items the enemy drops on kill
} EnemyType;

class Enemy {
private:
    int id;                   // The enemy id in the enemy definition array
    unsigned short x_pos;     // Position in the dungeon
    unsigned short y_pos;             
    int distance;             // The distance to the player (used for sorting and determining 
                              // which enemies to process on a turn)
    // stats
    unsigned short hp;        // The current enemy HP

    // The other stats live in the enemy table, for now.
    // If we add the ability for skills to adjust enemy stats,
    // we'll add 'actual' status as needed
};

#endif
