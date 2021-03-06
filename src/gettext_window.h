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

#ifndef __GETTEXT_WINDOW_H__
#define __GETTEXT_WINDOW_H__

#include <string>

#include "window.h"

class gettext_window : public window
{
public:
	gettext_window(std::string title, std::string desc);
	~gettext_window();
	std::string set_input();
	std::string get_input();
	void backup();
	void restore();
private:
	window* box;
	std::string input;
};

#endif //__GETTEXT_WINDOW_H__
