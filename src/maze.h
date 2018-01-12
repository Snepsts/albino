/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>. */

#ifndef __MAZE_H__
#define __MAZE_H__

#include <random> //default_random_engine
#include <string> //to_string

const int SIZE = 11;

enum attribute { Enter = -1, Exit = 0, Open = 1, Wall = 2, Unassigned = 3 };
enum generation { Unvisited = 0, Visited = 1 };

/* maze blocks
 * attribute atr:
 *   -1 = enter (starting block)
 *   0 = exit
 *   1 = open
 *   2 = wall
 *   3 = unassigned (there should be 0 of these when the maze is fully generated)
 * is_seen:
 *   true = draw it on the map
 *   false = draw it as unknown (it isn't seen yet)
 * is_deadend:
 *   true = trigger for greater probability of hard monster/good loot
 *   false = gen normally
 * generation gen: //only for maze generation purposes
 *   0 = unvisited
 *   1 = visited
 * int x and y:
 *   x = keeping track of the x axis position
 *   y = keeping track of the y axis position
 * has_player:
 *   true = the player is currently in this block of the maze
 *   false = the player is not in this block of the maze
 */
struct block
{
	attribute atr = Unassigned;
	bool is_seen = false;
	bool is_deadend = false;
	generation gen = Unvisited;
	int x, y; //these are for keeping track of the x/y for gen purposes
	bool has_player = false;
	bool operator==(const block& b) const //for check_spot()
	{ return (this->x == b.x && this->y == b.y && this->atr == b.atr); }
};

class maze
{
public:
	/* default constructor
	 * Define the walls of the maze and assign each block it's (x, y) value.
	 */
	maze();

	/* destructor
	 * Set to default bc I don't know what to do with it
	 */
	~maze() = default;

	/* function gen_main
	 * Upon calling this the maze generation is started.
	 *
	 * Calls get_directions each iteration of its loop.
	 * Calls gen_next each iteration of its loop.
	 * Calls gen_walls and gen_start upon completion.
	 */
	void gen_main();

	/* function get_directions
	 * Called by gen_main and also whenever we need to see where the "character"
	 * can move.
	 *
	 * Takes an x and a y, and checks the adjacent blocks (assuming they're IN
	 * the array) to see if they're open. If they are open, it adds chars to
	 * represent open directions (u for up, d for down, r for right, and l for
 	 * left) to a string.
	 *
	 * Also takes a bool "isGen" to see if it was called from gen_main or not.
	 * This defaults to false so you don't have to worry about passing a bool.
	 * The purpose of this bool is if it's called for generation purposes, we
	 * need to check for two "Unassigned"s, otherwise we're looking for "Open"
	 * blocks.
	 *
	 * It returns said string containing all available directions.
	 */
	std::string get_directions(const int& x, const int& y, bool isGen = false) const;

	/* function min_steps
	 * Runs through the maze until the end is reached. Then returns the amount
	 * of "steps" it took. It runs through open blocks that have not been run
	 * through yet, and eventually it will find the end. Since it gurantees
	 * only touching each block once, the path it takes to reach the end will
	 * always be the shortest.
	 *
	 * PLANNED: Use min_steps to determine the placement of the end such that
	 * there is a range of minimum steps to complete the maze has to have.
	 * (i.e): if the maze must be 40-60 steps, the exit will continue to be
	 * placed until it is 40-60 steps away from the beginning.
	 */
	int min_steps();

	/* function to_string
	 * Called whenever needed.
	 *
	 * If there's one thing I like about Java classes, it's toString functions.
	 * However, we're making it to_string because I like my snake case in C/C++.
	 */
	std::string to_string() const;

	/* function move
	 * Called whenever needed.
	 *
	 * Takes the x and y the "character" is moving to and puts them there. It
	 * sets the current "has_player" to "false" and the new (x,y) coord area to
	 * "true". If the area is a wall it will not move them there.
	 *
	 * Returns an int, 0 for unsuccessful move, 1 for successful move, and 2 to
	 * indicate the maze has been completed
	 */
	int move(const int& x, const int& y);

	//accessor for the "character"'s x position
	int get_x() const { return cx; }

	//accessor for the "character"'s y position
	int get_y() const { return cy; }

	block get_block(const int &x, const int &y) const { return grid[x][y]; };

private:
	//Methods:
	/* function gen_next
	 * Called every iteration of gen_main's maze generation loop.
	 *
	 * Takes a string dir. This string dir has all the possible directions
	 * ( u(p), d(own), l(eft), r(ight) ) the generation can go.
	 *
	 * It chooses randomly from its choices (unless it's only one) and returns
	 * that selection to the main maze generation function.
	 */
	char gen_next(const std::string& dir);

	/* function gen_walls
	 * Only called at the end of gen_main's maze generation loop.
	 *
	 * Takes all "Unassigned" blocks and turns them into "Wall"s. That's it.
	 */
	void gen_walls();

	/* function gen_start
	 * Only called from gen_main after calling gen_walls.
	 *
	 * Creates the entrance of the maze, which is guaranteed to be connected to
	 * an "Open" block in the maze grid (as one would expect).
	 *
	 * Calls gen_switch_case.
	 * Calls gen_exit upon completion.
	 */
	void gen_start();

	/* function gen_exit
	 * Only called after gen_start.
	 *
	 * Takes the int that represents what side the entrance is on and uses it to
	 * ensure the exit is not on the same wall.
	 *
	 * Creates the exit of the maze, which is guaranteed to be connected to an
	 * "Open" block in the maze grid (as one would expect). Also, the exit will
	 * never be on the same wall that "Enter" is located on.
	 *
	 * Calls gen_switch_case and gen_dead_end
	 */
	void gen_exit(const int& ent);

	/* function gen_switch_case
	 * Called from gen_start and gen_exit
	 *
	 * Takes an int and a bool. The int determines what side the wall is on, and
	 * the bool determines whether gen_start called it or gen_exit called it.
	 *
	 * Since gen_start and gen_exit use almost identical code for randomly
	 * selecting a spot, we move it to a separate function to save from having
	 * 30 nearly identical lines of code.
	 */
	void gen_switch_case(const int& swtch, const bool& isEnter);

	/* function gen_dead_end
	 * Only called from gen_exit.
	 *
	 * This function allows us to keep track of which block is and isn't a dead
	 * end. Instead of running a check each time, we do it once during
	 * generation and keep tabs on the blocks that are dead ends. This is useful
	 * for possible uses that want to have dead ends be something more than just
	 * a frustration.
	 */
	void gen_dead_end();

	/* function check_spot
	 * Called from min_steps multiple times each iteration of it's loop.
	 *
	 * Takes an x and a y for the coordinates.
	 *
	 * Sees whether or not the block (denoted by the x y coordinates) is a wall
	 * and if it's already been visited. If it is either of those, false is
	 * returned. The other case, if it's open __and__ has not been visited, the
	 * function returns true.
	 */
	bool check_spot(const int& x, const int& y);

	/* function gen_finish
	 * Called from gen_exit as the last function called in the generation
	 * process.
	 *
	 * The purpose of this function is to accomplish any tasks necessary for
	 * polishing the maze for the user. This includes: Setting the initial
	 * "is_seen" values, allowing the player to see initially. Placing the
	 * "character" in the start block (has_player = true) and the cx/cy values.
	 * As new stuff gets added, this will be amended.
	 */
	void gen_finish();

	//Members:
	block grid[SIZE][SIZE];
	block Start, End; //capitalize bc end all lowers throws an error
	int cx, cy; //current "character" position x and y
};

#endif //__MAZE_H__
