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
#ifndef __UTILS_H__
#define __UTILS_H__

#include "town.h"
#include "globals.h"

// Forward declaration for Render class
class Render;

// Utility structures
struct DungeonFloor {
    Maze *maze;                                                 // The maze itself
	std::map <std::pair<int, int>, std::list<Item*> > items;    // The items in the maze
	std::list<Enemy*> enemies;                                  // The enemies in the maze
    int maze_id;                                                // which maze we're in
    int depth;                                                  // The current depth
    int max_depth;                                              // The deepest floor allowed
    int ilevel;                                                 // The ilevel of the current floor
    int width;                                                  // The width of the dungeon floor
    int height;                                                 // The height of the dungeon floor
    int move_counter;                                           // Number of steps player has taken on this floor

    // Functions to add features to the maze
    void clear_lists();
    void add_enemy(int x, int y, Enemy *e);
	void generate_enemies(int min_enemies, int max_enemies);
    void spawn_boss_if_valid();
	void add_item(int x, int y, Item *i);
	void generate_items(int min_items, int max_items);
	std::list<Item *> get_items_at(int x, int y);
	void remove_item_from_end_at(int x, int y);
	int get_num_items_at(int x, int y);
    std::pair<int, int> get_random_position_for_enemy();
    int is_boss_alive_here();
};

typedef struct {
    bool has_entry;
    std::string name;
    unsigned long int elapsed;
    int generation;
} HallOfChampionsEntry;

namespace UtilConsts {
    // An enum to specify actors in the action queue
    const int ACTION_PLAYER = 0;
    const int ACTION_ENEMY = 1;
    const int ACTION_PLAYER_DEFER_SPEED = 2;
    const int ACTION_ENEMY_DEFER_SPEED = 3;

    // Only consider processing an enemy action if the player hasn't been
    // seen yet and is at least this close
    const int MAXIMUM_ENEMY_AI_DISTANCE_NEAR = 6;

    // Only consider processing an enemy action if the player has been
    // seen yet and is at least this close
    const int MAXIMUM_ENEMY_AI_DISTANCE_FAR  = 12;

    // Enemies further away than this will no longer pursue the player
    const int MAXIMUM_ENEMY_REMEMBER_DISTANCE = 16;

    // The odds that a single item will drop from an enemy
    // (this check is done once per potential item drop for an enemy that
    //  can drop multiple)
    const int CHANCE_OF_ENEMY_ITEM_DROP = 33;

    // A new enemy will be created (or at least attempted to be) once
    // this many player turns
    const int DUNGEON_ENEMY_GENERATE_TURNS = 100;

    // The number of attempts made to randomly add a new enemy to the
    // current dungeon floor
    const int DUNGEON_ENEMY_GENERATE_ATTEMPTS = 20;

    // The maximum number of enemies the new enemy generator will
    // allow in the enemy list before choosing not to generate another
    const int DUNGEON_MAX_ENEMIES = 70;

    // The number of bosses in the game; used for game flags
    const int NUM_BOSSES = 7;

    // The number of turns the player has to return Megalith's Soul Orb
    const int ORB_COUNTDOWN_TIME = 200;

    // The number of items in the Hall of Champions
    const int NUM_HALL_OF_CHAMPIONS_ENTRIES = 10;

    // The number of options (new, continue, delete) on the title menu
    const int NUM_TITLE_MENU_ENTRIES = 3;

    // The longest allowed character name
    const int MAX_CHARACTER_NAME_LENGTH = 10;

    // How long after a shop inventory is refreshed until it gets
    // deleted
    const int SHOP_RESET_TURNS = 1000;
}

// A collection of flags relevant to the game loop.  The game loop will want
// to farm tasks out to other functions; this provides a way to have them all
// in one place to make them easy to query, while keeping things manageable.
struct StateFlags {
    //--------------------------------------------------------------------------
    // State machine (states + substates)
    //--------------------------------------------------------------------------
    int  cur_state;
    int  prev_state;
    int  cur_substate;

    //--------------------------------------------------------------------------
    // Timer state
    //--------------------------------------------------------------------------
    volatile long int frame_counter;
    volatile int next_frame;

    //--------------------------------------------------------------------------
    // Graphics state
    //--------------------------------------------------------------------------
    bool update_display;                // Is the screen ready to be redrawn?

    // - title screen
    bool update_title_background;       // Update the background portion of the title screen
    bool update_title_menu;             // Update the menu and anything in it

    // - main screen dialogs
    bool update_text_dialog;            // Should the text dialog be redrawn?
    bool update_status_dialog;          // Should the status display be redrawn?
    bool update_maze_area;              // Should the maze area be redrawn?
    bool update_status_hp_exp;          // Should the HP/XP bars be updated?
    bool update_status_elapsed_time;    // Should the elapsed time be updated

    // - subscreen dialogs
    bool update_map_dialog;             // Should the map screen be redrawn?
    bool update_inventory_dialog;       // Should the inventory dialog be redrawn?
    bool update_shop_inventory_dialog;  // Should the shop inventory dialog be redrawn?

    // - inventory
    bool update_inventory_cursor;            // Should the inventory cursor be redrawn?
    bool update_inventory_description;       // Should the description area be redrawn?
    bool update_inventory_items;             // Should the inventory items be redrawn?
    bool update_inventory_submenu;           // Should the inventory submenu be redrawn?
    bool update_shop_inventory_cursor;       // Should the shop inventory cursor be redrawn?
    bool update_shop_inventory_description;  // Should the shop inventory description be redrawn?
    bool update_shop_inventory_items;        // Should the shop inventory items be redrawn?
    // - stats

    bool update_stats_screen;                // Should the stats screen be displayed

    //--------------------------------------------------------------------------
    // Other data
    //--------------------------------------------------------------------------

    // - game flags
    bool text_log_extended;  // Should we show the extended or standard text log

    // Note that many of the aspects of the game (input, inventory, etc) work
    // in a similar way both in and out of the dungeon, but there are differences:
    //  - Player can't attack things in town
    //  - Player can't drop things on the ground in town
    //  - (probably others I'll find along the way)
    bool in_dungeon;            // Is the player currently in the dungeon?

    // If the player is in town, they may be in one of the shops.  If so,
    // these flags will allow the game to render the shop areas instead of
    // the main town.  (Note that the shop behavior themselves will be managed
    // by a dedicated substate since the controls/actions are different;
    // this is mainly for rendering behavior)
    bool in_weapon_shop;
    bool in_item_shop;
    bool in_museum;
    bool is_shopping;

    // - control flags
    bool exit_game;           // Did the player choose to exit the game?
    bool loading_save;        // Is a save currently being loaded?

    // - hall of champions;
    int hall_of_champions_ranking;

    // - time flags
    int time_to_update_elapsed;  // How many frames until we increment the elapsed counter

    // - menu flags
    int title_menu_index;
    int new_game_char_text_index;

    // - shop flags
    bool weapon_shop_in_buy_mode;   // Is the buy or sell inventory displayed?
    bool item_shop_in_buy_mode;
    int  turns_until_weapon_shop_reset; // How many turns are left until the shops delete
    int  turns_until_item_shop_reset;   // their inventories

    // The temporary character name.  Will be copied to player name when ready
    char character_name[UtilConsts::MAX_CHARACTER_NAME_LENGTH + 1];

    // Flags related to state changes used by menus
    bool recently_died;
    bool save_loaded;

    // optimization flags
    int player_pos_dx;
    int player_pos_dy;

};

// A collection of flags related to game progression
struct GameFlags {
	bool can_enter_marble_halls;
	bool can_enter_crystal_depths;
    bool has_unlocked_marble_halls;
    bool has_unlocked_crystal_depths;
    bool has_defeated_bosses[UtilConsts::NUM_BOSSES];
    bool has_received_orb;
    int  orb_countdown_timer;
    bool has_finished_game;
    unsigned int elapsed_time;
    int generation;           // The current generation of player
    int max_ilevel;           // The maximum ilevel (based on dungeon/level) that
                              // this generation of player has attained
};

// Update functions
void update_main_game_display(void);
void update_display(void);

// String helper functions
std::string get_dungeon_name(int dungeon, bool abbrev);
std::string get_generation_string(int generation);

// Resource functions
int load_resources(void);
void init_resources(Render &r);
void unload_resources(void);
void reset_game_flags(void);

// Dungeon functions
void generate_new_dungeon_floor(DungeonFloor &d, int level, int stairs_from);
void use_stairs(int x, int y);
void exit_dungeon(bool used_recall);
void add_new_enemy_to_area();
void adjust_player_lighting_at(int x, int y);

// Text log functions
void add_items_at_player_to_log(void);
void describe_artifact(int artifact_id);

// State functions
void initialize_main_game_state(void);
void change_state(int new_state);
void display_hall_of_champions_log();
int get_hall_of_champions_ranking();

// Item functions
void pick_up_item_at(int x, int y);
void scramble_potion_icons(void);
void scramble_scroll_icons(void);
int roll_from_pool(const int *pool, int pool_size, int max_val);
void process_enemy_item_drop(Enemy *e);
int get_complete_artifact_quantity(int artifact_id);
void do_use_on_item(void);

// Miscellaneous enemy functions
void mark_boss_as_defeated(int id);

// Player stat calculation functions
void apply_modifier_value(ModifierMagType m, float *fixed, float *multiplicative, std::vector<ModifierMagType> &mods);
void apply_single_modifier(ModifierMagType m, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods);
void apply_item_values_to_stats(Item *i, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods);
void apply_mode_2_modifier_value(ModifierMagType m);

// Menu functions
void perform_inventory_menu_action(void);

// Game math functions
int get_diagonal_distance_between(int x1, int y1, int x2, int y2);
int get_manhattan_distance_between(int x1, int y1, int x2, int y2);
int get_distance_between(int x1, int y1, int x2, int y2);

// Action functions
void process_move(std::pair<int, int> proposed_location);
void process_town_move(std::pair<int, int> proposed_location);
void process_shop_move(std::pair<int, int> proposed_location);
void process_dungeon_move(std::pair<int, int> proposed_location);
void check_and_process_gates(int x, int y);
void check_for_active_area(int x, int y);
void process_orb_logic(void);
void process_shop_reset_logic(void);
void check_and_process_endgame(int x, int y);

#endif
