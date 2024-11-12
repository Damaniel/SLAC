// Auto-generated file - do not edit!

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
   {0, "Helm", 0},
   {1, "Hat", 0},
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
   {0, "Cloth Hat", 42, 0, 1, 255, {1, 1, 1}, 2, true, true, true, false, true, true, false}
};

