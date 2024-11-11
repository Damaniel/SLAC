//==========================================================================================
//   Secret Legacy of the Ancient Caves (SLAC)
//
//   Copyright (c) 2020-2021 Shaun Brandt / Holy Meatgoat Software
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
#ifndef __INVNTORY_H__
#define __INVNTORY_H__

#include <string>
#include <vector>

// The maximum size of the inventory
#define INVENTORY_SIZE      48

// An item in the item database.
class DBItem {
public:
    std::string name;
    std::string scrambled_name;
    bool usable;
    bool equippable;
    
};

// An instance of a DBItem (for example, an item on the ground or bought in a 
// store)
class Item {
    DBItem i;
};

// An item in the player's inventory.  It's an instance of Item that has
// additional information useful to the player (how many does the player have?
// Is it identified or equipped?)
class InventoryItem {
public:
    Item i;
    int quantity;
    bool identified;
    bool equipped;
};

// The inventory as a whole (INVENTORY_SIZE slots of InventoryItem)
class Inventory {
public:
    InventoryItem items[INVENTORY_SIZE];
    void addItem(Item i);
    void removeItem(int index);
    void compactIventory(void);
};

// A database of all items in the game.
class ItemList {
public:
    std::vector<DBItem> items;
    void loadItemsFromFile(char *itemFile);
};

#endif 