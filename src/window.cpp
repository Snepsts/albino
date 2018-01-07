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
#include <string>

#include "window.h"

window::window(const int &height, const int &width, const int &starty, const int &startx, const int &color)
{
	win = newwin(height, width, starty, startx); //make a new window
	box(win, 0, 0); //0, 0 gives default characters for the vertical and
	                //horizontal lines

	cache = new chtype[height][width]; //allocate space for the window cache
	this->height = height; //store height and width
	this->width = width;

	wrefresh(win); //show the box
	set_color(color);
}

window::~window()
{
	//we use all these ugly ' ' chars b/c it destroys all of the window sides
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win); //refresh to our empty window we just re-established
	delwin(win); //delete the window
	delete[] cache; //deallocate the cache
}

void window::print(const std::string &s, const int &y, const int &x)
{
	//wprintw takes a WINDOW* and a const char* argument
	mvwprintw(win, y, x, s.c_str()); //print the message

	wrefresh(win);
}

void window::print_char(const char &c, const int &y, const int &x)
{
	mvwaddch(win, y, x, c);
	wrefresh(win);
}

void window::set_color(int color)
{
	wattron(win, COLOR_PAIR(color)); //set the color
}

void window::backup()
{
	for (uint y = 0; y < height; y++) { //number of lines
		for (uint x = 0; x < width; x++) { //characters on each line
			cache[y][x] = mvwinch(win, y, x); //cache the window
		}
	}
}

void window::restore()
{
	for (uint y = 0; y < height; y++) { //number of lines
		for (uint x = 0; x < width; x++) { //characters on each line
			mvwaddch(win, y, x, cache[y][x]); //restore the window from the cache
		}
	}

	wrefresh(win);
}
