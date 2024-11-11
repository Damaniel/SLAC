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
#ifndef __PLAYER_H__
#define __PLAYER_H__

//------------------------------------------------------------------------------
// Player class definition
//------------------------------------------------------------------------------
class Player {
private:
	int hp;					// The player's current HP
	int max_hp;				// The player's max HP
	int mp;					// The player's current MP
	int max_mp;				// The player's max HP
	int level;				// The player's current level 
	int exp;				// The player's current number of experience points
	int character_class;	// What characer class is the player
	int dungeon;			// What dungeon is the player in
	int dungeon_floor;		// What floor of the dungeon the player is in
	int last_room_entered;  // What room was the player last in?
	
public:
	int x_pos;				// They're constantly set and read, so we'll skip the setter/getter for now
	int y_pos;				// (The compiler is probably smart, but I can understand this, at least)
	
	Player();
	Player(int x, int y);
	int get_last_room_entered() { return last_room_entered; }
	void set_last_room_entered(int room) { last_room_entered = room; }
};

#endif