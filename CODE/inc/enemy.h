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
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "globals.h"

namespace EnemyConsts {
    // Used in the generator function.  When rolling an enemy with a target elevel,
    // the actual elevel range considered will be
    // (elevel * MIN_ELEVEL_RANGE) to (elevel * MAX_ELEVEL_RANGE), inclusive and
    // capped at 0 and 100 at each end.
    const float MIN_ELEVEL_RANGE = 0.5;
    const float MAX_ELEVEL_RANGE = 1.2;

    // The 'bosses'.  They're specifically generated on key floors if they haven't
    // already been defeated
    enum {
        PRANG_WAR_ELEPHANT,         // Floor 25, Dusty Tunnels
        STEENKEY_ELDER_NAGA,        // Floor 50, Dusty Tunnels
        NAMELESS_BLACK_ORC,         // Floor 50, Marble Halls
        GROZ_GOBLIN_KING,           // Floor 100, Marble Halls
        LORTROX_DRAGON_KNIGHT,      // Floor 50, Crystal Depths
        SILANT_ICE_GIANT,           // Floor 100, Crystal Depths
        MEGALITH_ARMORED_BEAST      // Floor 150, Crystal Depths
    };

    // Every index >= this is considered a boss, and is spawned uniquely
    const int BOSS_INDEX_OFFSET = 200;

    const int ID_PRANG_WAR_ELEPHANT = 200;
    const int ID_STEENKEY_ELDER_NAGA = 201;
    const int ID_NAMELESS_BLACK_ORC = 202;
    const int ID_GROZ_GOBLIN_KING = 203;
    const int ID_LORTROX_DRAGON_KNIGHT = 204;
    const int ID_SILANT_ICE_GIANT = 205;
    const int ID_MEGALITH_ARMORED_BEAST = 206;
}

typedef struct {
    // Ids for different things
    int id;         // Offset into the enemy array
    std::string name;
    int bid;        // An index into AI behavior types
    int gid;        // The tile index
    // Stats
    unsigned short hp;
    unsigned short str;
    unsigned short spd;
    unsigned short atk;
    unsigned short def;
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
    unsigned short ilevel;      // ilevel for item drops
    unsigned short rarity;      // relative rarity of the enemy
    unsigned short max_items;   // maximum items the enemy drops on kill
} EnemyType;

class Enemy {
private:
    // positional
    int id;                     // The enemy id in the enemy definition array
    unsigned short x_pos;       // Position in the dungeon
    unsigned short y_pos;
    int distance;               // The distance to the player (used for sorting and determining
                                // which enemies to process on a turn)
    // stats
    short hp;                   // The current enemy HP

    // behavior
    bool has_seen_player;       // Has the enemy seen the player before?
    bool is_pursuing_player;    // Is the enemy currently chasing the player?

    // Movement
    int residual_action_points; // Any action points left over after their last executed turn

    bool is_alive;              // Used to flag enemy for future deletion
    // The other stats live in the enemy table, for now.
    // If we add the ability for skills to adjust enemy stats,
    // we'll add 'actual' status as needed
public:
    Enemy();
    Enemy(int eid);
    ~Enemy() { /*std::cout << "Deleting enemy..." << std::endl;*/ }
    void init(int eid);
    int get_hp() { return (int)hp; }
    void set_hp(int val) { hp = val; }
    int get_id() { return id; }
    void set_pos(int x, int y) { x_pos = x; y_pos = y; }
    int get_x_pos() { return x_pos; }
    int get_y_pos() { return y_pos; }
    int get_distance() { return distance; }
    void set_distance(int d) { distance = d; }
    int get_action_residual() { return residual_action_points; }
    void set_action_residual(int amount) { residual_action_points = amount; }
    bool has_seen_the_player() { return has_seen_player; }
    bool is_it_alive() { return is_alive; }
    void mark_alive_status(bool status) { is_alive = status; }
    void mark_has_seen_player(bool status) { has_seen_player = status; }
    // All of these fields are stored in a global array; these helper functions
    // get the appropriate fields at the relevant offset
    std::string get_name();
    int get_gid();
    int get_bid();
    int get_max_hp();
    int get_str();
    int get_atk();
    int get_def();
    int get_spd();
    int get_apt();
    int get_fatk();
    int get_iatk();
    int get_latk();
    int get_fdef();
    int get_idef();
    int get_ldef();
    int get_exp();
    int get_elevel();
    int get_rarity();
    int get_ilevel();
    int get_max_items();
    bool check_if_can_see(int x, int y);
};

class EnemyGenerator {
public:
    static Enemy* generate();
    static Enemy* generate(int elevel);
    static Enemy* generate_arbitrary(int id);
};

bool enemy_distance_sort(Enemy *first, Enemy *second);
void sort_enemy_list(std::list<Enemy *> &el);
void get_enemy_distances(std::list<Enemy *> &el, int x, int y);
bool is_valid_enemy_position(int x, int y);
bool is_enemy_here(std::list<Enemy *> &el, int x, int y);
void perform_enemy_action(Enemy *e);
Enemy* get_enemy_at(std::list<Enemy *> &el, int x, int y);
void process_enemy_forgetting_player(std::list<Enemy *> &el);
void process_enemy_vision(std::list<Enemy *> &el);
void perform_enemy_combat(Enemy *e);
void delete_dead_enemies(std::list<Enemy *> &el);

#endif
