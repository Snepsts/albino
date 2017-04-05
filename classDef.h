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

#ifndef __CLASS_DEF_H__
#define __CLASS_DEF_H__

#include <string>

using std::string;

string classInfo(int classvar);

//class names
const string CLASS_1 = "Knight";
const string CLASS_2 = "Thief";
const string CLASS_3 = "Assassin";

//class 1 definitions
const string DEF_1_ATK = "++";
const string DEF_1_DEF = "+++";
const string DEF_1_SPD = "---";
const string DEF_1_DESC = "The " + CLASS_1 + " is a powerful being, with high " +
"damage output and high resistance to damage. Unfortunately, he is slow, and " +
"as a result will suffer from many attacks.";

//class 2 definitions
const string DEF_2_ATK = "+";
const string DEF_2_DEF = "--";
const string DEF_2_SPD = "++";
const string DEF_2_DESC = "The " + CLASS_2 + " is a relatively quick entity, " +
"and as a result of his hauls, he has some muscle on him. However, he is weak " +
"to hits. Some kind of special ability will go here later.";

//class 3 definitions
const string DEF_3_ATK = "++";
const string DEF_3_DEF = "---";
const string DEF_3_SPD = "+++";
const string DEF_3_DESC = "The " + CLASS_3 + " is a fast and powerful fighter, " +
"feared by all that he targets. He strikes swiftly and without fault blah blah.";

#endif //__CLASS_DEF_H__
