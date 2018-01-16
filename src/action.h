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

#include "system.h"

#include <string> //string

/* action structure
	This structure represents the actions (selections) made by monsters/players.
	AType: Action type, one of three options:
	 - Attack: Does damage to the opposing entity.
	 - Heal: Adds health or removes negative status effects from the entity.
	 - Item: Currently unused ask me about it later.
	CType: Class type, one of four options:
	 - Null: No specific class type or doesn't apply.
	 - Melee: Does extra damage to ranged type entities.
	 - Ranged: Does extra damage to magic type entities.
	 - Magic: Does extra damage to melee type entities.
	Intensity: Amplifies the damage an attack does.
	Owner: This represents who is doing the move
		0 = player
		1 = monster
	Name: This will be a basic name for the attack.
	Desc: The description for the attack, not used currently but will make a
			standard for it eventually.
*/

struct action
{
	action_t atype;
	class_t ctype;
	ushort intensity;
	owner_t owner;
	int speed;
	std::string name;
	std::string desc;
};

#endif
