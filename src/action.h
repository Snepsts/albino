/* albino
Copyright (C) 2017 Michael Ranciglio

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

/* This is the action header to define the action struct for all entities to see */

#ifndef __ACTION_H__
#define __ACTION_H__

#include <string> //string

/* action structure
	This structure represents the actions (selections) made by monsters/players.
	Type: This represents what kind of action it is.
		0 = Attack/Offensive
		1 = Stat Boost/Defensive
		2 = Stat Harm/Offensive
		3 = Use Item (Heal and probably some other stuff too) NOT SUPPORTED YET
	Subtype: This represents what stat will be modified.
		0 = Strength
		1 = Defense
		2 = Speed
	Modifier: This represents how much will be modified
		- In terms of attack, it'll be the base value (higher is better)
		- In terms of Stat Boost/Harm, it's how much the stat is raised/lowered
		- In terms of item, it'll specifically pertain to that item (more later)
	Owner: This represents who is doing the move
		0 = player
		1 = monster
	Name: This will be a basic name for the attack.
	Desc: The description for the attack, not used currently but will make a
			standard for it eventually.
*/

struct action
{
	int type;
	int subtype;
	int modifier;
	int owner;
	std::string name;
	std::string desc;
};

#endif
