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

#include <vector> //battle_main

#include "action.h" //action object
#include "action_queue.h" //action_queue object
#include "battle.h"
#include "entity.h" //entity base class for player & monster
#include "monster.h" //monster object
#include "player.h" //player object

void battle_main(std::vector<entity*> vec)
{
	action_queue aq;

	if (vec.size() != 2) {
		//error not enough or too many entities
		return; //exit
	}

	for (int i = 0; i < 2; i++) {
		if (dynamic_cast<player*>(vec[i])) {
			aq.enqueue((dynamic_cast<player*>(vec[i]))->make_choice());
		} else if (dynamic_cast<monster*>(vec[i])) {
			aq.enqueue((dynamic_cast<monster*>(vec[i]))->make_choice());
		} else {
			//error
		}
	}

	aq.sort(); //ensure actions are in order

	while (!aq.empty()) {
		//do action
		aq.dequeue();
	}
}
