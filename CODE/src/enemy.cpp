//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2024 Shaun Brandt / Holy Meatgoat Software
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
#include "globals.h"

Enemy::Enemy() {
    init(0);        // Just use a default value
}

Enemy::Enemy(int eid) {
    init(eid);
}

void Enemy::init(int eid) {
    id = eid;
    hp = get_max_hp();
    x_pos = 0;
    y_pos = 0;
    distance = 0;
}

//----------------------------------------------------------------------------
// Looks up the name of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's name
//----------------------------------------------------------------------------
std::string Enemy::get_name() { 
    return g_enemy_ids[id].name; 
}

//----------------------------------------------------------------------------
// Looks up the GID/tile ID of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's gid
//----------------------------------------------------------------------------
int Enemy::get_gid() { 
    return g_enemy_ids[id].gid; 
}

//----------------------------------------------------------------------------
// Looks up the AI behavior ID of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's bid
//----------------------------------------------------------------------------
int Enemy::get_bid() { 
    return g_enemy_ids[id].bid; 
}

//----------------------------------------------------------------------------
// Looks up the max HP of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's max HP
//----------------------------------------------------------------------------
int Enemy::get_max_hp() { 
    return g_enemy_ids[id].hp; 
}

//----------------------------------------------------------------------------
// Looks up the STR of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's STR
//----------------------------------------------------------------------------
int Enemy::get_str() { 
    return g_enemy_ids[id].str; 
}

//----------------------------------------------------------------------------
// Looks up the ATK of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's ATK
//----------------------------------------------------------------------------
int Enemy::get_atk() { 
    return g_enemy_ids[id].atk; 
}

//----------------------------------------------------------------------------
// Looks up the DEF of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's DEF
//----------------------------------------------------------------------------
int Enemy::get_def() { 
    return g_enemy_ids[id].def; 
}

//----------------------------------------------------------------------------
// Looks up the speed of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's SPD
//----------------------------------------------------------------------------
int Enemy::get_spd() { 
    return g_enemy_ids[id].spd; 
}

//----------------------------------------------------------------------------
// Looks up the attacks per turn of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's APT
//----------------------------------------------------------------------------
int Enemy::get_apt() { 
    return g_enemy_ids[id].apt; 
}

//----------------------------------------------------------------------------
// Looks up the fire attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's FATK
//----------------------------------------------------------------------------
int Enemy::get_fatk() { 
    return g_enemy_ids[id].f_atk; 
}

//----------------------------------------------------------------------------
// Looks up the ice attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's IATK
//----------------------------------------------------------------------------
int Enemy::get_iatk() { 
    return g_enemy_ids[id].i_atk; 
}

//----------------------------------------------------------------------------
// Looks up the lightning attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's LATK
//----------------------------------------------------------------------------
int Enemy::get_latk() { 
    return g_enemy_ids[id].l_atk; 
}

//----------------------------------------------------------------------------
// Looks up the fire resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's FDEF
//----------------------------------------------------------------------------
int Enemy::get_fdef() { 
    return g_enemy_ids[id].f_def; 
}

//----------------------------------------------------------------------------
// Looks up the ice resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's IDEF
//----------------------------------------------------------------------------
int Enemy::get_idef() { 
    return g_enemy_ids[id].i_def; 
}

//----------------------------------------------------------------------------
// Looks up the lightning resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's LDEF
//----------------------------------------------------------------------------
int Enemy::get_ldef() { 
    return g_enemy_ids[id].l_def; 
}

//----------------------------------------------------------------------------
// Looks up the experience given on defeat of the enemy in the enemy 
// lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's EXP
//----------------------------------------------------------------------------
int Enemy::get_exp() { 
    return g_enemy_ids[id].exp; 
}

//----------------------------------------------------------------------------
// Looks up the enemy level of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's elevel
//
// Notes:
//   elevel is similar to the idea of ilevel for items - the deeper in the 
//   dungeon, the higher elevel of monsters that can spawn.
//----------------------------------------------------------------------------
int Enemy::get_elevel() { 
    return g_enemy_ids[id].elevel; 
}

//----------------------------------------------------------------------------
// Looks up the rarity of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's rarity (255=most common, 1=most rare)
//----------------------------------------------------------------------------
int Enemy::get_rarity() { 
    return g_enemy_ids[id].rarity; 
}

//----------------------------------------------------------------------------
// Looks up the ilevel of drops from the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's ilevel
//----------------------------------------------------------------------------
int Enemy::get_ilevel() { 
    return g_enemy_ids[id].ilevel; 
}

//----------------------------------------------------------------------------
// Looks up the maximum items the enemy can drop on kill in the enemy 
// lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's maximum number of item drops
//----------------------------------------------------------------------------
int Enemy::get_max_items() { 
    return g_enemy_ids[id].max_items; 
}

//----------------------------------------------------------------------------
// Generates an enemy.  This can be any enemy in the game.
//
// Arguments:
//   None
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate() {
    return generate(100);       // Generate an enemy of max level
}

//----------------------------------------------------------------------------
// Generates an enemy based on the specified elevel
//
// Arguments:
//   elevel - the elevel of the enemy to generate
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate(int elevel) {

    Enemy *e = new Enemy();
    bool done = false;
    int count = 0;
    int id = 0;
    int elevel_low = elevel - EnemyConsts::MIN_ELEVEL_RANGE;
    int elevel_high = elevel + EnemyConsts::MAX_ELEVEL_RANGE;

    // Ensure the range of elevels falls between 0 and 100
    if (elevel_low < 0 )
        elevel_low = 0;
    if (elevel_high >= 100) 
        elevel_high = 100;

    // Loop until we've found an enemy
    do {
        id = roll_from_pool(g_enemy_pool, g_enemy_pool_count, g_enemy_pool_entries);
        if (g_enemy_ids[id].elevel >= elevel_low && g_enemy_ids[id].elevel <= elevel_high)
            done = true;
        ++count;
    } while (!done && count < EnemyConsts::MAX_GENERATOR_REROLLS);

    // Initialize the enemy with the appropriate stats (mainly HP) for the selected enemy
    e->init(id);

    return e;
}

//----------------------------------------------------------------------------
// Generates an enemy of the specified ID (rather than a random one)
//
// Arguments:
//   id - the id of the enemy to generate
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate_arbitrary(int id) {
    Enemy *e = new Enemy(id);
    return e;
}