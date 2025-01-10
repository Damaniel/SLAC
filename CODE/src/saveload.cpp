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
// Writes the base header for the save file (minus offsets)
//
// Arguments:
//   f - the file pointer
//
// Returns:
//   Number of bytes written to the file
//----------------------------------------------------------------------------
int write_initial_header(FILE *f) {
    fprintf(f, "SLAC");
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
    fprintf(f, "PLAY");
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
    fprintf(f, "ITEM");
    bytes_written += 4;

    for (int i = 0; i < InventoryConsts::INVENTORY_SIZE; ++i) {
        Item *cur_item = g_inventory->get_item_in_slot(i);
        if (cur_item == NULL) {
            // load dummy data for the item
            fputc(0x00, f);
            for(int j = 0; j < 290; j++) {
                fputc(0x00, f);
            }
            bytes_written += 291;
        }
        else {
            fputc(0x01, f);
            short val = cur_item->get_id();
            char cval;
            bool bval;
            fwrite(&val, sizeof(short), 1, f);
            val = cur_item->get_quantity();
            fwrite(&val, sizeof(short), 1, f);
            
            // Write the full name
            std::string strval = cur_item->get_full_name();
            int len = strval.length();
            const char *name = strval.c_str();  
            if (len > 128)
                len = 128;
            for (int k = 0; k < len; k++) 
                fputc(name[k], f);
            for (int k = 0; k < 128 - len; k++)
                fputc(0x00, f);

            // Write the description
            strval = cur_item->get_description();
            len = strval.length();
            name = strval.c_str();  
            if (len > 128)
                len = 128;
            for (int k = 0; k < len; k++) 
                fputc(strval[k], f);
            for (int k = 0; k < 128 - len; k++)
                fputc(0x00, f);

            // Write the rest of the data
            val = cur_item->get_gid();
            fwrite(&val, sizeof(short), 1, f);
            val = cur_item->get_type_id();
            fwrite(&val, sizeof(short), 1, f);
            cval = cur_item->get_rarity();
            fwrite(&cval, sizeof(char), 1, f);
            cval = cur_item->get_ilevel();
            fwrite(&cval, sizeof(char), 1, f);
            int ival = cur_item->get_item_class();
            fwrite(&ival, sizeof(int), 1, f);
            // Write the base boolean flags
            bool flags[8];
            flags[0] = cur_item->can_have_a_prefix();
            flags[1] = cur_item->can_have_a_suffix();
            flags[2] = cur_item->can_have_curse();
            flags[3] = cur_item->can_it_stack();
            flags[4] = cur_item->can_be_used();
            flags[5] = cur_item->can_be_dropped();
            flags[6] = cur_item->can_be_equipped();
            flags[7] = cur_item->is_it_identified();
            fwrite(flags, sizeof(bool), 8, f);
            // Write the prefix and suffix
            val = (short)(cur_item->get_prefix());
            fwrite(&val, sizeof(short), 1, f);
            val = (short)(cur_item->get_suffix());
            fwrite(&val, sizeof(short), 1, f);
            // Write the cursed/equipped flags
            bval = cur_item->is_it_cursed();
            fwrite(&bval, sizeof(bool), 1, f);
            bval = cur_item->is_it_equipped();
            fwrite(&bval, sizeof(bool), 1, f);
            // Write attack/defense values (or -1 if not the right kind of equipment) 
            if (cur_item->get_item_class() == ItemConsts::WEAPON_CLASS) {
                val = (short)(cur_item->get_attack());
            }
            else {
                val = -1;
            }
            fwrite(&val, sizeof(short), 1, f);
            if (cur_item->get_item_class() == ItemConsts::ARMOR_CLASS) {
                val = (short)(cur_item->get_defense());
            }
            else {
                val = -1;
            }
            fwrite(&val, sizeof(short), 1, f);
            bytes_written += 291;
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
    fprintf(f, "ARTI");
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
    fprintf(f, "DUNG");
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
    fprintf(f, "FLAG");
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
    fprintf(f, "POTS");
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
    fprintf(f, "SCRS");
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
    fprintf(f, "POTI");
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
    fprintf(f, "SCRI");
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

    // Open the file
    FILE *fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        std::cout << "Unable to open save file for writing!" << std::endl;
        return false;
    }

    bytes_written += write_initial_header(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_player_data(fp); 
    std::cout << bytes_written << std::endl;
    bytes_written += write_inventory_data(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_artifact_data(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_dungeon_data(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_game_flags(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_potion_scramble_data(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_scroll_scramble_data(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_identified_potions(fp);
    std::cout << bytes_written << std::endl;
    bytes_written += write_identified_scrolls(fp);
    std::cout << bytes_written << std::endl;

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
    FILE *fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) {
        std::cout << "Unable to open save file for reading!" << std::endl;
        return false;
    }

    char magic[4];
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

    // Load the player data
    result = read_player_data(fp, SaveLoadConsts::PLAYER_DATA_OFFSET);
    if (!result) {
        std::cout << "player data bad" << std::endl;
        fclose(fp);
        return false;
    }


    // Load the inventory data

    // Load the artifact data

    // Load the dungeon data

    // Load the game flags

    // Load the potion scramblings

    // Load the scroll scramblings

    // Load the IDed potions

    // Load the IDed scrolls


    // Ensure the headers point to the correct sections
    // fseek(fp, SaveLoadConsts::PLAYER_DATA_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::INVENTORY_DATA_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::ARTIFACT_DATA_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::DUNGEON_DATA_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::GAME_FLAGS_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::POTION_SCRAMBLINGS_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::SCROLL_SCRAMBLINGS_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::ID_POTIONS_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;
    // fseek(fp, SaveLoadConsts::ID_SCROLLS_OFFSET, SEEK_SET);
    // fread(magic, sizeof(char), 4, fp);
    // std::cout << magic << std::endl;

    fclose(fp);
    return true;
}
