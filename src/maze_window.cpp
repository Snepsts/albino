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

#include <ncurses.h>

#include "maze.h"
#include "maze_window.h"
#include "universal.h"

maze_window::maze_window(maze* the_maze)
: window(MW_HEIGHT, MW_WIDTH, MW_STARTY, MW_STARTX, MW_COLOR)
{
	dungeon = the_maze;
}

maze_window::~maze_window()
{
	dungeon = nullptr;
}

void maze_window::print()
{
	uint rows = 1, cols = 1;
	for (int y = SIZE-1; y >= 0; y--) { //y axis, inverted so (0,0) is bot left
		for (int x = 0; x < SIZE; x++) { //x axis
			block current_block = dungeon->get_block(x, y);
			if (!current_block.is_seen) { //if it hasn't been seen yet
				print_mystery(rows, cols);
			} else if (current_block.has_player) { //contains player
				print_player(rows, cols);
			} else { //otherwise it's been seen
				if (current_block.atr == Open && current_block.stepped_on)
					print_event(rows, cols, current_block);
				else
					print_seen(rows, cols, current_block);
			} //end else
			cols += 2; //allows for two prints per block, makes it look good
		} //end x
		rows++;
		cols = 1;
	} //end y
}

void maze_window::print_mystery(const uint& rows, const uint& cols)
{
	set_color(1); //black
	print_char(' ', rows, cols); //for mystery ooOOOoOOoOOOOOo spooky
	print_char(' ', rows, cols+1);
}

void maze_window::print_player(const uint& rows, const uint& cols)
{
	set_color(15); //player color
	print_char('*', rows, cols);
	print_char('\\', rows, cols+1);
}

void maze_window::print_event(const uint& rows, const uint& cols, const block& curr_b)
{
	switch (curr_b.b_event.type) {
	case event_t::nothing:
		set_color(14);
		print_char(' ', rows, cols); //for now print nothing
		print_char(' ', rows, cols+1);
		break;
	case event_t::battle:
		set_color(16);
		print_char('b', rows, cols);
		print_char('a', rows, cols+1);
		break;
	case event_t::loot:
		set_color(15);
		print_char('l', rows, cols);
		print_char('t', rows, cols+1);
		break;
	case event_t::shop:
		set_color(17);
		print_char('s', rows, cols);
		print_char('h', rows, cols+1);
		break;
	default:
		set_color(16);
		print_char('E', rows, cols);
		print_char('R', rows, cols+1);
		break;
	}
}

void maze_window::print_seen(const uint& rows, const uint& cols, const block& curr_b)
{
	switch(curr_b.atr) {
	case Enter:
		set_color(14);
		print_char('s', rows, cols); //Start/Beginning
		print_char('t', rows, cols+1);
		break;
	case Exit:
		set_color(14);
		print_char('e', rows, cols); //Exit/End
		print_char('x', rows, cols+1);
		break;
	case Open:
		set_color(14);
		print_char(' ', rows, cols); //Open
		print_char(' ', rows, cols+1);
		break;
	case Wall:
		set_color(12); //magenta walls
		print_char(' ', rows, cols); //Wall
		print_char(' ', rows, cols+1);
		break;
	case Unassigned:
		print_char('n', rows, cols); //Invalid (Unassigned)
		print_char('l', rows, cols+1);
		break;
	default:
		exit(1); //In case of error
		break;
	} //end switch
}
