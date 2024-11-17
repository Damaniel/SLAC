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
//  The index from the pool selected, or -1 if something went wrong
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
    return -1;
}

// Generates an item.  This can be anything, weighted by overall item class, item base type and mod types.
//
// Arguments:
//   None
//
// Returns:
//   A pointer to a randomly generated Item.
Item *ItemGenerator::generate() {
    Item *i;
    int item_type = ItemGenerator::roll_from_pool(g_item_class_pool, g_item_class_pool_count, g_item_class_pool_entries);
    i = ItemGenerator::generate(item_type);
    return i;
}

// Generates an item of a particular item class, weighted by base type and mod types.
//
// Arguments:
//   item_type - item to generate
//
// Returns:
//   A pointer to a randomly generated Item of the item type.
//
// Valid item types are (WEAPON_CLASS, ARMOR_CLASS, CURRENCY_CLASS, CONSUMABLE_CLASS, ARTIFACT_CLASS).
Item *ItemGenerator::generate(int item_type) {
    Item *i;
    int *base_pool, pool_count, pool_entries;
    int rolled_base_type;

    if (item_type == WEAPON_CLASS || item_type == ARMOR_CLASS) {
        if (item_type == WEAPON_CLASS) {
            i = new Weapon();
            base_pool = g_weapon_base_pool;
            pool_count = g_weapon_base_pool_count;
            pool_entries = g_weapon_base_pool_entries;
            rolled_base_type = ItemGenerator::roll_from_pool(base_pool, pool_count, pool_entries);
        }
        else {
            i = new Armor();
            base_pool = g_armor_base_pool;
            pool_count = g_armor_base_pool_count;
            pool_entries = g_armor_base_pool_entries;
            rolled_base_type = ItemGenerator::roll_from_pool(base_pool, pool_count, pool_entries);            
        }
        i->init(rolled_base_type);
        ItemGenerator::apply_prefix(i);
        ItemGenerator::apply_suffix(i);
    }
    else {
        // Nothing else defined yet
        return NULL;
    }

    return i;
}

// Generates and applies a random prefix to an item, if the item is capable of taking one
//
// Arguments:
//   i - the Item to augment
//
// Returns:
//   Nothing
void ItemGenerator::apply_prefix(Item *i) {
    int roll;

    roll = rand() % 100;
    if (roll < CHANCE_OF_PREFIX) {
        int rolled_prefix_type = roll_from_pool(g_item_prefix_pool, g_item_prefix_pool_count, g_item_prefix_pool_entries);
        i->add_prefix(rolled_prefix_type);
    }
    else
    {
        i->remove_prefix();
    } 
}

// Generates and applies a random suffix to an item, if the item is capable of taking one
//
// Arguments:
//   i - the Item to augment
//
// Returns:
//   Nothing
void ItemGenerator::apply_suffix(Item *i) {
    int roll;

    roll = rand() % 100;
    if (roll < CHANCE_OF_SUFFIX) {
        int rolled_suffix_type = roll_from_pool(g_item_suffix_pool, g_item_suffix_pool_count, g_item_suffix_pool_entries);
        i->add_suffix(rolled_suffix_type);
    }
    else {
        i->remove_suffix();
    }
}
