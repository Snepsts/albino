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

#include <map> //p_class
#include <string> //string

#include "player.h"
#include "player_class.h"

extern std::map<uint, player_class*> p_classes;

player::player()
{
	max_hp = 10; attack = 5; defense = 5; speed = 5; level = 0; name = " "; hp = max_hp;
}

void player::level_up()
{
	level++;
}

void player::set_class(const uint& classvar)
{
	//std::pair<uint,
	p_class = (*p_classes.find(classvar)->second);
}
