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

#include "item_use.h"

//----------------------------------------------------------------------------
// Heals the player for an amount of their HP
//
// Arguments:
//  amount - the amount to heal
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void heal_player(int amount)
{
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
// Identifies the item
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
	int slot = g_ui_globals.inv_use_on_cursor_y * UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_use_on_cursor_x;
    Item *i = g_inventory->get_item_in_slot(slot);

    if (i != NULL) {
        if (!i->is_identified) {
            perform_identification_action(i, log);
            return true;
        }
        else {
            return false;
        }
    }
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
	int slot = g_ui_globals.inv_use_on_cursor_y * UiConsts::INVENTORY_ITEMS_PER_ROW + g_ui_globals.inv_use_on_cursor_x;
    Item *i = g_inventory->get_item_in_slot(slot);
    char text[80];

    if (i != NULL) {
        if (i->is_cursed) {
            i->is_cursed = false;
            if (log) {
                sprintf(text, "%s was decursed.", i->get_full_name().c_str());
                g_text_log.put_line(text);
            }
            return true;
        }
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

    // The decurse all scroll doesn't list each decursed item;
    // it will just display a generic 'X items were decursed'
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
// Sets a collection of screen update flags needed when updating the state
// of the maze while in the item screen (as is the case for a few different
// scrolls)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void item_use_update_screen_flags() {
    g_state_flags.update_maze_area = true;
    g_state_flags.update_text_dialog = true;
    if(g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY ||
       g_state_flags.cur_substate == GAME_SUBSTATE_INVENTORY_MENU) {
            // Don't actually update the inventory menu since the
            // item may be gone and the state will be reverted back
            // to SUBSTATE_INVENTORY shortly
            g_state_flags.update_inventory_cursor = true;
            g_state_flags.update_inventory_description = true;
            g_state_flags.update_inventory_items = true;
    }
    g_state_flags.update_display = true;
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
        distance = get_diagonal_distance_between(g_player.get_x_pos(), g_player.get_y_pos(), new_x, new_y);
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

    // If the player was teleported into a room, light it
	int room_id = g_dungeon.maze->get_room_id_at(g_player.get_x_pos(), g_player.get_y_pos());
	g_player.set_last_room_entered(room_id);
	if (room_id != -1) {
		//g_dungeon.maze->change_room_lit_status(room_id, false);
		g_dungeon.maze->change_room_lit_status(room_id, true);
	}

    g_text_log.put_line("You are whisked away to somewhere new...");

    // Update everything needed to ensure the tile cache is up to date and that
    // lighting is correct
    update_lighting();
    item_use_update_screen_flags();
    force_update_screen();

}

//----------------------------------------------------------------------------
// Performs the action of a magic map scroll (marks every square in the
// maze as seen, as if the player had walked through each square)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void expose_map() {
    // Mark all carved space in the maze, and each square immediately adjacent
    for (int i=0; i < g_dungeon.maze->get_width(); ++i) {
        for (int j=0; j < g_dungeon.maze->get_height(); ++j) {
            if (g_dungeon.maze->is_carved(i, j)) {
                g_dungeon.maze->mark_seen_state(i-1, j-1, true);
                g_dungeon.maze->mark_seen_state(i, j-1, true);
                g_dungeon.maze->mark_seen_state(i+1, j-1, true);
                g_dungeon.maze->mark_seen_state(i-1, j, true);
                g_dungeon.maze->mark_seen_state(i, j, true);
                g_dungeon.maze->mark_seen_state(i+1, j, true);
                g_dungeon.maze->mark_seen_state(i-1, j+1, true);
                g_dungeon.maze->mark_seen_state(i, j+1, true);
                g_dungeon.maze->mark_seen_state(i+1, j+1, true);
            }
        }
    }

    // Draw it all on the map
    g_render.fill_in_entire_map(&g_dungeon);

    g_text_log.put_line("The walls of the dungeon are revealed.");

    item_use_update_screen_flags();
}

//----------------------------------------------------------------------------
// Performs the action of a darkness scroll
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void darken_area() {
    // A darkness scroll should:
    // If in a room
    //   - Darken the room you're in
    //   - Mark the room as unseen
    // If not in a room
    //   - mark the spaces around the player (5x5) as unseen
    g_text_log.put_line("The darken scroll does nothing yet.");
}

//----------------------------------------------------------------------------
// Performs the action of a forget area scroll (darkens every square in the
// maze) and forgets it
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void hide_map() {
    int room;
    // for every square in the maze
    for (int i=0; i < g_dungeon.maze->get_width(); ++i) {
        for (int j=0; j < g_dungeon.maze->get_height(); ++j) {
            // darken the square
            g_dungeon.maze->change_lit_status_at(i, j, false);
            // mark as unseen
            g_dungeon.maze->mark_seen_state(i, j, false);
            // mark the room corresponding to this square (if there is one)
            // as unentered.
            room = g_dungeon.maze->get_room_id_at(i, j);
            if (room != -1) {
                g_dungeon.maze->set_room_entered_state(room, false);
            }
        }
    }

    // Clear the map bitmap
    g_render.initialize_map_bitmap(&g_dungeon);

    g_text_log.put_line("The dungeon is engulfed in darkness.");

    item_use_update_screen_flags();
}

//----------------------------------------------------------------------------
// Performs the action of a recall scroll (starts a counter that will return
// the player to the surface when it reaches 0)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void activate_recall(void) {
    if (g_player.recall_active) {
        g_player.recall_active = false;
        g_player.recall_count = 0;
        g_text_log.put_line("The energy pulling you to the surface subsides.");
        return;
    }
    else {
        if (g_state_flags.in_dungeon) {
            g_player.recall_active = true;
            g_player.recall_floor = g_dungeon.depth;
            g_player.recall_count = (rand() % (ItemConsts::RECALL_SCROLL_MAX_TURNS - ItemConsts::RECALL_SCROLL_MIN_TURNS)) +
                                    ItemConsts::RECALL_SCROLL_MIN_TURNS;
            g_text_log.put_line("Magical energy starts to tug you toward the surface...");
        }
        else {
            g_text_log.put_line("This scroll does nothing here.");
        }
    }
}

//----------------------------------------------------------------------------
// Performs the action of a summon item scroll (generating an item at the
// player's feet)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void summon_item(int additional) {
    int ilevel = g_dungeon.ilevel + additional;
    if (ilevel > 100)
        ilevel = 100;

    Item *i = ItemGenerator::generate(ilevel);
    g_dungeon.add_item(g_player.get_x_pos(), g_player.get_y_pos(), i);

    // Show the new item in the log
    add_items_at_player_to_log();

    // Update the screen
	g_state_flags.update_maze_area = true;
    g_state_flags.update_text_dialog = true;
	g_state_flags.update_display = true;
}

//----------------------------------------------------------------------------
// Performs the action of a curse scroll (cursing the first uncursed item
// in the inventory that can be cursed)
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
bool curse_item(void) {
    Item *i;
    int count = 0;

    while (count < InventoryConsts::INVENTORY_SIZE) {
        i = g_inventory->get_item_in_slot(count);
        if (i != NULL) {
            if (i->can_be_cursed && !i->is_cursed) {
                i->is_cursed = true;
                g_text_log.put_line("Your " + i->get_full_name() + " has been cursed!");
                return true;
            }
        }
        ++count;
    }

    return false;
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
            heal_player(50);
            break;
        case ItemConsts::POT_OF_MOD_HEAL:     // scroll of healing
            heal_player(250);
            break;
        case ItemConsts::POT_OF_FULL_HEAL:     // scroll of full healing
            heal_player(32000);
            break;
        case ItemConsts::POT_OF_CURE_POISON:
            if(g_player.is_poisoned) {
                g_player.is_poisoned = false;
                g_text_log.put_line("Your poison has lifted.");
                g_state_flags.update_status_dialog = true;
                g_state_flags.update_status_hp_exp = true;
                g_state_flags.update_status_elapsed_time = true;
                g_state_flags.update_display = true;
            }
            else {
                g_text_log.put_line("Nothing happens.");
            }
            break;
        case ItemConsts::POT_OF_BERSERK_STR:
            g_player.activate_potion_effect(ItemConsts::EFFECT_BERSERK_STRENGTH, 20);
            g_text_log.put_line("You feel as strong as a giant!");
            break;
        case ItemConsts::POT_OF_SPEED:
            g_player.activate_potion_effect(ItemConsts::EFFECT_SPEED, 20);
            g_text_log.put_line("You feel as fast as a cheetah!");
            break;
        case ItemConsts::POT_OF_HARDINESS:
            g_player.activate_potion_effect(ItemConsts::EFFECT_HARDINESS, 20);
            g_text_log.put_line("You feel unnaturally healthy!");
            break;
        case ItemConsts::POT_OF_EXTRA_ATTACKS:
            g_player.activate_potion_effect(ItemConsts::EFFECT_EXTRA_ATTACKS, 20);
            g_text_log.put_line("You feel extra proficient with your weapon!");
            break;
        case ItemConsts::POT_OF_POISON:
            // Apply the equivalent of medium poison to the player
    		if (!g_player.is_poisoned) {
	    		g_player.is_poisoned = true;
			    g_player.poison_intensity = EnemyConsts::POISON_MEDIUM;
			    g_player.poison_turns_remaining = EnemyConsts::MED_POISON_DURATION;
			    g_text_log.put_line("You've been heavily poisoned!");
                g_state_flags.update_status_dialog = true;
                g_state_flags.update_status_hp_exp = true;
                g_state_flags.update_status_elapsed_time = true;
                g_state_flags.update_display = true;
		    }
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
                g_text_log.put_line("This item is already identified.");
            }
            break;
        case ItemConsts::SCROLL_OF_IDENT_ALL:     // scroll of identify all
            count = identify_all();
            sprintf(text, "%d items were identified.", count);
            g_text_log.put_line(text);
            break;
        case ItemConsts::SCROLL_OF_MAGIC_MAP:
            if (g_state_flags.in_dungeon)
                expose_map();
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_DECURSE:
            result = decurse_item(true);
            if (result == false) {
                g_text_log.put_line("This item isn't cursed.");
            }
            break;
        case ItemConsts::SCROLL_OF_DECURSE_ALL:
            count = decurse_all();
            sprintf(text, "%d items were decursed.", count);
            g_text_log.put_line(text);
            break;
        case ItemConsts::SCROLL_OF_TELEPORT:
            if (g_state_flags.in_dungeon)
                teleport_player();
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_DARKNESS:
            if (g_state_flags.in_dungeon)
                darken_area();
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_FORGET_AREA:
            if (g_state_flags.in_dungeon)
                hide_map();
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_RECALL:
            if (g_state_flags.in_dungeon)
                activate_recall();
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_SUMMON_ITEM:
            if (g_state_flags.in_dungeon)
                summon_item(15);
            else
                g_text_log.put_line("This scroll does nothing here.");
            break;
        case ItemConsts::SCROLL_OF_CURSE:
            result = curse_item();
            if (result == false) {
                g_text_log.put_line("You have no items that can be cursed.");
            }
            break;
        default:
            g_text_log.put_line("This scroll shouldn't exist!");
            break;
    }
}