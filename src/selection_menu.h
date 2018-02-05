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

#ifndef __SELECTION_MENU_H__
#define __SELECTION_MENU_H__

#include <deque>
#include <string>
#include <vector>

class selection_menu
{
public:
	selection_menu(std::vector<std::string> vec, const uint& size);
	~selection_menu() { /* nothing */ }
	void move_cursor_up();
	void move_cursor_down();
	std::string get_ext_str(bool is_top);
	std::vector<std::string> get_menu();
	uint get_selection() { return selection; }
private:
	std::deque<std::string> display; //the limited number of items that can be displayed
	std::vector<std::string> choices; //total amount of choices
	uint selection; //current selection
	uint top, bottom; //vars to keep track of topmost and bottommost items
	uint size; //amount of items to be displayed at once
};

#endif //__SELECTION_MENU_H__
