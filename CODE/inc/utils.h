#ifndef __UTILS_H__
#define __UTILS_H__

#include "globals.h"

// Utility structures
struct DungeonFloor {
    Maze *maze;
    int maze_id;        // which maze we're in
    int depth;          // The current depth
    int max_depth;      // The deepest floor allowed
    int ilevel;         // The ilevel of the current floor
    int width;          // The width of the dungeon floor
    int height;         // The height of the dungeon floor
};

// A collection of flags relevant to the game loop.  The game loop will want
// to farm tasks out to other functions; this provides a way to have them all
// in one place to make them easy to query, while keeping things manageable. 
struct StateFlags {
    // Overall state
    int  cur_state;
    int  prev_state;
    int  cur_substate;

    // Graphics state
    bool update_display;            // Is the screen ready to be redrawn?
    bool map_displayed;             // Is the map currently on the screen?
    bool update_text_dialog;        // Should the text dialog be redrawn?
    bool update_status_dialog;      // Should the status display be redrawn?
    bool update_map_dialog;         // Should the map screen be redrawn?
    bool update_maze_area;          // Should the maze area be redrawn?
    bool update_inventory_dialog;   // Should the inventory area be redrawn?

    // Render component state
    bool text_log_extended;  // Should we show the extended or standard text log

    // Miscellaneous state
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

// Text log functions
void add_items_at_player_to_log(void);

// State functions
void initialize_main_game_state(void);
void change_state(int new_state);

#endif