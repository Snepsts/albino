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

#include "helper.h"

uint get_selection_width(std::vector<std::string> vec)
{
	uint ret = 0; //init to lowest value

	for (auto str : vec) {
		if (str.length() > ret)
			ret = str.length();
	}

	return ret + 6; //2 for borders, 3 for selection space, 1 for space on right
}
