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

#include "player_class.h"

std::string get_mod_string(int mod)
{
	std::string ret = "";

	for (int i = 0; i < mod; i++)
		ret += "+";

	return ret;
}

std::string player_class::to_string()
{
	std::string ret = "Type: " + get_str_from_ctype(ctype) + '\n';

	ret += get_desc() + '\n';
	ret += '\n';

	ret += "Attack: " + get_mod_string(atk_mod) + '\n';
	ret += "Defense: " + get_mod_string(def_mod) + '\n';
	ret += "Speed: " + get_mod_string(spd_mod);

	return ret;
}
