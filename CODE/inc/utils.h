#ifndef __UTILS_H__
#define __UTILS_H__

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

    // Functions to add features to the maze
    void clear_lists();
    void add_enemy(int x, int y, Enemy *e);
	void generate_enemies(int min_enemies, int max_enemies);
	void add_item(int x, int y, Item *i);
	void generate_items(int min_items, int max_items);
	std::list<Item *> get_items_at(int x, int y);
	void remove_item_from_end_at(int x, int y);
	int get_num_items_at(int x, int y);
};

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
    // Graphics state
    //--------------------------------------------------------------------------
    bool update_display;                // Is the screen ready to be redrawn?

    // - main screen dialogs
    bool update_text_dialog;            // Should the text dialog be redrawn?
    bool update_status_dialog;          // Should the status display be redrawn?
    bool update_maze_area;              // Should the maze area be redrawn?
    bool update_status_hp_exp;          // Should the HP/XP bars be updated?

    // - subscreen dialogs
    bool update_map_dialog;             // Should the map screen be redrawn?
    bool update_inventory_dialog;       // Should the inventory dialog be redrawn?
    
    // - inventory
    bool update_inventory_cursor;       // Should the inventory cursor be redrawn?
    bool update_inventory_description;  // Should the description area be redrawn?
    bool update_inventory_items;        // Should the inventory items be redrawn?
    bool update_inventory_submenu;      // Should the inventory submenu be redrawn?

    // - stats
    bool update_stats_screen;            // Should the stats screen be displayed

    //--------------------------------------------------------------------------
    // Other data
    //--------------------------------------------------------------------------

    // - game flags
    bool text_log_extended;  // Should we show the extended or standard text log

    // - control flags
    bool exit_game;           // Did the player choose to exit the game?
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

// Dungeon functions
void generate_new_dungeon_floor(DungeonFloor &d, int level, int stairs_from);
void use_stairs(int x, int y);

// Text log functions
void add_items_at_player_to_log(void);

// State functions
void initialize_main_game_state(void);
void change_state(int new_state);

// Item functions
void pick_up_item_at(int x, int y);
void process_equip(Item *i);
void process_unequip(Item *i);
void apply_modifier_value(ModifierMagType m, float *fixed, float *multiplicative, std::vector<ModifierMagType> &mods);
void apply_single_modifier(ModifierMagType m, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods);
void apply_item_values_to_stats(Item *i, Stats *fixed, Stats *multiplicative, std::vector<ModifierMagType> &mods);
void apply_mode_2_modifier_value(ModifierMagType m);
void drop_item_at(Item *i, int x, int y);
void scramble_potion_icons(void);
void scramble_scroll_icons(void);
int get_tile_to_render(Item *i);
void identify_previously_known_items_at_player();
void identify_if_previously_known(Item *i);
void perform_identification_action(Item *i, bool log);
int roll_from_pool(const int *pool, int pool_size, int max_val);

// Inventory functions
void perform_inventory_menu_action(void);

// Game math functions
int get_diagonal_distance_between(int x1, int y1, int x2, int y2);
int get_manhattan_distance_between(int x1, int y1, int x2, int y2);
int get_distance_between(int x1, int y1, int x2, int y2);

// Enemy functions
bool enemy_distance_sort(Enemy *first, Enemy *second);
void sort_enemy_list(std::list<Enemy *> &el);
void get_enemy_distances(std::list<Enemy *> &el, int x, int y);
bool is_valid_enemy_position(int x, int y);
bool is_enemy_here(std::list<Enemy *> &el, int x, int y);

// Search functions
void update_enemy_position(Enemy *e);

#endif
