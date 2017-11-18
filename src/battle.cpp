/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <cstdlib> //rand()
#include <iostream> //cout & cerr

#include "action.h" //action object
#include "action_queue.h" //action_queue object
#include "battle.h"
#include "monster.h" //monster object
#include "player.h" //player object

bool playerhpcheck(player& p1); //modular approach ftw

void battle(player& p1)
{
	action_queue aq;
	action pact, mact, curract;
	monster m1;
	bool playerisdead = false;
	bool monsterisdead = false;

	//init phase (check stuff)
	if (!playerhpcheck(p1))
		return; //send them back if they're dead (error handle I guess)

	p1.pbattle(); //make sure the temp stats are correctly set to default stats

	//spawn monster (end of init phase)
	m1.spawnmonster(p1.level);

	//begin battle
	while(p1.isAlive() && m1.isAlive()) {
		//choice phase
		pact = p1.choice();
		mact = m1.ai_choice();

		//calculation phase
		aq.calculation(pact, p1.speed, mact, m1.speed);
		while(!aq.empty() && p1.isAlive() && m1.isAlive()) {
			curract = aq.front();
			displayact(curract, p1); //display who is doing what to the player
			switch(curract.type) { //determine what type the action is
			case 0:
				damage(curract, p1, m1);
				break;
			case 1:
				dmodify(curract, p1, m1);
				break;
			case 2:
				omodify(curract, p1, m1);
				break;
			default:
				//error handler right here
				std::cerr << "Action passed does not have a valid type.\n";
				break;
			}

			aq.dequeue(); //once action has been completed, remove it from queue

			if (!p1.isAlive()) { //do player check
				playerisdead = true; //player ded
				break;
			}

			if (!m1.isAlive()) { //do monster check
				monsterisdead = true; //monster ded
				break;
			}
		}
		//end of turn phase
	} //end of battle

	p1.pbattle(); //ensure stats are fixed again

	if (playerisdead) { //what happens if player ded
		std::cout << "Gameover, I'll find something to put here later.\n";
		aq.clean(); //attempt to clean out the action_queue just incase
		return;
	} else if (monsterisdead) { //what happens if monster ded
		std::cout << "Victory!!!\n";
		aq.clean(); //attempt to clean out the action_queue just incase
		//will put a victory function/thing here later
		return;
	} else { //error handle for if a battle ends somehow without somebody dying
		std::cerr << "Welp, don't know how you reached here. My code logic says"
				  << "nobody died but the battle ended! Fix later :)\n";
		aq.clean(); //attempt to clean out the action_queue just incase
		return;
	}
}

bool playerhpcheck(player& p1)
{
	if (p1.isAlive())
		return true; //pass

	/* No need to run an else here since the function will have already ended
	if the player is alive, and there's nothing else to do in this function. */

	std::cout << "You're dead, you can't fight!!!\n";

	return false; //fail
}

void displayact(action act, player& p1)
{
	if (act.owner == 0)
		std::cout << p1.name;
	else if (act.owner == 1)
		std::cout << "Monster";
	else
		std::cout << "????? (invalid action owner set)"; //error handler

	std::cout << " used " << act.name << "!\n";
}

void damage(action act, player& p1, monster& m1)
{
	int dmg, mod, hmod;
	/* 	The 3 lines of code below are my way of adding some variety to the damage.
		Obviously it's not going to be like thisf forever but it's a rough draft
		of what I'm going to try to do, save major thought/changing process for
		this until we get to a "balance tweaking" stage of development */
	mod = act.modifier / 5;
	hmod = mod / 2;
	dmg = rand() % mod - hmod;

	if (act.owner == 0) { //player owns the action
		dmg = p1.tstrength + dmg;
		dmg = dmg - m1.defense;	//again, all of this code probably needs changing,
		m1.hp = m1.hp - dmg;	//but that's another "do later" sort of thing.
		std::cout << "Monster took " << dmg << " damage!\n";
	} else if (act.owner == 1) { //monster owns the action
		dmg = m1.strength + dmg;
		dmg = dmg - p1.tdefense;
		p1.hp = p1.hp - dmg;
		std::cout << p1.name << " took " << dmg << " damage!\n";
	} else //error handle
		std::cerr << "Error, the action owner was not set correctly.\n";
}

/* 	Mental note: Good way to cut down on the excessive code is to have it
	determine the subtype first, THEN the owner, as you can execute it in the
	same block, thus halfing the switch/case statements.
	...I'll do it AFTER I write the monster/player class functions */
void dmodify(action act, player& p1, monster& m1)
{
	if (act.owner == 0) { //player owns the action
		switch (act.subtype) { //determine which stat to modify
		case 0:
			p1.tstrength = p1.tstrength + act.modifier;
			break;
		case 1:
			p1.tdefense = p1.tdefense + act.modifier;
			break;
		case 2:
			p1.tspeed = p1.tspeed + act.modifier;
			break;
		default:
			std::cerr << "Error, the action subtype was not set correctly.\n";
			break; //error handle
		}
	} else if (act.owner == 1) { //monster owns the action
		switch (act.subtype) { //determine which stat to modify
		case 0:
			m1.strength = m1.strength + act.modifier;
			break;
		case 1:
			m1.defense = m1.defense + act.modifier;
			break;
		case 2:
			m1.speed = m1.speed + act.modifier;
			break;
		default:
			std::cerr << "Error, the action subtype was not set correctly.\n";
			break; //error handle
		}
	} else //error handle
		std::cerr << "Error, the action owner was not set correctly.\n";
}

void omodify(action act, player& p1, monster& m1)
{
	if (act.owner == 0) { //player owns the action
		switch (act.subtype) { //determine which stat to modify
		case 0:
			m1.strength = m1.strength - act.modifier;
			std::cout << "Monster lost " << act.modifier << " strength!\n";
			break;
		case 1:
			m1.defense = m1.defense - act.modifier;
			std::cout << "Monster lost " << act.modifier << " defense!\n";
			break;
		case 2:
			m1.speed = m1.speed - act.modifier;
			std::cout << "Monster lost " << act.modifier << " speed!\n";
			break;
		default:
			std::cerr << "Error, the action subtype was not set correctly.\n";
			break;
		}
	} else if (act.owner == 1) { //monster owns the action
		switch (act.subtype) { //determine which stat to modify
		case 0:
			p1.tstrength = p1.tstrength - act.modifier;
			std::cout << p1.name << " lost " << act.modifier << " strength!\n";
			break;
		case 1:
			p1.tdefense = p1.tdefense - act.modifier;
			std::cout << p1.name << " lost " << act.modifier << " defense!\n";
			break;
		case 2:
			p1.tspeed = p1.tspeed - act.modifier;
			std::cout << p1.name << " lost " << act.modifier << " speed!\n";
			break;
		default:
			std::cerr << "Error, the action subtype was not set correctly.\n";
			break; //error handle
		}
	} else //error handle
		std::cerr << "Error, the action owner was not set correctly.\n";
}
