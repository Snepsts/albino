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

#include "action.h" //make_choice
#include "entity.h" //class
#include "system.h" //make_choice

void entity::heal(uint plus_hp)
{
	if (hp <= 0) //if the entity is already dead
		return; //don't heal

	hp += plus_hp;

	if (hp > max_hp) //ensure hp doesn't exceed the max
		hp = max_hp;
}

action entity::make_choice()
{
	action ret;
	ret.atype = heal;
	ret.ctype = null;
	ret.intensity = 0;
	ret.owner = player;
	ret.name = "Error: make_choice defaulted to entity";
	ret.desc = "null";
	ret.speed = 0;

	return ret;
}
