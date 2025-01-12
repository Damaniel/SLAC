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
// types.
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
        // std::cout << "generator: ilevel roll attempt " << (attempt + 1) << " of " << MAX_GENERATOR_REROLLS << std::endl;
        switch (item_type) {
            case ItemConsts::WEAPON_CLASS:
                rolled_base_type = roll_from_pool(g_weapon_base_pool, g_weapon_base_pool_count, g_weapon_base_pool_entries);
                base_ilevel = g_weapon_base_ids[rolled_base_type].ilevel;
                break;
            case ItemConsts::ARMOR_CLASS:
                rolled_base_type = roll_from_pool(g_armor_base_pool, g_armor_base_pool_count, g_armor_base_pool_entries);
                base_ilevel = g_armor_base_ids[rolled_base_type].ilevel;
                break;
            case ItemConsts::CURRENCY_CLASS:
                rolled_base_type = roll_from_pool(g_currency_pool, g_currency_pool_count, g_currency_pool_entries);
                base_ilevel = g_currency_ids[rolled_base_type].ilevel;
                break;
             case ItemConsts::POTION_CLASS:
                rolled_base_type = roll_from_pool(g_potion_pool, g_potion_pool_count, g_potion_pool_entries);
                base_ilevel = g_potion_ids[rolled_base_type].ilevel;
                break;
            case ItemConsts::SCROLL_CLASS:
                rolled_base_type = roll_from_pool(g_scroll_pool, g_scroll_pool_count, g_scroll_pool_entries);
                base_ilevel = g_scroll_ids[rolled_base_type].ilevel;
                break;
            case ItemConsts::ARTIFACT_CLASS:
                rolled_base_type = roll_from_pool(g_artifact_pool, g_artifact_pool_count, g_artifact_pool_entries);
                base_ilevel = g_artifact_ids[rolled_base_type].ilevel;
                break;
        }

        // If the item is at or below the ilevel as-is, accept it immediately
        if (base_ilevel <= ilevel) {
            // std::cout <<  "  generator: item meets ilevel requirements, generating base" << std::endl;
            generated = true;
        }
        else {
            // Otherwise, do the 'level difference' roll to see if we generate it anyway
            // std::cout << "  generator: item doesn't meet ilevel requirement, rolling difference" << std::endl;
            int i = rand() % 100;
            int ilevel_diff = base_ilevel - ilevel;
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

    // Attempt to apply a curse to items that can be.  This will dictate what kinds of affixes can roll.
    if (i->can_be_cursed) {
        ItemGenerator::apply_curse(i, ilevel);
    }

    // Attempt to add a prefix or suffix to items that can have them
    if (i->can_have_prefix) {
        // std::cout << "generator: attempting to add prefix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::PREFIX_CLASS, ilevel);
    }
    if (i->can_have_suffix) {
        // std::cout << "generator: attempting to add suffix" << std::endl;
        ItemGenerator::apply_affix(i, ItemConsts::SUFFIX_CLASS, ilevel);
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
//   ilevel - the maximum ilevel to use when pulling from the affix pools
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void ItemGenerator::apply_affix(Item *i, int affix_type, int ilevel) {
    int roll, rolled_affix_type, attempt, base_ilevel, affix_chance;
    bool generated;

    // This will generate an affix chance between 10% at ilevel 1 and roughly 35% at iLevel 100
    affix_chance = ItemConsts::BASE_CHANCE_OF_AFFIX + (ilevel / 4);
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
            if (base_ilevel <= ilevel) {
                // std::cout <<  "  generator: affix meets ilevel requirements, will apply to item" << std::endl;
                generated = true;
            }
            else {
                // otherwise, do the same ilevel difference check as for item bases,
                // and apply the affix if it passes
                // std::cout << "  generator: affix doesn't meet ilevel requirement, rolling difference" << std::endl;
                int i = rand() % 100;
                int ilevel_diff = base_ilevel - ilevel;
                if (ilevel_diff > 10) {
                    ilevel_diff = 10;
                }
                // std::cout << "    generator: level difference is " << ilevel_diff << ", chance of generation is " << (100 - 10 * ilevel_diff) << "%" << std::endl;
                if (i >= (10 * ilevel_diff)) {
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
                i->prefix_id = -1;
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
//
// Returns:
//   Nothing.
//----------------------------------------------------------------------------
void ItemGenerator::apply_curse(Item *i, int ilevel) {
    int roll = rand() % 100;
    // The chance of a curse is the base chance plus 1% per 10 ilevels
    // (so an item with ilevel 100 has a 20% chance of being cursed)
    if (roll < (ItemConsts::BASE_CHANCE_OF_CURSE + (ilevel / 10))) {
        i->is_cursed = true;
        //std::cout << "generator: Item was cursed" << std::endl;
    }
    else {
        i->is_cursed = false;
    }
}