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

#ifndef __MAIN_MENU_WINDOW_H__
#define __MAIN_MENU_WINDOW_H__

#include <string>
#include <vector>

#include "window.h"

class main_menu_window : public window
{
public:
	main_menu_window(std::vector<std::string> vec);
	~main_menu_window();
	size_t make_selection();
private:
	size_t lines;
};

#endif //__MAIN_MENU_WINDOW_H__
