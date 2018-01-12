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

#ifndef __ENTITY_H__
#define __ENTITY_H__

class entity
{
public:
	int get_max_hp() { return max_hp; }
	int get_hp() { return hp; }
	int get_attack() { return attack; }
	int get_defense() { return defense; }
	int get_speed() { return speed; }
	uint get_level() { return level; }
	bool is_alive() { return (hp > 0); }
	void heal(const uint& plus_hp);
	void damage(const uint& minus_hp) { hp -= minus_hp; }

protected:
	int max_hp; //max hp
	int hp; //current hp
	int attack; //determines how much attacks do to others
 	int defense; //determines how little attacks do to self
 	int speed; //determines who goes first
	uint level; //determines xp and other things
};

#endif //__ENTITY_H__
