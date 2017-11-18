/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <string>

class window
{
public:
	window(const int &height, const int &width, const int &starty, const int &startx, const int &color);
	~window();
	void print(const std::string &s, const int &y = 1, const int &x = 1);
	void print_char(const char &c, const int &y = 1, const int &x = 1);

private:
	void set_color(int color);

	WINDOW *win;
};

#endif //__WINDOW_H__
