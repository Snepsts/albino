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

#include "player_window.h"
#include "universal.h"
#include "window.h"

player_window::player_window(player* playa)
: window(PI_HEIGHT, PI_WIDTH, PI_STARTY, PI_STARTX, PI_COLOR)
{
	p = playa;
}

player_window::~player_window()
{
	p = nullptr;
}

void player_window::update_win()
{
	print_name();
	print_class_info();
	print_health();
	refresh();
}

void player_window::print_name()
{
	std::string s = "Name: " + p->get_name();
	uint length = (s.length() < PI_WIDTH-2) ? s.length() : PI_WIDTH-2;

	for (uint i = 0; i < length; i++) {
		soft_print_char(s[i], 1, 1+i);
	}
}

void player_window::print_class_info()
{
	player_class pc = p->get_class();

	soft_print("Class: " + pc.get_name(), 2, 1);
}

void player_window::print_health()
{
	std::string msg = "HP: ";
	msg += std::to_string(p->get_hp());
	msg += "/";
	msg += std::to_string(p->get_max_hp());

	soft_print(msg, 3, 1);
}
