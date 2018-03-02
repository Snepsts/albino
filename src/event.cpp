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

#include <random>
#include <string>

#include "event.h"
#include "monster.h"
#include "player.h"

extern std::default_random_engine rand_albino; //global random engine

event gen_event()
{
	event e;

	std::uniform_int_distribution<int> event_type(1, 10);

	int random = event_type(rand_albino);
	if (random > 0 && random < 5) { //50%
		e.type = event_t::battle; //monster will still have to be generated on the fly
	} else if (random == 6) { //10&
		e.type = event_t::loot;
	} else if (random == 7) { //10%
		e.type = event_t::shop;
	} else { //rest of the %
		e.type = event_t::nothing;
	}

	return e;
}

std::string get_event_string(const event& e)
{
	std::string ret = "null";

	switch (e.type) {
	case event_t::battle:
		if (e.untouched)
			ret = "You encountered a monster!";
		//monster m = gen_monster(p->get_level());
		break;
	case event_t::loot:
		if (e.untouched)
			ret = "You found some loot!!! Too bad I don't have items implemented yet.";
		break;
	case event_t::shop:
		if (e.untouched)
			ret = "You encountered a shop.";
		break;
	case event_t::nothing:
		if (e.untouched)
			ret = "Nothing. How disappointing.";
		break;
	default:
		ret = "Well this is embarrassing. Generation error.";
	}

	return ret;
}

bool parse_event(event& e, player* p)
{
	switch (e.type) {
	case event_t::battle:
		//monster m = gen_monster(p->get_level());
		break;
	case event_t::loot:
		break;
	case event_t::shop:
		break;
	case event_t::nothing:
		break;
	default:
		break;
	}

	e.untouched = false;

	return true;
}
