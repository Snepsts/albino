/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "class_def.h"
#include <string>

string classinfo(int classvar)
{
	string r;

	switch(classvar)
	{
		case 1:
			r = CLASS_1 + ":\nATK: " + DEF_1_ATK + " DEF: " + DEF_1_DEF +
			" SPD: " + DEF_1_SPD + "\nDescription:\n" + DEF_1_DESC;
			break;
		case 2:
			r = CLASS_2 + ":\nATK: " + DEF_2_ATK + " DEF: " + DEF_2_DEF +
			" SPD: " + DEF_2_SPD + "\nDescription:\n" + DEF_2_DESC;
			break;
		case 3:
			r = CLASS_3 + ":\nATK: " + DEF_3_ATK + " DEF: " + DEF_3_DEF +
			" SPD: " + DEF_3_SPD + "\nDescription:\n" + DEF_3_DESC;
			break;
		default:
			r = "Something went wrong.";
			break;
	}

	return r;
}
