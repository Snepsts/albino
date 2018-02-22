/* albino
Copyright (C) 2017-2018 Michael Ranciglio

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

window::window(const uint &height, const uint &width, const int &starty, const int &startx, const int &color)
{
	win = newwin(height, width, starty, startx); //make a new window
	box(win, 0, 0); //0, 0 gives default characters for the vertical and
	                //horizontal lines

	cache = new chtype*[height]; //allocate height for the window cache
	for (uint i = 0; i < height; i++) //allocate width for each line
		cache[i] = new chtype[width];

	this->height = height; //store height and width
	this->width = width;

	wrefresh(win); //show the box
	set_color(color);
}

window::~window()
{
	base_destructor();
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
	base_backup();
}

void window::restore()
{
	base_restore();
}

void window::print_vector(std::vector<std::string> vec, uint height_start, uint width_start)
{
	for (size_t i = 0; i < vec.size(); i++)
		print(vec[i], height_start+i, width_start);
}

void window::clean(uint y, uint x)
{
	std::string clr = "";

	for (size_t i = x-1; i < width-2; i++)
		clr += ' ';

	for (size_t i = y-1; i < height-2; i++)
		print(clr.c_str(), i+1, 1);
}

void window::clear()
{
	std::string clr = "";

	for (size_t i = 0; i < width; i++)
		clr += ' ';

	for (size_t i = 0; i < height; i++)
		print(clr.c_str(), i+1, 0);
}

void window::base_destructor()
{
	//we use all these ugly ' ' chars b/c it destroys all of the window sides
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win); //refresh to our empty window we just re-established
	delwin(win); //delete the window

	for (uint i = 0; i < height; i++)
		delete[] cache[i]; //deallocate cache height i

	delete[] cache;
}

void window::base_backup()
{
	for (uint y = 0; y < height; y++) { //number of lines
		for (uint x = 0; x < width; x++) { //characters on each line
			cache[y][x] = mvwinch(win, y, x); //cache the window
		}
	}
}

void window::base_restore()
{
	for (uint y = 0; y < height; y++) { //number of lines
		for (uint x = 0; x < width; x++) { //characters on each line
			if (x == 0 || y == 0 || x == width-1 || y == height-1) //fixes maze_window colors edge breaking
				mvwaddch(win, y, x, cache[y][x] | COLOR_PAIR(1));
			else
				mvwaddch(win, y, x, cache[y][x]); //restore the window from the cache
		}
	}

	wrefresh(win);
}
