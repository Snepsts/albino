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

#ifndef __PLAYER_CLASS_H__
#define __PLAYER_CLASS_H__

#include <string>
#include <utility>
#include <vector>

#include "base.h"
#include "helper.h"
#include "move_battle.h"
#include "system.h"

class player_class : public base
{
public:
	class_t ctype;
	int atk_mod, def_mod, spd_mod;
	std::vector<std::pair<uint, uint>> move_list; //std::pair<move_id, level_req>
	std::string to_string();
	void operator=(const player_class& other);
};

#endif //__PLAYER_CLASS_H__
