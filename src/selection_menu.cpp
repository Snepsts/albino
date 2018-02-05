/* albino
Copyright (C) 2018 Michael Ranciglio

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
#include <deque>
#include <fstream> //debug
#include <iostream>
#include <string>
#include <vector>

#include "selection_menu.h"

extern std::ofstream debug;

selection_menu::selection_menu(std::vector<std::string> vec, const uint& size)
{
	selection = 1;
	this->size = size;
	choices = vec;
	top = selection;
	bottom = size;

	for (size_t i = top; i <= bottom; i++)
		display.push_back(vec[i-1]);
}

void selection_menu::move_cursor_up()
{
	if (selection == 1)
		return;

	if (selection == top) {
		display.pop_back();
		display.push_front(choices[selection-2]);
		top--;
		bottom--;
	}

	selection--;
}

void selection_menu::move_cursor_down()
{
	if (selection == choices.size())
		return;

	if (selection == bottom) {
		display.pop_front();
		display.push_back(choices[selection]);
		bottom++;
		top++;
	}

	selection++;
}

std::string selection_menu::get_ext_str(bool is_top)
{
	std::string ret = "     ";

	if (is_top) { //top check
		if (top != 1)
			ret = "^^^";
	} else { //bot check
		if (bottom < choices.size())
			ret = "vvv";
	}

	return ret;
}

std::vector<std::string> selection_menu::get_menu()
{
	std::vector<std::string> vec;

	for (auto q : display) {
		vec.push_back(q);
	}

	return vec;
}
