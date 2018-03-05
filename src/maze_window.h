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

#ifndef __MAZE_WINDOW_H__
#define __MAZE_WINDOW_H__

#include "maze.h"
#include "window.h"

class maze_window : public window
{
public:
	maze_window(maze* the_maze);
	~maze_window();
	void update_win();
	void test() { backup(); restore(); }

private:
	void print_player(const uint& rows, const uint& cols);
	void print_mystery(const uint& rows, const uint& cols);
	void print_event(const uint& rows, const uint& cols, const block& curr_b);
	void print_seen(const uint& rows, const uint& cols, const block& curr_b);
	void print_helper(const uint& rows, const uint& cols, const char& first, const char& second, const int& color);

	maze *dungeon;
};

#endif //__MAZE_WINDOW_H__
