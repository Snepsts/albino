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

void maze_window::update_win()
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

	refresh_win();
}

void maze_window::print_mystery(const uint& rows, const uint& cols)
{
	set_color(1); //black
	soft_print_char(' ', rows, cols); //for mystery ooOOOoOOoOOOOOo spooky
	soft_print_char(' ', rows, cols+1);
}

void maze_window::print_player(const uint& rows, const uint& cols)
{
	set_color(15); //player color
	soft_print_char('*', rows, cols);
	soft_print_char('\\', rows, cols+1);
}

void maze_window::print_event(const uint& rows, const uint& cols, const block& curr_b)
{
	switch (curr_b.b_event.type) {
	case event_t::nothing:
		print_helper(rows, cols, ' ', ' ', 14); //open white space
		break;
	case event_t::battle:
		print_helper(rows, cols, 'b', 'a', 16);
		break;
	case event_t::loot:
		print_helper(rows, cols, 'l', 't', 15);
		break;
	case event_t::shop:
		print_helper(rows, cols, 's', 'h', 17);
		break;
	default:
		print_helper(rows, cols, 'E', 'R', 16);
		break;
	}
}

void maze_window::print_seen(const uint& rows, const uint& cols, const block& curr_b)
{
	switch(curr_b.atr) {
	case Enter:
		print_helper(rows, cols, 's', 't', 14);
		break;
	case Exit:
		print_helper(rows, cols, 'e', 'x', 14);
		break;
	case Open:
		print_helper(rows, cols, ':', ':', 14); //unstepped spaces
		break;
	case Wall:
		print_helper(rows, cols, ' ', ' ', 12); //magenta walls
		break;
	case Unassigned:
		print_helper(rows, cols, 'n', 'l', 1);
		break;
	default:
		exit(1); //in case of error
		break;
	} //end switch
}

void maze_window::print_helper(const uint& rows, const uint& cols, const char& first, const char& second, const int& color)
{
	set_color(color);
	soft_print_char(first, rows, cols);
	soft_print_char(second, rows, cols+1);
}
