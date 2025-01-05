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

Enemy::Enemy() {
    init(0);        // Just use a default value
}

Enemy::Enemy(int eid) {
    init(eid);
}

void Enemy::init(int eid) {
    id = eid;
    hp = get_max_hp();
    x_pos = 0;
    y_pos = 0;
    distance = 0;
    residual_action_points = 0;
    has_seen_player = false;
    is_alive = true;
}

//----------------------------------------------------------------------------
// Looks up the name of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's name
//----------------------------------------------------------------------------
std::string Enemy::get_name() { 
    return g_enemy_ids[id].name; 
}

//----------------------------------------------------------------------------
// Looks up the GID/tile ID of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's gid
//----------------------------------------------------------------------------
int Enemy::get_gid() { 
    return g_enemy_ids[id].gid; 
}

//----------------------------------------------------------------------------
// Looks up the AI behavior ID of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's bid
//----------------------------------------------------------------------------
int Enemy::get_bid() { 
    return g_enemy_ids[id].bid; 
}

//----------------------------------------------------------------------------
// Looks up the max HP of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's max HP
//----------------------------------------------------------------------------
int Enemy::get_max_hp() { 
    return g_enemy_ids[id].hp; 
}

//----------------------------------------------------------------------------
// Looks up the STR of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's STR
//----------------------------------------------------------------------------
int Enemy::get_str() { 
    return g_enemy_ids[id].str; 
}

//----------------------------------------------------------------------------
// Looks up the ATK of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's ATK
//----------------------------------------------------------------------------
int Enemy::get_atk() { 
    return g_enemy_ids[id].atk; 
}

//----------------------------------------------------------------------------
// Looks up the DEF of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's DEF
//----------------------------------------------------------------------------
int Enemy::get_def() { 
    return g_enemy_ids[id].def; 
}

//----------------------------------------------------------------------------
// Looks up the speed of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's SPD
//----------------------------------------------------------------------------
int Enemy::get_spd() { 
    return g_enemy_ids[id].spd; 
}

//----------------------------------------------------------------------------
// Looks up the attacks per turn of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's APT
//----------------------------------------------------------------------------
int Enemy::get_apt() { 
    return g_enemy_ids[id].apt; 
}

//----------------------------------------------------------------------------
// Looks up the fire attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's FATK
//----------------------------------------------------------------------------
int Enemy::get_fatk() { 
    return g_enemy_ids[id].f_atk; 
}

//----------------------------------------------------------------------------
// Looks up the ice attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's IATK
//----------------------------------------------------------------------------
int Enemy::get_iatk() { 
    return g_enemy_ids[id].i_atk; 
}

//----------------------------------------------------------------------------
// Looks up the lightning attack damage of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's LATK
//----------------------------------------------------------------------------
int Enemy::get_latk() { 
    return g_enemy_ids[id].l_atk; 
}

//----------------------------------------------------------------------------
// Looks up the fire resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's FDEF
//----------------------------------------------------------------------------
int Enemy::get_fdef() { 
    return g_enemy_ids[id].f_def; 
}

//----------------------------------------------------------------------------
// Looks up the ice resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's IDEF
//----------------------------------------------------------------------------
int Enemy::get_idef() { 
    return g_enemy_ids[id].i_def; 
}

//----------------------------------------------------------------------------
// Looks up the lightning resistance of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's LDEF
//----------------------------------------------------------------------------
int Enemy::get_ldef() { 
    return g_enemy_ids[id].l_def; 
}

//----------------------------------------------------------------------------
// Looks up the experience given on defeat of the enemy in the enemy 
// lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's EXP
//----------------------------------------------------------------------------
int Enemy::get_exp() { 
    return g_enemy_ids[id].exp; 
}

//----------------------------------------------------------------------------
// Looks up the enemy level of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's elevel
//
// Notes:
//   elevel is similar to the idea of ilevel for items - the deeper in the 
//   dungeon, the higher elevel of monsters that can spawn.
//----------------------------------------------------------------------------
int Enemy::get_elevel() { 
    return g_enemy_ids[id].elevel; 
}

//----------------------------------------------------------------------------
// Looks up the rarity of the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's rarity (255=most common, 1=most rare)
//----------------------------------------------------------------------------
int Enemy::get_rarity() { 
    return g_enemy_ids[id].rarity; 
}

//----------------------------------------------------------------------------
// Looks up the ilevel of drops from the enemy in the enemy lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's ilevel
//----------------------------------------------------------------------------
int Enemy::get_ilevel() { 
    return g_enemy_ids[id].ilevel; 
}

//----------------------------------------------------------------------------
// Looks up the maximum items the enemy can drop on kill in the enemy 
// lookup table
//
// Arguments:
//   None
//
// Returns:
//   the enemy's maximum number of item drops
//----------------------------------------------------------------------------
int Enemy::get_max_items() { 
    return g_enemy_ids[id].max_items; 
}

//----------------------------------------------------------------------------
// Generates an enemy.  This can be any enemy in the game.
//
// Arguments:
//   None
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate() {
    return generate(100);       // Generate an enemy of max level
}

//----------------------------------------------------------------------------
// Generates an enemy based on the specified elevel
//
// Arguments:
//   elevel - the elevel of the enemy to generate
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate(int elevel) {

    Enemy *e = new Enemy();
    bool done = false;
    int count = 0;
    int id = 0;
    int elevel_low = (int)(floor((float)elevel * EnemyConsts::MIN_ELEVEL_RANGE));
    int elevel_high = (int)(ceil((float)elevel * EnemyConsts::MAX_ELEVEL_RANGE));

    //std::cout << "elevel_low = " << elevel_low << ", elevel_high = " << elevel_high << std::endl;

    // Ensure the range of elevels falls between 0 and 100
    if (elevel_low < 0 )
        elevel_low = 0;
    if (elevel_high >= 100) 
        elevel_high = 100;

    // Take advantage of the fact that there are 2 assigned enemies per elevel
    // to limit the enemies to choose from to just those in the specific range
    // corresponding to valid enemies
    int pool_min = elevel_low * 2;
    int pool_max = elevel_high * 2;
    id = (rand() % (pool_max - pool_min)) + pool_min;

    // Initialize the enemy with the appropriate stats (mainly HP) for the selected enemy
    e->init(id);

    return e;
}

//----------------------------------------------------------------------------
// Generates an enemy of the specified ID (rather than a random one)
//
// Arguments:
//   id - the id of the enemy to generate
//
// Returns:
//   A pointer to the new Enemy
//----------------------------------------------------------------------------
Enemy* EnemyGenerator::generate_arbitrary(int id) {
    Enemy *e = new Enemy(id);
    return e;
}

//----------------------------------------------------------------------------
// Determines if the enemy can see a target at the specified position
//
// Arguments:
//   x, y - the position to check
//
// Returns:
//   True if the target can be seen, false otherwise
//----------------------------------------------------------------------------
bool Enemy::check_if_can_see(int x, int y) {
    // To do the check, we'll essentially use an integer-only version of 
    // something like Bresenham's algorithm.  As we iterate through 
    // each point of the 'line', if it hits a wall, the target can't be seen.
    int dx = abs(x - x_pos);
    int sx = (x_pos < x) ? 1 : -1;
    int dy = -abs(y - y_pos);
    int sy = (y_pos < y) ? 1 : -1;
    int error = dx + dy;
    bool carved;

    int cur_x = x_pos;
    int cur_y = y_pos;
    int e2;

    //std::cout << "check_if_can_see: sx = " << sx << ", sy = " << sy << ", dx = " << dx << ", dy = " << dy << ", error = " << error << std::endl;
    //std::cout << "check_if_can_see: " << get_name() << " at (" << x_pos << ", " << y_pos << "), player at (" << x << ", " << y << ")" << std::endl;

    while(true) {
        //std::cout << "  - Checking position (" << cur_x << ", " << cur_y << ")" << std::endl;
        carved = g_dungeon.maze->is_carved(cur_x, cur_y);
        if (carved == false) {
            //std::cout << "  - The " << get_name() << " has not seen player" << std::endl;
            return false;
        }
        if (cur_x == x && cur_y == y) {
            //std::cout << "  - The " << get_name() << " has seen player" << std::endl;
            return true;
        }
        e2 = 2 * error;
        if (e2 >= dy) {
            error += dy;
            cur_x += sx;
        }     
        if (e2 <= dx) {
            error += dx;
            cur_y += sy;
        }
    }
}

//----------------------------------------------------------------------------
// A utility function used to assist with sorting the enemy list - this
// function assists with sorting by distance
//
// Arguments:
//	first, second - the enemies to compare
//
// Returns:
//  true if the first is lower, false otherwise
//----------------------------------------------------------------------------
bool enemy_distance_sort(Enemy *first, Enemy *second) {
	return (first->get_distance() < second->get_distance());
}

//----------------------------------------------------------------------------
// Sorts a list of enemies by distance, from closest to furthest
//
// Arguments:
//	el - the list to sort
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void sort_enemy_list(std::list<Enemy *> &el) {
	el.sort(enemy_distance_sort);
}

//----------------------------------------------------------------------------
// Calculates the distance from an arbitrary point to each enemy and
// sorts the resulting list by distance
//
// Arguments:
//	el - the enemy list
//  x, y - the point
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void get_enemy_distances(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), x, y);
		(*enemy_it)->set_distance(distance);
	}

	sort_enemy_list(el);
}

//----------------------------------------------------------------------------
// For any sufficiently close enemies, check to see if they can see the 
// player.
//
// Arguments:
//	el - the enemy list
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void process_enemy_vision(std::list<Enemy *> &el) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->has_seen_the_player()) {
			//std::cout << "process_enemy_vision: the " << (*enemy_it)->get_name() << " has already seen player" << std::endl;
		} 
		else {
			//std::cout << "process_enemy_vision: processing the " << (*enemy_it)->get_name() << std::endl;
			int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), g_player.get_x_pos(), g_player.get_y_pos());
			if (distance <= UtilConsts::MAXIMUM_ENEMY_AI_DISTANCE_FAR && (*enemy_it)->has_seen_the_player() == false) {
				bool seen = (*enemy_it)->check_if_can_see(g_player.get_x_pos(), g_player.get_y_pos());
				if (seen) {
					(*enemy_it)->mark_has_seen_player(true);
				}	
			}
			else {
				//std::cout << "  - enemy is too far away to care" << std::endl;
			}
		}
	}
}

//----------------------------------------------------------------------------
// Marks every enemy too far from the player as having forgotten that the 
// player exists. 
//
// Arguments:
//	el - the enemy list
//
// Returns:
//	Nothing
//----------------------------------------------------------------------------
void process_enemy_forgetting_player(std::list<Enemy *> &el) {
	int px = g_player.get_x_pos();
	int py = g_player.get_y_pos();
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->has_seen_the_player()) {
			int distance = get_diagonal_distance_between((*enemy_it)->get_x_pos(), (*enemy_it)->get_y_pos(), px, py);
			if (distance >= UtilConsts::MAXIMUM_ENEMY_REMEMBER_DISTANCE) {
				(*enemy_it)->mark_has_seen_player(false);
				//std::cout << "process_enemy_forgetting_player: the " << (*enemy_it)->get_name() << " has forgotten the player" << std::endl;
			}
		}
	}
}

//----------------------------------------------------------------------------
// Checks if an enemy is located in the specified position
//
// Arguments:
//	el - the enemy list
//  x, y - the point
//
// Returns:
//	True if an enemy is located there, false otherwise
//----------------------------------------------------------------------------
bool is_enemy_here(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->get_x_pos() == x && (*enemy_it)->get_y_pos() == y)
			return true;
	}

	return false;
}

//----------------------------------------------------------------------------
// Returns the Enemy at the specified position, if there is one
//
// Arguments:
//  x, y - the position
//
// Returns:
//	A pointer to the Enemy if present, NULL otherwise.
//----------------------------------------------------------------------------
Enemy* get_enemy_at(std::list<Enemy *> &el, int x, int y) {
	std::list<Enemy *>::iterator enemy_it;

	for(enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->get_x_pos() == x && (*enemy_it)->get_y_pos() == y)
			return (*enemy_it);
	}

	return NULL;
}

//----------------------------------------------------------------------------
// Goes through the enemy list and deletes any marked as dead
//
// Arguments:
//  el - the enemy list
//
// Returns:
//   Nothing
//----------------------------------------------------------------------------
void delete_dead_enemies(std::list<Enemy *> &el) {
	std::list<Enemy *>::iterator enemy_it;

	for (enemy_it = el.begin(); enemy_it != el.end(); ++enemy_it) {
		if ((*enemy_it)->is_it_alive() == false) {
			std::list<Enemy *>::iterator it = enemy_it;
			//std::cout << "delete_dead_enemies: deleting " << (*it)->get_name() << std::endl;
			delete *enemy_it;
			enemy_it = el.erase(it);
		}
	}

	// Now that enemies are dead, we need to update the maze area to
	// remove them from the screen
	g_state_flags.update_maze_area = true;
}

//----------------------------------------------------------------------------
// Checks if the specified location is a place an enemy can be
//
// Arguments:
//  x, y - the point
//
// Returns:
//	True if an enemy can be there, false otherwise
//----------------------------------------------------------------------------
bool is_valid_enemy_position(int x, int y) {
	// Is the square a floor?
	if (!g_dungeon.maze->is_carved(x,y))
		return false;
	// Does the square already contain an enemy?
	if (is_enemy_here(g_dungeon.enemies, x, y))
		return false;

	// If neither are true, the enemy can be here.
	return true;
}

//----------------------------------------------------------------------------
// Determines the direction an enemy should move on its turn
//
// Arguments:
//  e - the enemy
//
// Returns:
//   Nothing.  This function directly moves the enemy.
//----------------------------------------------------------------------------
void perform_enemy_action(Enemy *e) {
	// Does the following :
	//   - Check to see if the player is adjacent.  
	//      - If so, attack the player
	//   - Otherwise, for each of the 8 directions
	//      - If the position can be moved to (no wall, no enemy, no player)
	//          - calculate the distance from the player
	//          - push a pair <direction, distance> to a vector
	//	 - With the resulting vector:
	//   - Make a pass, find the lowest distance and add each one
	//   - Pick a random element from the second vector
	//   - Use the direction component of the selected element to move the enemy

	// Being greedy, this will lead to non-optimal behavior (enemies getting stuck
	// behind walls, and such), but non-optimal behavior is much better than the
	// cost and complexity of A*, and behavior in more open spaces will be just fine.
	int x = e->get_x_pos();
	int y = e->get_y_pos();
	int px = g_player.get_x_pos();
	int py = g_player.get_y_pos();

	// If the enemy is 0 or 1 away from the player in both the x and y direction, they're 'adjacent',
	// and should attack the player
	//std::cout << "perform_enemy_action: abs(px-x) = " << abs(px-x) << ", abs(py-y) = " << abs(py-y) << std::endl;
	if (abs(px-x) <= 1 && abs(py-y) <= 1) {
		g_text_log.put_line("The " + e->get_name() + " attacks you!");
		perform_enemy_combat(e);
		if (g_player.hp <= 0) {
			g_text_log.put_line("You are defeated!");
		}
		// TODO: Deal with player death
		return;
	}

	std::vector<std::pair<int, int> > directions;
	std::vector<int> lowest;

	if (is_valid_enemy_position(x - 1, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTHWEST, get_diagonal_distance_between(x - 1, y - 1, px, py)));
	if (is_valid_enemy_position(x, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTH, get_diagonal_distance_between(x, y - 1, px, py)));
	if (is_valid_enemy_position(x + 1, y - 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_NORTHEAST, get_diagonal_distance_between(x + 1, y - 1, px, py)));
	if (is_valid_enemy_position(x - 1, y))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_WEST, get_diagonal_distance_between(x - 1, y, px, py)));
	if (is_valid_enemy_position(x + 1, y))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_EAST, get_diagonal_distance_between(x + 1, y, px, py)));
	if (is_valid_enemy_position(x - 1, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTHWEST, get_diagonal_distance_between(x - 1, y + 1, px, py)));
	if (is_valid_enemy_position(x, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTH, get_diagonal_distance_between(x, y + 1, px, py)));
	if (is_valid_enemy_position(x + 1, y + 1))
		directions.push_back(std::make_pair(MazeConsts::DIRECTION_SOUTHEAST, get_diagonal_distance_between(x + 1, y + 1, px, py)));

	// The enemy can't move in any direction; return
	if (directions.size() == 0) {
		//std::cout << "  Enemy can't move" << std::endl;
		return;
	}

	int lowest_distance = 1000;
	// Loop through, find the lowest distance
	for (std::vector<std::pair<int, int> >::iterator it = directions.begin(); it != directions.end(); ++it) {
		if ((*it).second <= lowest_distance)
			lowest_distance = (*it).second;
	}

	// Loop through again, pull out all that have the lowest distance
	for (std::vector<std::pair<int, int> >::iterator it = directions.begin(); it != directions.end(); ++it) {
		if ((*it).second == lowest_distance)
			lowest.push_back((*it).first);
	}

	//std::cout << "Number of lowest values = " << lowest.size() << std::endl;

	int dir = rand() % lowest.size();
	switch (lowest[dir]) {
		case MazeConsts::DIRECTION_NORTHWEST:
			//std::cout << "  Enemy moves northwest" << std::endl;
			e->set_pos(x - 1, y - 1);
			break;
		case MazeConsts::DIRECTION_NORTH:
			//std::cout << "  Enemy moves north" << std::endl;
			e->set_pos(x, y - 1);
			break;
		case MazeConsts::DIRECTION_NORTHEAST:
			//std::cout << "  Enemy moves northeast" << std::endl;
			e->set_pos(x + 1, y - 1);
			break;
		case MazeConsts::DIRECTION_WEST:
			//std::cout << "  Enemy moves west" << std::endl;
			e->set_pos(x - 1, y);
			break;
		case MazeConsts::DIRECTION_EAST:
			//std::cout << "  Enemy moves east" << std::endl;
			e->set_pos(x + 1, y);
			break;
		case MazeConsts::DIRECTION_SOUTHWEST:
			//std::cout << "  Enemy moves southwest" << std::endl;
			e->set_pos(x - 1, y + 1);
			break;
		case MazeConsts::DIRECTION_SOUTH:
			//std::cout << "  Enemy moves south" << std::endl;
			e->set_pos(x, y + 1);
			break;
		case MazeConsts::DIRECTION_SOUTHEAST:
			//std::cout << "  Enemy moves southeast" << std::endl;
			e->set_pos(x + 1, y + 1);
			break;
		default:
			//std::cout << "  Enemy doesn't move" << std::endl;
			break;
	}
}

//----------------------------------------------------------------------------
// 'Attacks' the player, doing all required damage calculations and
// adjusting player/enemy health
//
// Arguments:
//   e - the enemy performing the attack
//
// Returns:
//   Nothing.  The enemy and player health will be adjusted accordingly
//----------------------------------------------------------------------------
void perform_enemy_combat(Enemy *e) {
	for (int attack = 0; attack < e->get_apt(); ++attack) {
		// Calculate physical base damage
		int base_physical_damage = (int)((e->get_atk() + (0.2 * e->get_str())) * ((rand() % 50) + 75) / 100);
		//std::cout << "perform_enemy_combat: enemy base phys = " << base_physical_damage << std::endl;

		// Calculate elemental base damage
		int base_fire_damage = 0;
		int base_ice_damage = 0;
		int base_lightning_damage = 0;
		bool fire_attack_done = false;
		bool ice_attack_done = false;
		bool lightning_attack_done = false;
		if (e->get_fatk() > 0) {
			base_fire_damage = (int)((e->get_fatk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			fire_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base fire = " << base_fire_damage << std::endl;
		}
		if (e->get_iatk() > 0) {
			base_ice_damage = (int)((e->get_iatk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			ice_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base fire = " << base_ice_damage << std::endl;
		}
		if (e->get_latk() > 0) {
			base_lightning_damage = (int)((e->get_latk() + (0.1 * e->get_str())) * ((rand() % 50) + 75) / 100);
			lightning_attack_done = true;
			//std::cout << "peform_enemy_combat: enemy base lightning = " << base_lightning_damage << std::endl;
		}		

		// Check for critical hit
		bool attack_crits = false;
		int chance_of_crit = 2 + (int)(e->get_str() / 10);
		if (chance_of_crit > 90)
			chance_of_crit = 90;
		if (rand() % 100 < chance_of_crit) {
			attack_crits = true;
			//std::cout << "perform_enemy_combat: attack crits!" << std::endl;
		}	

		int player_base_damage_taken;
		// Calculate actual base damage
		if (rand() % 100 < (2 + g_player.actual.block)) {
			player_base_damage_taken = 0;
		}
		else {
			player_base_damage_taken = (int)((base_physical_damage - (g_player.actual.def + 0.2 * g_player.actual.con) * (rand() % 50 + 75) / 100));
		}
		//std::cout << "perform_enemy_combat: player base damage taken = " << player_base_damage_taken << std::endl;
		if (player_base_damage_taken < 1)
			player_base_damage_taken = 1;
		//std::cout << "perform_enemy_combat: actual base damage taken = " << player_base_damage_taken << std::endl;

		// Calculate actual elemental damage
		float fire_resist = g_player.actual.f_def / 100;
		float ice_resist = g_player.actual.i_def / 100;
		float lightning_resist = g_player.actual.l_def / 100;
		int player_fire_damage_taken = (int)(base_fire_damage * g_player.actual.f_def * (1.0 - fire_resist) * (rand() % 50 + 75) / 100);
		int player_ice_damage_taken = (int)(base_ice_damage * g_player.actual.i_def * (1.0 - ice_resist) * (rand() % 50 + 75) / 100);
		int player_lightning_damage_taken = (int)(base_lightning_damage * g_player.actual.l_def * (1.0 - lightning_resist) * (rand() % 50 + 75) / 100);
		if (fire_attack_done && player_fire_damage_taken < 1)
			player_fire_damage_taken = 1;
		if (ice_attack_done && player_ice_damage_taken < 1)
			player_ice_damage_taken = 1;
		if (lightning_attack_done && player_lightning_damage_taken < 1)
			player_lightning_damage_taken = 1;
		//std::cout << "perform_enemy_combat: fire damage taken = " << player_fire_damage_taken << std::endl;
		//std::cout << "perform_enemy_combat: ice damage taken = " << player_ice_damage_taken << std::endl;
		//std::cout << "perform_enemy_combat: lightning damage taken = " << player_lightning_damage_taken << std::endl;

		// Sum up all damage
		int total_damage_taken = player_base_damage_taken + player_fire_damage_taken + player_ice_damage_taken + player_lightning_damage_taken;		
		if (attack_crits) {
			g_text_log.put_line("Critical hit!");
			int prevent_chance = (int)(g_player.actual.con / 2);
			if (prevent_chance > 90)
				prevent_chance = 90;
			if (rand() % 100 < prevent_chance) {
				if (rand() % 100 < 50) {
					//std::cout << "perform_enemy_combat: crit missed, no damage taken" << std::endl;
					total_damage_taken = 0;
				}
				//else {
					//std::cout << "perform_enemy_combat: crit missed, standard damage taken" << std::endl;
				//}
			}
			else {
				total_damage_taken = total_damage_taken * 2;
				//std::cout << "perform_enemy combat: crit landed, player takes 2x damage" << std::endl;
			}
		}

		// Subtract player HP
		g_player.hp = g_player.hp - total_damage_taken;

		// Log the damage done to the game log
		//std::cout << "perform_enemy_combat: player takes " << total_damage_taken << " damage." << std::endl;
		//std::cout << "  perform_enemy_combat: player hp remaining = " << g_player.hp << std::endl;
		char text[80];
		sprintf(text, "You take %d damage!", total_damage_taken);
		g_text_log.put_line(text);
	}
}