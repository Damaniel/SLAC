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
                std::string old_name = i->get_full_name();
                i->identify();
                if (log) {
                    g_text_log.put_line(old_name + " is actually a " + i->get_full_name() + ".");
                }
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

    // TODO - make the JSON file create an enum with item names
    switch (id) {
        case 0:     // Scroll of light healing
            heal_player(10);
            break;
        case 1:     // scroll of healing
            heal_player(50);
            break;
        case 2:     // scroll of full healing
            heal_player(100);
            break;
        default:
            g_text_log.put_line("This potion isn't enabled yet.");
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

    // TODO - make the JSON file create an enum with item names
    switch (id) {
        case 0:     // Scroll of identify
            result = identify_item(true);
            if (result == false) {
                g_text_log.put_line("You have no unidentified items.");
            }
            break;
        case 1:     // scroll of identify all
            count = identify_all();
            sprintf(text, "%d items were identified.", count);
            g_text_log.put_line(text);
            break;
        default:
            g_text_log.put_line("This scroll isn't enabled yet.");
            break;
    }
}