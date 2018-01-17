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

#include <fstream> //global debug log
#include <string>
#include <vector> //battle_main

#include "action.h" //action object
#include "action_queue.h" //action_queue object
#include "battle.h"
#include "entity.h" //entity base class for player & monster
#include "monster.h" //monster object
#include "player.h" //player object

extern std::ofstream debug; //tell c++ debug exists in global but in another file

void do_action(action act);
void battle_attack(action act, std::vector<entity*> vec);
entity* get_player(std::vector<entity*> vec);
entity* get_monster(std::vector<entity*> vec);

void battle_main(std::vector<entity*> vec)
{
	debug << "battle_main called.\n";
	action_queue aq;

	if (vec.size() != 2) {
		debug << "Error: Not enough or too many entities in battle_main: " << vec.size() << " entries.\n";
		return; //exit
	}

	for (size_t i = 0; i < 2; i++) {
		if (dynamic_cast<player*>(vec[i])) {
			debug << "Casting vec[" << i << "] to player.\n";
			aq.enqueue((dynamic_cast<player*>(vec[i]))->make_choice(vec, i));
		} else if (dynamic_cast<monster*>(vec[i])) {
			debug << "Casting vec[" << i << "] to monster.\n";
			aq.enqueue((dynamic_cast<monster*>(vec[i]))->make_choice(vec, i));
		} else {
			debug << "Error: vec[" << i << "] cannot be cast to player or monster.\n";
			return; //exit
		}
	}

	debug << "Sorting action_queue.\n";
	aq.sort(); //ensure actions are in order

	debug << "Beginning action sequence.\n";
	while (!aq.empty()) {
		//do action
		aq.dequeue();
	}
}

void battle_action_switch(action act, std::vector<entity*> vec)
{
	switch (act.atype) {
		case action_t::attack:
			battle_attack(act, vec);
			break;
		case action_t::regen:
			break;
		case action_t::item:
			break;
		default:
			debug << "Error: No action_t specified.\n";
			return; //exit
	}
}

void battle_attack(action act, std::vector<entity*> vec)
{
	entity* attacker = vec[act.owner];
	entity* attackee = vec[act.target];

	std::string msg = attacker->get_name() + " attacks " + attackee->get_name() + " with " + act.name + "!\n";
	//print msg
	int atk = attacker->get_attack();
	int def = attackee->get_defense();
	uint dmg = (uint)(atk * act.intensity - def);
	attackee->damage(dmg);
	msg = attackee->get_name() + " takes " + std::to_string(dmg) + " damage!\n";
	//print msg
	//check for deaths
}

entity* get_player(std::vector<entity*> vec)
{
	debug << "Searching for player...\n";
	for (size_t i = 0; i < vec.size(); i++) {
		if (dynamic_cast<player*>(vec[i])) {
			debug << "Found player! Returning it.\n";
			return vec[i];
		}
	}

	debug << "Error: Could not find a player in the vector.\n";
	exit(1);
}

entity* get_monster(std::vector<entity*> vec)
{
	debug << "Searching for monster...\n";
	for (size_t i = 0; i < vec.size(); i++) {
		if (dynamic_cast<player*>(vec[i])) {
			debug << "Found monster! Returning it.\n";
			return vec[i];
		}
	}

	debug << "Error: Could not find a monster in the vector.\n";
	exit(1);
}
