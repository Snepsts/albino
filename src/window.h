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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <string>
#include <vector>

class window
{
public:
	window(const uint &height, const uint &width, const int &starty, const int &startx, const int &color);
	virtual ~window();
	//soft_printing will not refresh the window
	void soft_print(const std::string& s, const int& y = 1, const int& x = 1);
	void print(const std::string &s, const int &y = 1, const int &x = 1);
	void soft_print_char(const char &c, const int &y = 1, const int &x = 1);
	void print_char(const char &c, const int &y = 1, const int &x = 1);
	void set_color(int color);
	virtual void backup();
	virtual void restore();
	void refresh_win() { wrefresh(win); }
	uint get_height() { return height; }
	uint get_width() { return width; }
	void print_vector(std::vector<std::string> vec, uint height_start, uint width_start);
	void soft_clean(uint y = 1, uint x = 1);
	void clean(uint y = 1, uint x = 1);
	void soft_clear();
	void clear();
protected:
	void base_destructor();
	void base_backup();
	void base_restore();
private:
	WINDOW *win; //ncurses window the class is wrapping around
	chtype **cache; //allows for window to be saved and redrawn
	uint height, width; //stores height and width for window
};

#endif //__WINDOW_H__
