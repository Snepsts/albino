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

#include "event.h"
#include "monster.h"

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

monster gen_monster(uint level)
{
	monster m(level);



	return m;
}
