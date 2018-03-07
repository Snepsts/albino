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

#ifndef __MOVE_H__
#define __MOVE_H__

#include <string> //description

#include "base.h" //base for DSW
#include "system.h" //ctype

class move_battle : public base
{
public:
	move_battle() { ctype = class_t::null; desc = ""; modifier = 0; cost = 0; }
	class_t ctype; //class type
	std::string desc;
	int modifier; //amount of attack etc
	uint8_t cost; //cost, for now hopefully stays 1-4
};

#endif //__MOVE_H__
