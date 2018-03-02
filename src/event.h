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

#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

#include "player.h"

enum class event_t { nothing, battle, shop, loot }; //TODO: Add more event types

struct event
{
	event_t type;
	std::string msg;
	bool untouched = true;
};

event gen_event();
std::string get_event_string(const event& e);
bool parse_event(event& e, player* p);

#endif //__EVENT_H__
