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

#include "event.h" //events

const int SIZE = 11;

enum attribute { Enter = -1, Exit = 0, Open = 1, Wall = 2, Unassigned = 3 };
enum generation { Unvisited = 0, Visited = 1 };

/* structure block (for maze)
 * The block structure represents a single block in the maze. The maze is just a
 * double array of blocks.
 *
 * Atr: The block's type in the maze.
 *  - Enter: The block the player starts in.
 *  - Exit: The block the player must make it to leave the maze.
 *  - Open: A block that the player can walk in.
 *  - Wall: A block that the player cannot walk in.
 *  - Unassigned: Not yet generated. (should be 0 when maze is generated)
 * is_seen: Denotes whether the block has been seen or not.
 *  - true: The block is drawn on the map.
 *  - false: The block is not drawn on the map.
 * is_deadend: Denotes whether the block is a dead end or not.
 *  - true: It's a dead end, a trigger for a hard monster or good loot.
 *  - false: It isn't a dead end, and will be normal.
 * Gen: A field that denotes if min_steps has been through the block yet.
 *  - Unvisited: The min_steps hasn't reached this block yet.
 *  - Visited: The min_steps algorithm has already reached this block.
 * int x and y:
 *  - x: keeps track of the x axis position of the block
 *  - y: keeps track of the y axis position of the block
 * has_player: Denotes whether the player is in this block or not.
 *  - true: Draw the player on this block of the map.
 *  - false: Draw the block on the map normally.
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
	bool stepped_on = false;
	event b_event;
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
	 */
	void gen_main();

	/* function get_directions
	 * A function that grabs all available directions from a block.
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
	 * Runs through the maze until the end is reached.
	 *
	 * It runs through open blocks that have not been run through yet, and
	 * eventually it will find the end. Since it gurantees only touching each
	 * block once, the path it takes to reach the end will always be the
	 * shortest.
	 *
	 * Returns an int representing the amount of "steps" it took.
	 *
	 * PLANNED: Use min_steps to determine the placement of the end such that
	 * there is a range of minimum steps to complete the maze has to have.
	 * (i.e): if the maze must be 40-60 steps, the exit will continue to be
	 * placed until it is 40-60 steps away from the beginning.
	 */
	int min_steps();

	/* function to_string
	 * Changes the maze into a string.
	 *
	 * If there's one thing I like about Java classes, it's toString functions.
	 * However, we're making it to_string because I like my snake case in C/C++.
	 *
	 * Returns the string representing the maze.
	 */
	std::string to_string() const;

	/* function move
	 * A function that moves the player to a new block.
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
	//methods:
	/* function gen_next
	 * Generates the next block in the maze from gen_main in a loop.
	 *
	 * Takes a string dir. This string dir has all the possible directions
	 * ( u(p), d(own), l(eft), r(ight) ) the generation can go.
	 *
	 * It chooses randomly from its choices (unless it's only one) and returns
	 * that selection to the main maze generation function.
	 */
	char gen_next(const std::string& dir);

	/* function gen_walls
	 * Takes all "Unassigned" blocks and turns them into "Wall"s. That's it.
	 */
	void gen_walls();

	/* function gen_start
	 * Creates the entrance of the maze, which is guaranteed to be connected to
	 * an "Open" block in the maze grid (as one would expect).
	 */
	void gen_start();

	/* function gen_exit
	 * Creates the exit of the maze, which is guaranteed to be connected to
	 * an "Open" block in the maze grid (as one would expect).
	 *
	 * The exit will never be on the same wall that "Enter" is located on.
	 *
	 * Takes the int that represents what side the entrance is on and uses it to
	 * ensure the exit is not on the same wall.
	 */
	void gen_exit(const int& ent);

	/* function gen_switch_case
	 * Reusable code between gen_start and gen_exit.
	 *
	 * Since gen_start and gen_exit use almost identical code for randomly
	 * selecting a spot, we move it to a separate function to save from having
	 * 30 nearly identical lines of code.
	 *
	 * Takes an int and a bool. The int determines what side the wall is on, and
	 * the bool determines whether gen_start called it or gen_exit called it.
	 */
	void gen_switch_case(const int& swtch, const bool& isEnter);

	/* function gen_dead_end
	 * Goes through the maze and marks all the dead ends.
	 *
	 * This function allows us to keep track of which block is and isn't a dead
	 * end. Instead of running a check each time, we do it once during
	 * generation and keep tabs on the blocks that are dead ends. This is useful
	 * for possible uses that want to have dead ends be something more than just
	 * a frustration.
	 */
	void gen_dead_end();

	/* function check_spot
	 * Checks if a block is open and has not been visited.
	 *
	 * Takes an x and a y for the coordinates.
	 *
	 * Sees whether or not the block (denoted by the x y coordinates) is a wall
	 * and if it's already been visited. If it is either of those, false is
	 * returned. The other case, if it's open __and__ has not been visited, the
	 * function returns true.
	 */
	bool check_spot(const int& x, const int& y);

	/* function gen_events
	 * Creates random events for each open block.
	 */
	void gen_events();

	/* function gen_finish
	 * Finishes up the generation process.
	 *
	 * The purpose of this function is to accomplish any tasks necessary for
	 * polishing the maze for the user. This includes: Setting the initial
	 * "is_seen" values, allowing the player to see initially. Placing the
	 * "character" in the start block (has_player = true) and the cx/cy values.
	 * As new stuff gets added, this will be amended.
	 */
	void gen_finish();

	//Members:
	block grid[SIZE][SIZE]; //the maze itself
	block Start, End; //capitalize bc end all lowers throws an error
	int cx, cy; //current "character" position x and y
};

#endif //__MAZE_H__
