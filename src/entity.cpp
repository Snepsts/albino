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

#include <vector>

#include "action.h" //make_choice
#include "entity.h" //class
#include "system.h" //make_choice

void entity::heal(const uint& plus_hp)
{
	if (hp <= 0) //if the entity is already dead
		return; //don't heal

	hp += plus_hp;

	if (hp > max_hp) //ensure hp doesn't exceed the max
		hp = max_hp;
}

action entity::make_choice(std::vector<entity*> vec, size_t self)
{
	action ret;

	ret.atype = action_t::regen;
	ret.ctype = class_t::null;
	ret.intensity = 0;
	ret.name = "Error: make_choice defaulted to entity";
	ret.desc = "null";
	ret.speed = 0;

	std::vector<size_t> choices; //code for attack choice, not heal
	for (size_t i = 0; i < vec.size(); i++) {
		if (i != self)
			choices.push_back(i);
	}

	return ret;
}
