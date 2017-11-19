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

char* string_to_char_array(const std::string &s)
{
	char* c = new char[s.length()]; //allocate memory

	for (uint i = 0; i < s.length(); i++)
		c[i] = s[i]; //assign string to char array

	return c;
}

window::window(const int &height, const int &width, const int &starty, const int &startx, const int &color)
{
	win = newwin(height, width, starty, startx); //make a new window
	box(win, 0, 0); //0, 0 gives default characters for the vertical and
	                //horizontal lines
	wrefresh(win); //show the box
	set_color(color);
}

window::~window()
{
	//we use all these ugly ' ' chars b/c it destroys all of the window sides
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win); //refresh to our empty window we just re-established
	delwin(win); //delete the window
}

void window::print(const std::string &s, const int &y, const int &x)
{
	//wprintw takes a WINDOW* and a const char* argument
	const char *msg = string_to_char_array(s); //turn string to char array

	mvwprintw(win, y, x, msg); //print the message

	delete[] msg; //clear memory
	msg = nullptr; //safely set msg to point at nothing

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
