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

//------------------------------------------------------------------------------
// Player::Player
//
// Constructor.  Initializes the player at (0, 0).
//
// Arguments:
//   None
//------------------------------------------------------------------------------
Player::Player(void) {
	x_pos = 0;
	y_pos = 0;
	gold = 0;
}

//------------------------------------------------------------------------------
// Player::Player
//
// Constructor.  Initializes the player at the specified location
//
// Arguments:
//   x, y - the position to place the player
//------------------------------------------------------------------------------
Player::Player(int x, int y) {
	x_pos = x;
	y_pos = y;
	gold = 0;
}

//------------------------------------------------------------------------------
// sets the player's position
//
// Arguments:
//   x, y - the player's new position
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_position(int x, int y) {
	x_pos = x;
	y_pos = y;
}

//------------------------------------------------------------------------------
// Gets the player's x position
// 
// Arguments:
//   None
//
// Returns:
//   The player's x position
//------------------------------------------------------------------------------
int Player::get_x_pos() {
	return x_pos;
}

//------------------------------------------------------------------------------
// Gets the player's y position
// 
// Arguments:
//   None
//
// Returns:
//   The player's y position
//------------------------------------------------------------------------------
int Player::get_y_pos() {
	return y_pos;
}

//------------------------------------------------------------------------------
// Sets the player's x position
// 
// Arguments:
//   pos - the position to set to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_x_pos(int pos) {
	x_pos = pos;
}

//------------------------------------------------------------------------------
// Sets the player's y position
// 
// Arguments:
//   pos - the position to set to
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::set_y_pos(int pos) {
	y_pos = pos;
}

//------------------------------------------------------------------------------
// Adds to the player's copper stash
// 
// Arguments:
//   amount - the amount to add
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Player::add_gold(int amount) {
	gold += amount;
}

//------------------------------------------------------------------------------
// Retreives the player's gold
// 
// Arguments:
//   None
//
// Returns:
//   Amount of gold the player has
//------------------------------------------------------------------------------
int Player::get_gold(void) {
	return gold;
}