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

unsigned short g_town_tile_data[TownConsts::TOWN_SIZE * TownConsts::TOWN_SIZE] = {
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   1,   2,   2,   2,   2,   2,   3,   4,   5,   6,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   7,   0,
	  0,   8,   9,  10,  10,  10,  11,  12,  13,  14,  15,  16,  17,  17,  17,  17,  17,  17,  18,  16,  17,  17,  17,  17,  17,  17,  18,  19,  20,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  22,  19,  19,  19,  23,   0,
	  0,   8,  24,  25,  26,  25,  27,  12,  13,  14,  15,  28,  29,  29,  29,  30,  31,  32,  33,  28,  30,  31,  31,  34,  29,  29,  33,  19,  35,  36,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  38,  35,  19,  19,  39,  23,   0,
	  0,   8,  24,  25,  40,  25,  24,  12,  13,  14,  15,  28,  32,  31,  31,  31,  31,  31,  33,  28,  41,  31,  31,  31,  41,  31,  33,  19,  35,  42,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  45,  35,  19,  46,  46,  23,   0,
	  0,   8,  47,  10,  48,  10,  49,  12,  13,  14,  15,  28,  31,  31,  31,  50,  29,  29,  33,  28,  31,  34,  31,  31,  31,  31,  33,  19,  35,  51,  52,  43,  52,  43,  52,  43,  52,  43,  52,  43,  52,  53,  35,  19,  46,  46,  23,   0,
	  0,  54,  55,  56,  40,  57,  55,  58,  13,  14,  15,  59,  17,  17,  60,  60,  17,  17,  61,  59,  17,  17,  60,  60,  17,  17,  61,  19,  62,  21,  21,  43,  21,  43,  21,  43,  21,  43,  21,  43,  21,  21,  63,  19,  46,  46,  23,   0,
	  0,  64,  65,  65,  40,  65,  65,  65,  66,  14,  15,  19,  19,  67,  19,  19,  19,  19,  19,  68,  68,  68,  68,  68,  68,  68,  19,  19,  69,  70,  71,  72,  73,  72,  73,  72,  73,  72,  73,  72,  74,  75,  69,  19,  46,  46,  23,   0,
	  0,  76,  77,  77,  40,  77,  77,  77,  77,  14,  15,  19,  19,  19,  19,  19,  19,  19,  78,  79,  80,  80,  80,  80,  80,  81,  82,  83,  69,  84,  72,  72,  72,  72,  72,  72,  72,  72,  72,  72,  72,  85,  69,  19,  46,  46,  23,   0,
	  0,  86,  87,  88,  40,  13,  14,  89,  87,  87,  19,  19,  19,  19,  19,  19,  39,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  69,  93,  94,  94,  94,  94,  94,  94,  94,  94,  72,  94,  94,  95,  69,  19,  83,  19,  23,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  19,  19,  19,  39,  19,  19,  19,  19,  19,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  19,  96,  96,  96,  96,  96,  96,  96,  96,  97,  40,  98,  96,  96,  19,  19,  19,  19,  23,   0,
	  0,   8,  99,  78,  40,  13,  14,  15,  19,  68,  68,  68,  68,  68,  68,  68,  19,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  19,  68,  68,  68,  68,  68,  68,  68,  19,  78,  40,  82,  19,  19,  19,  19,  19,  19,  23,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  78,  79,  80,  80,  80,  80,  80,  81,  82,  19,  78, 100, 101, 102, 103, 101, 101, 104,  82,  19,  78,  79,  80,  80,  80,  80,  80,  81,  39,  78,  40,  82,  19,  19,  20,  21,  21,  21, 105,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  19,  96,  96,  97,  40,  98,  96,  96, 106,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  78,  40,  82, 107,  19,  35,  69,  69,  69, 108,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  19, 109,  19,  78,  40,  82,  19,  39,  19,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  78,  40,  82,  19,  19,  35,  69, 110,  69, 108,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  78,  90,  91,  91,  91,  91,  91,  92,  82,  19,  19,  19,  68, 111,  40, 112,  68,  19,  19,  19,  78,  90,  91,  91,  91,  91,  91,  92,  82,  78,  40,  82,  19,  19,  35,  69,  40,  69, 108,   0,
	  0,   8,  19,  78,  40,  13,  14,  15,  78, 100, 101, 113, 103, 101, 101, 104,  82,  19,  19,  78,  70, 114,  72, 114,  75,  82, 115,  19,  78, 100, 101, 116, 103, 101, 101, 104,  82,  78,  40,  82,  19,  19,  62,  21,  40,  21, 117,   0,
	  0,   8,  19,  78,  40,  13,  14, 118,  68,  68,  68, 111,  40, 112,  68,  68,  68,  68,  68, 111, 119,  72,  72,  72,  85, 112,  68,  68,  68,  68,  68, 111,  40, 112,  68,  68,  68, 111,  40, 112,  68,  68,  68, 111,  40, 120,  23,   0,
	  0,   8,  19,  78,  93, 121, 122, 121, 121, 114, 122, 121,  94, 121, 122, 122, 121, 122, 122, 122,  72,  72, 123,  72,  72, 122, 122, 122, 122, 121, 122, 122,  94, 122, 122, 121, 122, 122,  94, 122, 114, 121, 122, 122,  95,  82,  23,   0,
	  0,   8,  39,  19, 124,  13,  14, 125,  97,  40,  98,   9,  10,  10,  10,  10,  10,  11,  96,  97, 119,  72,  72,  72,  85,  98,  96,   9,  10,  10,  10,  10,  10, 126,  10,  10,  10,  10,  10,  11,  40,  98,  96,  96,  96, 127,  23,   0,
	  0,   8,  46,  46,  12,  13,  14,  15,  78,  40, 128,  24,  46,  79,  80,  81,  69,  27,  19,  78, 119,  72,  72,  72,  85, 129,  19,  27,  69,  79,  80,  81,  46,  27, 130,  79,  80,  81,  69,  27,  40,  82,  19,  19,  19,  19,  23,   0,
	  0,   8,  46,  46,  12,  13,  14,  15,  78,  40, 128,  24,  46,  90,  91,  92,  10,  49, 131, 111, 132,  72, 133,  72,  85, 112,  68,  47,  10,  90,  91,  92,  46,  27, 130,  90,  91,  92,  10,  49,  40,  82,  25,  25,  25,  25,  23,   0,
	  0,   8,  46,  46,  12,  13,  14,  15,  78,  40, 128,  24,  46,  90,  91,  92, 121, 122, 122, 122,  72,  72,  72,  72,  72, 122, 122, 122, 122,  90,  91,  92,  46,  27, 130,  90,  91,  92, 121, 122, 134,  82, 135, 136, 136, 137,  23,   0,
	  0,   8,  46,  46,  12,  13,  14,  15,  78,  40, 128,  24,  46,  90,  91,  92,  10,  11,  96,  97, 119, 138,  72,  72,  85,  98,  96,   9,  10,  90,  91,  92,  30,  27, 130,  90,  91,  92,  10,  11,  40,  82, 139, 140, 140, 141,  23,   0,
	  0,   8,  46,  46,  12,  13,  14,  15,  78,  40, 128,  24,  46, 100, 101, 104,  69,  27,  19,  78, 119,  72, 123,  72,  85,  82,  19,  27,  69,  90,  91,  92,  46,  27, 130,  90,  91,  92,  69,  27, 119, 121, 122, 142, 140, 141,  23,   0,
	  0,   8,  19, 107,  12,  13,  14,  15,  78,  40, 128,  47,  10,  10,  10,  10,  10,  49,  19,  78, 119,  72,  72,  72,  85,  82,  19,  27,  69, 100, 101, 104,  46,  27, 130, 100, 101, 104,  69,  27,  40,  82, 139, 140, 140, 141,  23,   0,
	  0,   8,  19,  19,  12,  13,  14,  15,  78,  40, 128,  19,  19,  19,  19,  19, 143,  19,  83,  78, 119,  72,  72,  72,  85,  82,  19,   9,  10,  10,  10,  10,  10, 144,  10,  10,  10,  10,  10, 145,  40,  82,  19,  19,  19,  25,  23,   0,
	  0, 146, 146,  19,  12,  13,  14,  15,  78,  40, 128,   9,  10,  10,  10,  10,  10,  11,  19,  78, 119,  72,  72,  72,  85,  82,  19,  27,  69,  79,  80,  81, 147,  27, 148,  79,  80,  81,  69,  27,  40,  82, 149,  19,  19,  25,  23,   0,
	  0, 150,  69, 151, 146,  13,  14,  15,  78,  40, 128,  24, 148,  79,  80,  81,  69,  27,  19,  78, 119,  72,  72,  72,  85,  82,  19,  27,  69,  90,  91,  92, 147,  27,  30,  90,  91,  92,  69,  27,  40,  82,  19,  19,  19,  25,  23,   0,
	  0, 150,  69, 151, 146,  13,  14, 118, 111,  40, 128,  24, 148,  90,  91,  92,  10,  49,  68, 111, 119,  72,  72,  72,  85, 112,  68,  47,  10,  90,  91,  92, 152,  27, 148,  90,  91,  92,  10,  49,  40,  82, 135, 136, 136, 137,  23,   0,
	  0,  79,  80,  81, 146,  13,  14,  70, 122,  95, 128,  24, 148,  90,  91,  92, 121, 122, 122, 122,  72,  72, 123,  72,  72, 122, 122, 122, 122,  90,  91,  92,  30,  27, 148,  90,  91,  92, 121, 122,  85,  82, 139, 140, 140, 141,  23,   0,
	  0,  90,  91,  92, 146,  13,  14,  40,  98,  96,  19,  24, 148,  90,  91,  92,  10,  11, 153,  97, 119,  72,  72,  72,  85,  98, 154,   9,  10,  90,  91,  92, 152,  27, 148,  90,  91,  92,  10,  11, 119, 121, 122, 155, 140, 141,  23,   0,
	  0,  90,  91,  92, 122, 121, 122,  85, 128,  19,  19,  24, 148, 100, 101, 104,  69,  27,  19,  78,  93,  94,  72,  94,  95,  82,  19,  27,  69, 100, 101, 104, 148,  27, 148, 100, 101, 104,  69,  27,  40,  82, 139, 140, 140, 141,  23,   0,
	  0,  90,  91,  92, 146,  13,  14,  40, 128, 156,  19,  47,  10,  10,  10,  10,  10,  49,  19,  19,  96,  97,  40,  98,  96,  19, 107,  47,  10,  10,  10,  10,  10, 157,  10,  10,  10,  10,  10,  49,  40,  82,  25,  25,  25,  25,  23,   0,
	  0, 100, 101, 104, 146,  13,  14,  40, 158,  55,  55,  55,  55,  55,  55,  55,  55,  55,  55,  19,  39,  78,  40, 128,  19,  19,  19,  19,  19,  19,  68,  68,  68,  68,  68,  68,  68,  68,  68, 111,  40,  82,  19,  19,  19,  19,  23,   0,
	  0,   4,  65,  65,  65,  66,  77,  40,  65,  65,  65,  65,  65,  65,  65,  65,  65,  65,   5,  15,  19,  78,  40, 128, 159, 160, 160, 161, 162,  78,  70, 122, 122, 122, 121, 122, 122, 122, 122, 121,  85, 112,  68,  68,  68,  68, 163,   0,
	  0,  13,  77,  77,  77,  77,  77,  40,  77,  77,  77,  77,  77,  77,  77,  77,  77,  77,  14,  15,  19,  78,  40, 128, 164, 165, 165, 166, 167,  78,  40,  98,  96,  96,  96,  96,  96,  96,  96,  97,  40, 168, 168, 168, 168, 168, 168,   0,
	  0, 169, 169, 169, 169, 169, 169,  40, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13,  14,  15,  19, 170,  40, 128, 171, 172, 172, 172, 173,  78,  40, 128, 174, 174, 174, 174,  19,  68,  68, 175,  40, 168, 176, 176, 176, 176, 176,   0,
	  0, 169, 169, 169, 169, 169, 169,  40, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13,  14,  15,  83, 177,  40, 112,  68,  68,  68, 178,  68, 111,  40, 128, 174, 174, 174,  19, 111, 168, 168, 168, 179, 176, 180, 181, 181, 181, 182,   0,
	  0, 183, 184, 184, 184, 184, 184, 185, 184, 184, 184, 184, 184, 186, 169, 169, 169,  13,  14,  15,  19, 177,  93, 122, 122, 122, 122, 122, 122, 122,  95, 128, 174, 174, 174,  78, 168, 176, 176, 176, 187, 176, 188, 189, 189, 190, 190,   0,
	  0, 191, 192, 193, 194, 193, 195, 193, 196, 197, 198, 193, 199, 200, 169, 169, 169,  13,  14, 201,  55, 202, 203, 203, 203,  96,  96,  96,  96,  96,  96,  19, 174, 174, 174,  78, 168, 176, 180, 181, 187, 181, 204, 205, 206, 206, 207,   0,
	  0, 191, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 200, 169, 169, 169,  13, 208,  65,  65,  65,  65,  65,   5,  15, 174, 174, 174, 174, 174, 174, 174, 174, 174,  78, 168, 176, 188, 190, 187, 205, 206, 209, 210, 211, 212,   0,
	  0, 213, 214, 193, 215, 193, 216, 193, 217, 193, 194, 193, 218, 200, 169, 169, 169,  13,  77,  77,  77,  77,  77,  77,  14,  15, 174, 174, 174, 174, 174, 174, 174, 174, 174,  78, 168, 176, 188, 190, 187, 219, 220, 220, 220, 221, 212,   0,
	  0, 222, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 200, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13,  14,  15, 174, 174, 174, 174, 174, 174, 174, 174, 174,  78, 168, 176, 188, 190, 223, 224, 224, 224, 225, 226, 212,   0,
	  0, 222, 194, 193, 199, 193, 215, 193, 214, 193, 195, 193, 227, 200, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13,  14, 201,  55,  55,  55,  55,  55,  19, 174, 174, 174,  78, 168, 176, 188, 190, 205, 206, 228, 228, 228, 221, 212,   0,
	  0, 222, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 200, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13, 208,  65,  65,  65,  65,  65,   5,  15, 174, 174, 174,  78, 168, 176, 188, 190, 229, 210, 211, 211, 211, 211, 212,   0,
	  0, 230, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 231, 169, 169, 169, 169, 169, 169, 169, 169, 169,  13,  77,  77,  77,  77,  77,  77,  14, 232, 233, 233, 233, 234, 168, 176, 188, 190, 219, 235, 235, 235, 235, 235, 236,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

unsigned char g_town_movability[TownConsts::TOWN_SIZE * TownConsts::TOWN_SIZE] = {
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
	  0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	  0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0,
	  0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	  0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
	  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
	  0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0,
	  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
	  0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0,
	  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

unsigned short g_museum_tile_data[TownConsts::MUSEUM_WIDTH * TownConsts::MUSEUM_HEIGHT] = {
	   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	   0,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   8,   9,   9,   9,   9,   9,  10,   5,   5,   8,   9,   9,   9,   9,   9,   9,  10,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   8,   9,   9,   9,   9,   9,  10,   5,   5,   8,   9,   9,   9,   9,   9,   9,  10,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,   4,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   5,   7,   6,   0,
	   0,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   0,
	   0,  12,  13,  13,  13,  13,  13,  13,  14,  13,   5,  13,  14,  13,  13,  13,  13,  13,  13,  15,   0,
	   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  16,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16
	};

unsigned char g_museum_movability[TownConsts::MUSEUM_WIDTH * TownConsts::MUSEUM_HEIGHT] = {
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
	  0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
	  0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
	  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      0,   1,   1,   1,   1,   1,   1,   1,   0,   1,   1,   1,   0,   1,   1,   1,   1,   1,   1,   1,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
	};

unsigned short g_shops_tile_data[TownConsts::SHOPS_WIDTH * TownConsts::SHOPS_HEIGHT] = {
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0, 17, 29, 29, 18, 29, 29, 19,  0,
	 0, 20, 21, 21, 21, 21, 21, 22,  0,
	 0, 12, 23, 23,  5, 23, 23, 15,  0,
	 0,  0,  0,  0, 16,  0,  0,  0,  0,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0, 24, 29, 29, 25, 29, 26, 27,  0,
	 0, 20, 21, 21, 21, 21, 21, 22,  0,
	 0, 12, 13, 28,  5, 28, 13, 15,  0,
	 0,  0,  0,  0, 16,  0,  0,  0,  0,
	16, 16, 16, 16, 16, 16, 16, 16, 16
};

unsigned char g_shops_movability[TownConsts::SHOPS_WIDTH * TownConsts::SHOPS_HEIGHT] = {
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
	 0,  0,  0,  0,  1,  0,  0,  0,  0,
};
