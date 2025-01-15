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
#include "globals.h"

//----------------------------------------------------------------------------
// Determines which player slots had equipped items, and re-equips them from
// the inventory
//
// Arguments:
//   slots - a list of inventory slots corresponding to equipped items
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void equip_items_back_on_player(int *slots) {
    Item *i;

    for (int idx = 0; idx < 9; idx++) {
        if (slots[idx] != -1) {
             i = g_inventory->get_item_in_slot(slots[idx]);
             if (i != NULL)
                 g_player.equip(i);
        }
    }
}

//----------------------------------------------------------------------------
// Performs whatever tasks are needed after loading a save (mainly placing
// the player in the correct place)
//
// Arguments:
//
// Returns:
//   true
//----------------------------------------------------------------------------
bool finish_other_load_tasks(void) {
    // NOTE: I don't believe this should leak memory, since
    // generate_new_dungeon_floor will either be called in the
    // first block below, or if the player enters the dungeon after
    // going through the second block below.  Either route will
    // delete any existing dungeon.
    //
    // That being said, if any weirdness/crashing starts happening,
    // look here!
    if (g_state_flags.in_dungeon) {
        // Set up the dungeon and put the player there
        enter_dungeon(g_dungeon.depth);
    }
    else {
        // Start the player in the usual start spot
        g_player.x_pos = PlayerConsts::TOWN_START_X;
        g_player.y_pos = PlayerConsts::TOWN_START_Y;
        // Reset the shop flags (in case the player was in a shop when they reloaded)
        g_state_flags.in_item_shop = false;
        g_state_flags.in_museum = false;
        g_state_flags.in_weapon_shop = false;
    }

    // ensure that the dungeons are unlocked if they should be
    unlock_dungeon(MARBLE_HALLS, true);
    unlock_dungeon(CRYSTAL_DEPTHS, true);

    // Ensure stats are up to date
    g_player.recalculate_actual_stats();
    // redraw everything
    g_state_flags.update_maze_area = true;
    g_state_flags.update_text_dialog = true;
    g_state_flags.update_status_dialog = true;
    g_state_flags.update_status_hp_exp = true;
    g_state_flags.update_status_elapsed_time = true;
    g_state_flags.update_display = true;

    return true;
}

//----------------------------------------------------------------------------
// Loads the player portion of the save file and populates the relevant
// player data
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_player_data(FILE *f, int *slots) {
    char magic[4];
    char name[16];

    fseek(f, SaveLoadConsts::PLAYER_DATA_OFFSET, SEEK_SET);

    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'P' || magic[1] != 'L' || magic[2] != 'A' || magic[3] != 'Y' ) {
        return false;
    }

    fread(&name, sizeof(char), 16, f);
    g_player.name = name;

    fread(&(g_player.hp), sizeof(short), 1, f);
    fread(&(g_player.level), sizeof(short), 1, f);
    fread(&(g_player.gold), sizeof(int), 1, f);
    fread(&(g_player.exp), sizeof(int), 1, f);
    fread(&(g_player.is_poisoned), sizeof(bool), 1, f);
    fread(&(g_player.is_equip_poisoned), sizeof(bool), 1, f);

    for (int i = 0; i < ItemConsts::NUM_TURN_POTION_EFFECTS; ++i) {
        fread(&(g_player.potion_effects[i].enabled), sizeof(bool), 1, f);
        fread(&(g_player.potion_effects[i].turns_remaining), sizeof(char), 1, f);
    }

    // Read the base stats
    fread(&(g_player.base), sizeof(Stats), 1, f);
    // Read the actual stats
    fread(&(g_player.actual), sizeof(Stats), 1, f);

    // Read the recall and effect flags
    fread(&(g_player.recall_active), sizeof(bool), 1, f);
    fread(&(g_player.recall_floor), sizeof(int), 1, f);
    fread(&(g_player.effects), sizeof(ArtifactEffectFlags), 1, f);

    fread(slots, sizeof(int), 9, f);

    return true;
}

//----------------------------------------------------------------------------
// Loads data for a particular item, creates it, and puts it in the inventory
//
// Arguments:
//   f - the file pointer
//   slot - the item the slot goes in
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
void create_item_from_save_data(FILE *f, int slot) {
    Item *i;
    char name[128];
    char desc[128];
    short id;
    short quantity;
    short gid;
    short type_id;
    unsigned char rarity;
    unsigned char ilevel;
    int item_class;
    bool flags[8];
    short prefix;
    short suffix;
    bool cursed;
    bool equipped;
    short attack;
    short defense;
    std::string s_name;
    std::string s_desc;

    // read all the item data into the temporary variables
    fread(&id, sizeof(short), 1, f);
    fread(&quantity, sizeof(short), 1, f);
    fread(&name, sizeof(char), 128, f);
    fread(&desc, sizeof(char), 128, f);
    fread(&gid, sizeof(short), 1, f);
    fread(&type_id, sizeof(short), 1, f);
    fread(&rarity, sizeof(unsigned char), 1, f);
    fread(&ilevel, sizeof(unsigned char), 1, f);
    fread(&item_class, sizeof(int), 1, f);
    fread(&flags, sizeof(bool), 8, f);
    fread(&prefix, sizeof(short), 1, f);
    fread(&suffix, sizeof(short), 1, f);
    fread(&cursed, sizeof(bool), 1, f);
    fread(&equipped, sizeof(bool), 1, f);
    fread(&attack, sizeof(short), 1, f);
    fread(&defense, sizeof(short), 1, f);

    // Create the appropriate base item type based on the type id
    i = new Item(item_class);

    // Start populating fields
    s_name = name;
    s_desc = desc;
    i->id = id;
    i->quantity = quantity;
    i->name = s_name;
    i->description = s_desc;
    i->gid = gid;
    i->type_id = type_id;
    i->rarity = rarity;
    i->ilevel = ilevel;
    i->can_have_prefix = flags[0];
    i->can_have_suffix = flags[1];
    i->can_be_cursed = flags[2];
    i->can_stack = flags[3];
    i->can_use = flags[4];
    i->can_drop = flags[5];
    i->can_equip = flags[6];
    i->is_identified = flags[7];
    i->prefix_id = prefix;
    i->suffix_id = suffix;
    i->is_cursed = cursed;
    if (equipped)
        i->is_equipped = true;
    else
        i->is_equipped = false;
    i->attack = attack;
    i->defense = defense;

    g_inventory->add_at_slot(i, slot);
}

//----------------------------------------------------------------------------
// Loads the inventory portion of the save file and populates the relevant
// inventory / player /etc data
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_inventory_data(FILE *f) {
    char magic[4];
    bool exists;

    // start by clearing the existing inventory
    if (g_inventory != NULL)
        delete g_inventory;
    g_inventory = new Inventory();

    // For each inventory item:
    // Load all the data
    // If the first value is 0, set the inventory slot to null
    // If it's set to 1
    //   - create a new item of the appropriate base type
    //   - Assign prefix, suffix and other flags to the item
    //   - Attach it to the inventory slot

    fseek(f, SaveLoadConsts::INVENTORY_DATA_OFFSET, SEEK_SET);

    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'I' || magic[1] != 'T' || magic[2] != 'E' || magic[3] != 'M' ) {
        return false;
    }

    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        fread(&exists, sizeof(bool), 1, f);
        if (exists) {
            create_item_from_save_data(f, i);
        }
        else {
            // Skip past to the next record
            fseek(f, SaveLoadConsts::INVENTORY_ITEM_SIZE - 1, SEEK_CUR);
        }
    }
    return true;
}

//----------------------------------------------------------------------------
// Loads the artifact portion of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_artifact_data(FILE *f) {
    char magic[4];

    fseek(f, SaveLoadConsts::ARTIFACT_DATA_OFFSET, SEEK_SET);

    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'A' || magic[1] != 'R' || magic[2] != 'T' || magic[3] != 'I' ) {
        return false;
    }

    fread(g_collected_artifacts, sizeof(short), NUM_ARTIFACTS, f);
    fread(g_active_artifacts, sizeof(short), NUM_ARTIFACTS, f);

    return true;
}

//----------------------------------------------------------------------------
// Loads the dungeon portion of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_dungeon_data(FILE *f) {
    char magic[4];

    fseek(f, SaveLoadConsts::DUNGEON_DATA_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'D' || magic[1] != 'U' || magic[2] != 'N' || magic[3] != 'G' ) {
        return false;
    }

    fread(&(g_dungeon.maze_id), sizeof(int), 1, f);
    fread(&(g_dungeon.depth), sizeof(int), 1, f);
    fread(&(g_dungeon.max_depth), sizeof(int), 1, f);
    fread(&(g_dungeon.ilevel), sizeof(int), 1, f);
    fread(&(g_dungeon.width), sizeof(int), 1, f);
    fread(&(g_dungeon.height), sizeof(int), 1, f);

    return true;
}

//----------------------------------------------------------------------------
// Loads the game flags data of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_game_flags(FILE *f) {
    char magic[4];

    fseek(f, SaveLoadConsts::GAME_FLAGS_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'F' || magic[1] != 'L' || magic[2] != 'A' || magic[3] != 'G' ) {
        return false;
    }

    fread(&(g_state_flags.text_log_extended), sizeof(bool), 1, f);
    fread(&(g_state_flags.in_dungeon), sizeof(bool), 1, f);
    fread(&(g_game_flags), sizeof(GameFlags), 1, f);

    return true;
}

//----------------------------------------------------------------------------
// Loads the potion scramble data of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_potion_scramble_data(FILE *f) {
    char magic[4];
    int val;

    fseek(f, SaveLoadConsts::POTION_SCRAMBLINGS_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'P' || magic[1] != 'O' || magic[2] != 'T' || magic[3] != 'S' ) {
        return false;
    }

    for (int i=0; i < ItemConsts::NUM_POTIONS; ++i) {
        fread(&val, sizeof(int), 1, f);
        g_scrambled_potion_icons.push_back(val);
    }

    return true;
}

//----------------------------------------------------------------------------
// Loads the scroll scramble data of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_scroll_scramble_data(FILE *f) {
    char magic[4];
    int val;

    fseek(f, SaveLoadConsts::SCROLL_SCRAMBLINGS_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'S' || magic[1] != 'C' || magic[2] != 'R' || magic[3] != 'S' ) {
        return false;
    }

    for (int i=0; i < ItemConsts::NUM_SCROLLS; ++i) {
        fread(&val, sizeof(int), 1, f);
        g_scrambled_scroll_icons.push_back(val);
    }

    return true;
}

//----------------------------------------------------------------------------
// Loads the IDed potion data of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_ided_potion_data(FILE *f) {
    char magic[4];

    fseek(f, SaveLoadConsts::ID_POTIONS_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'P' || magic[1] != 'O' || magic[2] != 'T' || magic[3] != 'I' ) {
        return false;
    }

    bool b;
    for (int i=0; i < ItemConsts::NUM_POTIONS; ++i) {
        fread(&b, sizeof(bool), 1, f);
        g_identified_potions.push_back(b);
    }

    return true;
}

//----------------------------------------------------------------------------
// Loads the IDed scroll data of the save file and populates the relevant
// structures
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   true if processing was OK, false otherwise
//----------------------------------------------------------------------------
bool process_ided_scroll_data(FILE *f) {
    char magic[4];

    fseek(f, SaveLoadConsts::ID_SCROLLS_OFFSET, SEEK_SET);
    fread(&magic, sizeof(char), 4, f);
    if (magic[0] != 'S' || magic[1] != 'C' || magic[2] != 'R' || magic[3] != 'I' ) {
        return false;
    }

    bool b;
    for (int i=0; i < ItemConsts::NUM_SCROLLS; ++i) {
        fread(&b, sizeof(bool), 1, f);
        g_identified_scrolls.push_back(b);
    }

    return true;
}

//----------------------------------------------------------------------------
// Writes the base header for the save file (minus offsets)
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_initial_header(FILE *f) {
    fputc('S', f);
    fputc('L', f);
    fputc('A', f);
    fputc('C', f);
    fputc(SaveLoadConsts::FILE_VERSION, f);

    // The file has a known size for each section, so we'll write offsets
    // with hardcoded values.  If this changes, we'll have to be more
    // dynamic

    // Player data
    int offset = SaveLoadConsts::PLAYER_DATA_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // Inventory data
    offset = SaveLoadConsts::INVENTORY_DATA_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // Artifact data
    offset = SaveLoadConsts::ARTIFACT_DATA_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // Dungeon data
    offset = SaveLoadConsts::DUNGEON_DATA_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // Game flags
    offset = SaveLoadConsts::GAME_FLAGS_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // Potion scramblings
    offset = SaveLoadConsts::POTION_SCRAMBLINGS_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // scroll scramblings
    offset = SaveLoadConsts::SCROLL_SCRAMBLINGS_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // identified potions
    offset = SaveLoadConsts::ID_POTIONS_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);
    // identified scrolls
    offset = SaveLoadConsts::ID_SCROLLS_OFFSET;
    fwrite(&offset, sizeof(int), 1, f);

    for(int i=0; i < 87; ++i)
        fputc(0x00, f);

    // Return the number of bytes we wrote
    return 128;
}

//----------------------------------------------------------------------------
// Writes the player data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_player_data(FILE *f) {
    int bytes_written = 0;
    fputc('P', f);
    fputc('L', f);
    fputc('A', f);
    fputc('Y', f);
    bytes_written += 4;

    // Get and write up to the first 16 characters of the name, then pad
    // with nulls if there's space left
    int len = g_player.name.length();
    const char *name = g_player.name.c_str();
    if (len > 16)
        len = 16;
    for (int i = 0; i < len; i++)
        fputc(name[i], f);
    for (int i = 0; i < 16 - len; i++)
        fputc(0x00, f);
    bytes_written += 16;

    // Write the rest of the non stat data
    fwrite(&(g_player.hp), sizeof(short), 1, f);
    fwrite(&(g_player.level), sizeof(short), 1, f);
    fwrite(&(g_player.gold), sizeof(int), 1, f);
    fwrite(&(g_player.exp), sizeof(int), 1, f);
    fwrite(&(g_player.is_poisoned), sizeof(bool), 1, f);
    fwrite(&(g_player.is_equip_poisoned), sizeof(bool), 1, f);
    bytes_written += 14;

    // Write the potion effects
    for (int i = 0; i < ItemConsts::NUM_TURN_POTION_EFFECTS; ++i) {
        fwrite(&(g_player.potion_effects[i].enabled), sizeof(bool), 1, f);
        fwrite(&(g_player.potion_effects[i].turns_remaining), sizeof(char), 1, f);
        bytes_written += 2;
    }

    // Write the base stats
    fwrite(&(g_player.base), sizeof(Stats), 1, f);
    bytes_written += sizeof(Stats);

    // Write the actual stats
    fwrite(&(g_player.actual), sizeof(Stats), 1, f);
    bytes_written += sizeof(Stats);

    // Write the recall and effect flags
    fwrite(&(g_player.recall_active), sizeof(bool), 1, f);
    fwrite(&(g_player.recall_floor), sizeof(int), 1, f);
    fwrite(&(g_player.effects), sizeof(ArtifactEffectFlags), 1, f);
    bytes_written += (5 + sizeof(ArtifactEffectFlags));

    // Iterate through and determine which inventory slots have any equipped gear
    // Write those slot numbers (or -1) for each slot
    int slot[9];
    slot[0] = g_inventory->get_slot_of_item(g_player.equipment.amulet);
    slot[1] = g_inventory->get_slot_of_item(g_player.equipment.chest);
    slot[2] = g_inventory->get_slot_of_item(g_player.equipment.feet);
    slot[3] = g_inventory->get_slot_of_item(g_player.equipment.hands);
    slot[4] = g_inventory->get_slot_of_item(g_player.equipment.head);
    slot[5] = g_inventory->get_slot_of_item(g_player.equipment.legs);
    slot[6] = g_inventory->get_slot_of_item(g_player.equipment.ring);
    slot[7] = g_inventory->get_slot_of_item(g_player.equipment.shield);
    slot[8] = g_inventory->get_slot_of_item(g_player.equipment.weapon);
    fwrite(slot, sizeof(int), 9, f);
    bytes_written += 36;

    return bytes_written;
}

//----------------------------------------------------------------------------
// Writes the inventory data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_inventory_data(FILE *f) {
    int bytes_written = 0;
    fputc('I', f);
    fputc('T', f);
    fputc('E', f);
    fputc('M', f);
    bytes_written += 4;

    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        Item *cur_item = g_inventory->get_item_in_slot(i);
        if (cur_item == NULL) {
            // load dummy data for the item
            fputc(0x00, f);
            for(int j = 0; j < 288; j++) {
                fputc(0x00, f);
            }
            bytes_written += SaveLoadConsts::INVENTORY_ITEM_SIZE;
        }
        else {
            fputc(0x01, f);
            short val = cur_item->id;
            char cval;
            bool bval;
            fwrite(&val, sizeof(short), 1, f);
            val = cur_item->quantity;
            fwrite(&val, sizeof(short), 1, f);

            // Write the full name
            std::string strval = cur_item->name;
            int len = strval.length();
            const char *name = strval.c_str();
            if (len > 128)
                len = 128;
            for (int k = 0; k < len; k++)
                fputc(name[k], f);
            for (int k = 0; k < 128 - len; k++)
                fputc(0x00, f);

            // Write the description
            strval = cur_item->description;
            len = strval.length();
            name = strval.c_str();
            if (len > 128)
                len = 128;
            for (int k = 0; k < len; k++)
                fputc(strval[k], f);
            for (int k = 0; k < 128 - len; k++)
                fputc(0x00, f);

            // Write the rest of the data
            val = cur_item->gid;
            fwrite(&val, sizeof(short), 1, f);
            val = cur_item->type_id;
            fwrite(&val, sizeof(short), 1, f);
            cval = cur_item->rarity;
            fwrite(&cval, sizeof(char), 1, f);
            cval = cur_item->ilevel;
            fwrite(&cval, sizeof(char), 1, f);
            int ival = cur_item->item_class;
            fwrite(&ival, sizeof(int), 1, f);
            // Write the base boolean flags
            bool flags[8];
            flags[0] = cur_item->can_have_prefix;
            flags[1] = cur_item->can_have_suffix;
            flags[2] = cur_item->can_be_cursed;
            flags[3] = cur_item->can_stack;
            flags[4] = cur_item->can_use;
            flags[5] = cur_item->can_drop;
            flags[6] = cur_item->can_equip;
            flags[7] = cur_item->is_identified;
            fwrite(flags, sizeof(bool), 8, f);
            // Write the prefix and suffix
            val = (short)(cur_item->prefix_id);
            fwrite(&val, sizeof(short), 1, f);
            val = (short)(cur_item->suffix_id);
            fwrite(&val, sizeof(short), 1, f);
            // Write the cursed/equipped flags
            bval = cur_item->is_cursed;
            fwrite(&bval, sizeof(bool), 1, f);
            bval = cur_item->is_equipped;
            fwrite(&bval, sizeof(bool), 1, f);
            // Write attack/defense values (or -1 if not the right kind of equipment)
            if (cur_item->item_class == ItemConsts::WEAPON_CLASS) {
                val = (short)(cur_item->attack);
            }
            else {
                val = -1;
            }
            fwrite(&val, sizeof(short), 1, f);
            if (cur_item->item_class == ItemConsts::ARMOR_CLASS) {
                val = (short)(cur_item->defense);
            }
            else {
                val = -1;
            }
            fwrite(&val, sizeof(short), 1, f);
            bytes_written += SaveLoadConsts::INVENTORY_ITEM_SIZE;
        }
    }

    return bytes_written;
}


//----------------------------------------------------------------------------
// Writes the artifact data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_artifact_data(FILE *f) {
    fputc('A', f);
    fputc('R', f);
    fputc('T', f);
    fputc('I', f);

    fwrite(g_collected_artifacts, sizeof(short), NUM_ARTIFACTS, f);
    fwrite(g_active_artifacts, sizeof(short), NUM_ARTIFACTS, f);

    return (2 * sizeof(short) * NUM_ARTIFACTS) + 4;
}

//----------------------------------------------------------------------------
// Writes the dungeon data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_dungeon_data(FILE *f) {
    fputc('D', f);
    fputc('U', f);
    fputc('N', f);
    fputc('G', f);
    fwrite(&(g_dungeon.maze_id), sizeof(int), 1, f);
    fwrite(&(g_dungeon.depth), sizeof(int), 1, f);
    fwrite(&(g_dungeon.max_depth), sizeof(int), 1, f);
    fwrite(&(g_dungeon.ilevel), sizeof(int), 1, f);
    fwrite(&(g_dungeon.width), sizeof(int), 1, f);
    fwrite(&(g_dungeon.height), sizeof(int), 1, f);

    return 28;
}

//----------------------------------------------------------------------------
// Writes the game flags to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_game_flags(FILE *f) {
    fputc('F', f);
    fputc('L', f);
    fputc('A', f);
    fputc('G', f);
    fwrite(&(g_state_flags.text_log_extended), sizeof(bool), 1, f);
    fwrite(&(g_state_flags.in_dungeon), sizeof(bool), 1, f);
    fwrite(&(g_game_flags), sizeof(GameFlags), 1, f);

    return 6 + sizeof(GameFlags);
}

//----------------------------------------------------------------------------
// Writes the potion scramble data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_potion_scramble_data(FILE *f) {
    fputc('P', f);
    fputc('O', f);
    fputc('T', f);
    fputc('S', f);

    for (int i=0; i < g_scrambled_potion_icons.size(); ++i) {
        fwrite(&(g_scrambled_potion_icons[i]), sizeof(int), 1, f);
    }

    return g_scrambled_potion_icons.size() * sizeof(int) + 4;
}

//----------------------------------------------------------------------------
// Writes the scroll scramble data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_scroll_scramble_data(FILE *f) {
    fputc('S', f);
    fputc('C', f);
    fputc('R', f);
    fputc('S', f);
    for (int i=0; i < g_scrambled_scroll_icons.size(); ++i) {
        fwrite(&(g_scrambled_scroll_icons[i]), sizeof(int), 1, f);
    }

    return g_scrambled_scroll_icons.size() * sizeof(int) + 4;
}

//----------------------------------------------------------------------------
// Writes the identified potion data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_identified_potions(FILE *f) {
    fputc('P', f);
    fputc('O', f);
    fputc('T', f);
    fputc('I', f);

    for (int i=0; i < g_identified_potions.size(); ++i) {
        bool b = g_identified_potions[i];
        fwrite(&b, sizeof(bool), 1, f);
    }

    return g_identified_potions.size() * sizeof(bool) + 4;
}

//----------------------------------------------------------------------------
// Writes the identified scroll data to the save file
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_identified_scrolls(FILE *f) {
    fputc('S', f);
    fputc('C', f);
    fputc('R', f);
    fputc('I', f);

    for (int i=0; i < g_identified_scrolls.size(); ++i) {
        bool b = g_identified_scrolls[i];
        fwrite(&b, sizeof(bool), 1, f);
    }

    return g_identified_scrolls.size() * sizeof(bool) + 4;
}

//----------------------------------------------------------------------------
// Saves a save file
//
// Arguments:
//   filename - the name of the file to save to
//
// Returns:
//   true if the file load was sucessful, false otherwise
//----------------------------------------------------------------------------
bool save_game(std::string filename) {
    int bytes_written = 0;
    int count;

    // Open the file
    FILE *fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        std::cout << "Unable to open save file for writing!" << std::endl;
        return false;
    }

    write_initial_header(fp);
    write_player_data(fp);
    write_inventory_data(fp);
    write_artifact_data(fp);
    write_dungeon_data(fp);
    write_game_flags(fp);
    write_potion_scramble_data(fp);
    write_scroll_scramble_data(fp);
    write_identified_potions(fp);
    write_identified_scrolls(fp);

    // Close the file
    fclose(fp);

    return true;
}

//----------------------------------------------------------------------------
// Loads a save file
//
// Arguments:
//   filename - the name of the file to load from
//
// Returns:
//   true if file load was successful, false otherwise
//----------------------------------------------------------------------------
bool load_game(std::string filename) {

    g_state_flags.loading_save = true;

    FILE *fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) {
        std::cout << "Unable to open save file for reading!" << std::endl;
        return false;
    }

    char magic[5];
    magic[4] = 0x00;
    int slots[9];

    int idata;
    short sdata;
    char cdata;
    bool bdata;
    bool result;

    // Load the header and get the offsets
    fread(magic, sizeof(char), 4, fp);
    if (magic[0] != 'S' || magic[1] != 'L' || magic[2] != 'A' || magic[3] != 'C') {
        std::cout << "header magic bad" << std::endl;
        fclose(fp);
        return false;
    }
    fread(&cdata, sizeof(char), 1, fp);
    if(cdata != SaveLoadConsts::FILE_VERSION) {
        std::cout << "header version bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the inventory data
    result = process_inventory_data(fp);
    if (!result) {
        std::cout << "inventory data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the player data
    result = process_player_data(fp, slots);
    if (!result) {
        std::cout << "player data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the artifact data
    result = process_artifact_data(fp);
    if (!result) {
        std::cout << "artifact data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the dungeon data
    result = process_dungeon_data(fp);
    if (!result) {
        std::cout << "dungeon data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the game flags
    result = process_game_flags(fp);
    if (!result) {
        std::cout << "game flags bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the potion scramblings
    result = process_potion_scramble_data(fp);
    if (!result) {
        std::cout << "potion scramble data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the scroll scramblings
    result = process_scroll_scramble_data(fp);
    if (!result) {
        std::cout << "scroll scramble data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the IDed potions
    result = process_ided_potion_data(fp);
    if (!result) {
        std::cout << "IDed potion data bad" << std::endl;
        fclose(fp);
        return false;
    }

    // Load the IDed scrolls
    result = process_ided_scroll_data(fp);
    if (!result) {
        std::cout << "IDed potion data bad" << std::endl;
        fclose(fp);
        return false;
    }

    fclose(fp);

    equip_items_back_on_player(slots);

    // do any additional processing (init, state changes, etc)
    result = finish_other_load_tasks();

    g_state_flags.loading_save = false;

    return result;
}

//----------------------------------------------------------------------------
// Fills the Hall of Champions with default values
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void init_hall_of_champions_entries() {
    for (int i = 0; i < UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES; ++i) {
        g_hall_of_champions[i].has_entry = false;
        g_hall_of_champions[i].name = "";
        g_hall_of_champions[i].elapsed = 0;
        g_hall_of_champions[i].generation = 0;
    }
}

//----------------------------------------------------------------------------
// Saves the Hall of Champions File
//
// Arguments:
//   None
//
// Returns:
//   true if file save was successful, false otherwise
//----------------------------------------------------------------------------
bool save_hall_of_champions() {
    FILE *fp = fopen((SaveLoadConsts::hoc_file).c_str(), "wb");
    if (fp == NULL) {
        std::cout << "save_hall_of_champions: couldn't open file" << std::endl;
        return false;
    }

    // Write magic bytes
    fprintf(fp, "HOCF");

    for (int i=0; i < UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES; ++i) {
        fwrite(&(g_hall_of_champions[i].has_entry), sizeof(bool), 1, fp);
        int len = g_hall_of_champions[i].name.size();
        if (len > 32)
            len = 32;
        for (int j = 0; j < len; ++j)
            fputc(g_hall_of_champions[i].name[j], fp);
        for (int j = 0; j < 32 - len; ++j)
            fputc(0x00, fp);
        fwrite(&(g_hall_of_champions[i].elapsed), sizeof(unsigned long int), 1, fp);
        fwrite(&(g_hall_of_champions[i].generation), sizeof(int), 1, fp);
    }

    fclose(fp);
    return true;
}

//----------------------------------------------------------------------------
// Loads the Hall of Champions File
//
// Arguments:
//   None
//
// Returns:
//   true if file load was successful, false otherwise
//----------------------------------------------------------------------------
bool load_hall_of_champions() {
    init_hall_of_champions_entries();
    FILE *fp = fopen((SaveLoadConsts::hoc_file).c_str(), "rb");
    if (fp == NULL) {
        std::cout << "load_hall_of_champions: couldn't open file" << std::endl;
        return false;
    }

    char magic[4];
    fread(magic, sizeof(char), 4, fp);
    if (magic[0] != 'H' || magic[1] != 'O' || magic[2] != 'C' || magic[3] != 'F') {
        std::cout << "load_hall_of_champions: bad magic" << std::endl;
        return false;
    }

    char name[32];
    unsigned long int elapsed;
    int gen;
    bool has_entry;

    for (int i=0; i < UtilConsts::NUM_HALL_OF_CHAMPIONS_ENTRIES; ++i) {
        fread(&has_entry, sizeof(bool), 1, fp);
        fread(name, sizeof(char), 32, fp);
        fread(&elapsed, sizeof(unsigned long int), 1, fp);
        fread(&gen, sizeof(int), 1, fp);
        g_hall_of_champions[i].has_entry = has_entry;
        g_hall_of_champions[i].name = name;
        g_hall_of_champions[i].elapsed = elapsed;
        g_hall_of_champions[i].generation = gen;
    }

    fclose(fp);
    return true;
}

//----------------------------------------------------------------------------
// Checks if the save file or HOC file exists
//
// Arguments:
//   None
//
// Returns:
//   true if the file exists, false otherwise
//----------------------------------------------------------------------------
bool slac_file_exists(std::string name) {
    FILE *fp = fopen(name.c_str(), "rb");
    if (fp == NULL)
        return false;

    fclose(fp);
    return true;

}