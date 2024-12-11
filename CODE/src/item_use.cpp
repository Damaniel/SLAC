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

#include "item_use.h"

//----------------------------------------------------------------------------
// Heals the player for a percentage (0-100) of their max HP
//
// Arguments:
//  percentage - a value from 0 to 100, representing the percentage of max HP
//               to heal
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void heal_player(int percentage)
{
    int amount = (int)(((float)percentage / 100) * g_player.actual.max_hp);
    int actual_healed, old_hp;

    char text[40];

    old_hp = g_player.hp;
    g_player.hp += amount;
    if (g_player.hp > (int)g_player.actual.max_hp) { 
        g_player.hp = (int)g_player.actual.max_hp;
        actual_healed = g_player.hp - old_hp;

    }
    else {
        actual_healed = amount;
    }

    sprintf(text, "You recover %d HP.", actual_healed);
    g_text_log.put_line(text);

    // Tell the game to update the HP region of the screen
    g_state_flags.update_status_hp_exp = true;
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Identifies the first inventory item that hasn't been identfied yet
//
// Arguments:
//   log - should the identified item be displayed in the log?
//
// Returns:
//   true if an item was identified, false otherwise.
//
// Notes:
//   This function checks from lowest inventory slot to highest.
//----------------------------------------------------------------------------
bool identify_item(bool log)
{
    Item *i;
    int count = 0;

    while (count < InventoryConsts::INVENTORY_SIZE) {
        i = g_inventory->get_item_in_slot(count);
        if (i != NULL) {
            if (!i->is_it_identified()) {
                perform_identification_action(i, log);
                return true;
            }
        }
        ++count;
    }
    return false;
}

//----------------------------------------------------------------------------
// Identifies all inventory items that haven't been identfied yet
//
// Arguments:
//   None
//
// Returns:
//   the number of items identified
//
// Notes:
//   This function checks from lowest inventory slot to highest.
//   It also just calls identify_item() iteratively until it returns false
//----------------------------------------------------------------------------
int identify_all(void)
{
    bool result;
    int count = 0;

    // The identify all scroll doesn't list each identified item;
    // it will just display a generic 'X items were identified'
    // message
    result = identify_item(false);
    if (result == false) {
        return count;
    }
    else {
        do {
            ++count;
            result = identify_item(false);
        } while (result == true);
    }
    return count;
}

//----------------------------------------------------------------------------
// Decurses the first item in the inventory that is cursed.
//
// Arguments:
//   log - should the decursed item be displayed in the log?
//
// Returns:
//   true if an item was decursed, false otherwise.
//
// Notes:
//   This function checks from lowest inventory slot to highest.
//----------------------------------------------------------------------------
bool decurse_item(bool log) 
{
    Item *i;
    int count = 0;
    char text[80];

    while (count < InventoryConsts::INVENTORY_SIZE) {
        i = g_inventory->get_item_in_slot(count);
        if (i != NULL) {
            if (!i->is_it_cursed()) {
                i->set_curse_state(false);
                if (log) {
                    sprintf(text, "%s was decursed.", i->get_full_name().c_str());
                    g_text_log.put_line(text);
                }
                return true;
            }
        }
        ++count;
    }
    return false;
}

//----------------------------------------------------------------------------
// Removes the curse from all cursed items
//
// Arguments:
//   None
//
// Returns:
//   the number of items decursed
//
// Notes:
//   This function checks from lowest inventory slot to highest.
//   It also just calls decurse_item() iteratively until it returns false
//----------------------------------------------------------------------------
int decurse_all() {
    bool result;
    int count = 0;

    // The identify all scroll doesn't list each identified item;
    // it will just display a generic 'X items were identified'
    // message
    result = decurse_item(false);
    if (result == false) {
        return count;
    }
    else {
        do {
            ++count;
            result = decurse_item(false);
        } while (result == true);
    }
    return count;

}

//----------------------------------------------------------------------------
// Performs the action of a teleport scroll (randomly moves the player to a 
// new location on the floor)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void teleport_player() {
    // Pick random spots in the dungeon until we find a spot that is:
    //  - At least 12 units away (by Manhattan distance)
    //  - Is an empty space
    //  - Is currently unoccupied by an enemy (TBD)
    //
    // Give up after 100 attempts in case we get stuck
    int distance;
    int new_x, new_y, count;
    bool done = false;

    count = 0;
    do {
        new_x = rand() % g_dungeon.width;
        new_y = rand() % g_dungeon.height;
        distance = get_manhattan_distance_between(g_player.get_x_pos(), g_player.get_y_pos(), new_x, new_y);
        if (distance >= 12) {
            // Check to see if the square is not a wall
            if (g_dungeon.maze->is_carved(new_x, new_y)) {
                // Do enemy check here
                done = true;
                //std::cout << "teleport_player: new location is " << new_x << ", " << new_y << std::endl;
            }
        }
        ++count;
    } while (!done && count < 100);

    // If we had to bail out, don't move the player
    if (count >= 100) {
        g_text_log.put_line("A strange force holds you in place.");
        return;
    }

    g_player.set_x_pos(new_x);
    g_player.set_y_pos(new_y);

    g_text_log.put_line("You are whisked away to somewhere new...");

    // Moving the portion of the map the player is on requires a lot of redrawing.
    // This includes the maze itself, plus the inventory screen (which is still 
    // visible since we're using an item), plus the text dialog if it's in extended
    // mode.
    g_state_flags.update_maze_area = true;
    g_state_flags.update_text_dialog = true;
    if(g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY || 
       g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
            if(g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
                g_state_flags.update_inventory_submenu = true;
            }
            g_state_flags.update_inventory_cursor = true;
            g_state_flags.update_inventory_description = true;
            g_state_flags.update_inventory_items = true;
    }
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Performs the action of a magic map scroll (lights every square in the 
// maze)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void expose_map() {
    for (int i=0; i < g_dungeon.maze->get_width(); ++i) {
        for (int j=0; j < g_dungeon.maze->get_height(); ++j) {
            g_dungeon.maze->change_lit_status_at(i, j, true);
        }
    }

    // Mark the maze as globally lit, so rooms don't darken when entering/
    // leaving them
    g_dungeon.maze->set_globally_lit_state(true);
    
    g_text_log.put_line("The walls of the dungeon are revealed.");

    // Lighting the maze requires a lot of redrawing.
    // This includes the maze itself, plus the inventory screen (which is still 
    // visible since we're using an item), plus the text dialog if it's in extended
    // mode.
    g_state_flags.update_maze_area = true;
    g_state_flags.update_text_dialog = true;
    if(g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY || 
       g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
            if(g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
                g_state_flags.update_inventory_submenu = true;
            }
            g_state_flags.update_inventory_cursor = true;
            g_state_flags.update_inventory_description = true;
            g_state_flags.update_inventory_items = true;
    }
    g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Performs the specific action for a particular type of potion based on its
// ID
//
// Arguments:
//   id - the id of the potion
//
// Returns:
//   nothing
//----------------------------------------------------------------------------
void use_potion_action(int id) {
    int count;
    bool result;
    char text[40];

    switch (id) {
        case ItemConsts::POT_OF_LIGHT_HEAL:     // Scroll of light healing
            heal_player(10);
            break;
        case ItemConsts::POT_OF_MOD_HEAL:     // scroll of healing
            heal_player(50);
            break;
        case ItemConsts::POT_OF_FULL_HEAL:     // scroll of full healing
            heal_player(100);
            break;
        case ItemConsts::POT_OF_CURE_POISON:
            if(g_player.is_poisoned) {
                g_player.is_poisoned = false;
                g_text_log.put_line("Your poison has lifted.");
                g_state_flags.update_status_dialog = true;
                g_state_flags.update_display = true;
            }
            else {
                g_text_log.put_line("Nothing happens.");
            }
            break;
        case ItemConsts::POT_OF_CURE_PARALYSIS:
        case ItemConsts::POT_OF_BERSERK_STR:
        case ItemConsts::POT_OF_SPEED:
        case ItemConsts::POT_OF_HARDINESS:
        case ItemConsts::POT_OF_EXTRA_ATTACKS:
        case ItemConsts::POT_OF_POISON:
        case ItemConsts::POT_OF_PARALYSIS:
            g_text_log.put_line("The potion has no effect (yet).");
            break;
        case ItemConsts::POT_OF_DEATH:
            g_player.hp = 0;
            g_text_log.put_line("You feel the touch of Death upon you.");
            break;        
        default:
            g_text_log.put_line("This potion shouldn't exist!");
            break;
    }
}

//----------------------------------------------------------------------------
// Performs the specific action for a particular type of scroll based on its
// ID
//
// Arguments:
//   id - the id of the scroll
//
// Returns:
//   nothing
//----------------------------------------------------------------------------
void use_scroll_action(int id) {
    int count;
    bool result;
    char text[40];

    switch (id) {
        case ItemConsts::SCROLL_OF_IDENT:     // Scroll of identify
            result = identify_item(true);
            if (result == false) {
                g_text_log.put_line("You have no unidentified items.");
            }
            break;
        case ItemConsts::SCROLL_OF_IDENT_ALL:     // scroll of identify all
            count = identify_all();
            sprintf(text, "%d items were identified.", count);
            g_text_log.put_line(text);
            break;
        case ItemConsts::SCROLL_OF_MAGIC_MAP:
            expose_map();
            break;
        case ItemConsts::SCROLL_OF_DECURSE:
            result = decurse_item(true);
            if (result == false) {
                g_text_log.put_line("You have no cursed items.");
            }
            break;
        case ItemConsts::SCROLL_OF_DECURSE_ALL:
            count = decurse_all();
            sprintf(text, "%d items were decursed.", count);
            g_text_log.put_line(text);
            break;
        case ItemConsts::SCROLL_OF_TELEPORT:
            teleport_player();
            break;
        case ItemConsts::SCROLL_OF_DISCOVERY:
        case ItemConsts::SCROLL_OF_RECALL:
            g_text_log.put_line("This scroll does nothing (yet).");
            break;

        default:
            g_text_log.put_line("This scroll shouldn't exist!");
            break;
    }
}