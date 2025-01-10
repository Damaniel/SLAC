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
    fputc(0x01, f);
    for(int i=0; i < 123; ++i)
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
    fprintf(f, "PLAY");
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
    // Write the rest of the non stat data
    fwrite(&(g_player.hp), sizeof(short), 1, f);
    fwrite(&(g_player.level), sizeof(short), 1, f);
    fwrite(&(g_player.gold), sizeof(int), 1, f);
    fwrite(&(g_player.exp), sizeof(int), 1, f);
    fwrite(&(g_player.is_poisoned), sizeof(bool), 1, f);
    fwrite(&(g_player.is_equip_poisoned), sizeof(bool), 1, f);

    // Write the potion effects
    for (int i = 0; i < ItemConsts::NUM_TURN_POTION_EFFECTS; ++i) {
        fwrite(&(g_player.potion_effects[i].enabled), sizeof(bool), 1, f);
        fwrite(&(g_player.potion_effects[i].turns_remaining), sizeof(char), 1, f);
    }

    // Write the base stats
    fwrite(&(g_player.base), sizeof(Stats), 1, f);

    // Write the actual stats
    fwrite(&(g_player.actual), sizeof(Stats), 1, f);

    // Write the recall and effect flags
    fwrite(&(g_player.recall_active), sizeof(bool), 1, f);
    fwrite(&(g_player.recall_floor), sizeof(int), 1, f);
    fwrite(&(g_player.effects), sizeof(ArtifactEffectFlags), 1, f);

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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    return 0;
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
    // File offsets into the save file
    int player_data_offset;
    int inventory_data_offset;
    int artifact_data_offset;
    int dungeon_data_offset;
    int game_flags_offset;
    int potion_scramble_offset;
    int scroll_scramble_offset;
    int identified_potions_offset;
    int identified_scrolls_offset;
    int bytes_written = 0;

    // Open the file
    FILE *fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        std::cout << "Unable to open save file for writing!" << std::endl;
        return false;
    }

    bytes_written += write_initial_header(fp);
    player_data_offset = bytes_written;
    
    bytes_written += write_player_data(fp);
    inventory_data_offset = bytes_written;
    
    bytes_written += write_inventory_data(fp);
    artifact_data_offset = bytes_written;

    bytes_written += write_artifact_data(fp);
    dungeon_data_offset = bytes_written;

    bytes_written += write_dungeon_data(fp);
    game_flags_offset = bytes_written;

    bytes_written += write_game_flags(fp);
    potion_scramble_offset = bytes_written;

    bytes_written += write_potion_scramble_data(fp);
    scroll_scramble_offset = bytes_written;

    bytes_written += write_scroll_scramble_data(fp);
    identified_potions_offset = bytes_written;

    bytes_written += write_identified_potions(fp);
    identified_scrolls_offset = bytes_written;

    bytes_written += write_identified_scrolls(fp);

    // Write the offsets into the header

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

}
