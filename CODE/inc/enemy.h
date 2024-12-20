#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "globals.h"

namespace EnemyConsts {
    const int MAX_GENERATOR_REROLLS = 20;
    // Used in the generator function.  When rolling an enemy with a target elevel,
    // the actual elevel range considered will be 
    // (elevel - MIN_ELEVEL_RANGE) to (elevel + MAX_ELEVEL_RANGE), inclusive and
    // capped at 0 and 100 at each end.
    const int MIN_ELEVEL_RANGE = 15;
    const int MAX_ELEVEL_RANGE = 5;
}

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
    // positional
    int id;                     // The enemy id in the enemy definition array
    unsigned short x_pos;       // Position in the dungeon
    unsigned short y_pos;             
    int distance;               // The distance to the player (used for sorting and determining 
                                // which enemies to process on a turn)
    // stats
    unsigned short hp;          // The current enemy HP

    // behavior
    bool has_seen_player;       // Has the enemy seen the player before?
    bool is_pursuing_player;    // Is the enemy currently chasing the player?

    // Movement 
    int residual_action_points; // Any action points left over after their last executed turn

    // The other stats live in the enemy table, for now.
    // If we add the ability for skills to adjust enemy stats,
    // we'll add 'actual' status as needed
public:
    Enemy();
    Enemy(int eid);
    ~Enemy() { /*std::cout << "Deleting enemy..." << std::endl;*/ }
    void init(int eid);
    int get_hp() { return (int)hp; }
    int get_id() { return id; }
    void set_pos(int x, int y) { x_pos = x; y_pos = y; }
    int get_x_pos() { return x_pos; }
    int get_y_pos() { return y_pos; }
    int get_distance() { return distance; }
    void set_distance(int d) { distance = d; }
    int get_action_residual() { return residual_action_points; }
    void set_action_residual(int amount) { residual_action_points = amount; }
    bool has_seen_the_player() { return has_seen_player; }
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


#endif
