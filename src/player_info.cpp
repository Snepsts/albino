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

#include <string>

#include "universal.h"
#include "window.h"

player_info::player_info(player* playa)
{
	win = new window(PI_HEIGHT, PI_WIDTH, PI_STARTY, PI_STARTX, PI_COLOR);
	p = playa;
}

player_info::~player_info()
{
	delete win;
	win = nullptr;
	p = nullptr;
}

void player_info::refresh()
{

}

void player_info::print_name()
{
	std::string s = "Name: " + p->get_name();
	uint length = (s.length() > PI_WIDTH-2) : s.length() ? PI_WIDTH-2;

	for (uint i = 0; i < length; i++) {
		win->print_char(s[0], 1, 1+i);
	}
}
