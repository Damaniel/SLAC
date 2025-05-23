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

//------------------------------------------------------------------------------
// Maze::Maze
//
// Constructor.
//------------------------------------------------------------------------------
Maze::Maze() {

}

//------------------------------------------------------------------------------
// Maze::Maze
//
// Constructor.  Generates a maze of size (x,y).
//
// Arguments:
//   x - the width of the maze
//   y - the height of the maze
//------------------------------------------------------------------------------
Maze::Maze(int x, int y, int il) {
	if (x < MazeConsts::MIN_MAZE_WIDTH) x = MazeConsts::MIN_MAZE_WIDTH;
	if (y < MazeConsts::MIN_MAZE_HEIGHT) y = MazeConsts::MIN_MAZE_HEIGHT;
	if (x > MazeConsts::MAX_MAZE_WIDTH) x = MazeConsts::MAX_MAZE_WIDTH;
	if (y > MazeConsts::MAX_MAZE_HEIGHT) y = MazeConsts::MAX_MAZE_HEIGHT;

	/* If the maze is of even size, add an additional row/column to ensure
	 * a border surrounds the entire maze. */
	rows = y % 2 == 0 ? y + 1 : y;
	cols = x % 2 == 0 ? x + 1 : x;

	ilevel = il;

	stair_gen_behavior = MazeConsts::GENERATE_BOTH_STAIRS;

	init();
}

//------------------------------------------------------------------------------
// Adds stairs (both up and down) randomly to the maze
//
// Arguments:
//   numUpStairs - the number of up stairs to generate
//   numDownStairs - the number of down stairs to generate
//
// Returns:
//   None
//
// Notes:
//   Stairs only spawn in rooms; one maximum per room.  All spaces surrounding
//   the stairs must either be part of a room, or the walls of a room.
//------------------------------------------------------------------------------
void Maze::add_stairs(int num_up_stairs, int num_down_stairs) {
	int num_rooms = room_id - MazeConsts::STARTING_ROOM - 1;
	int up_stairs, down_stairs;

	//  We need at least 2 rooms.  Bail if we don't even have that.
	if (num_rooms < 2) {
		std::cout << "not enough rooms, period!" << std::endl;
		return;
	}

	// If we don't have enough rooms to meet the requirement, split the
	// room total in half (rounded down), then set num_up_stairs and
	// num_down_stairs to that total
	if (num_rooms < num_up_stairs + num_down_stairs) {
		int stair_target = num_rooms / 2;
		up_stairs = stair_target;
		down_stairs = stair_target;
	}
	else {
		up_stairs = num_up_stairs;
		down_stairs = num_down_stairs;
	}

	std::vector<int> selected_rooms;
	std::vector<int>::iterator room_it;

	// Iterate through up stairs
	if (stair_gen_behavior == MazeConsts::GENERATE_BOTH_STAIRS || stair_gen_behavior == MazeConsts::GENERATE_NO_DOWN_STAIRS) {
		for (int i=0; i < up_stairs; i++) {
			bool valid;
			int candidate_room;
			// Pick a random room and check to see if there's already stairs in it
			do {
				valid = true;
				candidate_room = rand() % num_rooms + MazeConsts::STARTING_ROOM;
				for(std::vector<int>::iterator it = selected_rooms.begin(); it != selected_rooms.end(); it++) {
					if (*it == candidate_room) {
						valid = false;
					}
				}
			}
			while (valid == false);

			// When a candidate room is found, create the stairs there.
			place_stairs(candidate_room, MazeConsts::STAIRS_UP);
			selected_rooms.push_back(candidate_room);
		}
	}

	if (stair_gen_behavior == MazeConsts::GENERATE_BOTH_STAIRS || stair_gen_behavior == MazeConsts::GENERATE_NO_UP_STAIRS) {
		// Repeat the same process for down stairs
		for (int i=0; i < down_stairs; i++) {
			bool valid;
			int candidate_room;
			do {
				valid = true;
				candidate_room = rand() % num_rooms + MazeConsts::STARTING_ROOM;
				for(std::vector<int>::iterator it = selected_rooms.begin(); it != selected_rooms.end(); it++) {
					if (*it == candidate_room) {
						valid = false;
					}
				}
			}
			while (valid == false);
			place_stairs(candidate_room, MazeConsts::STAIRS_DOWN);
			selected_rooms.push_back(candidate_room);
		}
	}
}

//------------------------------------------------------------------------------
// Carves a square out of the maze.
//
// Arguments:
//   x - the x location to carve
//   y - the y location to carve
//   tag - what the carved square is (PASSAGE or ROOM)
//
// Returns:
//   Nothing
//
// Notes:
//   A 'carved' square can either be a passageway, or part of a room.
//------------------------------------------------------------------------------
void Maze::carve(int x, int y, int tag) {
	m[y*cols + x].tag = tag;
	m[y*cols + x].carved = true;
}

//------------------------------------------------------------------------------
// Carves the maze in a particular direction.
//
// Arguments:
//   x - the x position to carve from
//   y - the y position to carve from
//   direction - the direction to carve (DIRECTION_NORTH, DIRECTION_SOUTH, etc.)
//
// Returns:
//   Nothing
//
// Notes:
//   Due to the way that mazes are stored, carving in a direction requires
//   carving three squares - the source square, the target square, and the
//   square between them.
//------------------------------------------------------------------------------
void Maze::carve_direction(int x, int y, int direction, int tag) {
	if (direction == MazeConsts::DIRECTION_NORTH) {
		carve(x, y, tag);
		carve(x, y-1, tag);
		carve(x, y-2, tag);
	}
	if (direction == MazeConsts::DIRECTION_SOUTH) {
		carve(x, y, tag);
		carve(x, y+1, tag);
		carve(x, y+2, tag);
	}
	if (direction == MazeConsts::DIRECTION_EAST) {
		carve(x, y, tag);
		carve(x+1, y, tag);
		carve(x+2, y, tag);
	}
	if (direction == MazeConsts::DIRECTION_WEST) {
		carve(x, y, tag);
		carve(x-1, y, tag);
		carve(x-2, y, tag);
	}
}

//------------------------------------------------------------------------------
// Updates the 'lit' status of a square (and marks it as visited)
//
// Arguments:
//	 x - the x location of the square to change status of
//	 y - the y location of the square to change status of
//   lit - should the square be marked as lit or unlit?
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::change_lit_status_at(int x, int y, bool lit) {
	m[y * cols + x].is_lit = lit;
	mark_seen_state(x, y, true);
}

//------------------------------------------------------------------------------
// Attempts to create a room in the maze, according to a specific set of
// criteria.
//
// Arguments:
//   x, y - the upper left corner of the candidate room
//   w, h - the width and height of the candidate room
//
// Returns:
//   true if the room was created, false if it wasn't.
//------------------------------------------------------------------------------
bool Maze::create_room(int x, int y, int w, int h) {
	// Notes:
	//	 To fit in the maze, the room must:
	//		- be odd in height and width
	//		- be offset by an odd amount
	//		- fully fit within the bounds of the maze, leaving at least one
	//        uncarved square on each side of the maze area
	//      - not intersect with any existing room
	//	 If any of these aren't true, the room won't be created.

	// The room must be odd in width and height
	if (w % 2 == 0 || h % 2 == 0) {
		return false;
	}

	// The room must be offset by an odd amount
	if (x % 2 == 0 || y % 2 == 0) {
		return false;
	}

	// The room can't be pressed against any edge of the maze (it makes
	// generation of passages more consistent)
	if (x <3 || y < 3 || (x + w) > (cols - 3) || (y + h) > (rows - 3)) {
		return false;
	}

	// Check for overlap with existing rooms.  If there is any, don't
	// make the room.
	for (int i = x; i < x+w; i++ ) {
		for (int j = y; j < y+h; j++ ) {
			if (m[j*cols + i].tag >= MazeConsts::STARTING_ROOM) {
				return false;
			}
		}
	}

	// Since all the previous critera were met, go ahead and carve the new room.
	for (int i = x; i < x+w; i++ ){
		for (int j = y; j < y+h; j++ ){
			carve(i, j, room_id);
		}
	}

	// Save the room information for later edge detection and wall removal
	rooms.push_back(Room(room_id, x, y, w, h));
	room_id++;

	return true;
}

//------------------------------------------------------------------------------
// Creates passageways in any uncarved non-room space using a standard maze
// generation algorithm.
//
// Arguments:
//   x, y - the location to start carving from
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::generate_passages(int x, int y) {
	// Notes:
	//   Uses a recursive backtracker to generate a maze.  It starts by carving a
	//   maze as greedily as possible, until there are no adjacent squares to carve
	//   to.  Then, the maze is systematically scanned over, and any uncarved spaces
	//   that are adjacent to carved ones will be attached to one of the adjacent
	//   carved spaces.  The result is that every space in the maze should be
	//   connected.

	int cur_x = x;
	int cur_y = y;
	int direction;
	bool done = false;
	std::vector<int> directions;
	std::stack< std::pair<int, int> > visited;

	while (!done) {
		std::pair<int, int> cur = std::make_pair(cur_x, cur_y);

		// Find uncarved adjacent spaces to the current one
		get_directions(directions, cur_x, cur_y);
		// If there aren't any, look to see if we have any others to look at
		// on the stack
		if (directions.size() == 0) {
			// If not, everything has been carved
			if (visited.size() == 0) {
				done = true;
			}
			else {
				// Otherwise, pull one off the top of the stack and start
				// carving from there
				std::pair<int, int> top = visited.top();
				visited.pop();
				cur_x = top.first;
				cur_y = top.second;
			}
		}
		else {
			// If we found at least one adjacent uncarved space, pick one
			// and carve in that direction.
			visited.push(cur);
			direction = directions[rand() % directions.size()];
			if (direction == MazeConsts::DIRECTION_NORTH) {
				carve_direction(cur_x, cur_y, MazeConsts::DIRECTION_NORTH, MazeConsts::PASSAGE);
				cur_y = cur_y - 2;
			}
			else if (direction == MazeConsts::DIRECTION_SOUTH) {
				carve_direction(cur_x, cur_y, MazeConsts::DIRECTION_SOUTH, MazeConsts::PASSAGE);
				cur_y = cur_y + 2;
			}
			else if (direction == MazeConsts::DIRECTION_EAST) {
				carve_direction(cur_x, cur_y, MazeConsts::DIRECTION_EAST, MazeConsts::PASSAGE);
				cur_x = cur_x + 2;
			}
			else if (direction == MazeConsts::DIRECTION_WEST ) {
				carve_direction(cur_x, cur_y, MazeConsts::DIRECTION_WEST, MazeConsts::PASSAGE);
				cur_x = cur_x - 2;
			}
			directions.clear();
		}
	}
}

//------------------------------------------------------------------------------
// Creates candidate rooms and attempts to add them to the maze
//
// Arguments:
//   num_attempts - the number of times a room creation attempt will happen
//   min_size     - the smallest size of the width or height of a room
//   max_size     - the largest size of the width or height of a room
//------------------------------------------------------------------------------
void Maze::generate_rooms(int num_attempts, int min_size, int max_size) {
	// Notes:
	//   Since rooms need to have odd width and height, this method will ensure that
	//   any candidate rooms it creates will have this property.

	for (int i = 0; i < num_attempts; i++) {
		int x = rand() % cols;
		x = (x % 2 == 1) ? x : x + 1;
		int y = rand() % rows;
		y = (y % 2 == 1) ? y : y + 1;
		int w = rand() % (max_size-min_size) + min_size;
		w = (w % 2 == 1) ? w : w + 1;
		int h = rand() % (max_size-min_size) + min_size;
		h = (h % 2 == 1) ? h : h + 1;
		create_room(x, y, w, h);
	}
}

//------------------------------------------------------------------------------
// Given a square, returns a list of directions that contain an adjacent
// uncarved square.
//
// Arguments:
//   directions - a reference to a vector that will hold directions
//   x, y - the position to determine directions from
//
// Returns
//   Nothing.  Results are placed in the directions vector.
//------------------------------------------------------------------------------
void Maze::get_directions(std::vector<int> & directions, int x, int y) {
	// Notes:
	//   Used for maze generation, which requires such a list.

	if (x >= 3 && !is_carved(x-2 , y)) {
		directions.push_back(MazeConsts::DIRECTION_WEST);
	}
	if (x <= cols - 3 && !is_carved(x+2, y)) {
		directions.push_back(MazeConsts::DIRECTION_EAST);
	}
	if (y >= 3 && !is_carved(x, y-2)) {
		directions.push_back(MazeConsts::DIRECTION_NORTH);
	}
	if (y <= rows -3 && !is_carved(x, y+2)) {
		directions.push_back(MazeConsts::DIRECTION_SOUTH);
	}
}

//------------------------------------------------------------------------------
// Find 'walls' in the maze and mark them as such.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::mark_walls(void) {
	// Notes:
	//   Walls are found by finding uncarved spaces and checking to see what's
	//   around them.  If any adjacent space is carved (either as a passageway
	//   or as part of a room), the uncarved space is marked as a wall.
	//   Uncarved spaces surrounded by other uncarved spaces on all sides are
	//   uncarved, but are not walls.  Walls can be torn down to connect passageways
	//   to other passageways or to rooms, but uncarved squares that aren't walls
	//   (i.e. are embedded in unreachable areas of the maze) can't be.
	for (int x = 0; x < cols; x++ ) {
		for (int y = 0; y < rows; y++ ) {
			// Is the square uncarved?
			if (m[y*cols + x].tag == MazeConsts::EMPTY) {
				// Check the spot above and to the left of the current square
				if (y>0 && x>0 && (m[(y-1)*cols+(x-1)].tag == MazeConsts::PASSAGE || m[(y-1)*cols+(x-1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot directly above the current square
				else if (y>0 && (m[(y-1)*cols + x].tag == MazeConsts::PASSAGE || m[(y-1)*cols + x].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot above and to the right of the current square
				else if (y>0 && x<(cols-1) && (m[(y-1)*cols +(x+1)].tag == MazeConsts::PASSAGE || m[(y-1)*cols +(x+1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot to the left of the current square
				else if (x>0 && (m[y*cols + (x-1)].tag == MazeConsts::PASSAGE || m[y*cols + (x-1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot to the right of the current square
				else if (x<(cols-1) && (m[y*cols + (x+1)].tag == MazeConsts::PASSAGE || m[y*cols + (x+1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot below and to the left of the current square
				else if (y<(rows-1) && x>0 && (m[(y+1)*cols+(x-1)].tag == MazeConsts::PASSAGE || m[(y+1)*cols+(x-1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot directly below the current square
				else if (y<(rows-1) && (m[(y+1)*cols + x].tag == MazeConsts::PASSAGE || m[(y+1)*cols + x].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
				// Check the spot below and to the right of the current square
				else if (y<(rows-1) && x<(cols-1) && (m[(y+1)*cols +(x+1)].tag == MazeConsts::PASSAGE || m[(y+1)*cols +(x+1)].tag >= MazeConsts::STARTING_ROOM)) {
					m[y*cols + x].tag = MazeConsts::WALL;
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
// Connects a room to an adjacent passage by tearing down a wall between the
// two.
//
// Arguments:
//   r - the room to be opened
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::open_room(Room &r) {
	// Notes:
	//   Finds all edges that could connect a room to a passage.  Picks one to
	//   open, then iterates through the rest and randomly picks a tiny number
	//   of them to also open.
	std::vector<WallLoc> edges;

	// Check all north and south walls to see if the adjacent spaces are passageways
	for (int i = r.x; i < r.x + r.w; i+=2 ) {
		// Check the spot north of the top edge
		if (m[(r.y - 2) * cols + i].tag == MazeConsts::PASSAGE) {
			edges.push_back(WallLoc(i, r.y, MazeConsts::DIRECTION_NORTH));
		}
		// Check the spot south of the bottom edge
		if (m[(r.y + r.h + 1) * cols + i].tag == MazeConsts::PASSAGE) {
			edges.push_back(WallLoc(i, r.y+r.h-1, MazeConsts::DIRECTION_SOUTH));
		}
	}

	// Check all east and west walls to see if the adjacent spaces are passageways
	for (int i = r.y; i < r.y + r.h; i+=2) {
		if (m[i*cols + (r.x - 2)].tag == MazeConsts::PASSAGE) {
			edges.push_back(WallLoc(r.x, i, MazeConsts::DIRECTION_WEST));

		}
		if (m[i*cols + (r.x + r.w  + 1)].tag == MazeConsts::PASSAGE) {
			edges.push_back(WallLoc(r.x+r.w-1, i, MazeConsts::DIRECTION_EAST));
		}
	}

	if(edges.size() > 0) {
		// Pick a random edge from the list and carve it.
		int to_carve = rand() % edges.size();
		carve_direction(edges[to_carve].x, edges[to_carve].y, edges[to_carve].direction, MazeConsts::PASSAGE);
		// Re-mark the original source square as part of the room (since carve_direction will mark it
		// as passageway)
		m[edges[to_carve].y * cols + edges[to_carve].x].tag = r.id;

		edges.erase(edges.begin() + to_carve);
		// Now iterate through all edges and remove them with small (2%) probability
		for (int i=0 ; i<edges.size(); i++) {
			if (rand() % 1000 < 20) {
				carve_direction(edges[i].x, edges[i].y, edges[i].direction, MazeConsts::PASSAGE);
				// Re-mark the original source square as part of the room (since carve_direction will mark it
				// as passageway)
				m[edges[i].y * cols + edges[i].x].tag = r.id;
			}
		}
	}
}

//------------------------------------------------------------------------------
// Place a set of stairs somewhere in the specified room.
//
// Arguments:
//   room_id - the ID of the room in which to place the stairs
//   type    - the kind of stairs to add (up or down)
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::place_stairs(int room_id, int type) {
	// Notes:
	//   Randomly picks spots in the room, and continues to do so until a valid
	//   placement is made.  'Valid' means all surrounding spaces are either room
	//   spaces or walls, and the space isn't already occupied by stairs.
	int x, y;
	bool valid = false;
	Room r = get_room(room_id);

	do {
		// Pick a random spot in the room
		x = (rand() % r.w) + r.x;
		y = (rand() % r.h) + r.y;
		// Is the space to the right a wall or room space?
		if (m[y*cols + x + 1].tag == room_id || !is_carved(x+1, y)) {
			// Is the space to the left a wall or a room space?
			if(m[y*cols +x -1].tag == room_id || !is_carved(x-1, y)) {
				// Is the space below a wall or a room space?
				if(m[(y+1)*cols+x].tag == room_id || !is_carved(x, y+1)) {
					// Is the space above a wall or room space?
					if(m[(y-1)*cols+x].tag == room_id || !is_carved(x, y-1)) {
						// If so, good.  Now see if there's already stairs in this location
						valid = true;
						for(std::vector<Stair>::iterator it = stairs.begin(); it != stairs.end(); it++) {
							// If there is, start over
							if (it->x == x && it->y == y) {
								valid = false;
							}
						}
					}
				}
			}
		}
	}
	while (valid == false);

	stairs.push_back(Stair(x, y, type, room_id));
}

//------------------------------------------------------------------------------
// Finds and removes all dead ends (squares carved in only 1 direction) from the
// maze
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::remove_dead_ends(void) {
	// Notes:
	//   This might be a slow process due to all the looping.  The general steps
	//   are:
	//
	//   do:
	//     - Set number of dead ends filled in to 0
	//     - Scan over the maze, going by 2s
	//     - If not in a room:
	//       - Count adjacent walls
	//       - If adjacent wall count = 3
	//         - Uncarve the current space and the adjacent non-wall space
	//         - Increment number of dead ends filled in by 1
	//   While dead ends filled in !=0

	int num_dead_ends;
	bool carved[4];
	int num_carved;

	do {
		num_dead_ends = 0;
		for(int y = 1; y < rows - 1; y += 2) {
			for (int x = 1; x < cols - 1; x += 2) {
				num_carved = 0;
				carved[0] = false;
				carved[1] = false;
				carved[2] = false;
				carved[3] = false;
				if(m[y*cols + x].tag == MazeConsts::PASSAGE && m[y*cols + x].carved == true) {
					if(m[y*cols +x -1].carved == true) {
						carved[MazeConsts::DIRECTION_WEST] = true;
						num_carved++;
					}
					if(m[y*cols + x + 1].carved == true) {
						carved[MazeConsts::DIRECTION_EAST] = true;
						num_carved++;
					}
					if(m[(y+1)*cols + x].carved == true) {
						carved[MazeConsts::DIRECTION_SOUTH] = true;
						num_carved++;
					}
					if(m[(y-1)*cols + x].carved == true) {
						carved[MazeConsts::DIRECTION_NORTH] = true;
						num_carved++;
					}
					if(num_carved == 1) {
						if(carved[MazeConsts::DIRECTION_NORTH] == true) {
							uncarve(x, y);
							uncarve(x, y-1);
						}
						else if(carved[MazeConsts::DIRECTION_SOUTH] == true) {
							uncarve(x, y);
							uncarve(x, y+1);
						}
						else if(carved[MazeConsts::DIRECTION_EAST] == true) {
							uncarve(x, y);
							uncarve(x+1, y);
						}
						else if(carved[MazeConsts::DIRECTION_WEST] == true) {
							uncarve(x, y);
							uncarve(x-1, y);
						}
						num_dead_ends++;
					}
				}
			}
		}
	}
	while(num_dead_ends != 0);
}

//------------------------------------------------------------------------------
// Randomly carves out walls from a finished maze.
//
// Arguments:
//   chance - the chance (0-1000) a wall will be removed, where 1000 = 100%
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::knock_out_walls(int chance) {
	// Notes:
	//   Used to open up some of the longer passages a little more.  The 'chance'
	//   value should fall between 0 (don't knock out any walls) to 1000 (destroy
	//   every wall) - the value of chance corresponds to a chance/1000 odds that
	//   a particular wall will be destroyed.

	int val;

	// Don't carve the outermost rows/columns of the maze
	for (int y = 1; y < rows-1; y++) {
		for (int x = 1; x < cols-1; x++) {
			val = rand() % 1000;
			if (is_carved(x,y) == false && val < chance) {
				// Only carve if the space on each side of the wall is open,
				// making sure the opening actually opens a space between
				// adjacent passages
				if ((is_carved(x-1, y) == true && is_carved(x+1, y) == true) ||
					(is_carved(x, y-1) == true && is_carved(x, y+1) == true)) {
					carve(x,y, MazeConsts::PASSAGE);
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
// Puts back a previously carved square.
//
// Arguments:
//   x, y - the coordinates of the location to uncarve
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::uncarve(int x, int y) {
	m[y*cols + x].tag = MazeConsts::EMPTY;
	m[y*cols + x].carved = false;
}

//------------------------------------------------------------------------------
// Changes the light state of the maze square at (x,y), and each square adjacent
// to it.
//
// Arguments:
//   x, y - the location to change the light state
//   lit  - the light state to change to (true = on, false = off)
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::change_lit_status_around(int x, int y, bool lit) {
	// Adjust the 3x3 space around the player
	change_lit_status_at(x-1, y-1, lit);
	change_lit_status_at(x  , y-1, lit);
	change_lit_status_at(x+1, y-1, lit);
	change_lit_status_at(x-1,   y, lit);
	change_lit_status_at(x  ,   y, lit);
	change_lit_status_at(x+1,   y, lit);
	change_lit_status_at(x-1, y+1, lit);
	change_lit_status_at(x  , y+1, lit);
	change_lit_status_at(x+1, y+1, lit);

	// Adjust one additional square in each cardinal direction, as long
	// as the square adjacent to the player in that direction is not a wall
	if (is_carved(x-1, y) && (x-2) >= 0)
		change_lit_status_at(x-2, y, lit);
	if (is_carved(x+1, y) && (x+2) < get_width())
		change_lit_status_at(x+2, y, lit);
	if (is_carved(x, y-1) && (y-2) >= 0)
		change_lit_status_at(x, y-2, lit);
	if (is_carved(x, y+1) && (y+2) < get_height())
		change_lit_status_at(x, y+2, lit);


}

//------------------------------------------------------------------------------
// Marks every square in a room as lit or unlit.  This also marks the room
// as visited, to enable fog of war.
//
// Arguments:
//   room_id  - the room to light (or unlight)
//   lit      - should the room be lit (true), or unlit (false)?
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::change_room_lit_status(int room_id, bool lit) {
	int room_offset = room_id - MazeConsts::STARTING_ROOM;
	Room r = rooms[room_offset];

	for(int i=r.x-1; i < r.x + r.w + 1; i++) {
		for (int j = r.y-1; j < r.y + r.h + 1; j++) {
			change_lit_status_at(i, j, lit);
			if(lit == true) {
				mark_seen_state(i, j, true);
			}
		}
	}
}

//------------------------------------------------------------------------------
// Marks a square of the maze as seen or unseen
//
// Arguments:
//	 x, y - the square to mark
//   state - true for seen, false for unseen
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::mark_seen_state(int x, int y, int state) {
	m[y * cols + x].was_seen = state;
}

//------------------------------------------------------------------------------
// The primary maze generator.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::generate(void) {
	// Notes:
	//   Generating a maze includes the following steps:
	//     - Placing rooms
	//     - Filling in the remaining space with passages
	//     - Removing dead ends so that every passageway eventually gets to a room.
	//     - Opening walls between rooms and passageways.  At least one passageway
	//       will be opened for every room, but some will open more
	//     - Placing stairs in rooms

	// Create rooms with widths and heights between 4 and 10 squares
	generate_rooms(MazeConsts::ROOM_ATTEMPTS, 4, 10);
	// Fill in the remaining space with passages
	generate_passages(1, 1);

	// Open at least one connection between each room and a passage
	for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		open_room((*it));
	}

	// Clean up the maze and add stairs
	remove_dead_ends();
	mark_walls();

	add_stairs(MazeConsts::NUM_STAIRS, MazeConsts::NUM_STAIRS);

	// Generate a few monsters in the maze

	// Attempt to remove some additional walls to open things up
	knock_out_walls(100);

	//std::cout << "maze_generator: finished generating" << std::endl;
}

//------------------------------------------------------------------------------
// Finds and returns the coordinates of a random up or down stair.
//
// Arguments:
//   direction - should the coordinates be for an up stair or down stair?
//
// Returns:
//   A pair containing the location of the requested stair
//------------------------------------------------------------------------------
std::pair<int, int> Maze::get_random_stair(int direction) {
	// Notes:
	//   Used to position the player when entering a new maze.  Players always
	//   spawn on a set of stairs.
	int idx;

	// The vector contains an equal number of up and down stairs.  Just pick
	// them at random until we find one that goes the correct direction.
	while(1) {
		idx = rand() % stairs.size();
		Stair s = stairs[idx];
		if (s.direction == direction) {
			std::pair<int, int> p = std::make_pair(s.x, s.y);
			return p;
		}
	}
}

//------------------------------------------------------------------------------
// Returns the Room specified by the room id.
//
// Arguments:
//	 room_id - the ID of the room to return
//
// Returns:
//   The room data.
//------------------------------------------------------------------------------
Room Maze::get_room(int room_id) {
	for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		if (it->id == room_id) {
			return *it;
		}
	}

	// Just return the last room for now.  Should throw something.
	std::cout << "Warning - room not found!" << std::endl;
	return rooms[rooms.size()-1];
}

//------------------------------------------------------------------------------
// Returns the room id associated with a particular location in the maze.
//
// Arguments:
//   x, y - the location in the maze
//
// Returns:
//   The id of the room corresponding to the location, or -1 if not a room
//------------------------------------------------------------------------------
int Maze::get_room_id_at(int x, int y) {
	int room = m[y * cols + x].tag;
	if(room < MazeConsts::STARTING_ROOM) {
		return -1;
	}
	else {
		return room;
	}
}

//------------------------------------------------------------------------------
// Returns the square at the specified location
//
// Arguments:
//   x, y - the coordinates of the square to retreive
//
// Returns:
//   The Square at the specified location
//------------------------------------------------------------------------------
Square Maze::get_square(int x, int y) {
	return m[y*cols+x];
}

//------------------------------------------------------------------------------
// Initializes a maze structure, setting the status of each square and room.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::init(void) {
	room_id = MazeConsts::STARTING_ROOM;
	for (int i = 0; i < rows * cols; ++i) {
		Square s;
		s.tag = MazeConsts::EMPTY;
		s.carved = false;
		s.is_lit = false;
		s.was_seen = false;
		m.push_back(s);
	}

	// Clear out the room and stair vectors
	rooms.clear();
	stairs.clear();
}

//------------------------------------------------------------------------------
// Determines whether a square at a particular location is carved or not.
//
// Arguments:
//   x, y - the coordinates of the location to check
//
// Returns:
//   true if the location is carved, false otherwise
//------------------------------------------------------------------------------
bool Maze::is_carved(int x, int y) {
	return m[y*cols + x].carved;
}

//------------------------------------------------------------------------------
// Determines whether a square is currently lit or not.
//
// Arguments:
//   x, y - the coordinates of the location to check
//
// Returns:
//   true if the square is lit, false if not
//------------------------------------------------------------------------------
bool Maze::is_square_lit(int x, int y) {
	return m[y*cols + x].is_lit;
}

//------------------------------------------------------------------------------
// Debug - prints out a ASCII representation of the maze.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::print(void) {
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			if (m[y*cols + x].carved) {
				std::cout << " ";
			}
			else {
				std::cout << (char)219;
			}
		}
		std::cout << std::endl;
	}

	for (std::vector<Stair>::iterator it = stairs.begin(); it != stairs.end(); it++) {
		std::cout << (it->direction == MazeConsts::STAIRS_UP ? "Up " : "Down ");
		std::cout << "stairs at (" << it->x << ", " << it->y << ")" << std::endl;
	}
}

//------------------------------------------------------------------------------
// Debug - returns the total size used by a maze object.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::print_memory_usage(void) {
	std::cout << "Memory usage:" << std::endl;
	std::cout << "Size of maze class: " << sizeof(Maze) << " bytes" << std::endl;
	std::cout << "Size of square vector: " << m.size() * sizeof(Square) << " bytes" << std::endl;
	std::cout << "Size of room vector: " << rooms.size() * sizeof(Room) << " bytes" << std::endl;
	std::cout << "Size of stairs vector: " << stairs.size() * sizeof(Stair) << " bytes" << std::endl;
}

//------------------------------------------------------------------------------
// Debug - lists the ids of all rooms in a maze.
//
// Arguments:
//   None
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::print_room_ids(void) {
	for(std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); it++) {
		std::cout << "Room id is " << it->id << std::endl;
	}
}

//------------------------------------------------------------------------------
// Flags an entire room as having been entered or not
//
// Arguments:
//   room_id - the room to mark
//   state - true if entered, false otherwise
//
// Returns:
//   Nothing
//------------------------------------------------------------------------------
void Maze::set_room_entered_state(int room_id, bool state) {
	rooms[room_id - MazeConsts::STARTING_ROOM].has_been_entered = state;
}

//------------------------------------------------------------------------------
// Determines what kind of stairs (if any) are in a location
//
// Arguments:
//   x, y - the coordinates of the location
//
// Returns:
//   STAIRS_UP, STAIRS_DOWN, or NO_STAIRS
//------------------------------------------------------------------------------
int Maze::stairs_here(int x, int y) {
	for (std::vector<Stair>::iterator it = stairs.begin(); it != stairs.end(); it++) {
		if (it->x == x && it->y == y) {
			return it->direction;
		}
	}
	return MazeConsts::NO_STAIRS;
}

//------------------------------------------------------------------------------
// Checks if the specified location has been seen by the player before
//
// Arguments:
//   x, y - the coordinates of the location to check
//
// Returns:
//   true if the player has seen it, false otherwise
//------------------------------------------------------------------------------
bool Maze::was_seen(int x, int y) {
	return m[y * cols + x].was_seen;
}