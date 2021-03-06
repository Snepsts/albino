/* albino
Copyright (C) 2017-2018 Michael Ranciglio

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

/* Currently the enemy or thing the player fights is called "monster" this is
subject to change in the future, but for now here's the definition */

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "action.h" //action object
#include "entity.h" //base class

class monster : public entity
{
public:
	/* default constructor
		Task: To create the "monster" object. Default values are set here and
		can be adjusted as seen fit. */
	monster(uint lvl);
};

#endif //__MONSTER_H__
