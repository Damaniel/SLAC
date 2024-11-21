// Auto-generated file - do not edit!
#include "globals.h"

const int g_weapon_base_pool_entries = 6635;
const int g_weapon_base_pool_count = 42;
const int g_armor_base_pool_entries = 12025;
const int g_armor_base_pool_count = 84;
const int g_currency_pool_entries = 580;
const int g_currency_pool_count = 4;
const int g_potion_pool_entries = 1225;
const int g_potion_pool_count = 12;
const int g_scroll_pool_entries = 1553;
const int g_scroll_pool_count = 12;
const int g_artifact_pool_entries = 6056;
const int g_artifact_pool_count = 63;
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
int g_currency_pool [] = { 255, 455, 555, 580 };
int g_potion_pool [] = { 255, 405, 425, 625, 825, 875, 925, 975, 995, 1115, 1215, 1225 };
int g_scroll_pool [] = { 255, 280, 480, 640, 790, 795, 975, 1200, 1328, 1478, 1528, 1553 };
int g_artifact_pool [] = { 255, 510, 765, 1020, 1275, 1530, 1770, 1920, 2070, 2220, 2370, 2520, 2670, 2798, 2862, 2926, 2990, 
      3054, 3118, 3182, 3214, 3406, 3598, 3790, 3886, 3982, 4078, 4110, 4142, 4174, 4238, 4254, 4258, 
      4482, 4706, 4930, 5042, 5154, 5266, 5298, 5330, 5362, 5458, 5506, 5522, 5538, 5570, 5698, 5826, 
      5858, 5890, 5894, 5898, 5906, 5914, 5946, 5962, 5966, 5970, 5974, 5976, 6040, 6056 };
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
//   {id, name, gid, type id, attack, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
WeaponBaseType g_weapon_base_ids[] = {
   {0, "Wooden Dagger", 0, 0, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {1, "Copper Dagger", 1, 0, 3, 240, 2, 5, true, true, true, false, true, true, false},
   {2, "Bronze Dagger", 2, 0, 8, 200, 5, 10, true, true, true, false, true, true, false},
   {3, "Iron Dagger", 3, 0, 18, 160, 10, 30, true, true, true, false, true, true, false},
   {4, "Steel Dagger", 4, 0, 35, 120, 20, 100, true, true, true, false, true, true, false},
   {5, "Mythril Dagger", 5, 0, 80, 40, 40, 600, true, true, true, false, true, true, false},
   {6, "Wooden Sword", 6, 1, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {7, "Copper Sword", 7, 1, 8, 235, 4, 10, true, true, true, false, true, true, false},
   {8, "Bronze Sword", 8, 1, 15, 195, 10, 20, true, true, true, false, true, true, false},
   {9, "Iron Sword", 9, 1, 38, 155, 20, 60, true, true, true, false, true, true, false},
   {10, "Steel Sword", 10, 1, 75, 110, 40, 250, true, true, true, false, true, true, false},
   {11, "Mythril Sword", 11, 1, 130, 30, 60, 1500, true, true, true, false, true, true, false},
   {12, "Wooden Broadsword", 12, 2, 5, 255, 4, 10, true, true, true, false, true, true, false},
   {13, "Copper Broadsword", 13, 2, 15, 235, 8, 30, true, true, true, false, true, true, false},
   {14, "Bronze Broadsword", 14, 2, 35, 195, 15, 100, true, true, true, false, true, true, false},
   {15, "Iron Broadsword", 15, 2, 80, 155, 30, 400, true, true, true, false, true, true, false},
   {16, "Steel Broadsword", 16, 2, 150, 110, 50, 1300, true, true, true, false, true, true, false},
   {17, "Mythril Broadsword", 17, 2, 255, 30, 75, 3000, true, true, true, false, true, true, false},
   {18, "Wooden Axe", 18, 3, 4, 255, 2, 5, true, true, true, false, true, true, false},
   {19, "Copper Axe", 19, 3, 12, 235, 4, 10, true, true, true, false, true, true, false},
   {20, "Bronze Axe", 20, 3, 25, 195, 10, 20, true, true, true, false, true, true, false},
   {21, "Iron Axe", 21, 3, 50, 155, 20, 60, true, true, true, false, true, true, false},
   {22, "Steel Axe", 22, 3, 110, 110, 40, 250, true, true, true, false, true, true, false},
   {23, "Mythril Axe", 23, 3, 160, 30, 60, 1500, true, true, true, false, true, true, false},
   {24, "Wooden Battleaxe", 24, 4, 10, 240, 5, 10, true, true, true, false, true, true, false},
   {25, "Copper Battleaxe", 25, 4, 30, 225, 10, 30, true, true, true, false, true, true, false},
   {26, "Bronze Battleaxe", 26, 4, 70, 180, 20, 100, true, true, true, false, true, true, false},
   {27, "Iron Battleaxe", 27, 4, 120, 130, 40, 400, true, true, true, false, true, true, false},
   {28, "Steel Battleaxe", 28, 4, 175, 100, 60, 1300, true, true, true, false, true, true, false},
   {29, "Mythril Battleaxe", 29, 4, 255, 15, 80, 1300, true, true, true, false, true, true, false},
   {30, "Wooden Mace", 30, 5, 5, 255, 3, 8, true, true, true, false, true, true, false},
   {31, "Copper Mace", 31, 5, 15, 230, 6, 25, true, true, true, false, true, true, false},
   {32, "Bronze Mace", 32, 5, 25, 185, 12, 80, true, true, true, false, true, true, false},
   {33, "Iron Mace", 33, 5, 45, 145, 25, 250, true, true, true, false, true, true, false},
   {34, "Steel Mace", 34, 5, 80, 100, 45, 1000, true, true, true, false, true, true, false},
   {35, "Mythril Mace", 35, 5, 120, 25, 65, 2500, true, true, true, false, true, true, false},
   {36, "Wooden Maul", 36, 6, 15, 230, 5, 10, true, true, true, false, true, true, false},
   {37, "Copper Maul", 37, 6, 40, 215, 10, 30, true, true, true, false, true, true, false},
   {38, "Bronze Maul", 38, 6, 80, 170, 25, 100, true, true, true, false, true, true, false},
   {39, "Iron Maul", 39, 6, 130, 120, 45, 400, true, true, true, false, true, true, false},
   {40, "Steel Maul", 40, 6, 180, 95, 65, 1300, true, true, true, false, true, true, false},
   {41, "Mythril Maul", 41, 6, 255, 20, 85, 3000, true, true, true, false, true, true, false}
};

// ArmorBaseType g_armor_base_ids
//
//   A list of armor base types
//
//   Fields:
//   {id, name, gid, type id, defense, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArmorBaseType g_armor_base_ids[] = {
   {0, "Cloth Hat", 42, 0, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {1, "Felt Hat", 43, 0, 3, 220, 2, 5, true, true, true, false, true, true, false},
   {2, "Reinforced Hat", 44, 0, 8, 180, 5, 10, true, true, true, false, true, true, false},
   {3, "Leather Hat", 45, 0, 15, 150, 10, 30, true, true, true, false, true, true, false},
   {4, "Fur Hat", 46, 0, 25, 100, 20, 100, true, true, true, false, true, true, false},
   {5, "Mage's Hat", 47, 0, 40, 50, 40, 600, true, true, true, false, true, true, false},
   {6, "Wooden Helm", 48, 1, 3, 255, 2, 5, true, true, true, false, true, true, false},
   {7, "Copper Helm", 49, 1, 10, 210, 4, 10, true, true, true, false, true, true, false},
   {8, "Bronze Helm", 50, 1, 20, 170, 10, 20, true, true, true, false, true, true, false},
   {9, "Iron Helm", 51, 1, 45, 130, 20, 60, true, true, true, false, true, true, false},
   {10, "Steel Helm", 52, 1, 65, 80, 40, 250, true, true, true, false, true, true, false},
   {11, "Mythril Helm", 53, 1, 90, 30, 60, 1500, true, true, true, false, true, true, false},
   {12, "Cloth Gloves", 54, 2, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {13, "Felt Gloves", 55, 2, 3, 220, 2, 5, true, true, true, false, true, true, false},
   {14, "Reinforced Gloves", 56, 2, 8, 180, 5, 10, true, true, true, false, true, true, false},
   {15, "Leather Gloves", 57, 2, 15, 150, 10, 30, true, true, true, false, true, true, false},
   {16, "Fur Gloves", 58, 2, 25, 100, 20, 100, true, true, true, false, true, true, false},
   {17, "Mage's Gloves", 59, 2, 40, 50, 40, 600, true, true, true, false, true, true, false},
   {18, "Wooden Gauntlets", 60, 3, 3, 255, 2, 5, true, true, true, false, true, true, false},
   {19, "Copper Gauntlets", 61, 3, 10, 210, 4, 10, true, true, true, false, true, true, false},
   {20, "Bronze Gauntlets", 62, 3, 20, 170, 10, 20, true, true, true, false, true, true, false},
   {21, "Iron Gauntlets", 63, 3, 45, 130, 20, 60, true, true, true, false, true, true, false},
   {22, "Steel Gauntlets", 64, 3, 65, 80, 40, 250, true, true, true, false, true, true, false},
   {23, "Mythril Gauntlets", 65, 3, 90, 30, 60, 1500, true, true, true, false, true, true, false},
   {24, "Cloth Shirt", 66, 4, 3, 255, 1, 5, true, true, true, false, true, true, false},
   {25, "Felt Shirt", 67, 4, 8, 210, 3, 10, true, true, true, false, true, true, false},
   {26, "Reinforced Shirt", 68, 4, 15, 170, 8, 30, true, true, true, false, true, true, false},
   {27, "Leather Shirt", 69, 4, 25, 140, 15, 100, true, true, true, false, true, true, false},
   {28, "Fur Shirt", 70, 4, 40, 90, 30, 600, true, true, true, false, true, true, false},
   {29, "Mage's Shirt", 71, 4, 60, 40, 50, 1200, true, true, true, false, true, true, false},
   {30, "Wooden Mail", 72, 5, 10, 255, 5, 10, true, true, true, false, true, true, false},
   {31, "Copper Mail", 73, 5, 20, 200, 10, 50, true, true, true, false, true, true, false},
   {32, "Bronze Mail", 74, 5, 45, 150, 20, 100, true, true, true, false, true, true, false},
   {33, "Iron Mail", 75, 5, 65, 100, 40, 400, true, true, true, false, true, true, false},
   {34, "Steel Mail", 76, 5, 90, 45, 60, 1500, true, true, true, false, true, true, false},
   {35, "Mythril Mail", 77, 5, 130, 10, 80, 3000, true, true, true, false, true, true, false},
   {36, "Cloth Pants", 78, 6, 3, 255, 1, 5, true, true, true, false, true, true, false},
   {37, "Felt Pants", 79, 6, 8, 220, 3, 10, true, true, true, false, true, true, false},
   {38, "Reinforced Pants", 80, 6, 15, 180, 8, 30, true, true, true, false, true, true, false},
   {39, "Leather Pants", 81, 6, 25, 150, 15, 100, true, true, true, false, true, true, false},
   {40, "Fur Pants", 82, 6, 40, 100, 30, 600, true, true, true, false, true, true, false},
   {41, "Mage's Pants", 83, 6, 60, 50, 50, 1000, true, true, true, false, true, true, false},
   {42, "Wooden Leggings", 84, 7, 10, 255, 4, 10, true, true, true, false, true, true, false},
   {43, "Copper Leggings", 85, 7, 20, 210, 8, 50, true, true, true, false, true, true, false},
   {44, "Bronze Leggings", 86, 7, 45, 170, 15, 100, true, true, true, false, true, true, false},
   {45, "Iron Leggings", 87, 7, 65, 130, 30, 400, true, true, true, false, true, true, false},
   {46, "Steel Leggings", 88, 7, 90, 80, 50, 1000, true, true, true, false, true, true, false},
   {47, "Mythril Leggings", 89, 7, 130, 30, 70, 2000, true, true, true, false, true, true, false},
   {48, "Cloth Shoes", 90, 8, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {49, "Felt Shoes", 91, 8, 3, 220, 2, 5, true, true, true, false, true, true, false},
   {50, "Reinforced Shoes", 92, 8, 8, 180, 5, 10, true, true, true, false, true, true, false},
   {51, "Leather Shoes", 93, 8, 15, 150, 10, 30, true, true, true, false, true, true, false},
   {52, "Fur Shoes", 94, 8, 25, 100, 20, 100, true, true, true, false, true, true, false},
   {53, "Mage's Shoes", 95, 8, 40, 50, 40, 600, true, true, true, false, true, true, false},
   {54, "Wooden Boots", 96, 9, 3, 255, 2, 5, true, true, true, false, true, true, false},
   {55, "Copper Boots", 97, 9, 10, 210, 4, 10, true, true, true, false, true, true, false},
   {56, "Bronze Boots", 98, 9, 20, 170, 10, 20, true, true, true, false, true, true, false},
   {57, "Iron Boots", 99, 9, 45, 130, 20, 60, true, true, true, false, true, true, false},
   {58, "Steel Boots", 100, 9, 65, 80, 40, 250, true, true, true, false, true, true, false},
   {59, "Mythril Boots", 101, 9, 90, 30, 60, 1500, true, true, true, false, true, true, false},
   {60, "Leather Buckler", 102, 10, 5, 255, 2, 15, true, true, true, false, true, true, false},
   {61, "Reinforced Buckler", 103, 10, 15, 220, 4, 80, true, true, true, false, true, true, false},
   {62, "Wooden Buckler", 104, 10, 25, 180, 10, 200, true, true, true, false, true, true, false},
   {63, "Bronze Buckler", 105, 10, 45, 150, 20, 400, true, true, true, false, true, true, false},
   {64, "Steel Buckler", 106, 10, 65, 100, 40, 800, true, true, true, false, true, true, false},
   {65, "Mythril Buckler", 107, 10, 85, 50, 60, 2000, true, true, true, false, true, true, false},
   {66, "Wooden Shield", 108, 11, 10, 255, 4, 20, true, true, true, false, true, true, false},
   {67, "Copper Shield", 109, 11, 20, 210, 8, 100, true, true, true, false, true, true, false},
   {68, "Bronze Shield", 110, 11, 30, 170, 15, 250, true, true, true, false, true, true, false},
   {69, "Iron Shield", 111, 11, 50, 130, 30, 500, true, true, true, false, true, true, false},
   {70, "Steel Shield", 112, 11, 70, 80, 50, 1200, true, true, true, false, true, true, false},
   {71, "Mythril Shield", 113, 11, 90, 30, 75, 2400, true, true, true, false, true, true, false},
   {72, "Copper Ring", 114, 12, 1, 200, 5, 100, true, true, true, false, true, true, false},
   {73, "Brass Ring", 115, 12, 2, 160, 15, 300, true, true, true, false, true, true, false},
   {74, "Silver Ring", 116, 12, 3, 120, 30, 800, true, true, true, false, true, true, false},
   {75, "Gold Ring", 117, 12, 4, 80, 50, 1500, true, true, true, false, true, true, false},
   {76, "Electrum Ring", 118, 12, 5, 40, 70, 2500, true, true, true, false, true, true, false},
   {77, "Mythril Ring", 119, 12, 6, 5, 90, 5000, true, true, true, false, true, true, false},
   {78, "Copper Amulet", 120, 13, 1, 200, 5, 100, true, true, true, false, true, true, false},
   {79, "Bronze Amulet", 121, 13, 2, 160, 15, 300, true, true, true, false, true, true, false},
   {80, "Silver Amulet", 122, 13, 3, 120, 30, 800, true, true, true, false, true, true, false},
   {81, "Gold Amulet", 123, 13, 4, 80, 50, 1500, true, true, true, false, true, true, false},
   {82, "Electrum Amulet", 124, 13, 5, 40, 70, 2500, true, true, true, false, true, true, false},
   {83, "Mythril Amulet", 125, 13, 6, 5, 90, 5000, true, true, true, false, true, true, false}
};

// CurrencyType g_currency_ids
//
//   A list of currency types
//
//   Fields:
//   {id, name, gid, type id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
CurrencyType g_currency_ids[] = {
   {0, "Copper Coins", 126, 0, 255, 1, 1, false, false, false, true, false, true, false},
   {1, "Silver Coins", 127, 0, 200, 10, 10, false, false, false, true, false, true, false},
   {2, "Gold Coins", 128, 0, 100, 30, 100, false, false, false, true, false, true, false},
   {3, "Gems", 129, 0, 25, 70, 500, false, false, false, true, false, true, false}
};

// PotionType g_potion_ids
//
//   A list of potion types
//
//   Fields:
//   {id, name, gid, type id, effect id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
PotionType g_potion_ids[] = {
   {0, "Potion of Light Healing", 130, 0, 0, 255, 1, 10, false, false, false, true, false, true, true},
   {1, "Potion of Moderate Healing", 131, 0, 1, 150, 15, 100, false, false, false, true, false, true, true},
   {2, "Potion of Full Healing", 132, 0, 2, 20, 70, 1000, false, false, false, true, false, true, true},
   {3, "Potion of Cure Poison", 133, 0, 3, 200, 2, 50, false, false, false, true, false, true, true},
   {4, "Potion of Cure Paralysis", 134, 0, 4, 200, 10, 50, false, false, false, true, false, true, true},
   {5, "Potion of Berserk Strength", 135, 0, 5, 50, 50, 600, false, false, false, true, false, true, true},
   {6, "Potion of Speed", 136, 0, 6, 50, 50, 600, false, false, false, true, false, true, true},
   {7, "Potion of Hardiness", 137, 0, 7, 50, 50, 600, false, false, false, true, false, true, true},
   {8, "Potion of Extra Attacks", 138, 0, 8, 20, 60, 1000, false, false, false, true, false, true, true},
   {9, "Potion of Poison", 139, 0, 9, 120, 25, 20, false, false, false, true, false, true, true},
   {10, "Potion of Paralysis", 140, 0, 10, 100, 60, 20, false, false, false, true, false, true, true},
   {11, "Potion of Death", 141, 0, 11, 10, 75, 20, false, false, false, true, false, true, true}
};

// ScrollType g_scroll_ids
//
//   A list of scroll types
//
//   Fields:
//   {id, name, gid, type id, effect id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ScrollType g_scroll_ids[] = {
   {0, "Scroll of Identify", 142, 0, 12, 255, 1, 5, false, false, false, true, false, true, true},
   {1, "Scroll of Identify All", 143, 0, 13, 25, 60, 500, false, false, false, true, false, true, true},
   {2, "Scroll of Magic Map", 144, 0, 14, 200, 5, 25, false, false, false, true, false, true, true},
   {3, "Scroll of Discovery", 145, 0, 15, 160, 20, 100, false, false, false, true, false, true, true},
   {4, "Scroll of Decurse", 146, 0, 16, 150, 10, 200, false, false, false, true, false, true, true},
   {5, "Scroll of Decurse All", 147, 0, 17, 5, 80, 1500, false, false, false, true, false, true, true},
   {6, "Scroll of Teleport", 148, 0, 18, 180, 10, 30, false, false, false, true, false, true, true},
   {7, "Scroll of Recall", 149, 0, 19, 225, 3, 15, false, false, false, true, false, true, true},
   {8, "Scroll of Summon Item", 150, 0, 20, 128, 25, 250, false, false, false, true, false, true, true},
   {9, "Scroll of Darkness", 151, 0, 21, 150, 15, 15, false, false, false, true, false, true, true},
   {10, "Scroll of Forget Area", 152, 0, 22, 50, 30, 5, false, false, false, true, false, true, true},
   {11, "Scroll of Curse", 153, 0, 23, 25, 50, 10, false, false, false, true, false, true, true}
};

// ArtifactType g_artifact_ids
//
//   A list of artifact types
//
//   Fields:
//   {id, name, gid, artifact type, pieces, effect id, rarity, ilevel, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArtifactType g_artifact_ids[] = {
   {0, "Sign of Strength", 154, 0, 1, 24, 255, 5, false, false, false, true, false, false, false},
   {1, "Sign of Constitution", 155, 0, 1, 25, 255, 5, false, false, false, true, false, false, false},
   {2, "Sign of Dexterity", 156, 0, 1, 26, 255, 5, false, false, false, true, false, false, false},
   {3, "Sign of Attack", 157, 0, 1, 27, 255, 5, false, false, false, true, false, false, false},
   {4, "Sign of Defense", 158, 0, 1, 28, 255, 5, false, false, false, true, false, false, false},
   {5, "Sign of Accuracy", 159, 0, 1, 29, 255, 10, false, false, false, true, false, false, false},
   {6, "Sign of Speed", 160, 0, 1, 30, 240, 10, false, false, false, true, false, false, false},
   {7, "Medal of Strength", 161, 0, 1, 31, 150, 30, false, false, false, true, false, false, false},
   {8, "Medal of Constitution", 162, 0, 1, 32, 150, 30, false, false, false, true, false, false, false},
   {9, "Medal of Dexterity", 163, 0, 1, 33, 150, 30, false, false, false, true, false, false, false},
   {10, "Medal of Attack", 164, 0, 1, 34, 150, 30, false, false, false, true, false, false, false},
   {11, "Medal of Defense", 165, 0, 1, 35, 150, 30, false, false, false, true, false, false, false},
   {12, "Medal of Accuracy", 166, 0, 1, 36, 150, 35, false, false, false, true, false, false, false},
   {13, "Medal of Speed", 167, 0, 1, 37, 128, 35, false, false, false, true, false, false, false},
   {14, "Trophy of Strength", 168, 0, 1, 38, 64, 60, false, false, false, true, false, false, false},
   {15, "Trophy of Constitution", 169, 0, 1, 39, 64, 60, false, false, false, true, false, false, false},
   {16, "Trophy of Dexterity", 170, 0, 1, 40, 64, 60, false, false, false, true, false, false, false},
   {17, "Trophy of Attack", 171, 0, 1, 41, 64, 60, false, false, false, true, false, false, false},
   {18, "Trophy of Defense", 172, 0, 1, 42, 64, 60, false, false, false, true, false, false, false},
   {19, "Trophy of Accuracy", 173, 0, 1, 43, 64, 65, false, false, false, true, false, false, false},
   {20, "Trophy of Speed", 174, 0, 1, 44, 32, 65, false, false, false, true, false, false, false},
   {21, "Ward of Fire", 175, 0, 1, 45, 192, 8, false, false, false, true, false, false, false},
   {22, "Ward of Ice", 176, 0, 1, 46, 192, 8, false, false, false, true, false, false, false},
   {23, "Ward of Lightning", 177, 0, 1, 47, 192, 8, false, false, false, true, false, false, false},
   {24, "Sigil of Fire", 178, 0, 1, 48, 96, 35, false, false, false, true, false, false, false},
   {25, "Sigil of Ice", 179, 0, 1, 49, 96, 35, false, false, false, true, false, false, false},
   {26, "Sigil of Lightning", 180, 0, 1, 50, 96, 35, false, false, false, true, false, false, false},
   {27, "Relic of Fire", 181, 0, 1, 51, 32, 60, false, false, false, true, false, false, false},
   {28, "Relic of Ice", 182, 0, 1, 52, 32, 60, false, false, false, true, false, false, false},
   {29, "Relic of Lightning", 183, 0, 1, 53, 32, 60, false, false, false, true, false, false, false},
   {30, "Lucky Token", 184, 0, 1, 54, 64, 10, false, false, false, true, false, false, false},
   {31, "Lucky Coin", 185, 0, 1, 55, 16, 30, false, false, false, true, false, false, false},
   {32, "Lucky Pendant", 186, 0, 1, 56, 4, 50, false, false, false, true, false, false, false},
   {33, "Book of the Warrior", 187, 1, 2, 57, 224, 15, false, false, false, true, false, false, false},
   {34, "Book of the Thief", 188, 1, 2, 58, 224, 15, false, false, false, true, false, false, false},
   {35, "Book of the Combatant", 189, 1, 2, 59, 224, 15, false, false, false, true, false, false, false},
   {36, "Tome of the Warrior", 190, 1, 3, 60, 112, 40, false, false, false, true, false, false, false},
   {37, "Tome of the Thief", 191, 1, 3, 61, 112, 40, false, false, false, true, false, false, false},
   {38, "Tome of the Combatant", 192, 1, 3, 62, 112, 40, false, false, false, true, false, false, false},
   {39, "Bible of the Warrior", 193, 1, 5, 63, 32, 70, false, false, false, true, false, false, false},
   {40, "Bible of the Thief", 194, 1, 5, 64, 32, 70, false, false, false, true, false, false, false},
   {41, "Bible of the Combatant", 195, 1, 5, 65, 32, 70, false, false, false, true, false, false, false},
   {42, "Ward of the Elements", 196, 1, 2, 66, 96, 20, false, false, false, true, false, false, false},
   {43, "Sigil of the Elements", 197, 1, 4, 67, 48, 40, false, false, false, true, false, false, false},
   {44, "Relic of the Elements", 198, 1, 6, 68, 16, 65, false, false, false, true, false, false, false},
   {45, "Cup of Wealth", 199, 1, 8, 69, 16, 25, false, false, false, true, false, false, false},
   {46, "Puzzle Box of Frivolousness", 200, 1, 255, 70, 32, 1, false, false, false, true, false, false, false},
   {47, "Book of the Polymath", 201, 2, 3, 71, 128, 20, false, false, false, true, false, false, false},
   {48, "Book of the Gladiator", 202, 2, 3, 72, 128, 20, false, false, false, true, false, false, false},
   {49, "Tome of the Polymath", 203, 2, 5, 73, 32, 50, false, false, false, true, false, false, false},
   {50, "Tome of the Gladiator", 204, 2, 5, 74, 32, 50, false, false, false, true, false, false, false},
   {51, "Bible of the Polymath", 205, 2, 8, 75, 4, 90, false, false, false, true, false, false, false},
   {52, "Bible of the Gladiator", 206, 2, 8, 76, 4, 90, false, false, false, true, false, false, false},
   {53, "Trickster Trinket", 207, 2, 4, 77, 8, 80, false, false, false, true, false, false, false},
   {54, "Prismatic Mirror", 208, 2, 4, 78, 8, 75, false, false, false, true, false, false, false},
   {55, "Glasses of Foresight", 209, 2, 6, 79, 32, 45, false, false, false, true, false, false, false},
   {56, "Ethereal Barrier", 210, 2, 4, 80, 16, 70, false, false, false, true, false, false, false},
   {57, "Righteous Fire", 211, 2, 6, 81, 4, 80, false, false, false, true, false, false, false},
   {58, "Righteous Ice", 212, 2, 6, 82, 4, 80, false, false, false, true, false, false, false},
   {59, "Righteous Lightning", 213, 2, 6, 83, 4, 80, false, false, false, true, false, false, false},
   {60, "Ark of Enlightenment", 214, 2, 3, 84, 2, 85, false, false, false, true, false, false, false},
   {61, "Chalice of Riches", 215, 2, 16, 85, 64, 60, false, false, false, true, false, false, false},
   {62, "Amphora of Holy Water", 216, 2, 8, 86, 16, 40, false, false, false, true, false, false, false}
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
//   {id, name, gid, rarity, ilevel, modifier(s)}
//
ItemPrefixType g_item_prefix_ids[] = {
   {0, "Strong", 0, 240, 5, 1, {{3, 0, 1.1}}},
   {1, "Mighty", 1, 128, 20, 2, {{3, 0, 1.25}, {0, 1, 1}}}
};

// ItemSuffixType g_item_suffix_ids
//
//   Item suffixes
//
//   Fields:
//   {id, name, gid, rarity, ilevel, modifier(s)}
//
ItemSuffixType g_item_suffix_ids[] = {
   {0, "of Strength", 0, 240, 5, 1, {{3, 1, 1}}}
};

