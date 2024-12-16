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
const int g_item_prefix_pool_entries = 2810;
const int g_item_prefix_pool_count = 27;
const int g_cursed_item_prefix_pool_entries = 1800;
const int g_cursed_item_prefix_pool_count = 16;
const int g_item_suffix_pool_entries = 2700;
const int g_item_suffix_pool_count = 25;
const int g_cursed_item_suffix_pool_entries = 2177;
const int g_cursed_item_suffix_pool_count = 15;
const int g_enemy_pool_entries = 2550;
const int g_enemy_pool_count = 10;

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
int g_item_prefix_pool [] = { 240, 368, 400, 640, 768, 784, 1024, 1152, 1168, 1296, 1328, 1330, 1394, 1586, 1682, 1874, 1970, 
      2162, 2258, 2386, 2418, 2546, 2578, 2706, 2738, 2802, 2810 };
int g_cursed_item_prefix_pool [] = { 192, 288, 480, 576, 768, 864, 896, 904, 1064, 1128, 1288, 1352, 1544, 1640, 1768, 1800 };
int g_item_suffix_pool [] = { 240, 368, 432, 687, 815, 879, 1134, 1262, 1326, 1566, 1678, 1726, 1966, 2078, 2126, 2381, 2509, 
      2573, 2637, 2657, 2665, 2690, 2695, 2699, 2700 };
int g_cursed_item_suffix_pool [] = { 240, 352, 592, 704, 944, 1056, 1280, 1376, 1616, 1728, 1952, 2048, 2144, 2176, 2177 };
int g_enemy_pool [] = { 255, 510, 765, 1020, 1275, 1530, 1785, 2040, 2295, 2550 };

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
   {1, "Silver Coins", 127, 0, 200, 10, 5, false, false, false, true, false, true, false},
   {2, "Gold Coins", 128, 0, 100, 30, 25, false, false, false, true, false, true, false},
   {3, "Gems", 129, 0, 25, 70, 125, false, false, false, true, false, true, false}
};

// PotionType g_potion_ids
//
//   A list of potion types
//
//   Fields:
//   {id, name, description, gid, type id, effect id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
PotionType g_potion_ids[] = {
   {0, "Potion of Light Healing", "Recovers 10% of HP", 130, 0, 0, 255, 1, 10, false, false, false, true, false, true, true},
   {1, "Potion of Moderate Healing", "Recovers 50% of HP", 131, 0, 1, 150, 15, 100, false, false, false, true, false, true, true},
   {2, "Potion of Full Healing", "Recovers 100% of HP", 132, 0, 2, 20, 70, 1000, false, false, false, true, false, true, true},
   {3, "Potion of Cure Poison", "Removes poison", 133, 0, 3, 200, 2, 50, false, false, false, true, false, true, true},
   {4, "Potion of Cure Paralysis", "Removes paralysis", 134, 0, 4, 200, 10, 50, false, false, false, true, false, true, true},
   {5, "Potion of Berserk Strength", "+100% STR for 20 turns", 135, 0, 5, 50, 50, 600, false, false, false, true, false, true, true},
   {6, "Potion of Speed", "+100% SPD for 20 turns", 136, 0, 6, 50, 50, 600, false, false, false, true, false, true, true},
   {7, "Potion of Hardiness", "+100% HP for 20 turns", 137, 0, 7, 50, 50, 600, false, false, false, true, false, true, true},
   {8, "Potion of Extra Attacks", "+1 APT for 20 turns", 138, 0, 8, 20, 60, 1000, false, false, false, true, false, true, true},
   {9, "Potion of Poison", "Applies poison", 139, 0, 9, 120, 25, 20, false, false, false, true, false, true, true},
   {10, "Potion of Paralysis", "Applies paralysis", 140, 0, 10, 100, 60, 20, false, false, false, true, false, true, true},
   {11, "Potion of Death", "Reduces HP to 0", 141, 0, 11, 10, 75, 20, false, false, false, true, false, true, true}
};

// ScrollType g_scroll_ids
//
//   A list of scroll types
//
//   Fields:
//   {id, name, gid, type id, effect id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ScrollType g_scroll_ids[] = {
   {0, "Scroll of Identify", "Identifies an item", 142, 0, 12, 255, 1, 5, false, false, false, true, false, true, true},
   {1, "Scroll of Identify All", "Identifies all items", 143, 0, 13, 25, 60, 500, false, false, false, true, false, true, true},
   {2, "Scroll of Magic Map", "Marks map as discovered", 144, 0, 14, 200, 5, 25, false, false, false, true, false, true, true},
   {3, "Scroll of Discovery", "Shows items and stairs on map", 145, 0, 15, 160, 20, 100, false, false, false, true, false, true, true},
   {4, "Scroll of Decurse", "Removes curse from an item", 146, 0, 16, 150, 10, 200, false, false, false, true, false, true, true},
   {5, "Scroll of Decurse All", "Removes curse from all items", 147, 0, 17, 5, 80, 1500, false, false, false, true, false, true, true},
   {6, "Scroll of Teleport", "Moves player to a random location", 148, 0, 18, 180, 10, 30, false, false, false, true, false, true, true},
   {7, "Scroll of Recall", "Returns player to surface", 149, 0, 19, 225, 3, 15, false, false, false, true, false, true, true},
   {8, "Scroll of Summon Item", "Creates a good item", 150, 0, 20, 128, 25, 250, false, false, false, true, false, true, true},
   {9, "Scroll of Darkness", "Darkens all lit areas", 151, 0, 21, 150, 15, 15, false, false, false, true, false, true, true},
   {10, "Scroll of Forget Area", "Forgets the explored map", 152, 0, 22, 50, 30, 5, false, false, false, true, false, true, true},
   {11, "Scroll of Curse", "Curses a random unequipped item", 153, 0, 23, 25, 50, 10, false, false, false, true, false, true, true}
};

// ArtifactType g_artifact_ids
//
//   A list of artifact types
//
//   Fields:
//   {id, name, gid, description, artifact type, pieces, effect id, rarity, ilevel, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArtifactType g_artifact_ids[] = {
   {0, "Sign of Strength", "+1 STR", 154, 0, 1, 24, 255, 5, false, false, false, true, false, false, false},
   {1, "Sign of Constitution", "+1 CON", 155, 0, 1, 25, 255, 5, false, false, false, true, false, false, false},
   {2, "Sign of Dexterity", "+1 DEX", 156, 0, 1, 26, 255, 5, false, false, false, true, false, false, false},
   {3, "Sign of Attack", "+1 ATK", 157, 0, 1, 27, 255, 5, false, false, false, true, false, false, false},
   {4, "Sign of Defense", "+1 DEF", 158, 0, 1, 28, 255, 5, false, false, false, true, false, false, false},
   {5, "Sign of Accuracy", "+1 ACC", 159, 0, 1, 29, 255, 10, false, false, false, true, false, false, false},
   {6, "Sign of Speed", "+1 SPD", 160, 0, 1, 30, 240, 10, false, false, false, true, false, false, false},
   {7, "Medal of Strength", "+2 STR", 161, 0, 1, 31, 150, 30, false, false, false, true, false, false, false},
   {8, "Medal of Constitution", "+2 CON", 162, 0, 1, 32, 150, 30, false, false, false, true, false, false, false},
   {9, "Medal of Dexterity", "+2 DEX", 163, 0, 1, 33, 150, 30, false, false, false, true, false, false, false},
   {10, "Medal of Attack", "+2 ATK", 164, 0, 1, 34, 150, 30, false, false, false, true, false, false, false},
   {11, "Medal of Defense", "+2 DEF", 165, 0, 1, 35, 150, 30, false, false, false, true, false, false, false},
   {12, "Medal of Accuracy", "+2 ACC", 166, 0, 1, 36, 150, 35, false, false, false, true, false, false, false},
   {13, "Medal of Speed", "+2 SPD", 167, 0, 1, 37, 128, 35, false, false, false, true, false, false, false},
   {14, "Trophy of Strength", "+3 STR", 168, 0, 1, 38, 64, 60, false, false, false, true, false, false, false},
   {15, "Trophy of Constitution", "+3 CON", 169, 0, 1, 39, 64, 60, false, false, false, true, false, false, false},
   {16, "Trophy of Dexterity", "+3 DEX", 170, 0, 1, 40, 64, 60, false, false, false, true, false, false, false},
   {17, "Trophy of Attack", "+3 ATK", 171, 0, 1, 41, 64, 60, false, false, false, true, false, false, false},
   {18, "Trophy of Defense", "+3 DEF", 172, 0, 1, 42, 64, 60, false, false, false, true, false, false, false},
   {19, "Trophy of Accuracy", "+3 ACC", 173, 0, 1, 43, 64, 65, false, false, false, true, false, false, false},
   {20, "Trophy of Speed", "+3 SPD", 174, 0, 1, 44, 32, 65, false, false, false, true, false, false, false},
   {21, "Ward of Fire", "+1 Fire Resist", 175, 0, 1, 45, 192, 8, false, false, false, true, false, false, false},
   {22, "Ward of Ice", "+1 Ice Resist", 176, 0, 1, 46, 192, 8, false, false, false, true, false, false, false},
   {23, "Ward of Lightning", "+1 Lightning Resist", 177, 0, 1, 47, 192, 8, false, false, false, true, false, false, false},
   {24, "Sigil of Fire", "+2 Fire Resist", 178, 0, 1, 48, 96, 35, false, false, false, true, false, false, false},
   {25, "Sigil of Ice", "+2 Ice Resist", 179, 0, 1, 49, 96, 35, false, false, false, true, false, false, false},
   {26, "Sigil of Lightning", "+2 Lightning Resist", 180, 0, 1, 50, 96, 35, false, false, false, true, false, false, false},
   {27, "Relic of Fire", "+3 Fire Resist", 181, 0, 1, 51, 32, 60, false, false, false, true, false, false, false},
   {28, "Relic of Ice", "+3 Ice Resist", 182, 0, 1, 52, 32, 60, false, false, false, true, false, false, false},
   {29, "Relic of Lightning", "+3 Lightning Resist", 183, 0, 1, 53, 32, 60, false, false, false, true, false, false, false},
   {30, "Lucky Token", "+1% currency drop value", 184, 0, 1, 54, 64, 10, false, false, false, true, false, false, false},
   {31, "Lucky Coin", "+2% currency drop value", 185, 0, 1, 55, 16, 30, false, false, false, true, false, false, false},
   {32, "Lucky Pendant", "+3% currency drop value", 186, 0, 1, 56, 4, 50, false, false, false, true, false, false, false},
   {33, "Book of the Warrior", "+1 STR, +1 CON", 187, 1, 2, 57, 224, 15, false, false, false, true, false, false, false},
   {34, "Book of the Thief", "+1 SPD, +1 DEX", 188, 1, 2, 58, 224, 15, false, false, false, true, false, false, false},
   {35, "Book of the Combatant", "+1 ATK, +1 DEF", 189, 1, 2, 59, 224, 15, false, false, false, true, false, false, false},
   {36, "Tome of the Warrior", "+2 STR, +2 CON", 190, 1, 3, 60, 112, 40, false, false, false, true, false, false, false},
   {37, "Tome of the Thief", "+2 SPD, +2 DEX", 191, 1, 3, 61, 112, 40, false, false, false, true, false, false, false},
   {38, "Tome of the Combatant", "+2 ATK, +2 DEF", 192, 1, 3, 62, 112, 40, false, false, false, true, false, false, false},
   {39, "Bible of the Warrior", "+3 STR, +3 CON", 193, 1, 5, 63, 32, 70, false, false, false, true, false, false, false},
   {40, "Bible of the Thief", "+3 SPD, +3 DEX", 194, 1, 5, 64, 32, 70, false, false, false, true, false, false, false},
   {41, "Bible of the Combatant", "+3 ATK, +3 DEF", 195, 1, 5, 65, 32, 70, false, false, false, true, false, false, false},
   {42, "Ward of the Elements", "+1 to all resists", 196, 1, 2, 66, 96, 20, false, false, false, true, false, false, false},
   {43, "Sigil of the Elements", "+2 to all resists", 197, 1, 4, 67, 48, 40, false, false, false, true, false, false, false},
   {44, "Relic of the Elements", "+3 to all resists", 198, 1, 6, 68, 16, 65, false, false, false, true, false, false, false},
   {45, "Cup of Wealth", "+10% currency drop value", 199, 1, 8, 69, 16, 25, false, false, false, true, false, false, false},
   {46, "Puzzle Box of Frivolousness", "For bragging rights only!", 200, 1, 255, 70, 32, 1, false, false, false, true, false, false, false},
   {47, "Book of the Polymath", "+1 SPD, +1 ATK, +1 DEF", 201, 2, 3, 71, 128, 20, false, false, false, true, false, false, false},
   {48, "Book of the Gladiator", "+1 STR, +1 CON, +1 DEX", 202, 2, 3, 72, 128, 20, false, false, false, true, false, false, false},
   {49, "Tome of the Polymath", "+2 SPD, +2 ATK, +2 DEF", 203, 2, 5, 73, 32, 50, false, false, false, true, false, false, false},
   {50, "Tome of the Gladiator", "+2 STR, +2 CON, +2 DEX", 204, 2, 5, 74, 32, 50, false, false, false, true, false, false, false},
   {51, "Bible of the Polymath", "+3 SPD, +3 ATK, +3 DEF", 205, 2, 8, 75, 4, 90, false, false, false, true, false, false, false},
   {52, "Bible of the Gladiator", "+3 STR, +3 CON, +3 DEX", 206, 2, 8, 76, 4, 90, false, false, false, true, false, false, false},
   {53, "Trickster Trinket", "+1 APT", 207, 2, 4, 77, 8, 80, false, false, false, true, false, false, false},
   {54, "Prismatic Mirror", "+10 to all elemental resists", 208, 2, 4, 78, 8, 75, false, false, false, true, false, false, false},
   {55, "Glasses of Foresight", "Permanent 'discovery' effect", 209, 2, 6, 79, 32, 45, false, false, false, true, false, false, false},
   {56, "Ethereal Barrier", "Reduce all damage by 1%", 210, 2, 4, 80, 16, 70, false, false, false, true, false, false, false},
   {57, "Righteous Fire", "+1 to maximum fire resist", 211, 2, 6, 81, 4, 80, false, false, false, true, false, false, false},
   {58, "Righteous Ice", "+1 to maximum ice resist", 212, 2, 6, 82, 4, 80, false, false, false, true, false, false, false},
   {59, "Righteous Lightning", "+1 to maximum lightning resist", 213, 2, 6, 83, 4, 80, false, false, false, true, false, false, false},
   {60, "Ark of Enlightenment", "Auto-identify of all items", 214, 2, 3, 84, 2, 85, false, false, false, true, false, false, false},
   {61, "Chalice of Riches", "+100% currency drop value", 215, 2, 16, 85, 64, 60, false, false, false, true, false, false, false},
   {62, "Amphora of Holy Water", "All items are auto-decursed", 216, 2, 8, 86, 16, 40, false, false, false, true, false, false, false}
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
   {12, "Attacks Per Turn", "APT"},
   {13, "HP", "HP"},
   {14, "Fire Damage Taken", "FDam"},
   {15, "Ice Damage Taken", "IDam"},
   {16, "Lightning Damage Taken", "LDam"},
   {17, "Poisoned", "Pois"},
   {18, "Chance to block", "CBlk"},
   {19, "All damage taken", "ADmg"}
};

// ItemPrefixType g_item_prefix_ids
//
//   Item prefixes
//
//   Fields:
//   {id, name, description, gid, rarity, ilevel, modifier(s)}
//
ItemPrefixType g_item_prefix_ids[] = {
   {0, "Strong", "+10% ATK", 0, 240, 5, 1, {{3, 0, 1.1, 0}}},
   {1, "Mighty", "+25% ATK, +1 STR", 1, 128, 20, 2, {{3, 0, 1.25, 0}, {0, 1, 1, 0}}},
   {2, "Herculean", "+50% ATK, +4 STR", 2, 32, 70, 2, {{3, 0, 1.5, 0}, {0, 1, 4, 0}}},
   {3, "Quick", "+10% SPD", 3, 240, 5, 1, {{5, 0, 1.1, 0}}},
   {4, "Speedy", "+25% SPD, +1 DEX", 4, 128, 20, 2, {{5, 0, 1.25, 0}, {2, 1, 1, 0}}},
   {5, "Supersonic", "+50% SPD, +4 DEX", 5, 16, 70, 2, {{5, 0, 1.5, 0}, {2, 1, 4, 0}}},
   {6, "Stout", "+10% DEF", 6, 240, 5, 1, {{4, 0, 1.1, 0}}},
   {7, "Hardy", "+25% DEF, +1 CON", 7, 128, 20, 2, {{4, 0, 1.25, 0}, {1, 1, 1, 0}}},
   {8, "Unbreakable", "+50% DEF, +4 CON", 8, 16, 70, 2, {{4, 0, 1.5, 0}, {1, 1, 4, 0}}},
   {9, "Buffed", "+20% HP", 9, 128, 25, 1, {{13, 0, 1.2, 0}}},
   {10, "Healthy", "+50% HP", 10, 32, 50, 1, {{13, 0, 1.5, 0}}},
   {11, "Immortal", "+100% HP", 11, 2, 80, 1, {{13, 0, 2.0, 0}}},
   {12, "Ogre's", "+50% ATK, -20% SPD", 12, 64, 35, 2, {{3, 0, 1.5, 0}, {5, 0, 0.8, 0}}},
   {13, "Flaming", "+10% of damage as fire", 13, 192, 15, 1, {{3, 2, 0.1, 6}}},
   {14, "Infernous", "+50% of damage as fire", 14, 96, 50, 1, {{3, 2, 0.5, 6}}},
   {15, "Icy", "+10% of damage as ice", 15, 192, 15, 1, {{3, 2, 0.1, 7}}},
   {16, "Freezing", "+50% of damage as ice", 16, 96, 50, 1, {{3, 2, 0.5, 7}}},
   {17, "Sparking", "+10% of damage as lightning", 17, 192, 15, 1, {{3, 2, 0.1, 8}}},
   {18, "Shocking", "+50% of damage as lightning", 18, 96, 50, 1, {{3, 2, 0.5, 8}}},
   {19, "Fire-shrouded", "20% fire damage reduction", 19, 128, 15, 1, {{14, 1, -0.2, 0}}},
   {20, "Fire-cloaked", "40% fire damage reduction", 20, 32, 55, 1, {{14, 1, -0.4, 0}}},
   {21, "Ice-shrouded", "20% ice damage reduction", 21, 128, 15, 1, {{15, 1, -0.2, 0}}},
   {22, "Ice-cloaked", "40% ice damage reduction", 22, 32, 55, 1, {{15, 1, -0.4, 0}}},
   {23, "Spark-shrouded", "20% lightning damage reduction", 23, 128, 15, 1, {{16, 1, -0.2, 0}}},
   {24, "Spark-cloaked", "40% lightning damage reduction", 24, 32, 55, 1, {{16, 1, -0.2, 0}}},
   {25, "Elemental-shrouded", "10% elemental damage reduction", 25, 64, 15, 3, {{14, 1, -0.1, 0}, {15, 1, -0.1, 0}, {16, 1, -0.1, 0}}},
   {26, "Elemental-cloaked", "20% elemental damage reduction", 26, 8, 55, 3, {{14, 1, -0.2, 0}, {15, 1, -0.2, 0}, {16, 1, -0.2, 0}}}
};

// ItemPrefixType g_cursed_item_prefix_ids
//
//   Cursed item prefixes
//
//   Fields:
//   {id, name, description, gid, rarity, ilevel, modifier(s)}
//
ItemPrefixType g_cursed_item_prefix_ids[] = {
   {27, "Ignited", "+20% fire damage taken", 27, 192, 10, 1, {{14, 1, 0.2, 0}}},
   {28, "Engulfed", "+40% fire damage taken", 28, 96, 40, 1, {{14, 1, 0.4, 0}}},
   {29, "Chilled", "+20% ice damage taken", 29, 192, 10, 1, {{15, 1, 0.2, 0}}},
   {30, "Chilled", "+40% ice damage taken", 30, 96, 40, 1, {{15, 1, 0.4, 0}}},
   {31, "Shocked", "+20% lightning damage taken", 31, 192, 10, 1, {{16, 1, 0.2, 0}}},
   {32, "Electrified", "+40 lightning damage taken", 32, 96, 40, 1, {{16, 1, 0.4, 0}}},
   {33, "Element-touched", "+10% elemental damage taken", 33, 32, 20, 3, {{14, 1, 0.1, 0}, {15, 1, 0.1, 0}, {16, 1, 0.1, 0}}},
   {34, "Element-tangled", "+20% elemental damage taken", 34, 8, 50, 3, {{14, 1, 0.2, 0}, {15, 1, 0.2, 0}, {16, 1, 0.2, 0}}},
   {35, "Weak", "-10% ATK", 35, 160, 10, 1, {{3, 0, 0.9, 0}}},
   {36, "Crippled", "-25% ATK", 36, 64, 30, 1, {{3, 0, 0.75, 0}}},
   {37, "Slow", "-10% SPD", 37, 160, 20, 1, {{5, 0, 0.9, 0}}},
   {38, "Halting", "-25% SPD", 38, 64, 45, 1, {{5, 0, 0.75, 0}}},
   {39, "Frail", "-10% DEF", 39, 192, 15, 1, {{4, 0, 0.9, 0}}},
   {40, "Defenseless", "-25% DEF", 40, 96, 35, 1, {{4, 0, 0.75, 0}}},
   {41, "Infirm", "-10% HP", 41, 128, 25, 1, {{13, 0, 0.9, 0}}},
   {42, "Sickly", "-25% HP", 42, 32, 50, 1, {{13, 0, 0.75, 0}}}
};

// ItemSuffixType g_item_suffix_ids
//
//   Item suffixes
//
//   Fields:
//   {id, name, description, gid, rarity, ilevel, modifier(s)}
//
ItemSuffixType g_item_suffix_ids[] = {
   {0, "of Strength", "+1 STR", 0, 240, 5, 1, {{0, 1, 1, 0}}},
   {1, "of the Troll", "+3 STR", 1, 128, 20, 1, {{0, 1, 3, 0}}},
   {2, "of the Giant", "+6 STR", 2, 64, 70, 1, {{0, 1, 6, 0}}},
   {3, "of Dexterity", "+1 DEX", 3, 255, 5, 1, {{2, 1, 1, 0}}},
   {4, "of the Thief", "+3 DEX", 4, 128, 20, 1, {{2, 1, 3, 0}}},
   {5, "of the Ninja", "+6 DEX", 5, 64, 70, 1, {{2, 1, 6, 0}}},
   {6, "of Constitution", "+1 CON", 6, 255, 5, 1, {{1, 1, 1, 0}}},
   {7, "of the Athlete", "+3 CON", 7, 128, 20, 1, {{1, 1, 3, 0}}},
   {8, "of the Bodybuilder", "+6 CON", 8, 64, 70, 1, {{1, 1, 6, 0}}},
   {9, "of Attack", "+1 ATK", 9, 240, 7, 1, {{3, 1, 1, 0}}},
   {10, "of the Soldier", "+3 ATK", 10, 112, 22, 1, {{3, 1, 3, 0}}},
   {11, "of the General", "+6 ATK", 11, 48, 74, 1, {{3, 1, 6, 0}}},
   {12, "of Speed", "+1 SPD", 12, 240, 7, 1, {{5, 1, 1, 0}}},
   {13, "of the Runner", "+3 SPD", 13, 112, 22, 1, {{5, 1, 3, 0}}},
   {14, "of the Sprinter", "+6 SPD", 14, 48, 74, 1, {{5, 1, 6, 0}}},
   {15, "of Defense", "+1 DEF", 15, 255, 5, 1, {{4, 1, 1, 0}}},
   {16, "of the Blocker", "+3 DEF", 16, 128, 20, 1, {{4, 1, 3, 0}}},
   {17, "of the Guardian", "+6 DEF", 17, 64, 70, 1, {{4, 1, 6, 0}}},
   {18, "of Kings", "+1 STR, +1 DEX, +1 CON", 18, 64, 50, 3, {{0, 1, 1, 0}, {1, 1, 1, 0}, {2, 1, 1, 0}}},
   {19, "of the Gods", "+3 STR, +3 DEX, +3 CON", 19, 20, 65, 3, {{0, 1, 3, 0}, {1, 1, 3, 0}, {2, 1, 3, 0}}},
   {20, "of the Primordials", "+6 STR, +6 DEX, +6 CON", 20, 8, 80, 3, {{0, 1, 6, 0}, {1, 1, 6, 0}, {2, 1, 6, 0}}},
   {21, "of Extra Attacks", "+1 APT", 21, 25, 40, 1, {{12, 1, 1, 0}}},
   {22, "of the Berserker", "+1 APT, +1 STR", 22, 5, 65, 2, {{12, 1, 1, 0}, {0, 1, 3, 0}}},
   {23, "of Perfect Defense", "15% block, 20% DMG reduction", 23, 4, 75, 2, {{18, 0, 0.15, 0}, {19, 1, -0.2, 0}}},
   {24, "of the Unstoppable", "+1 APT, +6 all stats, -20% DMG taken", 24, 1, 100, 5, {{12, 1, 1, 0}, {0, 1, 6, 0}, {1, 1, 6, 0}, {2, 1, 6, 0}, {19, 1, -0.2, 0}}}
};

// ItemSuffixType g_cursed_item_suffix_ids
//
//   Cursedtem suffixes
//
//   Fields:
//   {id, name, description, gid, rarity, ilevel, modifier(s)}
//
ItemSuffixType g_cursed_item_suffix_ids[] = {
   {25, "of Weakness", "-1 STR", 25, 240, 7, 1, {{0, 1, -1, 0}}},
   {26, "of Fraility", "-3 STR", 26, 112, 24, 1, {{0, 1, -3, 0}}},
   {27, "of Clumsiness", "-1 DEX", 27, 240, 7, 1, {{2, 1, -1, 0}}},
   {28, "of Fumbling", "-3 DEX", 28, 112, 24, 1, {{2, 1, -3, 0}}},
   {29, "of Illness", "-1 CON", 29, 240, 7, 1, {{1, 1, -1, 0}}},
   {30, "of Sickliness", "-3 CON", 30, 112, 224, 1, {{1, 1, -3, 0}}},
   {31, "of Slowness", "-1 SPD", 31, 224, 96, 1, {{5, 1, -1, 0}}},
   {32, "of Halting", "-3 SPD", 32, 96, 27, 1, {{5, 1, -3, 0}}},
   {33, "of Vulnerability", "-1 DEF", 33, 240, 7, 1, {{4, 1, -1, 0}}},
   {34, "of Defenselessness", "-3 DEF", 34, 112, 24, 1, {{4, 1, -3, 0}}},
   {35, "of Cowardice", "-1 ATK", 35, 224, 10, 1, {{3, 1, -1, 0}}},
   {36, "of Surrender", "-3 ATK", 36, 96, 27, 1, {{3, 1, -3, 0}}},
   {37, "of the Indecisive", "-1 APT", 37, 96, 27, 1, {{12, 1, -1, 0}}},
   {38, "of the Envenomed", "Always poisoned", 38, 32, 35, 1, {{17, 3, 1, 0}}},
   {39, "of the Damned", "-1 APT, -3 all stats, +20% DMG taken", 39, 1, 100, 5, {{12, 1, -1, 0}, {0, 1, -3, 0}, {1, 1, -3, 0}, {2, 1, -3, 0}, {19, 1, 0.2, 0}}}
};

// EnemyType g_enemy_ids
//
//   A list of enemy types
//
//   Fields:
//   {id, name, gid, bid, hp, str, atk, def, spd, apt, f_atk, i_atk, l_atk, f_def, i_def, l_def, exp, elevel, rarity, ilevel, max_items}
//
EnemyType g_enemy_ids[] = {
   {0, "slime", 0, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {1, "brown rat", 1, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {2, "skeleton", 2, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {3, "zombie", 3, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {4, "ant", 4, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {5, "spider", 5, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {6, "brown bat", 6, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {7, "kobold", 7, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {8, "archdemon", 8, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1},
   {9, "wolf", 9, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 2, 1, 255, 1, 1}
};

