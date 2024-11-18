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
#include "globals.h"

// Generates a random item index from the given pool
//
// Arguments:
//  pool - the pool to draw from
//  pool_size - the number of elements in the pool to consider
//  max_val - the highest possible value in the pool
//
// Returns:
//  The index from the pool selected, or 0 (the default item) if something went wrong
int ItemGenerator::roll_from_pool(const int *pool, int pool_size, int max_val) {
    int val = rand() % max_val;
    //std::cout << "size = " << pool_size << ", max val =  " << max_val << ", rolled val = " << val << std::endl;
    for (int i = 0; i < pool_size; ++i) {
        //std::cout << "i = " << i << ", pool[i] = " << pool[i] << std::endl;
        if (val < pool[i]) {
            //std::cout << "Rolled " << val << " in a pool of " << max_val << ", index is " << i << std::endl;
            return i;
        }
    }
    return 0;
}

// Generates an item.  This can be anything, weighted by overall item class, item base type and mod types, 
// assuming a max item level of 100
//
// Arguments:
//   None
//
// Returns:
//   A pointer to a randomly generated Item.
Item *ItemGenerator::generate() {
    return ItemGenerator::generate(100);
}

// Generates an item based on a specified item level.  Within that constraint, this can be anything, 
// weighted by overall item class, item base type and mod types.
//
// Arguments:
//   ilevel - the target item level to use for item generation
//
// Returns:
//   A pointer to a randomly generated Item.
Item *ItemGenerator::generate(int ilevel) {
    Item *i;
    int item_type = ItemGenerator::roll_from_pool(g_item_class_pool, g_item_class_pool_count, g_item_class_pool_entries);
    i = ItemGenerator::generate(item_type, ilevel);
    return i;
}

// Generates an item of a particular item class, weighted by base type and mod types.
//
// Arguments:
//   item_type - item to generate
//   ilevel - the target item level to use for item generation
//
// Returns:
//   A pointer to a randomly generated Item of the item type.
//
// Valid item types are (WEAPON_CLASS, ARMOR_CLASS, CURRENCY_CLASS, CONSUMABLE_CLASS, ARTIFACT_CLASS).
Item *ItemGenerator::generate(int item_type, int ilevel) {
    Item *i;
    int attempt, base_ilevel;
    int rolled_base_type;
    bool generated;

    // Equipment generator
    if (item_type == WEAPON_CLASS || item_type == ARMOR_CLASS) {
        generated = false;
        attempt = 0;

        // Create an instance of the specific base class of equipment
        if (item_type == WEAPON_CLASS) {
            i = new Weapon();
        }
        else {
            i = new Armor();
        }

        // Roll (up to 'g_item_generate_max_cycles' times) for an item base.  Only keep it if it meets the ilevel requirements.  If no item is 
        // generated, make a default item (in this case, an item with id 0).
        do {
            // std::cout << "generator: ilevel roll attempt " << (attempt + 1) << " of " << MAX_GENERATOR_REROLLS << std::endl;
            if (item_type == WEAPON_CLASS) {
                rolled_base_type = ItemGenerator::roll_from_pool(g_weapon_base_pool, g_weapon_base_pool_count, g_weapon_base_pool_entries);
                base_ilevel = g_weapon_base_ids[rolled_base_type].ilevel;
            }
            else {
                rolled_base_type = ItemGenerator::roll_from_pool(g_armor_base_pool, g_armor_base_pool_count, g_armor_base_pool_entries);
                base_ilevel = g_armor_base_ids[rolled_base_type].ilevel;
            }
            // std::cout << "  generator: ilevel is " << ilevel << ", base ilevel of item is " << base_ilevel << std::endl;

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
        } while (generated == false && attempt < MAX_GENERATOR_REROLLS);

        // If the item was successfully generated, initialize it, otherwise create a 'default' item 
        // (that is, an item with id 0)
        if (generated) {
            // std::cout << "generator: generating the item" << std::endl;
            i->init(rolled_base_type);
        }
        else {
            // std::cout << "generator: item base roll failed, generating 'default' item" << std::endl;
            i->init(0);
        }

        // Attempt to apply a curse.  This will dictate what kinds of affixes can roll.
        if (i->can_have_curse()) {
            ItemGenerator::apply_curse(i);
        }

        // Attempt to add a prefix or suffix
        if (i->can_have_a_prefix()) {
            // std::cout << "generator: attempting to add prefix" << std::endl;
            ItemGenerator::apply_affix(i, PREFIX_CLASS, ilevel);
        }
        if (i->can_have_a_suffix()) {
            // std::cout << "generator: attempting to add suffix" << std::endl;
            ItemGenerator::apply_affix(i, SUFFIX_CLASS, ilevel);
        }
    }
    else {
        // Nothing else defined yet
        return NULL;
    }

    // std::cout << std::endl;
    return i;
}

// Generates and applies a random affix to an item, if the item is capable of taking one
//
// Arguments:
//   i - the Item to augment
//
// Returns:
//   Nothing
void ItemGenerator::apply_affix(Item *i, int affix_type, int ilevel) {
    int roll, rolled_affix_type, attempt, base_ilevel;
    bool generated;

    roll = rand() % 100;
    if (roll < CHANCE_OF_AFFIX) {
        attempt = 0;
        generated = false;
        do {
            // std::cout << "generator: ilevel roll attempt " << (attempt + 1) << " of " << MAX_GENERATOR_REROLLS << std::endl;
            // generate the affix
            if (affix_type == PREFIX_CLASS) {
                rolled_affix_type = roll_from_pool(g_item_prefix_pool, g_item_prefix_pool_count, g_item_prefix_pool_entries);
                base_ilevel = g_item_prefix_ids[rolled_affix_type].ilevel;
            }
            if (affix_type == SUFFIX_CLASS) {
                rolled_affix_type = roll_from_pool(g_item_suffix_pool, g_item_suffix_pool_count, g_item_suffix_pool_entries);
                base_ilevel = g_item_suffix_ids[rolled_affix_type].ilevel;
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
        } while (generated == false && attempt < MAX_GENERATOR_REROLLS);

        // If an affix was generated, apply it, otherwise clear it
        if (generated) {
            // std::cout << "generator: applying the affix" << std::endl;
            if (affix_type == PREFIX_CLASS)
                i->add_prefix(rolled_affix_type);
            if (affix_type == SUFFIX_CLASS)
                i->add_suffix(rolled_affix_type);
        }
        else {
            // std::cout << "generator: no affix was applied" << std::endl;
            if (affix_type == PREFIX_CLASS)
                i->remove_prefix();
            if (affix_type == SUFFIX_CLASS)
                i->remove_suffix();           
        }
    }
    else
    {
        // std::cout << "generator: 'apply affix' roll failed, no affix was applied" << std::endl;
        if (affix_type == PREFIX_CLASS)
            i->remove_prefix();
        if (affix_type == SUFFIX_CLASS)
            i->remove_suffix();
    } 
}

// Attempts to curse an item according to a weighting factor.
//
// Arguments:
//   i - the item to curse
//
// Returns:
//   Nothing.
void ItemGenerator::apply_curse(Item *i) {
    int roll = rand() % 100;
    if (roll < CHANCE_OF_CURSE) {
        i->set_curse_state(true);
        //std::cout << "generator: Item was cursed" << std::endl;
    }
    else {
        i->set_curse_state(false);
    }
}