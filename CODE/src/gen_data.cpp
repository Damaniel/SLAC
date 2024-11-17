// Auto-generated file - do not edit!
#include "globals.h"

const int g_weapon_base_pool_entries = 6635;
const int g_weapon_base_pool_count = 42;
const int g_armor_base_pool_entries = 12025;
const int g_armor_base_pool_count = 84;
const int g_item_prefix_pool_entries = 368;
const int g_item_prefix_pool_count = 2;
const int g_item_suffix_pool_entries = 240;
const int g_item_suffix_pool_count = 1;

int g_weapon_base_pool [] = { 255, 495, 695, 855, 975, 1015, 1270, 1505, 1700, 1855, 1965, 1995, 2250, 2485, 2680, 2835, 2945, 
      2975, 3230, 3465, 3660, 3815, 3925, 3955, 4195, 4420, 4600, 4730, 4830, 4845, 5100, 5330, 5515, 
      5660, 5760, 5785, 6015, 6230, 6400, 6520, 6615, 6635 };
int g_armor_base_pool [] = { 255, 475, 655, 805, 905, 955, 1210, 1420, 1590, 1720, 1800, 1830, 2085, 2305, 2485, 2635, 2735, 
      2785, 3040, 3250, 3420, 3550, 3630, 3660, 3915, 4125, 4295, 4435, 4525, 4565, 4820, 5020, 5170, 
      5270, 5315, 5325, 5580, 5800, 5980, 6130, 6230, 6280, 6535, 6745, 6915, 7045, 7125, 7155, 7410, 
      7630, 7810, 7960, 8060, 8110, 8365, 8575, 8745, 8875, 8955, 8985, 9240, 9460, 9640, 9790, 9890, 
      9940, 10195, 10405, 10575, 10705, 10785, 10815, 11015, 11175, 11295, 11375, 11415, 11420, 11620, 11780, 11900, 
      11980, 12020, 12025 };
int g_item_prefix_pool [] = { 240, 368 };
int g_item_suffix_pool [] = { 240 };

// BodyPartType g_body_part_type_ids
//
//   A list of body part types for equipment
//
//   Fields:
//   {id, name}
//
BodyPartType g_body_part_type_ids[] = {
   {0, "head"},
   {1, "hand"},
   {2, "chest"},
   {3, "legs"},
   {4, "feet"},
   {5, "shield"},
   {6, "ring"},
   {7, "amulet"}
};

// WeaponType g_weapon_type_ids
//
//   A list of weapon types
//
//   Fields:
//   {id, name, handed}
//
WeaponType g_weapon_type_ids[] = {
   {0, "Dagger", 1},
   {1, "Sword", 1},
   {2, "Broadsword", 2},
   {3, "Axe", 1},
   {4, "Battleaxe", 2},
   {5, "Mace", 1},
   {6, "Maul", 1}
};

// ArmorType g_armor_type_ids
//
//   A list of armor types
//
//   Fields:
//   {id, name, body_part}
//
ArmorType g_armor_type_ids[] = {
   {0, "Hat", 0},
   {1, "Helm", 0},
   {2, "Gloves", 1},
   {3, "Gauntlets", 1},
   {4, "Shirt", 2},
   {5, "Mail", 2},
   {6, "Pants", 3},
   {7, "Leggings", 3},
   {8, "Shoes", 4},
   {9, "Boots", 4},
   {10, "Buckler", 5},
   {11, "Shield", 5},
   {12, "Ring", 6},
   {13, "Amulet", 7}
};

// WeaponBaseType g_weapon_base_ids
//
//   A list of weapon base types
//
//   Fields:
//   {id, name, gid, type id, attack, rarity, depth, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
WeaponBaseType g_weapon_base_ids[] = {
   {0, "Wooden Dagger", 0, 0, 1, 255, {1, 1, 1}, 2, true, true, true, false, true, true, false},
   {1, "Copper Dagger", 1, 0, 3, 240, {2, 1, 1}, 5, true, true, true, false, true, true, false},
   {2, "Bronze Dagger", 2, 0, 8, 200, {5, 1, 1}, 10, true, true, true, false, true, true, false},
   {3, "Iron Dagger", 3, 0, 18, 160, {15, 2, 1}, 30, true, true, true, false, true, true, false},
   {4, "Steel Dagger", 4, 0, 35, 120, {25, 10, 1}, 100, true, true, true, false, true, true, false},
   {5, "Mythril Dagger", 5, 0, 80, 40, {25, 50, 1}, 600, true, true, true, false, true, true, false},
   {6, "Wooden Sword", 6, 1, 2, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {7, "Copper Sword", 7, 1, 8, 235, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {8, "Bronze Sword", 8, 1, 15, 195, {5, 1, 1}, 20, true, true, true, false, true, true, false},
   {9, "Iron Sword", 9, 1, 38, 155, {15, 2, 1}, 60, true, true, true, false, true, true, false},
   {10, "Steel Sword", 10, 1, 75, 110, {25, 10, 1}, 250, true, true, true, false, true, true, false},
   {11, "Mythril Sword", 11, 1, 130, 30, {25, 50, 1}, 1500, true, true, true, false, true, true, false},
   {12, "Wooden Broadsword", 12, 2, 5, 255, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {13, "Copper Broadsword", 13, 2, 15, 235, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {14, "Bronze Broadsword", 14, 2, 35, 195, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {15, "Iron Broadsword", 15, 2, 80, 155, {25, 5, 1}, 400, true, true, true, false, true, true, false},
   {16, "Steel Broadsword", 16, 2, 150, 110, {25, 25, 1}, 1300, true, true, true, false, true, true, false},
   {17, "Mythril Broadsword", 17, 2, 255, 30, {25, 50, 10}, 3000, true, true, true, false, true, true, false},
   {18, "Wooden Axe", 18, 3, 4, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {19, "Copper Axe", 19, 3, 12, 235, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {20, "Bronze Axe", 20, 3, 25, 195, {5, 1, 1}, 20, true, true, true, false, true, true, false},
   {21, "Iron Axe", 21, 3, 50, 155, {15, 2, 1}, 60, true, true, true, false, true, true, false},
   {22, "Steel Axe", 22, 3, 110, 110, {25, 10, 1}, 250, true, true, true, false, true, true, false},
   {23, "Mythril Axe", 23, 3, 160, 30, {25, 50, 1}, 1500, true, true, true, false, true, true, false},
   {24, "Wooden Battleaxe", 24, 4, 10, 240, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {25, "Copper Battleaxe", 25, 4, 30, 225, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {26, "Bronze Battleaxe", 26, 4, 70, 180, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {27, "Iron Battleaxe", 27, 4, 120, 130, {25, 5, 1}, 400, true, true, true, false, true, true, false},
   {28, "Steel Battleaxe", 28, 4, 175, 100, {25, 25, 1}, 1300, true, true, true, false, true, true, false},
   {29, "Mythril Battleaxe", 29, 4, 255, 15, {25, 50, 10}, 1300, true, true, true, false, true, true, false},
   {30, "Wooden Mace", 30, 5, 5, 255, {1, 1, 1}, 8, true, true, true, false, true, true, false},
   {31, "Copper Mace", 31, 5, 15, 230, {5, 1, 1}, 25, true, true, true, false, true, true, false},
   {32, "Bronze Mace", 32, 5, 25, 185, {20, 1, 1}, 80, true, true, true, false, true, true, false},
   {33, "Iron Mace", 33, 5, 45, 145, {25, 1, 1}, 250, true, true, true, false, true, true, false},
   {34, "Steel Mace", 34, 5, 80, 100, {25, 10, 1}, 1000, true, true, true, false, true, true, false},
   {35, "Mythril Mace", 35, 5, 120, 25, {25, 20, 1}, 2500, true, true, true, false, true, true, false},
   {36, "Wooden Maul", 36, 6, 15, 230, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {37, "Copper Maul", 37, 6, 40, 215, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {38, "Bronze Maul", 38, 6, 80, 170, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {39, "Iron Maul", 39, 6, 130, 120, {25, 15, 1}, 400, true, true, true, false, true, true, false},
   {40, "Steel Maul", 40, 6, 180, 95, {25, 35, 5}, 1300, true, true, true, false, true, true, false},
   {41, "Mythril Maul", 41, 6, 255, 20, {25, 50, 25}, 3000, true, true, true, false, true, true, false}
};

// ArmorBaseType g_armor_base_ids
//
//   A list of armor base types
//
//   Fields:
//   {id, name, gid, type id, defense, rarity, depth, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArmorBaseType g_armor_base_ids[] = {
   {0, "Cloth Hat", 42, 0, 1, 255, {1, 1, 1}, 2, true, true, true, false, true, true, false},
   {1, "Felt Hat", 43, 0, 3, 220, {2, 1, 1}, 5, true, true, true, false, true, true, false},
   {2, "Reinforced Hat", 44, 0, 8, 180, {5, 1, 1}, 10, true, true, true, false, true, true, false},
   {3, "Leather Hat", 45, 0, 15, 150, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {4, "Fur Hat", 46, 0, 25, 100, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {5, "Mage's Hat", 47, 0, 40, 50, {25, 5, 1}, 600, true, true, true, false, true, true, false},
   {6, "Wooden Helm", 48, 1, 3, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {7, "Copper Helm", 49, 1, 10, 210, {3, 1, 1}, 10, true, true, true, false, true, true, false},
   {8, "Bronze Helm", 50, 1, 20, 170, {10, 1, 1}, 20, true, true, true, false, true, true, false},
   {9, "Iron Helm", 51, 1, 45, 130, {20, 1, 1}, 60, true, true, true, false, true, true, false},
   {10, "Steel Helm", 52, 1, 65, 80, {25, 2, 1}, 250, true, true, true, false, true, true, false},
   {11, "Mythril Helm", 53, 1, 90, 30, {25, 20, 1}, 1500, true, true, true, false, true, true, false},
   {12, "Cloth Gloves", 54, 2, 1, 255, {1, 1, 1}, 2, true, true, true, false, true, true, false},
   {13, "Felt Gloves", 55, 2, 3, 220, {2, 1, 1}, 5, true, true, true, false, true, true, false},
   {14, "Reinforced Gloves", 56, 2, 8, 180, {5, 1, 1}, 10, true, true, true, false, true, true, false},
   {15, "Leather Gloves", 57, 2, 15, 150, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {16, "Fur Gloves", 58, 2, 25, 100, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {17, "Mage's Gloves", 59, 2, 40, 50, {25, 5, 1}, 600, true, true, true, false, true, true, false},
   {18, "Wooden Gauntlets", 60, 3, 3, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {19, "Copper Gauntlets", 61, 3, 10, 210, {3, 1, 1}, 10, true, true, true, false, true, true, false},
   {20, "Bronze Gauntlets", 62, 3, 20, 170, {10, 1, 1}, 20, true, true, true, false, true, true, false},
   {21, "Iron Gauntlets", 63, 3, 45, 130, {20, 1, 1}, 60, true, true, true, false, true, true, false},
   {22, "Steel Gauntlets", 64, 3, 65, 80, {25, 2, 1}, 250, true, true, true, false, true, true, false},
   {23, "Mythril Gauntlets", 65, 3, 90, 30, {25, 20, 1}, 1500, true, true, true, false, true, true, false},
   {24, "Cloth Shirt", 66, 4, 3, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {25, "Felt Shirt", 67, 4, 8, 210, {3, 1, 1}, 10, true, true, true, false, true, true, false},
   {26, "Reinforced Shirt", 68, 4, 15, 170, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {27, "Leather Shirt", 69, 4, 25, 140, {20, 1, 1}, 100, true, true, true, false, true, true, false},
   {28, "Fur Shirt", 70, 4, 40, 90, {25, 2, 1}, 600, true, true, true, false, true, true, false},
   {29, "Mage's Shirt", 71, 4, 60, 40, {25, 20, 1}, 1200, true, true, true, false, true, true, false},
   {30, "Wooden Mail", 72, 5, 10, 255, {1, 1, 1}, 10, true, true, true, false, true, true, false},
   {31, "Copper Mail", 73, 5, 20, 200, {5, 1, 1}, 50, true, true, true, false, true, true, false},
   {32, "Bronze Mail", 74, 5, 45, 150, {20, 1, 1}, 100, true, true, true, false, true, true, false},
   {33, "Iron Mail", 75, 5, 65, 100, {25, 5, 1}, 400, true, true, true, false, true, true, false},
   {34, "Steel Mail", 76, 5, 90, 45, {25, 25, 1}, 1500, true, true, true, false, true, true, false},
   {35, "Mythril Mail", 77, 5, 130, 10, {25, 50, 10}, 3000, true, true, true, false, true, true, false},
   {36, "Cloth Pants", 78, 6, 3, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {37, "Felt Pants", 79, 6, 8, 220, {2, 1, 1}, 10, true, true, true, false, true, true, false},
   {38, "Reinforced Pants", 80, 6, 15, 180, {5, 1, 1}, 30, true, true, true, false, true, true, false},
   {39, "Leather Pants", 81, 6, 25, 150, {10, 1, 1}, 100, true, true, true, false, true, true, false},
   {40, "Fur Pants", 82, 6, 40, 100, {25, 1, 1}, 600, true, true, true, false, true, true, false},
   {41, "Mage's Pants", 83, 6, 60, 50, {25, 5, 1}, 1000, true, true, true, false, true, true, false},
   {42, "Wooden Leggings", 84, 7, 10, 255, {1, 1, 1}, 10, true, true, true, false, true, true, false},
   {43, "Copper Leggings", 85, 7, 20, 210, {3, 1, 1}, 50, true, true, true, false, true, true, false},
   {44, "Bronze Leggings", 86, 7, 45, 170, {10, 1, 1}, 100, true, true, true, false, true, true, false},
   {45, "Iron Leggings", 87, 7, 65, 130, {20, 1, 1}, 400, true, true, true, false, true, true, false},
   {46, "Steel Leggings", 88, 7, 90, 80, {25, 2, 1}, 1000, true, true, true, false, true, true, false},
   {47, "Mythril Leggings", 89, 7, 130, 30, {25, 20, 1}, 2000, true, true, true, false, true, true, false},
   {48, "Cloth Shoes", 90, 8, 1, 255, {1, 1, 1}, 2, true, true, true, false, true, true, false},
   {49, "Felt Shoes", 91, 8, 3, 220, {2, 1, 1}, 5, true, true, true, false, true, true, false},
   {50, "Reinforced Shoes", 92, 8, 8, 180, {5, 1, 1}, 10, true, true, true, false, true, true, false},
   {51, "Leather Shoes", 93, 8, 15, 150, {10, 1, 1}, 30, true, true, true, false, true, true, false},
   {52, "Fur Shoes", 94, 8, 25, 100, {25, 1, 1}, 100, true, true, true, false, true, true, false},
   {53, "Mage's Shoes", 95, 8, 40, 50, {25, 5, 1}, 600, true, true, true, false, true, true, false},
   {54, "Wooden Boots", 96, 9, 3, 255, {1, 1, 1}, 5, true, true, true, false, true, true, false},
   {55, "Copper Boots", 97, 9, 10, 210, {3, 1, 1}, 10, true, true, true, false, true, true, false},
   {56, "Bronze Boots", 98, 9, 20, 170, {10, 1, 1}, 20, true, true, true, false, true, true, false},
   {57, "Iron Boots", 99, 9, 45, 130, {20, 1, 1}, 60, true, true, true, false, true, true, false},
   {58, "Steel Boots", 100, 9, 65, 80, {25, 2, 1}, 250, true, true, true, false, true, true, false},
   {59, "Mythril Boots", 101, 9, 90, 30, {25, 20, 1}, 1500, true, true, true, false, true, true, false},
   {60, "Leather Buckler", 102, 10, 5, 255, {1, 1, 1}, 15, true, true, true, false, true, true, false},
   {61, "Reinforced Buckler", 103, 10, 15, 220, {5, 1, 1}, 80, true, true, true, false, true, true, false},
   {62, "Wooden Buckler", 104, 10, 25, 180, {15, 1, 1}, 200, true, true, true, false, true, true, false},
   {63, "Bronze Buckler", 105, 10, 45, 150, {25, 5, 1}, 400, true, true, true, false, true, true, false},
   {64, "Steel Buckler", 106, 10, 65, 100, {25, 20, 2}, 800, true, true, true, false, true, true, false},
   {65, "Mythril Buckler", 107, 10, 85, 50, {25, 50, 15}, 2000, true, true, true, false, true, true, false},
   {66, "Wooden Shield", 108, 11, 10, 255, {3, 1, 1}, 20, true, true, true, false, true, true, false},
   {67, "Copper Shield", 109, 11, 20, 210, {8, 1, 1}, 100, true, true, true, false, true, true, false},
   {68, "Bronze Shield", 110, 11, 30, 170, {20, 1, 1}, 250, true, true, true, false, true, true, false},
   {69, "Iron Shield", 111, 11, 50, 130, {25, 5, 1}, 500, true, true, true, false, true, true, false},
   {70, "Steel Shield", 112, 11, 70, 80, {25, 25, 5}, 1200, true, true, true, false, true, true, false},
   {71, "Mythril Shield", 113, 11, 90, 30, {25, 50, 25}, 2400, true, true, true, false, true, true, false},
   {72, "Copper Ring", 114, 12, 1, 200, {1, 1, 1}, 100, true, true, true, false, true, true, false},
   {73, "Brass Ring", 115, 12, 2, 160, {10, 1, 1}, 300, true, true, true, false, true, true, false},
   {74, "Silver Ring", 116, 12, 3, 120, {25, 5, 1}, 800, true, true, true, false, true, true, false},
   {75, "Gold Ring", 117, 12, 4, 80, {25, 25, 5}, 1500, true, true, true, false, true, true, false},
   {76, "Electrum Ring", 118, 12, 5, 40, {25, 50, 10}, 2500, true, true, true, false, true, true, false},
   {77, "Mythril Ring", 119, 12, 6, 5, {25, 50, 40}, 5000, true, true, true, false, true, true, false},
   {78, "Copper Amulet", 120, 13, 1, 200, {1, 1, 1}, 100, true, true, true, false, true, true, false},
   {79, "Bronze Amulet", 121, 13, 2, 160, {10, 1, 1}, 300, true, true, true, false, true, true, false},
   {80, "Silver Amulet", 122, 13, 3, 120, {25, 5, 1}, 800, true, true, true, false, true, true, false},
   {81, "Gold Amulet", 123, 13, 4, 80, {25, 25, 5}, 1500, true, true, true, false, true, true, false},
   {82, "Electrum Amulet", 124, 13, 5, 40, {25, 50, 10}, 2500, true, true, true, false, true, true, false},
   {83, "Mythril Amulet", 125, 13, 6, 5, {25, 50, 40}, 5000, true, true, true, false, true, true, false}
};

// ModifierType g_modifier_ids
//
//   Equipment modifiers (stat and otherwise)
//
//   Fields:
//   {id, name, abbrev_name}
//
ModifierType g_modifier_ids[] = {
   {0, "Strength", "STR"},
   {1, "Constitution", "CON"},
   {2, "Dexterity", "DEX"},
   {3, "Attack", "ATK"},
   {4, "Defense", "DEF"},
   {5, "Speed", "SPD"},
   {6, "Fire Attack", "FAtk"},
   {7, "Ice Attack", "IAtk"},
   {8, "Lightning Attack", "LAtk"},
   {9, "Fire Resist", "FRes"},
   {10, "Ice Resist", "IRes"},
   {11, "Lightning Resist", "LRes"},
   {12, "Attacks Per Turn", "APT"}
};

// ItemPrefixType g_item_prefix_ids
//
//   Item prefixes
//
//   Fields:
//   {id, name, gid, rarity, weapons?, armor?, shield?, jewelry?, modifier(s)}
//
ItemPrefixType g_item_prefix_ids[] = {
   {0, "Strong", 0, 240, true, false, false, false, 1, {{3, false, 1.1}}},
   {1, "Mighty", 1, 128, true, false, false, false, 2, {{3, 0, 1.25}, {0, 1, 1}}}
};

// ItemSuffixType g_item_suffix_ids
//
//   Item suffixes
//
//   Fields:
//   {id, name, gid, rarity, weapons?, armor?, shield?, jewelry?, modifier(s)}
//
ItemSuffixType g_item_suffix_ids[] = {
   {0, "of Strength", 0, 240, true, false, false, false, 1, {{3, true, 1}}}
};

