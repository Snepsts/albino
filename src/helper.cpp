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

#include <string>
#include <vector>

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

std::vector<std::string> get_clean_vec(std::vector<std::string> vec, uint size)
{
	std::vector<std::string> ret;

	/* This double loop is to go over the WHOLE line
	It solves the problem of:
	 * New Game
	 * Some Options
	Becoming:
	 * New Gameions */
	for (auto q : vec) {
		std::string str = "";
		for (size_t j = 0; j < size; j++) {
			if (j < q.length()) //if we're still printing the string
				str += q[j];
			else //else we're done and need to print spaces
				str += ' ';
		}
		ret.push_back(str);
	}

	return ret;
}

std::vector<std::string> str_to_vec(std::string str)
{
	std::vector<std::string> vec;
	std::string line = "";

	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == '\n') {
			vec.push_back(line);
			line.clear();
		} else {
			line += str[i];
		}
	}

	if (line.length() > 0)
		vec.push_back(line);

	return vec;
}
