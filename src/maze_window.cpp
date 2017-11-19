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

maze_window::maze_window(maze* the_maze)
{
	win = new window(13, 23, 8, 0, 5);
	dungeon = the_maze;
}

maze_window::~maze_window()
{
	delete win;
	win = nullptr;
	dungeon = nullptr;
}

void maze_window::print()
{
	uint rows = 1, cols = 1;
	for (int y = SIZE-1; y >= 0; y--) { //y axis, inverted so (0,0) is bot left
		for (int x = 0; x < SIZE; x++) { //x axis
			block current_block = dungeon->get_block(x, y);
			if (!current_block.is_seen) { //if it hasn't been seen yet
				win->set_color(1); //black
				win->print_char(' ', rows, cols); //for mystery ooOOOoOOoOOOOOo spooky
				cols++;
			} else { //otherwise it's been seen so we can draw it
				switch(current_block.atr) {
					case -1:
						if (current_block.has_player) { //check for a player
							win->set_color(15); //player color
							win->print_char('*', rows, cols);
						} else {
							win->set_color(14);
							win->print_char('s', rows, cols); //Start/Beginning
						}
						break;
					case 0:
						if (current_block.has_player) { //check for a player
							win->set_color(15); //player color
							win->print_char('*', rows, cols);
						} else {
							win->set_color(14);
							win->print_char('e', rows, cols); //Exit/End
						}
						break;
					case 1:
						if (current_block.has_player) { //check for a player
							win->set_color(15); //player color
							win->print_char('*', rows, cols);
						} else if (current_block.is_deadend) { //check for a dead end
							win->set_color(14);
							win->print_char('d', rows, cols); //Dead End
						} else {
							win->set_color(14);
							win->print_char(' ', rows, cols); //Open
						}
						break;
					case 2:
						win->set_color(12); //magenta walls
						win->print_char(' ', rows, cols); //Wall
						break;
					case 3:
						win->print_char('n', rows, cols); //Invalid (Unassigned)
						break;
					default:
						exit(1); //In case of error
						break;
				} //end switch
			} //end else
			cols++;
			//win->set_color(12); //magenta walls
			//win->print_char(' ', rows, cols); //space to make the formatting look nicer
			//cols++;
		} //end x
		rows++;
		cols = 1;
	} //end y
}
