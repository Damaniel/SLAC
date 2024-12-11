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
#ifndef __MAZE_H__
#define __MAZE_H__

#include "globals.h"

namespace MazeConsts {
	// Directions used by the maze generator
	const int DIRECTION_NORTH = 0;
	const int DIRECTION_SOUTH = 1;
	const int DIRECTION_EAST = 2;
	const int DIRECTION_WEST = 3;

	// Square types used by the maze generator
	const int EMPTY = 0;
	const int PASSAGE = 1;
	const int WALL = 2;

	// The starting room ID, assigned to the first room
	const int STARTING_ROOM = 100;

	// Number of attempts made to add valid rooms to the maze
	const int ROOM_ATTEMPTS = 200;

	// Stair types for the stair generator
	const int NO_STAIRS = -1;
	const int STAIRS_UP = 0;
	const int STAIRS_DOWN = 1;
	const int NUM_STAIRS = 3;

	// The minimum and maximum size of maze that can be generated
	const int MIN_MAZE_WIDTH = 30;
	const int MIN_MAZE_HEIGHT = 30;
	const int MAX_MAZE_WIDTH = 64;
	const int MAX_MAZE_HEIGHT = 64;

	// Controls the generator's behavior regarding whether to render 
	// both kinds of stairs in the maze, or only one or the other.
	enum {
		GENERATE_BOTH_STAIRS,
		GENERATE_NO_UP_STAIRS,
		GENERATE_NO_DOWN_STAIRS,
		GENERATE_NO_STAIRS				// Not used 
	};
}

//------------------------------------------------------------------------------
// Stair struct definition
//
// Pretty much just the location of the stairs, the type (up or down), and the
// room that the stairs are in.  Stairs are always generated in rooms.
//------------------------------------------------------------------------------
struct Stair {
    int x;
	int y;
	int direction;
	int room_id;
	Stair(int x, int y, int direction, int roomId) : x(x), y(y), direction(direction), room_id(room_id) {}
};

//------------------------------------------------------------------------------
// WallLoc struct definition
//
// Used to track walls leading to rooms.  These walls can be opened, linking 
// rooms to passageways.
//------------------------------------------------------------------------------
struct WallLoc {
	int x;
	int y;
	int direction;
	WallLoc(int x, int y, int direction) : x(x), y(y), direction(direction) {}
};

//------------------------------------------------------------------------------
// Room struct definition
//
// Location and size of rooms - open areas with no internal passageways.
//
// Note: hasBeenEntered is used to mark a room as having been visited by the 
// player.  This information may be of use to the renderer.
//------------------------------------------------------------------------------
struct Room {
	int id;
	int x;
	int y;
	int w;
	int h;
	bool has_been_entered;
	Room(int id, int x, int y, int w, int h) : id(id), x(x), y(y), w(w), h(h) {
		has_been_entered = false;
	}
};

//------------------------------------------------------------------------------
// Square struct definition
//
// A square - that is, a grid location - in the maze.  It can be a wall or
// floor, and it can also be part of a passageway or room.
//------------------------------------------------------------------------------
struct Square {
	int tag;			// Contains the ID of the room it sits in, if any
	bool carved;		// Is the square solid or has it been carved
	bool is_lit;		// Is the square currently lit?
	bool was_seen;		// The player has previously seen/lit this location but may or may not be in it now
};

//------------------------------------------------------------------------------
// Maze class definition
//
// All of the information required to hold and generate a maze.  The maze 
// generator generates a perfect maze, adds rooms, and then removes
// unnecessary dead ends.
//------------------------------------------------------------------------------
class Maze {
private:
	std::vector<Square> m;
	std::vector<Room> rooms;
	std::vector<Stair> stairs;
	std::map <std::pair<int, int>, std::list<Item*> > items;
	int rows;
	int cols;
    int room_id;
	int ilevel;
	int stair_gen_behavior;
	bool globally_lit;

	void add_stairs(int num_up_stairs, int num_down_stairs);
	void carve(int x, int y, int tag);
	void carve_direction(int x, int y, int direction, int tag);	
	bool create_room(int x, int y, int w, int h);
	void generate_passages(int x, int y);
	void generate_rooms(int num_attempts, int min_size, int max_size);
	void generate_items(int min_items, int max_items);
	void get_directions(std::vector<int> & directions, int x, int y);
	void mark_walls(void);	
	void open_room(Room &r);
	void place_stairs(int room_id, int type);
	void remove_dead_ends(void); 	
	void uncarve(int x, int y);
	
public:
	Maze();
	Maze(int x, int y, int il);
	~Maze();
	void add_item(int x, int y, Item *i);
	std::list<Item *> get_items_at(int x, int y);
	void remove_item_from_end_at(int x, int y);
	int get_num_items_at(int x, int y);
	void change_lit_status_around(int x, int y, bool lit);	
	void change_lit_status_at(int x, int y, bool lit);
	void change_room_lit_status(int room, bool lit);
	void generate(void);
	int get_height(void) { return rows; }
	std::pair<int, int> get_random_stair(int direction);
	Room get_room(int room_id);	
	int get_room_id_at(int x, int y);
	Square get_square(int x, int y);
	int get_width(void) { return cols; }
	void init(void);
	bool is_carved(int x, int y);
	bool is_square_lit(int x, int y);
	void knock_out_walls(int chance);
	void print(void);
	void print_memory_usage(void); 
	void print_room_ids(void);
	void set_room_entered_state(int room_id, bool state);
	void set_stair_gen_behavior(int behavior) { stair_gen_behavior = behavior; }
	bool is_globally_lit() { return globally_lit; }
	void set_globally_lit_state(bool state) { globally_lit = state; }
	int stairs_here(int x, int y);
	bool was_seen(int x, int y);
	void mark_seen_state(int x, int y, int state);
};

#endif
