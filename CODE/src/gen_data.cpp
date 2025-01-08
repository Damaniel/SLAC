// Auto-generated file - do not edit!
#include "globals.h"

const int g_weapon_base_pool_entries = 6635;
const int g_weapon_base_pool_count = 42;
const int g_armor_base_pool_entries = 12028;
const int g_armor_base_pool_count = 84;
const int g_currency_pool_entries = 580;
const int g_currency_pool_count = 4;
const int g_potion_pool_entries = 925;
const int g_potion_pool_count = 10;
const int g_scroll_pool_entries = 1393;
const int g_scroll_pool_count = 11;
const int g_artifact_pool_entries = 6925;
const int g_artifact_pool_count = 70;
const int g_item_prefix_pool_entries = 2810;
const int g_item_prefix_pool_count = 27;
const int g_cursed_item_prefix_pool_entries = 1800;
const int g_cursed_item_prefix_pool_count = 16;
const int g_item_suffix_pool_entries = 2700;
const int g_item_suffix_pool_count = 25;
const int g_cursed_item_suffix_pool_entries = 2177;
const int g_cursed_item_suffix_pool_count = 15;

int g_weapon_base_pool [] = { 255, 495, 695, 855, 975, 1015, 1270, 1505, 1700, 1855, 1965, 1995, 2250, 2485, 2680, 2835, 2945, 
      2975, 3230, 3465, 3660, 3815, 3925, 3955, 4195, 4420, 4600, 4730, 4830, 4845, 5100, 5330, 5515, 
      5660, 5760, 5785, 6015, 6230, 6400, 6520, 6615, 6635 };
int g_armor_base_pool [] = { 255, 475, 655, 805, 905, 955, 1210, 1420, 1590, 1720, 1800, 1830, 2085, 2305, 2485, 2635, 2735, 
      2785, 3040, 3250, 3420, 3550, 3630, 3660, 3915, 4125, 4295, 4435, 4525, 4565, 4820, 5020, 5170, 
      5270, 5315, 5325, 5580, 5800, 5980, 6130, 6230, 6280, 6535, 6745, 6915, 7045, 7125, 7155, 7410, 
      7630, 7810, 7960, 8060, 8110, 8365, 8575, 8745, 8875, 8955, 8985, 9240, 9460, 9640, 9790, 9890, 
      9940, 10195, 10405, 10575, 10705, 10785, 10818, 11018, 11178, 11298, 11378, 11418, 11423, 11623, 11783, 11903, 
      11983, 12023, 12028 };
int g_currency_pool [] = { 255, 455, 555, 580 };
int g_potion_pool [] = { 255, 405, 425, 625, 675, 725, 775, 795, 915, 925 };
int g_scroll_pool [] = { 255, 280, 480, 630, 635, 815, 1040, 1168, 1318, 1368, 1393 };
int g_artifact_pool [] = { 255, 510, 765, 1020, 1275, 1530, 1770, 1920, 2070, 2220, 2370, 2520, 2670, 2798, 2862, 2926, 2990, 
      3054, 3118, 3182, 3214, 3406, 3598, 3790, 3886, 3982, 4078, 4110, 4142, 4174, 4238, 4254, 4258, 
      4482, 4706, 4930, 5042, 5154, 5266, 5298, 5330, 5362, 5458, 5506, 5522, 5538, 5570, 5698, 5826, 
      5858, 5890, 5894, 5898, 5906, 5914, 5946, 5962, 5966, 5970, 5974, 5976, 6040, 6056, 6311, 6461, 
      6525, 6749, 6861, 6893, 6925 };
int g_item_prefix_pool [] = { 240, 368, 400, 640, 768, 784, 1024, 1152, 1168, 1296, 1328, 1330, 1394, 1586, 1682, 1874, 1970, 
      2162, 2258, 2386, 2418, 2546, 2578, 2706, 2738, 2802, 2810 };
int g_cursed_item_prefix_pool [] = { 192, 288, 480, 576, 768, 864, 896, 904, 1064, 1128, 1288, 1352, 1544, 1640, 1768, 1800 };
int g_item_suffix_pool [] = { 240, 368, 432, 687, 815, 879, 1134, 1262, 1326, 1566, 1678, 1726, 1966, 2078, 2126, 2381, 2509, 
      2573, 2637, 2657, 2665, 2690, 2695, 2699, 2700 };
int g_cursed_item_suffix_pool [] = { 240, 352, 592, 704, 944, 1056, 1280, 1376, 1616, 1728, 1952, 2048, 2144, 2176, 2177 };

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
   {1, "Copper Dagger", 1, 0, 2, 240, 2, 5, true, true, true, false, true, true, false},
   {2, "Bronze Dagger", 2, 0, 4, 200, 5, 10, true, true, true, false, true, true, false},
   {3, "Iron Dagger", 3, 0, 10, 160, 10, 30, true, true, true, false, true, true, false},
   {4, "Steel Dagger", 4, 0, 20, 120, 20, 100, true, true, true, false, true, true, false},
   {5, "Mythril Dagger", 5, 0, 40, 40, 40, 600, true, true, true, false, true, true, false},
   {6, "Wooden Sword", 6, 1, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {7, "Copper Sword", 7, 1, 4, 235, 4, 10, true, true, true, false, true, true, false},
   {8, "Bronze Sword", 8, 1, 7, 195, 10, 20, true, true, true, false, true, true, false},
   {9, "Iron Sword", 9, 1, 15, 155, 20, 60, true, true, true, false, true, true, false},
   {10, "Steel Sword", 10, 1, 28, 110, 40, 250, true, true, true, false, true, true, false},
   {11, "Mythril Sword", 11, 1, 60, 30, 60, 1500, true, true, true, false, true, true, false},
   {12, "Wooden Broadsword", 12, 2, 3, 255, 4, 10, true, true, true, false, true, true, false},
   {13, "Copper Broadsword", 13, 2, 8, 235, 8, 30, true, true, true, false, true, true, false},
   {14, "Bronze Broadsword", 14, 2, 12, 195, 15, 100, true, true, true, false, true, true, false},
   {15, "Iron Broadsword", 15, 2, 22, 155, 30, 400, true, true, true, false, true, true, false},
   {16, "Steel Broadsword", 16, 2, 35, 110, 50, 1300, true, true, true, false, true, true, false},
   {17, "Mythril Broadsword", 17, 2, 80, 30, 75, 3000, true, true, true, false, true, true, false},
   {18, "Wooden Axe", 18, 3, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {19, "Copper Axe", 19, 3, 4, 235, 4, 10, true, true, true, false, true, true, false},
   {20, "Bronze Axe", 20, 3, 7, 195, 10, 20, true, true, true, false, true, true, false},
   {21, "Iron Axe", 21, 3, 15, 155, 20, 60, true, true, true, false, true, true, false},
   {22, "Steel Axe", 22, 3, 28, 110, 40, 250, true, true, true, false, true, true, false},
   {23, "Mythril Axe", 23, 3, 60, 30, 60, 1500, true, true, true, false, true, true, false},
   {24, "Wooden Battleaxe", 24, 4, 4, 240, 5, 10, true, true, true, false, true, true, false},
   {25, "Copper Battleaxe", 25, 4, 10, 225, 10, 30, true, true, true, false, true, true, false},
   {26, "Bronze Battleaxe", 26, 4, 15, 180, 20, 100, true, true, true, false, true, true, false},
   {27, "Iron Battleaxe", 27, 4, 28, 130, 40, 400, true, true, true, false, true, true, false},
   {28, "Steel Battleaxe", 28, 4, 45, 100, 60, 1300, true, true, true, false, true, true, false},
   {29, "Mythril Battleaxe", 29, 4, 90, 15, 80, 1300, true, true, true, false, true, true, false},
   {30, "Wooden Mace", 30, 5, 2, 255, 3, 8, true, true, true, false, true, true, false},
   {31, "Copper Mace", 31, 5, 5, 230, 6, 25, true, true, true, false, true, true, false},
   {32, "Bronze Mace", 32, 5, 9, 185, 12, 80, true, true, true, false, true, true, false},
   {33, "Iron Mace", 33, 5, 17, 145, 25, 250, true, true, true, false, true, true, false},
   {34, "Steel Mace", 34, 5, 32, 100, 45, 1000, true, true, true, false, true, true, false},
   {35, "Mythril Mace", 35, 5, 60, 25, 65, 2500, true, true, true, false, true, true, false},
   {36, "Wooden Maul", 36, 6, 4, 230, 5, 10, true, true, true, false, true, true, false},
   {37, "Copper Maul", 37, 6, 12, 215, 10, 30, true, true, true, false, true, true, false},
   {38, "Bronze Maul", 38, 6, 18, 170, 25, 100, true, true, true, false, true, true, false},
   {39, "Iron Maul", 39, 6, 30, 120, 45, 400, true, true, true, false, true, true, false},
   {40, "Steel Maul", 40, 6, 50, 95, 65, 1300, true, true, true, false, true, true, false},
   {41, "Mythril Maul", 41, 6, 95, 20, 85, 3000, true, true, true, false, true, true, false}
};

// ArmorBaseType g_armor_base_ids
//
//   A list of armor base types
//
//   Fields:
//   {id, name, gid, type id, defense, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArmorBaseType g_armor_base_ids[] = {
   {0, "Cloth Hat", 42, 7, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {1, "Felt Hat", 43, 7, 2, 220, 2, 5, true, true, true, false, true, true, false},
   {2, "Reinforced Hat", 44, 7, 4, 180, 5, 10, true, true, true, false, true, true, false},
   {3, "Leather Hat", 45, 7, 7, 150, 10, 30, true, true, true, false, true, true, false},
   {4, "Fur Hat", 46, 7, 10, 100, 20, 100, true, true, true, false, true, true, false},
   {5, "Mage's Hat", 47, 7, 15, 50, 40, 600, true, true, true, false, true, true, false},
   {6, "Wooden Helm", 48, 8, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {7, "Copper Helm", 49, 8, 4, 210, 4, 10, true, true, true, false, true, true, false},
   {8, "Bronze Helm", 50, 8, 6, 170, 10, 20, true, true, true, false, true, true, false},
   {9, "Iron Helm", 51, 8, 10, 130, 20, 60, true, true, true, false, true, true, false},
   {10, "Steel Helm", 52, 8, 15, 80, 40, 250, true, true, true, false, true, true, false},
   {11, "Mythril Helm", 53, 8, 22, 30, 60, 1500, true, true, true, false, true, true, false},
   {12, "Cloth Gloves", 54, 9, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {13, "Felt Gloves", 55, 9, 2, 220, 2, 5, true, true, true, false, true, true, false},
   {14, "Reinforced Gloves", 56, 9, 4, 180, 5, 10, true, true, true, false, true, true, false},
   {15, "Leather Gloves", 57, 9, 7, 150, 10, 30, true, true, true, false, true, true, false},
   {16, "Fur Gloves", 58, 9, 10, 100, 20, 100, true, true, true, false, true, true, false},
   {17, "Mage's Gloves", 59, 9, 15, 50, 40, 600, true, true, true, false, true, true, false},
   {18, "Wooden Gauntlets", 60, 10, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {19, "Copper Gauntlets", 61, 10, 4, 210, 4, 10, true, true, true, false, true, true, false},
   {20, "Bronze Gauntlets", 62, 10, 6, 170, 10, 20, true, true, true, false, true, true, false},
   {21, "Iron Gauntlets", 63, 10, 10, 130, 20, 60, true, true, true, false, true, true, false},
   {22, "Steel Gauntlets", 64, 10, 15, 80, 40, 250, true, true, true, false, true, true, false},
   {23, "Mythril Gauntlets", 65, 10, 22, 30, 60, 1500, true, true, true, false, true, true, false},
   {24, "Cloth Shirt", 66, 11, 1, 255, 1, 5, true, true, true, false, true, true, false},
   {25, "Felt Shirt", 67, 11, 2, 210, 3, 10, true, true, true, false, true, true, false},
   {26, "Reinforced Shirt", 68, 11, 4, 170, 8, 30, true, true, true, false, true, true, false},
   {27, "Leather Shirt", 69, 11, 7, 140, 15, 100, true, true, true, false, true, true, false},
   {28, "Fur Shirt", 70, 11, 10, 90, 30, 600, true, true, true, false, true, true, false},
   {29, "Mage's Shirt", 71, 11, 15, 40, 50, 1200, true, true, true, false, true, true, false},
   {30, "Wooden Mail", 72, 12, 2, 255, 5, 10, true, true, true, false, true, true, false},
   {31, "Copper Mail", 73, 12, 4, 200, 10, 50, true, true, true, false, true, true, false},
   {32, "Bronze Mail", 74, 12, 6, 150, 20, 100, true, true, true, false, true, true, false},
   {33, "Iron Mail", 75, 12, 10, 100, 40, 400, true, true, true, false, true, true, false},
   {34, "Steel Mail", 76, 12, 15, 45, 60, 1500, true, true, true, false, true, true, false},
   {35, "Mythril Mail", 77, 12, 22, 10, 80, 3000, true, true, true, false, true, true, false},
   {36, "Cloth Pants", 78, 13, 2, 255, 1, 5, true, true, true, false, true, true, false},
   {37, "Felt Pants", 79, 13, 4, 220, 3, 10, true, true, true, false, true, true, false},
   {38, "Reinforced Pants", 80, 13, 7, 180, 8, 30, true, true, true, false, true, true, false},
   {39, "Leather Pants", 81, 13, 10, 150, 15, 100, true, true, true, false, true, true, false},
   {40, "Fur Pants", 82, 13, 15, 100, 30, 600, true, true, true, false, true, true, false},
   {41, "Mage's Pants", 83, 13, 20, 50, 50, 1000, true, true, true, false, true, true, false},
   {42, "Wooden Leggings", 84, 14, 3, 255, 4, 10, true, true, true, false, true, true, false},
   {43, "Copper Leggings", 85, 14, 5, 210, 8, 50, true, true, true, false, true, true, false},
   {44, "Bronze Leggings", 86, 14, 8, 170, 15, 100, true, true, true, false, true, true, false},
   {45, "Iron Leggings", 87, 14, 12, 130, 30, 400, true, true, true, false, true, true, false},
   {46, "Steel Leggings", 88, 14, 17, 80, 50, 1000, true, true, true, false, true, true, false},
   {47, "Mythril Leggings", 89, 14, 23, 30, 70, 2000, true, true, true, false, true, true, false},
   {48, "Cloth Shoes", 90, 15, 1, 255, 1, 2, true, true, true, false, true, true, false},
   {49, "Felt Shoes", 91, 15, 2, 220, 2, 5, true, true, true, false, true, true, false},
   {50, "Reinforced Shoes", 92, 15, 4, 180, 5, 10, true, true, true, false, true, true, false},
   {51, "Leather Shoes", 93, 15, 7, 150, 10, 30, true, true, true, false, true, true, false},
   {52, "Fur Shoes", 94, 15, 10, 100, 20, 100, true, true, true, false, true, true, false},
   {53, "Mage's Shoes", 95, 15, 15, 50, 40, 600, true, true, true, false, true, true, false},
   {54, "Wooden Boots", 96, 16, 2, 255, 2, 5, true, true, true, false, true, true, false},
   {55, "Copper Boots", 97, 16, 4, 210, 4, 10, true, true, true, false, true, true, false},
   {56, "Bronze Boots", 98, 16, 6, 170, 10, 20, true, true, true, false, true, true, false},
   {57, "Iron Boots", 99, 16, 10, 130, 20, 60, true, true, true, false, true, true, false},
   {58, "Steel Boots", 100, 16, 15, 80, 40, 250, true, true, true, false, true, true, false},
   {59, "Mythril Boots", 101, 16, 22, 30, 60, 1500, true, true, true, false, true, true, false},
   {60, "Leather Buckler", 102, 17, 3, 255, 2, 15, true, true, true, false, true, true, false},
   {61, "Reinforced Buckler", 103, 17, 6, 220, 4, 80, true, true, true, false, true, true, false},
   {62, "Wooden Buckler", 104, 17, 10, 180, 10, 200, true, true, true, false, true, true, false},
   {63, "Bronze Buckler", 105, 17, 15, 150, 20, 400, true, true, true, false, true, true, false},
   {64, "Steel Buckler", 106, 17, 22, 100, 40, 800, true, true, true, false, true, true, false},
   {65, "Mythril Buckler", 107, 17, 30, 50, 60, 2000, true, true, true, false, true, true, false},
   {66, "Wooden Shield", 108, 18, 4, 255, 4, 20, true, true, true, false, true, true, false},
   {67, "Copper Shield", 109, 18, 7, 210, 8, 100, true, true, true, false, true, true, false},
   {68, "Bronze Shield", 110, 18, 12, 170, 15, 250, true, true, true, false, true, true, false},
   {69, "Iron Shield", 111, 18, 18, 130, 30, 500, true, true, true, false, true, true, false},
   {70, "Steel Shield", 112, 18, 25, 80, 50, 1200, true, true, true, false, true, true, false},
   {71, "Mythril Shield", 113, 18, 90, 33, 75, 2400, true, true, true, false, true, true, false},
   {72, "Copper Ring", 114, 19, 1, 200, 5, 100, true, true, true, false, true, true, false},
   {73, "Brass Ring", 115, 19, 2, 160, 15, 300, true, true, true, false, true, true, false},
   {74, "Silver Ring", 116, 19, 3, 120, 30, 800, true, true, true, false, true, true, false},
   {75, "Gold Ring", 117, 19, 4, 80, 50, 1500, true, true, true, false, true, true, false},
   {76, "Electrum Ring", 118, 19, 5, 40, 70, 2500, true, true, true, false, true, true, false},
   {77, "Mythril Ring", 119, 19, 6, 5, 90, 5000, true, true, true, false, true, true, false},
   {78, "Copper Amulet", 120, 20, 1, 200, 5, 100, true, true, true, false, true, true, false},
   {79, "Bronze Amulet", 121, 20, 2, 160, 15, 300, true, true, true, false, true, true, false},
   {80, "Silver Amulet", 122, 20, 3, 120, 30, 800, true, true, true, false, true, true, false},
   {81, "Gold Amulet", 123, 20, 4, 80, 50, 1500, true, true, true, false, true, true, false},
   {82, "Electrum Amulet", 124, 20, 5, 40, 70, 2500, true, true, true, false, true, true, false},
   {83, "Mythril Amulet", 125, 20, 6, 5, 90, 5000, true, true, true, false, true, true, false}
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
   {0, "Potion of Light Healing", "Recovers 50 HP", 130, 0, 0, 255, 1, 10, false, false, false, true, false, true, true},
   {1, "Potion of Moderate Healing", "Recovers 250 HP", 131, 0, 1, 150, 15, 100, false, false, false, true, false, true, true},
   {2, "Potion of Full Healing", "Recovers 100% of HP", 132, 0, 2, 20, 70, 1000, false, false, false, true, false, true, true},
   {3, "Potion of Cure Poison", "Removes poison", 133, 0, 3, 200, 2, 50, false, false, false, true, false, true, true},
   {4, "Potion of Berserk Strength", "+100% STR for 20 turns", 134, 0, 5, 50, 50, 600, false, false, false, true, false, true, true},
   {5, "Potion of Speed", "+100% SPD for 20 turns", 135, 0, 6, 50, 50, 600, false, false, false, true, false, true, true},
   {6, "Potion of Hardiness", "+100% HP for 20 turns", 136, 0, 7, 50, 50, 600, false, false, false, true, false, true, true},
   {7, "Potion of Extra Attacks", "+1 APT for 20 turns", 137, 0, 8, 20, 60, 1000, false, false, false, true, false, true, true},
   {8, "Potion of Poison", "Applies poison", 138, 0, 9, 120, 25, 20, false, false, false, true, false, true, true},
   {9, "Potion of Death", "Reduces HP to 0", 139, 0, 11, 10, 75, 20, false, false, false, true, false, true, true}
};

// ScrollType g_scroll_ids
//
//   A list of scroll types
//
//   Fields:
//   {id, name, gid, type id, effect id, rarity, ilevel, value, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ScrollType g_scroll_ids[] = {
   {0, "Scroll of Identify", "Identifies an item", 140, 0, 12, 255, 1, 5, false, false, false, true, false, true, true},
   {1, "Scroll of Identify All", "Identifies all items", 141, 0, 13, 25, 60, 500, false, false, false, true, false, true, true},
   {2, "Scroll of Magic Map", "Marks map as discovered", 142, 0, 14, 200, 5, 25, false, false, false, true, false, true, true},
   {3, "Scroll of Decurse", "Removes curse from an item", 143, 0, 16, 150, 10, 200, false, false, false, true, false, true, true},
   {4, "Scroll of Decurse All", "Removes curse from all items", 144, 0, 17, 5, 80, 1500, false, false, false, true, false, true, true},
   {5, "Scroll of Teleport", "Moves player to a random location", 145, 0, 18, 180, 10, 30, false, false, false, true, false, true, true},
   {6, "Scroll of Recall", "Returns player to surface", 146, 0, 19, 225, 3, 15, false, false, false, true, false, true, true},
   {7, "Scroll of Summon Item", "Creates a good item", 147, 0, 20, 128, 25, 250, false, false, false, true, false, true, true},
   {8, "Scroll of Darkness", "Darkens all lit areas", 148, 0, 21, 150, 15, 15, false, false, false, true, false, true, true},
   {9, "Scroll of Forget Area", "Forgets the explored map", 149, 0, 22, 50, 30, 5, false, false, false, true, false, true, true},
   {10, "Scroll of Curse", "Curses a random unequipped item", 150, 0, 23, 25, 50, 10, false, false, false, true, false, true, true}
};

// ArtifactType g_artifact_ids
//
//   A list of artifact types
//
//   Fields:
//   {id, name, gid, description, artifact type, pieces, effect id, rarity, ilevel, cursed?, prefix?, suffix?, stack?, equip?, drop?, use?}
//
ArtifactType g_artifact_ids[] = {
   {0, "Sign of Strength", "+1 STR", 151, 0, 1, 24, 255, 5, false, false, false, true, false, false, false},
   {1, "Sign of Constitution", "+1 CON", 152, 0, 1, 25, 255, 5, false, false, false, true, false, false, false},
   {2, "Sign of Dexterity", "+1 DEX", 153, 0, 1, 26, 255, 5, false, false, false, true, false, false, false},
   {3, "Sign of Attack", "+1 ATK", 154, 0, 1, 27, 255, 5, false, false, false, true, false, false, false},
   {4, "Sign of Defense", "+1 DEF", 155, 0, 1, 28, 255, 5, false, false, false, true, false, false, false},
   {5, "Sign of Accuracy", "+1 ACC", 156, 0, 1, 29, 255, 10, false, false, false, true, false, false, false},
   {6, "Sign of Speed", "+1 SPD", 157, 0, 1, 30, 240, 10, false, false, false, true, false, false, false},
   {7, "Medal of Strength", "+2 STR", 158, 0, 1, 31, 150, 30, false, false, false, true, false, false, false},
   {8, "Medal of Constitution", "+2 CON", 159, 0, 1, 32, 150, 30, false, false, false, true, false, false, false},
   {9, "Medal of Dexterity", "+2 DEX", 160, 0, 1, 33, 150, 30, false, false, false, true, false, false, false},
   {10, "Medal of Attack", "+2 ATK", 161, 0, 1, 34, 150, 30, false, false, false, true, false, false, false},
   {11, "Medal of Defense", "+2 DEF", 162, 0, 1, 35, 150, 30, false, false, false, true, false, false, false},
   {12, "Medal of Accuracy", "+2 ACC", 163, 0, 1, 36, 150, 35, false, false, false, true, false, false, false},
   {13, "Medal of Speed", "+2 SPD", 164, 0, 1, 37, 128, 35, false, false, false, true, false, false, false},
   {14, "Trophy of Strength", "+3 STR", 165, 0, 1, 38, 64, 60, false, false, false, true, false, false, false},
   {15, "Trophy of Constitution", "+3 CON", 166, 0, 1, 39, 64, 60, false, false, false, true, false, false, false},
   {16, "Trophy of Dexterity", "+3 DEX", 167, 0, 1, 40, 64, 60, false, false, false, true, false, false, false},
   {17, "Trophy of Attack", "+3 ATK", 168, 0, 1, 41, 64, 60, false, false, false, true, false, false, false},
   {18, "Trophy of Defense", "+3 DEF", 169, 0, 1, 42, 64, 60, false, false, false, true, false, false, false},
   {19, "Trophy of Accuracy", "+3 ACC", 170, 0, 1, 43, 64, 65, false, false, false, true, false, false, false},
   {20, "Trophy of Speed", "+3 SPD", 171, 0, 1, 44, 32, 65, false, false, false, true, false, false, false},
   {21, "Ward of Fire", "+1 Fire Resist", 172, 0, 1, 45, 192, 8, false, false, false, true, false, false, false},
   {22, "Ward of Ice", "+1 Ice Resist", 173, 0, 1, 46, 192, 8, false, false, false, true, false, false, false},
   {23, "Ward of Lightning", "+1 Lightning Resist", 174, 0, 1, 47, 192, 8, false, false, false, true, false, false, false},
   {24, "Sigil of Fire", "+2 Fire Resist", 175, 0, 1, 48, 96, 35, false, false, false, true, false, false, false},
   {25, "Sigil of Ice", "+2 Ice Resist", 176, 0, 1, 49, 96, 35, false, false, false, true, false, false, false},
   {26, "Sigil of Lightning", "+2 Lightning Resist", 177, 0, 1, 50, 96, 35, false, false, false, true, false, false, false},
   {27, "Relic of Fire", "+3 Fire Resist", 178, 0, 1, 51, 32, 60, false, false, false, true, false, false, false},
   {28, "Relic of Ice", "+3 Ice Resist", 179, 0, 1, 52, 32, 60, false, false, false, true, false, false, false},
   {29, "Relic of Lightning", "+3 Lightning Resist", 180, 0, 1, 53, 32, 60, false, false, false, true, false, false, false},
   {30, "Lucky Token", "+1% currency drop value", 181, 0, 1, 54, 64, 10, false, false, false, true, false, false, false},
   {31, "Lucky Coin", "+2% currency drop value", 182, 0, 1, 55, 16, 30, false, false, false, true, false, false, false},
   {32, "Lucky Pendant", "+3% currency drop value", 183, 0, 1, 56, 4, 50, false, false, false, true, false, false, false},
   {33, "Book of the Warrior", "+1 STR, +1 CON", 184, 1, 2, 57, 224, 15, false, false, false, true, false, false, false},
   {34, "Book of the Thief", "+1 SPD, +1 DEX", 185, 1, 2, 58, 224, 15, false, false, false, true, false, false, false},
   {35, "Book of the Combatant", "+1 ATK, +1 DEF", 186, 1, 2, 59, 224, 15, false, false, false, true, false, false, false},
   {36, "Tome of the Warrior", "+2 STR, +2 CON", 187, 1, 3, 60, 112, 40, false, false, false, true, false, false, false},
   {37, "Tome of the Thief", "+2 SPD, +2 DEX", 188, 1, 3, 61, 112, 40, false, false, false, true, false, false, false},
   {38, "Tome of the Combatant", "+2 ATK, +2 DEF", 189, 1, 3, 62, 112, 40, false, false, false, true, false, false, false},
   {39, "Bible of the Warrior", "+3 STR, +3 CON", 190, 1, 5, 63, 32, 70, false, false, false, true, false, false, false},
   {40, "Bible of the Thief", "+3 SPD, +3 DEX", 191, 1, 5, 64, 32, 70, false, false, false, true, false, false, false},
   {41, "Bible of the Combatant", "+3 ATK, +3 DEF", 192, 1, 5, 65, 32, 70, false, false, false, true, false, false, false},
   {42, "Ward of the Elements", "+1 to all resists", 193, 1, 2, 66, 96, 20, false, false, false, true, false, false, false},
   {43, "Sigil of the Elements", "+2 to all resists", 194, 1, 4, 67, 48, 40, false, false, false, true, false, false, false},
   {44, "Relic of the Elements", "+3 to all resists", 195, 1, 6, 68, 16, 65, false, false, false, true, false, false, false},
   {45, "Cup of Wealth", "+10% currency drop value", 196, 1, 8, 69, 16, 25, false, false, false, true, false, false, false},
   {46, "Puzzle Box of Frivolousness", "For bragging rights only!", 197, 1, 255, 70, 32, 1, false, false, false, true, false, false, false},
   {47, "Book of the Polymath", "+1 SPD, +1 ATK, +1 DEF", 198, 2, 3, 71, 128, 20, false, false, false, true, false, false, false},
   {48, "Book of the Gladiator", "+1 STR, +1 CON, +1 DEX", 199, 2, 3, 72, 128, 20, false, false, false, true, false, false, false},
   {49, "Tome of the Polymath", "+2 SPD, +2 ATK, +2 DEF", 200, 2, 5, 73, 32, 50, false, false, false, true, false, false, false},
   {50, "Tome of the Gladiator", "+2 STR, +2 CON, +2 DEX", 201, 2, 5, 74, 32, 50, false, false, false, true, false, false, false},
   {51, "Bible of the Polymath", "+3 SPD, +3 ATK, +3 DEF", 202, 2, 8, 75, 4, 90, false, false, false, true, false, false, false},
   {52, "Bible of the Gladiator", "+3 STR, +3 CON, +3 DEX", 203, 2, 8, 76, 4, 90, false, false, false, true, false, false, false},
   {53, "Trickster Trinket", "+1 APT", 204, 2, 4, 77, 8, 80, false, false, false, true, false, false, false},
   {54, "Prismatic Mirror", "+10 to all elemental resists", 205, 2, 4, 78, 8, 75, false, false, false, true, false, false, false},
   {55, "Glasses of Foresight", "Permanent 'discovery' effect", 206, 2, 6, 79, 32, 45, false, false, false, true, false, false, false},
   {56, "Ethereal Barrier", "Reduce all damage by 1%", 207, 2, 4, 80, 16, 70, false, false, false, true, false, false, false},
   {57, "Righteous Fire", "+1 to maximum fire resist", 208, 2, 6, 81, 4, 80, false, false, false, true, false, false, false},
   {58, "Righteous Ice", "+1 to maximum ice resist", 209, 2, 6, 82, 4, 80, false, false, false, true, false, false, false},
   {59, "Righteous Lightning", "+1 to maximum lightning resist", 210, 2, 6, 83, 4, 80, false, false, false, true, false, false, false},
   {60, "Ark of Enlightenment", "Auto-identify of all items", 211, 2, 3, 84, 2, 85, false, false, false, true, false, false, false},
   {61, "Chalice of Riches", "+100% currency drop value", 212, 2, 16, 85, 64, 60, false, false, false, true, false, false, false},
   {62, "Amphora of Holy Water", "All items are auto-decursed", 213, 2, 8, 86, 16, 40, false, false, false, true, false, false, false},
   {63, "Sign of Health", "+3 HP", 214, 0, 1, 87, 255, 5, false, false, false, true, false, false, false},
   {64, "Medal of Health", "+8 HP", 215, 0, 1, 88, 150, 30, false, false, false, true, false, false, false},
   {65, "Trophy of Health", "+15 HP", 216, 0, 1, 89, 64, 60, false, false, false, true, false, false, false},
   {66, "Book of the Healthy", "+1 CON, +5 HP", 217, 1, 2, 90, 224, 15, false, false, false, true, false, false, false},
   {67, "Tome of the Healthy", "+1 CON, +10 HP", 218, 1, 3, 91, 112, 40, false, false, false, true, false, false, false},
   {68, "Bible of the Healthy", "+1 CON, +20 HP", 219, 1, 5, 92, 32, 70, false, false, false, true, false, false, false},
   {69, "Fountain of Youth", "+100 HP", 220, 2, 6, 93, 32, 60, false, false, false, true, false, false, false}
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
//   {id, name, bid, gid, hp, str, spd, atk, def, apt, f_atk, i_atk, l_atk, f_def, i_def, l_def, exp, elevel, ilevel, rarity, max_items}
//
EnemyType g_enemy_ids[] = {
   {0, "Small Flea", 0, 0, 10, 9, 70, 9, 9, 1, 0, 0, 0, 0, 0, 0, 2, 1, 1, 255, 1},
   {1, "clear slime", 0, 1, 10, 9, 90, 9, 9, 1, 0, 0, 0, 0, 0, 0, 2, 1, 1, 255, 1},
   {2, "mouse", 0, 2, 12, 10, 80, 10, 10, 1, 0, 0, 0, 0, 0, 0, 4, 2, 2, 253, 1},
   {3, "worm", 0, 3, 12, 10, 80, 10, 10, 1, 0, 0, 0, 0, 0, 0, 5, 2, 2, 253, 1},
   {4, "brown bat", 0, 4, 14, 12, 80, 13, 12, 1, 0, 0, 0, 0, 0, 0, 7, 3, 3, 240, 1},
   {5, "sandworm", 0, 5, 15, 12, 80, 13, 12, 1, 0, 0, 0, 0, 0, 0, 8, 3, 3, 255, 2},
   {6, "baby crab", 0, 6, 18, 13, 80, 16, 13, 1, 0, 0, 0, 0, 0, 0, 10, 4, 4, 255, 1},
   {7, "little lizard", 0, 7, 19, 13, 75, 16, 13, 1, 0, 0, 0, 0, 0, 0, 12, 4, 4, 255, 1},
   {8, "small fly", 0, 8, 21, 15, 80, 15, 17, 1, 0, 0, 0, 0, 0, 0, 15, 5, 5, 255, 1},
   {9, "brown worm", 0, 9, 22, 15, 75, 15, 17, 1, 0, 0, 0, 0, 0, 0, 17, 5, 5, 255, 1},
   {10, "slug", 0, 10, 24, 15, 80, 15, 18, 1, 0, 0, 0, 0, 0, 0, 20, 6, 6, 255, 1},
   {11, "black worm", 0, 11, 25, 14, 80, 15, 18, 1, 0, 0, 0, 0, 0, 0, 22, 6, 6, 255, 1},
   {0, "putrid pup", 0, 12, 35, 18, 80, 19, 20, 1, 0, 0, 0, 0, 0, 0, 28, 7, 7, 255, 2},
   {13, "green worm", 0, 13, 35, 18, 90, 19, 20, 1, 0, 0, 0, 0, 0, 0, 30, 7, 7, 255, 1},
   {14, "skeleton", 0, 14, 35, 20, 50, 20, 22, 1, 1, 0, 0, 10, 10, 10, 33, 8, 8, 255, 2},
   {15, "brown ant", 0, 15, 40, 18, 90, 19, 18, 1, 0, 0, 0, 0, 0, 0, 35, 8, 8, 255, 1},
   {16, "vulture", 0, 16, 55, 18, 100, 19, 22, 1, 0, 0, 0, 0, 0, 0, 40, 9, 9, 255, 1},
   {17, "sprite", 0, 17, 60, 19, 80, 15, 18, 1, 0, 0, 2, 10, 10, 10, 42, 9, 9, 255, 1},
   {18, "green ooze", 0, 18, 65, 22, 50, 22, 25, 1, 0, 0, 0, 0, 0, 0, 48, 10, 10, 255, 2},
   {19, "small black bat", 0, 19, 70, 21, 90, 21, 22, 1, 0, 0, 0, 0, 0, 0, 52, 10, 10, 255, 1},
   {20, "small gray bat", 0, 20, 75, 22, 80, 23, 25, 1, 0, 0, 0, 0, 0, 0, 60, 11, 11, 255, 1},
   {21, "small blue bat", 0, 21, 77, 15, 50, 13, 20, 1, 0, 4, 0, 5, 5, 5, 62, 11, 11, 255, 1},
   {22, "small red bat", 0, 22, 80, 12, 80, 12, 20, 1, 4, 0, 0, 25, 0, 0, 70, 12, 12, 255, 1},
   {23, "ram", 0, 23, 65, 30, 60, 30, 20, 1, 0, 0, 0, 0, 0, 0, 73, 12, 12, 255, 2},
   {24, "trickster", 0, 24, 80, 15, 90, 12, 22, 1, 2, 0, 0, 0, 0, 0, 78, 13, 13, 255, 2},
   {25, "baby griffon", 0, 25, 85, 24, 80, 24, 28, 1, 0, 0, 0, 0, 0, 0, 82, 13, 13, 255, 2},
   {26, "baby green griffon", 0, 26, 80, 25, 80, 15, 25, 1, 0, 0, 2, 0, 0, 0, 86, 14, 14, 255, 2},
   {27, "baby white griffon", 0, 27, 80, 20, 80, 15, 22, 1, 0, 3, 0, 0, 40, 0, 90, 14, 14, 255, 2},
   {28, "baby black griffon", 0, 28, 80, 28, 80, 29, 33, 1, 0, 0, 0, 0, 0, 0, 95, 15, 15, 255, 2},
   {29, "brigand", 0, 29, 85, 28, 90, 28, 32, 1, 0, 0, 0, 0, 0, 0, 99, 15, 15, 255, 3},
   {30, "New Enemy", 0, 30, 95, 31, 70, 31, 35, 1, 0, 0, 0, 0, 0, 0, 105, 16, 16, 255, 1},
   {31, "demon dog", 0, 31, 80, 33, 80, 33, 38, 1, 0, 0, 0, 10, 10, 10, 110, 16, 16, 255, 2},
   {32, "fireworm", 0, 32, 80, 32, 80, 20, 35, 1, 3, 0, 0, 50, 0, 0, 115, 17, 17, 255, 1},
   {33, "flipper", 0, 33, 90, 40, 50, 40, 36, 1, 0, 0, 0, 0, 0, 0, 120, 17, 17, 255, 2},
   {34, "snail", 0, 34, 90, 40, 80, 38, 40, 1, 0, 0, 0, 0, 0, 0, 126, 18, 18, 255, 1},
   {35, "blue jelly", 0, 35, 90, 40, 80, 20, 36, 1, 0, 3, 0, 0, 50, 0, 131, 18, 18, 255, 2},
   {36, "crab", 0, 36, 100, 44, 80, 40, 40, 1, 0, 0, 0, 0, 0, 0, 137, 19, 19, 255, 1},
   {37, "blue fungus", 0, 37, 70, 25, 50, 28, 44, 1, 0, 3, 0, 0, 50, 0, 143, 19, 19, 255, 1},
   {38, "brown fungus", 0, 38, 110, 37, 50, 52, 42, 1, 0, 0, 0, 0, 0, 0, 149, 20, 20, 255, 1},
   {39, "spirit", 0, 39, 110, 37, 80, 48, 40, 1, 0, 0, 0, 30, 30, 30, 156, 20, 20, 255, 1},
   {40, "baby fire griffon", 0, 40, 100, 10, 80, 10, 15, 1, 15, 0, 0, 90, 0, 0, 161, 21, 21, 255, 2},
   {41, "fire swirl", 0, 41, 110, 15, 100, 15, 30, 1, 5, 0, 0, 80, 0, 0, 167, 21, 21, 255, 1},
   {42, "ice swirl", 0, 42, 120, 20, 100, 20, 40, 1, 0, 5, 0, 0, 80, 0, 173, 22, 22, 255, 1},
   {43, "lightning swirl", 0, 43, 120, 20, 100, 20, 40, 1, 0, 0, 5, 0, 0, 80, 178, 22, 22, 255, 1},
   {44, "feline thief", 0, 44, 130, 42, 90, 44, 55, 1, 0, 0, 0, 0, 0, 0, 184, 23, 23, 255, 3},
   {45, "zombie", 0, 45, 130, 42, 50, 50, 55, 1, 0, 0, 0, 0, 0, 0, 189, 23, 23, 255, 2},
   {46, "kobold", 0, 46, 140, 48, 70, 54, 57, 1, 0, 0, 0, 0, 0, 0, 193, 24, 24, 255, 3},
   {47, "devil cat", 0, 47, 140, 48, 90, 54, 54, 1, 0, 0, 0, 10, 10, 10, 198, 24, 24, 255, 1},
   {48, "bleached skeleton", 0, 48, 130, 50, 70, 50, 50, 1, 2, 0, 0, 0, 0, 0, 202, 25, 25, 255, 2},
   {49, "mini mummy", 0, 49, 135, 50, 50, 65, 55, 1, 0, 0, 0, 0, 0, 0, 210, 25, 25, 255, 2},
   {50, "mage", 0, 50, 90, 5, 80, 5, 60, 1, 3, 3, 3, 30, 30, 30, 216, 26, 26, 255, 2},
   {51, "red demon", 0, 51, 150, 60, 80, 60, 60, 1, 0, 0, 0, 0, 0, 0, 222, 26, 26, 255, 3},
   {52, "tick", 0, 52, 100, 55, 120, 55, 65, 1, 0, 0, 0, 0, 0, 0, 228, 27, 27, 255, 1},
   {53, "glowing eye", 0, 53, 150, 65, 60, 65, 60, 1, 0, 0, 0, 0, 0, 0, 234, 27, 27, 255, 1},
   {54, "ice goblin", 0, 54, 170, 70, 80, 50, 40, 1, 0, 8, 0, 0, 50, 0, 240, 28, 28, 255, 2},
   {55, "pale spider", 0, 55, 140, 65, 90, 65, 63, 1, 0, 0, 0, 0, 0, 0, 247, 28, 28, 255, 1},
   {56, "evil tree", 0, 56, 200, 75, 50, 75, 70, 1, 0, 0, 0, 20, 20, 20, 253, 29, 29, 255, 2},
   {57, "baby spider", 0, 57, 200, 65, 100, 65, 60, 1, 0, 0, 0, 0, 0, 0, 260, 29, 29, 255, 1},
   {58, "mudman", 0, 58, 200, 67, 80, 67, 75, 1, 0, 0, 0, 0, 0, 0, 266, 30, 30, 255, 3},
   {59, "giant slug", 0, 59, 200, 67, 80, 67, 75, 1, 0, 0, 0, 0, 0, 0, 273, 30, 30, 255, 2},
   {60, "gnome", 0, 60, 150, 60, 80, 80, 60, 2, 0, 0, 0, 0, 0, 0, 280, 31, 31, 255, 1},
   {61, "snake", 0, 61, 230, 75, 75, 75, 70, 1, 0, 0, 0, 10, 10, 10, 286, 31, 31, 255, 1},
   {62, "black_snake", 0, 62, 240, 80, 80, 75, 70, 1, 0, 0, 0, 10, 10, 10, 293, 32, 32, 255, 1},
   {63, "green snake", 0, 63, 220, 80, 100, 75, 60, 1, 0, 0, 0, 0, 0, 0, 300, 32, 32, 255, 1},
   {64, "black ant", 0, 64, 225, 70, 80, 70, 75, 1, 0, 2, 0, 0, 0, 0, 306, 33, 33, 255, 1},
   {65, "baby scorpion", 0, 65, 240, 70, 80, 80, 75, 1, 0, 0, 0, 0, 0, 0, 312, 33, 33, 255, 1},
   {66, "baby ice griffon", 0, 66, 250, 50, 60, 50, 75, 1, 0, 10, 0, 0, 80, 0, 319, 34, 34, 255, 2},
   {67, "flying snake", 0, 67, 250, 90, 50, 90, 80, 1, 0, 0, 0, 15, 15, 15, 325, 34, 34, 255, 1},
   {68, "spotted jelly", 0, 68, 280, 100, 30, 105, 60, 1, 0, 0, 0, 25, 25, 25, 331, 35, 35, 255, 2},
   {69, "ladybug", 0, 69, 275, 80, 50, 90, 80, 1, 0, 0, 0, 0, 0, 0, 338, 35, 35, 255, 1},
   {70, "gecko", 0, 70, 290, 85, 80, 85, 85, 1, 0, 0, 0, 0, 0, 0, 345, 36, 36, 255, 2},
   {71, "gorgon", 0, 71, 250, 40, 80, 75, 70, 1, 3, 3, 3, 0, 0, 0, 351, 36, 36, 255, 2},
   {72, "shambling dead", 0, 72, 210, 90, 80, 102, 85, 1, 0, 0, 0, 25, 25, 25, 358, 37, 37, 255, 3},
   {73, "rabbit", 0, 73, 220, 90, 120, 95, 70, 1, 0, 0, 0, 0, 0, 0, 365, 37, 37, 255, 1},
   {74, "blue dragon", 0, 74, 220, 80, 75, 100, 50, 1, 0, 15, 0, 0, 75, 0, 372, 38, 38, 255, 3},
   {75, "blue basilisk", 0, 75, 270, 110, 80, 108, 80, 1, 0, 0, 0, 0, 0, 0, 380, 38, 38, 255, 2},
   {76, "black dragon", 0, 76, 300, 100, 70, 95, 80, 1, 5, 0, 3, 50, 50, 50, 387, 39, 39, 255, 3},
   {77, "pale ant", 0, 77, 400, 95, 60, 105, 40, 2, 0, 0, 0, 0, 0, 0, 394, 39, 39, 255, 1},
   {78, "locust", 0, 78, 350, 75, 90, 105, 90, 1, 0, 0, 0, 0, 0, 0, 402, 40, 40, 255, 1},
   {79, "aged wolf", 0, 79, 350, 75, 80, 108, 90, 1, 0, 0, 0, 0, 0, 0, 409, 40, 40, 255, 2},
   {80, "griffon", 0, 80, 350, 110, 75, 115, 97, 1, 0, 0, 0, 0, 0, 0, 416, 41, 41, 255, 3},
   {81, "large flea", 0, 81, 250, 100, 90, 108, 60, 3, 0, 0, 0, 0, 0, 0, 424, 41, 41, 255, 1},
   {82, "gila monster", 0, 82, 400, 100, 70, 100, 85, 1, 8, 0, 0, 0, 0, 0, 432, 42, 42, 255, 2},
   {83, "flapper", 0, 83, 350, 95, 80, 100, 90, 1, 0, 0, 0, 90, 90, 90, 439, 42, 42, 255, 1},
   {84, "eel", 0, 84, 350, 115, 70, 115, 100, 1, 0, 0, 0, 0, 0, 0, 447, 43, 43, 255, 1},
   {85, "yellow fungus", 0, 85, 400, 120, 30, 125, 50, 1, 0, 0, 4, 0, 0, 0, 455, 43, 43, 255, 1},
   {86, "hound", 0, 86, 350, 125, 70, 115, 90, 1, 2, 0, 0, 20, 0, 0, 462, 44, 44, 255, 2},
   {87, "brown spider", 0, 87, 350, 125, 70, 118, 93, 1, 0, 0, 0, 0, 0, 0, 469, 44, 44, 255, 1},
   {88, "black bat", 0, 88, 250, 100, 120, 120, 80, 2, 0, 0, 0, 0, 0, 0, 477, 45, 45, 255, 1},
   {89, "zombie hare", 0, 89, 380, 120, 60, 120, 110, 1, 0, 0, 0, 50, 50, 50, 485, 45, 45, 255, 1},
   {90, "zombie ram", 0, 90, 380, 120, 70, 125, 105, 1, 0, 0, 0, 0, 0, 0, 492, 46, 46, 255, 3},
   {91, "skink", 0, 91, 375, 105, 90, 125, 100, 1, 0, 0, 0, 15, 15, 15, 500, 46, 46, 255, 1},
   {92, "fire naga", 0, 92, 400, 120, 70, 120, 100, 1, 10, 0, 0, 90, 0, 0, 507, 47, 47, 255, 3},
   {93, "ice naga", 0, 93, 400, 120, 70, 120, 100, 1, 10, 0, 0, 90, 0, 0, 515, 47, 47, 255, 3},
   {94, "lightning naga", 0, 94, 400, 122, 70, 122, 105, 1, 0, 0, 10, 0, 0, 90, 522, 48, 48, 255, 3},
   {95, "moss man", 0, 95, 420, 140, 60, 140, 120, 1, 0, 0, 0, 0, 20, 0, 530, 48, 48, 255, 2},
   {96, "green griffon", 0, 96, 420, 80, 80, 130, 120, 1, 0, 0, 1, 0, 0, 10, 537, 49, 49, 255, 2},
   {97, "giant fireworm", 0, 97, 450, 40, 60, 120, 130, 1, 10, 0, 0, 90, 0, 0, 543, 49, 49, 255, 2},
   {98, "feline brigand", 0, 98, 450, 135, 80, 130, 125, 1, 0, 0, 0, 0, 0, 0, 550, 50, 50, 255, 4},
   {99, "blue devil", 0, 99, 500, 135, 50, 140, 125, 1, 0, 0, 0, 20, 20, 20, 555, 50, 50, 255, 3},
   {100, "fire elemental", 0, 100, 500, 30, 50, 0, 120, 1, 20, 0, 0, 90, 0, 0, 562, 51, 51, 255, 1},
   {101, "ice elemental", 0, 101, 500, 30, 50, 0, 120, 1, 0, 20, 0, 0, 90, 0, 570, 51, 51, 255, 1},
   {102, "bolt elemental", 0, 102, 500, 30, 50, 0, 120, 1, 0, 0, 20, 0, 0, 90, 577, 52, 52, 255, 1},
   {103, "unded rabbit", 0, 103, 510, 140, 70, 140, 127, 1, 0, 0, 0, 0, 0, 0, 585, 52, 52, 255, 1},
   {104, "rabid squirrel", 0, 104, 500, 141, 90, 142, 130, 1, 0, 0, 0, 0, 0, 0, 592, 53, 53, 255, 1},
   {105, "fairy", 0, 105, 340, 30, 80, 120, 120, 2, 3, 3, 3, 60, 60, 60, 599, 53, 53, 255, 2},
   {106, "gray bat", 0, 106, 540, 120, 80, 145, 130, 1, 0, 0, 0, 0, 0, 0, 607, 54, 54, 255, 1},
   {107, "albino gecko", 0, 107, 540, 120, 70, 145, 130, 1, 0, 0, 0, 0, 0, 0, 614, 54, 54, 255, 1},
   {108, "lamia", 0, 108, 500, 130, 100, 155, 130, 1, 0, 0, 0, 0, 0, 0, 622, 55, 55, 255, 3},
   {109, "green naga", 0, 109, 500, 130, 90, 155, 130, 1, 0, 0, 0, 0, 0, 0, 629, 55, 55, 255, 2},
   {110, "toxic rat", 0, 110, 520, 120, 70, 145, 130, 2, 0, 0, 0, 30, 30, 30, 637, 56, 56, 255, 2},
   {111, "blue ant", 0, 111, 525, 80, 70, 150, 140, 1, 0, 1, 0, 0, 0, 0, 644, 56, 56, 255, 1},
   {112, "ice wolf", 0, 112, 520, 40, 80, 145, 140, 1, 0, 15, 0, 0, 90, 0, 652, 57, 57, 255, 2},
   {113, "fire wolf", 0, 113, 520, 40, 80, 145, 140, 1, 15, 0, 0, 90, 0, 0, 659, 57, 57, 255, 2},
   {114, "green fungus", 0, 114, 550, 155, 80, 155, 145, 1, 0, 0, 0, 0, 0, 0, 667, 58, 58, 255, 1},
   {115, "rotten dog", 0, 115, 550, 155, 80, 155, 145, 1, 0, 0, 0, 25, 25, 25, 674, 58, 58, 255, 2},
   {116, "toxic skeleton", 0, 116, 560, 160, 40, 187, 155, 1, 0, 0, 0, 0, 0, 0, 681, 59, 59, 255, 3},
   {117, "demonic ram", 0, 117, 550, 160, 80, 180, 160, 1, 0, 0, 0, 0, 0, 0, 688, 59, 59, 255, 3},
   {118, "bodkin", 0, 118, 580, 170, 100, 170, 150, 1, 0, 0, 0, 0, 0, 0, 696, 60, 60, 255, 3},
   {119, "jackal", 0, 119, 580, 50, 80, 160, 155, 2, 3, 0, 0, 80, 0, 0, 703, 60, 60, 255, 2},
   {120, "devil dog", 0, 120, 666, 140, 66, 165, 150, 1, 0, 0, 0, 0, 0, 0, 711, 61, 61, 255, 2},
   {121, "vampire fly", 0, 121, 580, 150, 120, 160, 150, 2, 0, 0, 0, 0, 0, 0, 719, 61, 61, 255, 1},
   {122, "giant toad", 0, 122, 610, 180, 80, 175, 170, 1, 0, 0, 0, 0, 0, 0, 726, 62, 62, 255, 1},
   {123, "dark eel", 0, 123, 610, 150, 80, 175, 100, 1, 0, 0, 5, 0, 0, 40, 735, 62, 62, 255, 1},
   {124, "white griffon", 0, 124, 650, 80, 100, 160, 140, 1, 0, 10, 0, 0, 80, 0, 742, 63, 63, 255, 3},
   {125, "black griffon", 0, 125, 650, 80, 100, 160, 140, 1, 5, 0, 5, 50, 0, 50, 750, 63, 63, 255, 3},
   {126, "basilisk", 0, 126, 680, 180, 90, 180, 160, 1, 0, 0, 0, 0, 0, 0, 757, 64, 64, 255, 2},
   {127, "red basilisk", 0, 127, 680, 100, 90, 180, 150, 1, 5, 0, 0, 90, 0, 0, 764, 64, 64, 255, 2},
   {128, "rabid gray squirrel", 0, 128, 690, 180, 90, 170, 170, 2, 0, 0, 0, 0, 0, 0, 771, 65, 65, 255, 1},
   {129, "blue bat", 0, 129, 650, 120, 100, 175, 140, 1, 0, 10, 0, 0, 50, 0, 778, 65, 65, 255, 1},
   {130, "red bat", 0, 130, 650, 120, 100, 175, 140, 1, 10, 0, 0, 50, 0, 0, 785, 66, 66, 255, 1},
   {131, "red jelly", 0, 131, 400, 170, 50, 240, 160, 1, 0, 0, 0, 80, 80, 80, 793, 66, 66, 255, 1},
   {132, "blue crab", 0, 132, 700, 190, 80, 190, 170, 1, 0, 0, 0, 0, 0, 0, 800, 67, 67, 255, 1},
   {133, "burned skeleton", 0, 133, 700, 170, 40, 190, 160, 1, 10, 0, 0, 80, 0, 0, 807, 67, 67, 255, 3},
   {134, "mummy warrior", 0, 134, 700, 170, 60, 195, 165, 1, 0, 0, 10, 0, 0, 0, 814, 68, 68, 255, 3},
   {135, "turtle", 0, 135, 550, 200, 40, 205, 190, 1, 0, 0, 0, 0, 0, 0, 821, 68, 68, 255, 1},
   {136, "burning bush", 0, 136, 650, 180, 80, 180, 160, 1, 15, 0, 0, 90, 0, 0, 828, 69, 69, 255, 1},
   {137, "giant spider", 0, 137, 720, 200, 70, 205, 180, 1, 0, 0, 0, 0, 0, 0, 835, 69, 69, 255, 2},
   {138, "cyclops", 0, 138, 750, 200, 40, 225, 190, 1, 0, 0, 0, 50, 50, 50, 842, 70, 70, 255, 3},
   {139, "giant snail", 0, 139, 720, 210, 80, 210, 180, 1, 0, 0, 0, 0, 0, 0, 850, 70, 70, 255, 1},
   {140, "giant fly", 0, 140, 650, 190, 110, 190, 160, 2, 0, 0, 0, 0, 0, 0, 857, 71, 71, 255, 1},
   {141, "giant sandworm", 0, 141, 720, 200, 70, 210, 180, 1, 0, 0, 0, 0, 0, 0, 864, 71, 71, 255, 2},
   {142, "scorpion", 0, 142, 750, 125, 80, 200, 175, 1, 1, 1, 1, 0, 0, 0, 871, 72, 72, 255, 1},
   {143, "possessed cape", 0, 143, 250, 200, 90, 200, 255, 1, 0, 0, 0, 0, 0, 0, 878, 72, 72, 255, 2},
   {144, "ooze", 0, 144, 750, 220, 50, 230, 200, 1, 0, 0, 0, 0, 0, 0, 885, 73, 73, 255, 1},
   {145, "yeti", 0, 145, 800, 180, 55, 220, 190, 1, 0, 15, 0, 0, 80, 0, 892, 73, 73, 255, 3},
   {146, "beholder", 0, 146, 800, 140, 55, 220, 180, 1, 15, 0, 0, 90, 0, 0, 899, 74, 74, 255, 2},
   {147, "fire griffon", 0, 147, 820, 100, 90, 200, 180, 2, 10, 0, 0, 90, 0, 0, 905, 74, 74, 255, 3},
   {148, "ice griffon", 0, 148, 820, 100, 90, 200, 180, 2, 0, 10, 0, 0, 90, 0, 905, 75, 75, 255, 3},
   {149, "gorilla", 0, 149, 880, 220, 50, 240, 200, 1, 0, 0, 0, 0, 0, 0, 912, 75, 75, 255, 2},
   {150, "venom jackal", 0, 150, 800, 150, 80, 220, 170, 1, 0, 0, 3, 0, 0, 0, 920, 76, 76, 255, 1},
   {151, "fire elder naga", 0, 151, 800, 200, 90, 180, 160, 2, 5, 0, 0, 95, 0, 0, 927, 76, 76, 255, 3},
   {152, "leopard gecko", 0, 152, 820, 200, 60, 225, 180, 1, 0, 0, 0, 15, 15, 15, 934, 77, 77, 255, 1},
   {153, "stone scorpion", 0, 153, 750, 200, 50, 235, 220, 1, 0, 0, 0, 70, 70, 70, 941, 77, 77, 255, 2},
   {154, "ghost", 0, 154, 500, 200, 80, 190, 180, 2, 5, 5, 5, 0, 0, 0, 948, 78, 78, 255, 1},
   {155, "shadow", 0, 155, 850, 200, 120, 215, 195, 2, 0, 0, 0, 0, 0, 0, 956, 78, 78, 255, 1},
   {156, "ninja", 0, 156, 880, 200, 100, 230, 190, 1, 0, 0, 0, 0, 0, 0, 963, 79, 79, 255, 2},
   {157, "caveman", 0, 157, 850, 220, 70, 240, 220, 1, 0, 0, 0, 0, 0, 0, 970, 79, 79, 255, 3},
   {158, "alpha wolf", 0, 158, 900, 220, 80, 235, 200, 1, 0, 0, 0, 0, 0, 0, 977, 80, 80, 255, 2},
   {159, "warlock", 0, 159, 650, 190, 70, 200, 160, 2, 3, 3, 3, 0, 0, 0, 984, 80, 80, 255, 2},
   {160, "serpent", 0, 160, 900, 230, 80, 230, 200, 1, 0, 0, 0, 0, 0, 0, 991, 81, 81, 255, 1},
   {161, "judge", 0, 161, 900, 190, 80, 230, 180, 1, 1, 1, 1, 0, 0, 0, 999, 81, 81, 255, 4},
   {162, "black serpent", 0, 162, 920, 240, 80, 245, 200, 1, 0, 0, 0, 0, 0, 0, 1006, 82, 82, 255, 1},
   {162, "mossy crab", 0, 162, 900, 240, 80, 245, 220, 1, 0, 0, 0, 0, 0, 0, 1013, 82, 82, 255, 1},
   {164, "orange fungus", 0, 164, 850, 160, 50, 245, 220, 2, 0, 1, 1, 75, 75, 75, 1020, 83, 83, 255, 1},
   {165, "archdemon", 0, 165, 950, 250, 60, 250, 230, 1, 4, 0, 0, 0, 0, 0, 1027, 83, 83, 255, 2},
   {166, "living fire", 0, 166, 900, 255, 70, 220, 180, 2, 12, 0, 0, 90, 0, 0, 1034, 84, 84, 255, 2},
   {167, "living ice", 0, 167, 900, 255, 70, 220, 180, 2, 0, 12, 0, 0, 90, 0, 1042, 84, 84, 255, 2},
   {168, "living lightning", 0, 168, 900, 255, 70, 220, 180, 2, 0, 0, 12, 0, 0, 90, 1049, 85, 85, 255, 2},
   {169, "shadow wolf", 0, 169, 940, 255, 80, 255, 230, 1, 0, 0, 0, 70, 70, 70, 1056, 85, 85, 255, 2},
   {170, "walking dead", 0, 170, 960, 255, 50, 255, 225, 2, 0, 0, 0, 0, 0, 0, 1063, 86, 86, 255, 2},
   {171, "zombie king", 0, 171, 960, 255, 60, 255, 220, 2, 0, 0, 0, 0, 0, 0, 1070, 86, 86, 255, 3},
   {172, "gargoyle", 0, 172, 1000, 160, 80, 255, 200, 3, 2, 0, 0, 0, 0, 0, 1077, 87, 87, 255, 2},
   {173, "mini goblin", 0, 173, 1100, 255, 120, 245, 220, 2, 0, 0, 0, 0, 0, 0, 1085, 87, 87, 255, 2},
   {174, "green giant", 0, 174, 1100, 255, 60, 260, 220, 2, 0, 0, 0, 0, 0, 0, 1092, 88, 88, 255, 3},
   {175, "red devil", 0, 175, 1100, 200, 70, 250, 200, 2, 1, 0, 1, 0, 0, 0, 1099, 88, 88, 255, 3},
   {176, "elder lamia", 0, 176, 1100, 120, 80, 200, 200, 3, 2, 2, 2, 0, 0, 0, 1106, 89, 89, 255, 3},
   {178, "cyclops warrior", 0, 178, 1100, 255, 55, 265, 230, 2, 0, 0, 0, 80, 80, 80, 1113, 90, 90, 255, 4},
   {179, "lizard king", 0, 179, 1120, 260, 70, 290, 220, 1, 0, 0, 0, 0, 0, 0, 1120, 90, 90, 255, 3},
   {180, "white dragon", 0, 180, 1050, 225, 70, 255, 180, 2, 0, 25, 0, 0, 90, 0, 1127, 91, 91, 255, 4},
   {181, "green dragon", 0, 181, 1050, 225, 70, 255, 180, 2, 0, 0, 25, 0, 0, 90, 1134, 91, 91, 255, 4},
   {182, "red dragon", 0, 182, 1070, 225, 70, 255, 180, 2, 25, 0, 0, 90, 0, 0, 1141, 92, 92, 255, 4},
   {183, "illusionist", 0, 183, 1000, 255, 70, 255, 200, 1, 3, 3, 3, 0, 0, 0, 1148, 92, 92, 255, 2},
   {184, "archangel", 0, 184, 1100, 255, 80, 285, 225, 3, 0, 0, 0, 50, 50, 50, 1156, 93, 93, 255, 3},
   {185, "monk", 0, 185, 1050, 255, 100, 255, 190, 3, 0, 0, 0, 0, 0, 0, 1163, 93, 93, 255, 2},
   {186, "war tortoise", 0, 186, 1000, 255, 40, 290, 255, 2, 0, 0, 0, 0, 0, 0, 1170, 94, 94, 255, 4},
   {187, "bowman", 0, 187, 1050, 260, 110, 260, 220, 2, 0, 0, 0, 0, 0, 0, 1177, 94, 94, 255, 2},
   {188, "faded fungus", 0, 188, 1050, 260, 40, 280, 200, 2, 3, 3, 3, 0, 0, 0, 1184, 95, 95, 255, 2},
   {189, "hooded one", 0, 189, 1050, 255, 70, 270, 215, 3, 0, 0, 0, 0, 0, 0, 1191, 95, 95, 255, 2},
   {190, "shade", 0, 190, 800, 255, 110, 235, 220, 3, 0, 0, 0, 0, 0, 0, 1199, 96, 96, 255, 2},
   {191, "shrouded one", 0, 191, 1100, 140, 70, 240, 220, 2, 5, 5, 5, 0, 0, 0, 1206, 96, 96, 255, 2},
   {192, "zealot", 0, 192, 1100, 200, 70, 220, 230, 2, 0, 0, 10, 0, 0, 0, 1213, 97, 97, 255, 2},
   {193, "lightning elder naga", 0, 193, 1150, 255, 75, 255, 230, 1, 0, 0, 30, 0, 0, 95, 1220, 97, 97, 255, 3},
   {194, "ice elder naga", 0, 194, 1150, 255, 75, 255, 230, 1, 0, 30, 0, 0, 95, 0, 1228, 98, 98, 255, 4},
   {195, "ancient tree", 0, 195, 1100, 255, 50, 200, 200, 1, 8, 8, 8, 0, 0, 0, 1235, 98, 98, 255, 2},
   {196, "elder dragon", 0, 196, 1250, 260, 80, 290, 230, 2, 0, 0, 0, 0, 0, 0, 1242, 99, 99, 255, 4},
   {197, "vampire", 0, 197, 1200, 100, 80, 225, 190, 3, 4, 4, 4, 0, 0, 0, 1249, 99, 99, 255, 2},
   {198, "reaper", 0, 198, 1000, 125, 70, 255, 220, 3, 2, 2, 2, 0, 0, 0, 1255, 100, 100, 255, 2},
   {199, "rhino", 0, 199, 1300, 280, 60, 270, 255, 2, 0, 0, 0, 0, 0, 0, 1262, 100, 100, 255, 4},
   {200, "Prang, war elephant", 0, 200, 150, 35, 70, 32, 20, 2, 0, 0, 0, 0, 0, 0, 400, 12, 12, 255, 3},
   {201, "Steenkey, elder naga", 0, 201, 300, 40, 70, 50, 50, 2, 1, 1, 1, 0, 0, 0, 750, 25, 25, 255, 3},
   {202, "Nameless, black orc", 0, 202, 530, 100, 90, 155, 120, 1, 1, 1, 1, 50, 50, 50, 2500, 50, 50, 255, 4},
   {203, "Groz, goblin king", 0, 203, 1000, 190, 75, 225, 205, 2, 0, 0, 0, 0, 0, 0, 5000, 70, 70, 255, 5},
   {204, "Lortrox, dragon knight", 0, 204, 800, 160, 70, 160, 150, 3, 0, 0, 0, 0, 0, 0, 10, 55, 55, 255, 4},
   {205, "Silant, ice giant", 0, 205, 1400, 160, 75, 255, 200, 2, 0, 10, 0, 80, 90, 80, 7500, 80, 80, 255, 5},
   {206, "Megalith, armored beast", 0, 206, 3500, 255, 120, 280, 280, 3, 15, 15, 15, 85, 85, 85, 10000, 100, 100, 255, 6}
};

NPCInfoType g_npc_info[] = {
	{13, 7, "These animals may be cute, but nasty ones live below."},
	{29, 8, "Training is key to survival."},
	{19, 14, "Artifacts make you stronger over time."},
	{26, 16, "A Scroll of Recall can save your life."},
	{25, 20, "Always identify your gear, lest you be cursed."},
	{22, 21, "Meow? Meow. Ekekekek!"},
	{18, 21, "Uniquely strong monsters await you deep below."},
	{16, 26, "If you don't equip your stuff, it won't help you."},
	{18, 31, "Don't be afraid to flee from battle."},
	{26, 31, "Stock up on healing potions when you can."},
	{27, 38, "There are three dungeons to explore."},
	{9, 33, "You may die, but your heirs will live on."},
	{9, 40, "Cursed gear can be saved with the right scroll."},
	{43, 31, "No, you can't fish here. Sorry."},
	{42, 27, "You can't even fish in this place. Lame!"},
	{43, 24, "Use a recall circle to return where you were."},
	{30, 7, "- Level 1 training dummy -"},
	{32, 7, "- Level 10 training dummy -"},
	{34, 7, "- Level 25 training dummy -"},
	{36, 7, "- Level 50 training dummy -"},
	{38, 7, "- Level 100 training dummy -"},
	{40, 7, "- Training dummies - check your strength here! -"},
	{45, 17, "- Portal to the Dusty Tunnels -"},
	{3, 9, "- Portal to the Marble Halls -"},
	{39, 37, "- Portal to the Crystal Depths -"},
	{21, 12, "- Museum and Artifact Collection -"},
	{31, 16, "- Weapon and Armor Shop -"},
	{11, 16, "- Potion and Scroll Shop -"}
};

