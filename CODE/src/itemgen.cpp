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
// Generates an item based on rules for creating items to go into the
// equipment shop.  Ilevel ranges, adjusted prefix, suffix and curse rates,
// and identification status are all non-standard compared to the 'usual'
// item generator, and are further adjusted based on whether the item is
// a 'mystery' item or not.
//
// Arguments:
//    None
//
// Returns:
//   A pointer to a randomly generated Item.  The memory for this will need
//   to be freed later since it's heap allocated.
//----------------------------------------------------------------------------
Item *ItemGenerator::shop_generate() {
    Item *i;

    // Determine an ilevel range to roll.  It should be the player's maximum
    // dungeon ilevel, +/- 25
    int ilevel_min = g_game_flags.max_ilevel - 25;
    int ilevel_max = g_game_flags.max_ilevel + 25;

    if (ilevel_min < 0)
        ilevel_min = 0;
    if (ilevel_max > 100)
        ilevel_max = 100;

    // Generate either a weapon or an armor.  Weapons are slightly more likely
    // on average than an arbitrary piece of armor.  Pick a number from 0-9 -
    // 0-7 generate armor, 8 or 9 generate a weapon
    int equipment_type = rand() % 9;
    if (equipment_type < 8) {
        i = ItemGenerator::generate_base_item(ItemConsts::ARMOR_CLASS, ilevel_min, ilevel_max);
    }
    else {
        i = ItemGenerator::generate_base_item(ItemConsts::WEAPON_CLASS, ilevel_min, ilevel_max);
    }

    // With 1 in 4 odds, flag an item as 'mystery'
    bool mystery = false;
    if (rand() % 100 < 25)
        mystery = true;

    int curse_chance;
    int chance_of_affix;
    // If mystery, roll prefixes/suffixes/curse with higher odds
    if (mystery) {
        curse_chance = (ItemConsts::BASE_CHANCE_OF_CURSE + 5) + (g_game_flags.max_ilevel / 4);
        chance_of_affix = (ItemConsts::BASE_CHANCE_OF_AFFIX + 15) + (g_game_flags.max_ilevel / 2);
    }
    // If standard, roll prefixes/suffixes/curses with standard odds
    else {
        curse_chance = 0;
        chance_of_affix = ItemConsts::BASE_CHANCE_OF_AFFIX + (g_game_flags.max_ilevel / 4);
    }

    // Cap the chance of curse/prefix/suffix, so that some mystery items will always be 'normal'
    if (curse_chance > 90)
        curse_chance = 90;
    if (chance_of_affix > 90)
        chance_of_affix = 90;

    // Attempt to apply a curse to items that can be.  This will dictate what kinds of affixes can roll.
    if (i->can_be_cursed) {
        ItemGenerator::apply_curse(i, curse_chance);
    }
    if (i->can_have_prefix) {
        // std::cout << "generator: attempting to add prefix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::PREFIX_CLASS, chance_of_affix);
    }
    if (i->can_have_suffix) {
        // std::cout << "generator: attempting to add suffix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::SUFFIX_CLASS, chance_of_affix);
    }

    // If standard, mark the item as identified.  If mystery, mark as
    // unidentified
    if (mystery) {
        i->is_identified = false;
    }
    else {
        i->is_identified = true;
    }

    // return the finished item
    return i;
}

//----------------------------------------------------------------------------
// Generates an index corresponding to the base type of a randomly generated
// item of a type (e.g. WEAPON_CLASS might return 'Iron Broadsword', depending
// on the target ilevel)
//
// Arguments:
//   item_type - item to generate
//   ilevel - the target item level to use for item generation
//
// Returns:
//   The index of the selected base item type
//----------------------------------------------------------------------------
int ItemGenerator::generate_base_type(int item_type) {
    int base_type;
    switch (item_type) {
        case ItemConsts::WEAPON_CLASS:
            base_type = roll_from_pool(g_weapon_base_pool, g_weapon_base_pool_count, g_weapon_base_pool_entries);
            break;
        case ItemConsts::ARMOR_CLASS:
            base_type = roll_from_pool(g_armor_base_pool, g_armor_base_pool_count, g_armor_base_pool_entries);
            break;
        case ItemConsts::CURRENCY_CLASS:
            base_type = roll_from_pool(g_currency_pool, g_currency_pool_count, g_currency_pool_entries);
            break;
        case ItemConsts::POTION_CLASS:
            base_type = roll_from_pool(g_potion_pool, g_potion_pool_count, g_potion_pool_entries);
            break;
        case ItemConsts::SCROLL_CLASS:
            base_type = roll_from_pool(g_scroll_pool, g_scroll_pool_count, g_scroll_pool_entries);
            break;
        case ItemConsts::ARTIFACT_CLASS:
            base_type = roll_from_pool(g_artifact_pool, g_artifact_pool_count, g_artifact_pool_entries);
            break;
    }
    return base_type;
}

//----------------------------------------------------------------------------
// Gets the ilevel of the specified item type / item index pair
//
// Arguments:
//   item_type - the type of item
//   item_idx  - the offset into the relevant item table
//
// Returns:
//   the ilevel of the item base
//----------------------------------------------------------------------------
int ItemGenerator::get_base_ilevel(int item_type, int item_idx) {
    int base_ilevel;
    switch (item_type) {
        case ItemConsts::WEAPON_CLASS:
            base_ilevel = g_weapon_base_ids[item_idx].ilevel;
            break;
        case ItemConsts::ARMOR_CLASS:
            base_ilevel = g_armor_base_ids[item_idx].ilevel;
            break;
        case ItemConsts::CURRENCY_CLASS:
            base_ilevel = g_currency_ids[item_idx].ilevel;
            break;
        case ItemConsts::POTION_CLASS:
            base_ilevel = g_potion_ids[item_idx].ilevel;
            break;
        case ItemConsts::SCROLL_CLASS:
            base_ilevel = g_scroll_ids[item_idx].ilevel;
            break;
        case ItemConsts::ARTIFACT_CLASS:
            base_ilevel = g_artifact_ids[item_idx].ilevel;
            break;
    }
    return base_ilevel;
}

//----------------------------------------------------------------------------
// Generates an base item of a particular item class (for example, an armor,
// or a weapon).  This item will have no affixes of any kind.
//
// Arguments:
//   item_type - item to generate
//   ilevel - the target item level to use for item generation
//
// Returns:
//   A pointer to a randomly generated Item of the item type.
//
// Valid item types are (WEAPON_CLASS, ARMOR_CLASS, CURRENCY_CLASS,
// CONSUMABLE_CLASS, ARTIFACT_CLASS).
//----------------------------------------------------------------------------
Item *ItemGenerator::generate_base_item(int item_type, int min_ilevel, int max_ilevel) {
    Item *i;
    int attempt, base_ilevel;
    int rolled_base_type;
    bool generated;

    generated = false;

    i = new Item(item_type);

    attempt = 0;

    // Roll (up to 'g_item_generate_max_cycles' times) for an item base.  Only keep it if it meets the ilevel requirements.  If no item is
    // generated, make a default item (in this case, an item with id 0).
    do {
        rolled_base_type = ItemGenerator::generate_base_type(item_type);
        base_ilevel = ItemGenerator::get_base_ilevel(item_type, rolled_base_type);

        // If the item is at or below the ilevel as-is, accept it immediately
        if (base_ilevel >= min_ilevel && base_ilevel <= max_ilevel) {
            // std::cout <<  "  generator: item meets ilevel requirements, generating base" << std::endl;
            generated = true;
        }
        else {
            // Otherwise, do the 'level difference' roll to see if we generate it anyway
            // std::cout << "  generator: item doesn't meet ilevel requirement, rolling difference" << std::endl;
            int i = rand() % 100;
            int ilevel_diff;
            if (base_ilevel < min_ilevel)
                ilevel_diff = min_ilevel - base_ilevel;
            if (base_ilevel > max_ilevel)
                ilevel_diff = base_ilevel - max_ilevel;
            if (ilevel_diff > 10) {
                ilevel_diff = 10;
            }
            // std::cout << "    generator: level difference is " << ilevel_diff << ", chance of generation is " << (100 - 10 * ilevel_diff) << "%" << std::endl;
            if (i >= (10 * ilevel_diff)) {
                // std::cout << "    generator: level difference override passed, generating item base" << std::endl;
                generated = true;
            } else {
                // std::cout << "    generator: level difference override failed, not generating item base" << std::endl;
                generated = false;
            }
        }
        ++attempt;
    } while (generated == false && attempt < ItemConsts::MAX_GENERATOR_REROLLS);

    // If the item was successfully generated, initialize it, otherwise create a 'default' item
    // (that is, an item with id 0)
    if (generated) {
        // std::cout << "generator: generating the item" << std::endl;
        i->init(i->item_class, rolled_base_type);
    }
    else {
        // std::cout << "generator: item base roll failed, generating 'default' item" << std::endl;
        i->init(i->item_class, 0);
    }

    return i;
}

//----------------------------------------------------------------------------
// Generates an item.  This can be anything, weighted by overall item class,
// item base type and mod types, assuming a max item level of 100
//
// Arguments:
//   None
//
// Returns:
//   A pointer to a randomly generated Item.
//----------------------------------------------------------------------------
Item *ItemGenerator::generate() {
    return ItemGenerator::generate(100);
}

//----------------------------------------------------------------------------
// Generates an item based on a specified item level.  Within that constraint,
// this can be anything, weighted by overall item class, item base type and
// mod types.
//
// Arguments:
//   ilevel - the target item level to use for item generation
//
// Returns:
//   A pointer to a randomly generated Item.  The memory for this will need
//   to be freed later since it's heap allocated.
//----------------------------------------------------------------------------
Item *ItemGenerator::generate(int ilevel) {
    Item *i;
    int item_type = roll_from_pool(ItemConsts::g_item_class_pool,
                                   ItemConsts::g_item_class_pool_count,
                                   ItemConsts::g_item_class_pool_entries);
    i = ItemGenerator::generate(item_type, ilevel);

    // i->dump_item();
    // std::cout << std::endl;

    return i;
}

//----------------------------------------------------------------------------
// Generates an item of a particular item class, weighted by base type and mod
// types, of a max base ilevel
//
// Arguments:
//   item_type - item to generate
//   ilevel - the target item level to use for item generation
//
// Returns:
//   A pointer to a randomly generated Item of the item type.
//
// Valid item types are (WEAPON_CLASS, ARMOR_CLASS, CURRENCY_CLASS,
// CONSUMABLE_CLASS, ARTIFACT_CLASS).
//----------------------------------------------------------------------------
Item *ItemGenerator::generate(int item_type, int ilevel) {
    return ItemGenerator::generate(item_type, 0, ilevel);
}

//----------------------------------------------------------------------------
// Generates an item of a particular item class, weighted by base type and mod
// types, in a particular base ilevel range
//
// Arguments:
//   item_type - item to generate
//   min_ilevel, max_ilevel - the target item level range to use for item
//                            generation
//
// Returns:
//   A pointer to a randomly generated Item of the item type.
//
// Valid item types are (WEAPON_CLASS, ARMOR_CLASS, CURRENCY_CLASS,
// CONSUMABLE_CLASS, ARTIFACT_CLASS).
//----------------------------------------------------------------------------
Item *ItemGenerator::generate(int item_type, int min_ilevel, int max_ilevel) {
    Item *i;

    i = ItemGenerator::generate_base_item(item_type, min_ilevel, max_ilevel);

    int curse_chance = ItemConsts::BASE_CHANCE_OF_CURSE + (g_game_flags.max_ilevel / 10);
    // Attempt to apply a curse to items that can be.  This will dictate what kinds of affixes can roll.
    if (i->can_be_cursed) {
        ItemGenerator::apply_curse(i, curse_chance);
    }

    // This will generate an affix chance between 10% at ilevel 1 and roughly 35% at iLevel 100
    int affix_chance = ItemConsts::BASE_CHANCE_OF_AFFIX + (g_game_flags.max_ilevel / 4);

    // Attempt to add a prefix or suffix to items that can have them
    if (i->can_have_prefix) {
        // std::cout << "generator: attempting to add prefix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::PREFIX_CLASS, affix_chance);
    }
    if (i->can_have_suffix) {
        // std::cout << "generator: attempting to add suffix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::SUFFIX_CLASS, affix_chance);
    }

    // If the item is cursed but didn't get a prefix or a suffix, demote it back to
    // a non-cursed item (so we don't end up with a cursed item with no adjusted
    // stats)
    if (i->is_cursed && i->prefix_id == -1 && i->suffix_id == -1) {
        i->is_cursed = false;
    }

    // If the item is a potion or scroll and has been previously identified,
    // mark it as such
    identify_if_previously_known(i);

    // std::cout << std::endl;
    return i;
}

//----------------------------------------------------------------------------
// Generates and applies a random affix to an item, if the item is capable of
// taking one
//
// Arguments:
//   i - the Item to augment
//   affix_type - the type of affix to apply (PREFIX_CLASS or SUFFIX_CLASS)
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void ItemGenerator::apply_affix(Item *i, int affix_type, int affix_chance) {
    int roll, rolled_affix_type, attempt, base_ilevel;
    bool generated;

    roll = rand() % 100;
    if (roll < affix_chance) {
        attempt = 0;
        generated = false;
        do {
            // std::cout << "generator: ilevel roll attempt " << (attempt + 1) << " of " << MAX_GENERATOR_REROLLS << std::endl;
            // generate the affix
            if (affix_type == ItemConsts::PREFIX_CLASS) {
                if (i->is_cursed) {
                    rolled_affix_type = roll_from_pool(g_cursed_item_prefix_pool, g_cursed_item_prefix_pool_count, g_cursed_item_prefix_pool_entries);
                    base_ilevel = g_cursed_item_prefix_ids[rolled_affix_type].ilevel;
                }
                else {
                    rolled_affix_type = roll_from_pool(g_item_prefix_pool, g_item_prefix_pool_count, g_item_prefix_pool_entries);
                    base_ilevel = g_item_prefix_ids[rolled_affix_type].ilevel;
                }
            }
            if (affix_type == ItemConsts::SUFFIX_CLASS) {
                if (i->is_cursed) {
                    rolled_affix_type = roll_from_pool(g_cursed_item_suffix_pool, g_cursed_item_suffix_pool_count, g_cursed_item_suffix_pool_entries);
                    base_ilevel = g_cursed_item_suffix_ids[rolled_affix_type].ilevel;
                }
                else {
                    rolled_affix_type = roll_from_pool(g_item_suffix_pool, g_item_suffix_pool_count, g_item_suffix_pool_entries);
                    base_ilevel = g_item_suffix_ids[rolled_affix_type].ilevel;
                }
            }

            // std::cout << "  generator: ilevel is " << ilevel << ", base ilevel of item is " << base_ilevel << std::endl;
            // if the item level of the affix is lower than the passed in one, we're done
            if (base_ilevel <= i->ilevel) {
                // std::cout <<  "  generator: affix meets ilevel requirements, will apply to item" << std::endl;
                generated = true;
            }
            else {
                // otherwise, do the same ilevel difference check as for item bases,
                // and apply the affix if it passes
                // std::cout << "  generator: affix doesn't meet ilevel requirement, rolling difference" << std::endl;
                int ilevel_idx = rand() % 100;
                int ilevel_diff = base_ilevel - i->ilevel;
                if (ilevel_diff > 10) {
                    ilevel_diff = 10;
                }
                // std::cout << "    generator: level difference is " << ilevel_diff << ", chance of generation is " << (100 - 10 * ilevel_diff) << "%" << std::endl;
                if (ilevel_idx >= (10 * ilevel_diff)) {
                    // std::cout << "    generator: level difference override passed, generating affix" << std::endl;
                    generated = true;
                } else {
                    // std::cout << "    generator: level difference override failed, not generating affix" << std::endl;
                    generated = false;
                }
            }
            ++attempt;
        } while (generated == false && attempt < ItemConsts::MAX_GENERATOR_REROLLS);

        // If an affix was generated, apply it, otherwise clear it
        if (generated) {
            // std::cout << "generator: applying the affix" << std::endl;
            if (affix_type == ItemConsts::PREFIX_CLASS)
                i->prefix_id = rolled_affix_type;
            if (affix_type == ItemConsts::SUFFIX_CLASS)
                i->suffix_id = rolled_affix_type;
        }
        else {
            // std::cout << "generator: no affix was applied" << std::endl;
            if (affix_type == ItemConsts::PREFIX_CLASS)
                i->prefix_id = -1;
            if (affix_type == ItemConsts::SUFFIX_CLASS)
                i->suffix_id = -1;
        }
    }
    else
    {
        // std::cout << "generator: 'apply affix' roll failed, no affix was applied" << std::endl;
        if (affix_type == ItemConsts::PREFIX_CLASS)
            i->prefix_id = -1;
        if (affix_type == ItemConsts::SUFFIX_CLASS)
            i->suffix_id = -1;
    }
}

//----------------------------------------------------------------------------
// Attempts to curse an item according to a weighting factor.
//
// Arguments:
//   i - the item to curse
//   curse_chance - the odds of the item actually being cursed
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void ItemGenerator::apply_curse(Item *i, int curse_chance) {
    int roll = rand() % 100;
    // The chance of a curse is the base chance plus 1% per 10 ilevels
    // (so an item with ilevel 100 has a 20% chance of being cursed)
    if (roll < curse_chance) {
        i->is_cursed = true;
        //std::cout << "generator: Item was cursed" << std::endl;
    }
    else {
        i->is_cursed = false;
    }
}