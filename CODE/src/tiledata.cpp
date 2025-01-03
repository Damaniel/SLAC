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

unsigned short g_town_tile_data[TOWN_SIZE * TOWN_SIZE] = {
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   1,   2,   2,   2,   2,   2,   3,   4,   5,   6,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   7,   0, 
	  0,   8,   9,  10,  10,  10,  11,  12,  13,  14,  15,  16,  17,  17,  17,  17,  17,  17,  18,  16,  17,  17,  17,  17,  17,  17,  18,  19,  20,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  22,  19,  19,  19,  23,   0, 
	  0,   8,  24,  25,  26,  25,  27,  12,  13,  14,  15,  28,  29,  29,  29,  30,  31,  32,  33,  28,  30,  31,  31,  34,  29,  29,  33,  19,  35,  36,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  38,  35,  19,  19,  39,  23,   0, 
	  0,   8,  24,  25,  40,  25,  24,  12,  13,  14,  15,  28,  32,  31,  31,  31,  31,  31,  33,  28,  41,  31,  31,  31,  41,  31,  33,  19,  35,  42,  43,  44,  43,  44,  43,  44,  43,  44,  43,  44,  43,  45,  35,  19,  46,  46,  23,   0, 
	  0,   8,  47,  10,  48,  10,  49,  12,  13,  14,  15,  28,  31,  31,  31,  50,  29,  29,  33,  28,  31,  34,  31,  31,  31,  31,  33,  19,  35,  51,  52,  43,  52,  43,  52,  43,  52,  43,  52,  43,  52,  53,  35,  19,  46,  46,  23,   0, 
	  0,  54,  55,  56,  57,  58,  55,  59,  13,  14,  15,  60,  17,  17,  61,  61,  17,  17,  62,  60,  17,  17,  61,  61,  17,  17,  62,  19,  63,  21,  21,  43,  21,  43,  21,  43,  21,  43,  21,  43,  21,  21,  64,  19,  46,  46,  23,   0, 
	  0,  65,  66,  66,  40,  66,  66,  66,  67,  14,  15,  19,  19,  68,  19,  19,  19,  19,  19,  69,  69,  69,  69,  69,  69,  69,  19,  19,  70,  71,  72,  73,  74,  73,  74,  73,  74,  73,  74,  73,  75,  76,  70,  19,  46,  46,  23,   0, 
	  0,  77,  78,  78,  40,  78,  78,  78,  78,  14,  15,  19,  19,  19,  19,  19,  19,  19,  79,  80,  81,  81,  81,  81,  81,  82,  83,  84,  70,  85,  73,  73,  73,  73,  73,  73,  73,  73,  73,  73,  73,  86,  70,  19,  46,  46,  23,   0, 
	  0,  87,  88,  89,  40,  13,  14,  90,  88,  88,  19,  19,  19,  19,  19,  19,  39,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  70,  94,  95,  95,  95,  95,  95,  95,  95,  95,  73,  95,  95,  96,  70,  19,  84,  19,  23,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  19,  19,  19,  39,  19,  19,  19,  19,  19,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  19,  97,  97,  97,  97,  97,  97,  97,  97,  98,  40,  99,  97,  97,  19,  19,  19,  19,  23,   0, 
	  0,   8, 100,  79,  40,  13,  14,  15,  19,  69,  69,  69,  69,  69,  69,  69,  19,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  19,  69,  69,  69,  69,  69,  69,  69,  19,  79,  40,  83,  19,  19,  19,  19,  19,  19,  23,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  79,  80,  81,  81,  81,  81,  81,  82,  83,  19,  79, 101, 102, 103, 104, 102, 102, 105,  83,  19,  79,  80,  81,  81,  81,  81,  81,  82,  39,  79,  40,  83,  19,  19,  20,  21,  21,  21, 106,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  19,  97,  97,  98,  40,  99,  97,  97, 107,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  79,  40,  83, 108,  19,  35,  70,  70,  70, 109,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  19, 110,  19,  79,  40,  83,  19,  39,  19,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  79,  40,  83,  19,  19,  35,  70, 111,  70, 109,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  79,  91,  92,  92,  92,  92,  92,  93,  83,  19,  19,  19,  69, 112,  40, 113,  69,  19,  19,  19,  79,  91,  92,  92,  92,  92,  92,  93,  83,  79,  40,  83,  19,  19,  35,  70,  40,  70, 109,   0, 
	  0,   8,  19,  79,  40,  13,  14,  15,  79, 101, 102, 114, 104, 102, 102, 105,  83,  19,  19,  79,  71, 115,  73, 115,  76,  83, 116,  19,  79, 101, 102, 117, 104, 102, 102, 105,  83,  79,  40,  83,  19,  19,  63,  21,  40,  21, 118,   0, 
	  0,   8,  19,  79,  40,  13,  14, 119,  69,  69,  69, 120,  40, 113,  69,  69,  69,  69,  69, 112, 121,  73,  73,  73,  86, 113,  69,  69,  69,  69,  69, 112,  40, 113,  69,  69,  69, 112,  40, 113,  69,  69,  69, 112,  40, 122,  23,   0, 
	  0,   8,  19,  79,  94, 123, 124, 123, 123, 115, 124, 123,  95, 123, 124, 124, 123, 124, 124, 124,  73,  73, 125,  73,  73, 124, 124, 124, 124, 123, 124, 124,  95, 124, 124, 123, 124, 124,  95, 124, 115, 123, 124, 124,  96,  83,  23,   0, 
	  0,   8,  39,  19, 126,  13,  14, 127,  98,  40,  99,   9,  10,  10,  10,  10,  10,  11,  97,  98, 121,  73,  73,  73,  86,  99,  97,   9,  10,  10,  10,  10,  10, 128,  10,  10,  10,  10,  10,  11,  40,  99,  97,  97,  97, 129,  23,   0, 
	  0,   8,  46,  46,  12,  13,  14,  15,  79,  40, 130,  24,  46,  80,  81,  82,  70,  27,  19,  79, 121,  73,  73,  73,  86, 131,  19,  27,  70,  80,  81,  82,  46,  27, 132,  80,  81,  82,  70,  27,  40,  83,  19,  19,  19,  19,  23,   0, 
	  0,   8,  46,  46,  12,  13,  14,  15,  79,  40, 130,  24,  46,  91,  92,  93,  10,  49, 133, 112, 134,  73, 135,  73,  86, 113,  69,  47,  10,  91,  92,  93,  46,  27, 132,  91,  92,  93,  10,  49,  40,  83,  25,  25,  25,  25,  23,   0, 
	  0,   8,  46,  46,  12,  13,  14,  15,  79,  40, 130,  24,  46,  91,  92,  93, 123, 124, 124, 124,  73,  73,  73,  73,  73, 124, 124, 124, 124,  91,  92,  93,  46,  27, 132,  91,  92,  93, 123, 124, 136,  83, 137, 138, 138, 139,  23,   0, 
	  0,   8,  46,  46,  12,  13,  14,  15,  79,  40, 130,  24,  46,  91,  92,  93,  10,  11,  97,  98, 121, 140,  73,  73,  86,  99,  97,   9,  10,  91,  92,  93,  30,  27, 132,  91,  92,  93,  10,  11,  40,  83, 141, 142, 142, 143,  23,   0, 
	  0,   8,  46,  46,  12,  13,  14,  15,  79,  40, 130,  24,  46, 101, 102, 105,  70,  27,  19,  79, 121,  73, 125,  73,  86,  83,  19,  27,  70,  91,  92,  93,  46,  27, 132,  91,  92,  93,  70,  27, 121, 123, 124, 144, 142, 143,  23,   0, 
	  0,   8,  19, 108,  12,  13,  14,  15,  79,  40, 130,  47,  10,  10,  10,  10,  10,  49,  19,  79, 121,  73,  73,  73,  86,  83,  19,  27,  70, 101, 102, 105,  46,  27, 132, 101, 102, 105,  70,  27,  40,  83, 141, 142, 142, 143,  23,   0, 
	  0,   8,  19,  19,  12,  13,  14,  15,  79,  40, 130,  19,  19,  19,  19,  19, 145,  19,  84,  79, 121,  73,  73,  73,  86,  83,  19,   9,  10,  10,  10,  10,  10, 146,  10,  10,  10,  10,  10, 147,  40,  83,  19,  19,  19,  25,  23,   0, 
	  0, 148, 148,  19,  12,  13,  14,  15,  79,  40, 130,   9,  10,  10,  10,  10,  10,  11,  19,  79, 121,  73,  73,  73,  86,  83,  19,  27,  70,  80,  81,  82, 149,  27, 150,  80,  81,  82,  70,  27,  40,  83, 151,  19,  19,  25,  23,   0, 
	  0, 152,  70, 153, 148,  13,  14,  15,  79,  40, 130,  24, 150,  80,  81,  82,  70,  27,  19,  79, 121,  73,  73,  73,  86,  83,  19,  27,  70,  91,  92,  93, 149,  27,  30,  91,  92,  93,  70,  27,  40,  83,  19,  19,  19,  25,  23,   0, 
	  0, 152,  70, 153, 148,  13,  14, 119, 112,  40, 130,  24, 150,  91,  92,  93,  10,  49,  69, 112, 121,  73,  73,  73,  86, 113,  69,  47,  10,  91,  92,  93, 154,  27, 150,  91,  92,  93,  10,  49,  40,  83, 137, 138, 138, 139,  23,   0, 
	  0,  80,  81,  82, 148,  13,  14,  71, 124,  96, 130,  24, 150,  91,  92,  93, 123, 124, 124, 124,  73,  73, 125,  73,  73, 124, 124, 124, 124,  91,  92,  93,  30,  27, 150,  91,  92,  93, 123, 124,  86,  83, 141, 142, 142, 143,  23,   0, 
	  0,  91,  92,  93, 148,  13,  14,  40,  99,  97,  19,  24, 150,  91,  92,  93,  10,  11, 155,  98, 121,  73,  73,  73,  86,  99, 156,   9,  10,  91,  92,  93, 154,  27, 150,  91,  92,  93,  10,  11, 121, 123, 124, 157, 142, 143,  23,   0, 
	  0,  91,  92,  93, 124, 123, 124,  86, 130,  19,  19,  24, 150, 101, 102, 105,  70,  27,  19,  79,  94,  95,  73,  95,  96,  83,  19,  27,  70, 101, 102, 105, 150,  27, 150, 101, 102, 105,  70,  27,  40,  83, 141, 142, 142, 143,  23,   0, 
	  0,  91,  92,  93, 148,  13,  14,  40, 130, 158,  19,  47,  10,  10,  10,  10,  10,  49,  19,  19,  97,  98,  40,  99,  97,  19, 108,  47,  10,  10,  10,  10,  10, 159,  10,  10,  10,  10,  10,  49,  40,  83,  25,  25,  25,  25,  23,   0, 
	  0, 101, 102, 105, 148,  13,  14,  40, 160,  55,  55,  55,  55,  55,  55,  55,  55,  55,  55,  19,  39,  79,  40, 130,  19,  19,  19,  19,  19,  19,  69,  69,  69,  69,  69,  69,  69,  69,  69, 112,  40,  83,  19,  19,  19,  19,  23,   0, 
	  0,   4,  66,  66,  66,  67,  78,  40,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,   5,  15,  19,  79,  40, 130, 161, 162, 162, 163, 164,  79,  71, 124, 124, 124, 123, 124, 124, 124, 124, 123,  86, 113,  69,  69,  69,  69, 165,   0, 
	  0,  13,  78,  78,  78,  78,  78,  40,  78,  78,  78,  78,  78,  78,  78,  78,  78,  78,  14,  15,  19,  79,  40, 130, 166, 167, 167, 168, 169,  79,  40,  99,  97,  97,  97,  97,  97,  97,  97,  98,  40, 170, 170, 170, 170, 170, 170,   0, 
	  0, 171, 171, 171, 171, 171, 171,  40, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13,  14,  15,  19, 172,  40, 130, 173, 174, 174, 174, 175,  79,  40, 130, 176, 176, 176, 176,  19,  69,  69, 177,  40, 170, 178, 178, 178, 178, 178,   0, 
	  0, 171, 171, 171, 171, 171, 171,  40, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13,  14,  15,  84, 179,  40, 113,  69,  69,  69, 180,  69, 112,  40, 130, 176, 176, 176,  19, 112, 170, 170, 170, 181, 178, 182, 183, 183, 183, 184,   0, 
	  0, 185, 186, 186, 186, 186, 186, 187, 186, 186, 186, 186, 186, 188, 171, 171, 171,  13,  14,  15,  19, 179,  94, 124, 124, 124, 124, 124, 124, 124,  96, 130, 176, 176, 176,  79, 170, 178, 178, 178, 189, 178, 190, 191, 191, 192, 192,   0, 
	  0, 193, 194, 195, 196, 195, 197, 195, 198, 199, 200, 195, 201, 202, 171, 171, 171,  13,  14, 203,  55, 204, 205, 205, 205,  97,  97,  97,  97,  97,  97,  19, 176, 176, 176,  79, 170, 178, 182, 183, 189, 183, 206, 207, 208, 208, 209,   0, 
	  0, 193, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 202, 171, 171, 171,  13, 210,  66,  66,  66,  66,  66,   5,  15, 176, 176, 176, 176, 176, 176, 176, 176, 176,  79, 170, 178, 190, 192, 189, 207, 208, 211, 212, 213, 214,   0, 
	  0, 215, 216, 195, 217, 195, 218, 195, 219, 195, 196, 195, 220, 202, 171, 171, 171,  13,  78,  78,  78,  78,  78,  78,  14,  15, 176, 176, 176, 176, 176, 176, 176, 176, 176,  79, 170, 178, 190, 192, 189, 221, 222, 222, 222, 223, 214,   0, 
	  0, 224, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 202, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13,  14,  15, 176, 176, 176, 176, 176, 176, 176, 176, 176,  79, 170, 178, 190, 192, 225, 226, 226, 226, 227, 228, 214,   0, 
	  0, 224, 196, 195, 201, 195, 217, 195, 216, 195, 197, 195, 229, 202, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13,  14, 203,  55,  55,  55,  55,  55,  19, 176, 176, 176,  79, 170, 178, 190, 192, 207, 208, 230, 230, 230, 223, 214,   0, 
	  0, 224, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 202, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13, 210,  66,  66,  66,  66,  66,   5,  15, 176, 176, 176,  79, 170, 178, 190, 192, 231, 212, 213, 213, 213, 213, 214,   0, 
	  0, 232, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 233, 171, 171, 171, 171, 171, 171, 171, 171, 171,  13,  78,  78,  78,  78,  78,  78,  14, 234, 235, 235, 235, 236, 170, 178, 190, 192, 221, 237, 237, 237, 237, 237, 238,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

unsigned char g_town_movability[TOWN_SIZE * TOWN_SIZE] = {
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
