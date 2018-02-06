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

#ifndef __DETAILED_SELECTION_WINDOW_H__
#define __DETAILED_SELECTION_WINDOW_H__

#include <string>
#include <vector>

#include "base.h"
#include "selection_window.h"
#include "textlog_window.h"
#include "window.h"

class detailed_selection_window : public window
{
public:
	detailed_selection_window(std::string title, std::vector<base*> vec);
	~detailed_selection_window();
	size_t get_selection();
private:
	selection_window* select;
	textlog_window* info;
	std::vector<base*> choices;
};

#endif //__DETAILED_SELECTION_WINDOW_H__
