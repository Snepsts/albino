#include <iostream>
#include <cstdlib>
#include "action.h"
#include "action_queue.h"
#include "battle.h"
#include "player.h"
#include "monster.h"

bool playerhpcheck(player& p1);

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

	p1.prebattle();

	//spawn monster (end of init phase)
	m1.spawnmonster(p1.level);

	//begin battle
	while(p1.isAlive() && m1.isAlive())
	{
		//choice phase
		pact = p1.choice();
		mact = m1.ai_choice();

		//calculation phase
		aq.calculation(pact, p1.speed, mact, m1.speed);
		while(!aq.empty() && p1.isAlive() && m1.isAlive())
		{
			curract = aq.front();
			displayact(curract, p1);
			switch(curract.type)
			{
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
				std::cerr << "Action passed does not have a valid type.\n";
				break;
			}

			aq.dequeue();

			if (!p1.isAlive()) //do player check
			{
				playerisdead = true;
				break;
			}

			if (!m1.isAlive()) //do monster check
			{
				monsterisdead = true;
				break;
			}
		}
		//end of turn phase
	} //end of battle
	if (playerisdead)
	{
		std::cout << "Gameover, I'll find something to put here later.\n";
		aq.clean();
		return;
	}
	else if (monsterisdead)
	{
		std::cout << "Victory!!!\n";
		aq.clean();
		//will put a victory function/thing here later
		return;
	}
	else
	{
		std::cerr << "Welp, don't know how you reached here. Fix later :)\n";
		aq.clean();
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
		std::cout << p1.name << " ";
	else if (act.owner == 1)
		std::cout << "Monster ";
	else
		std::cout << "????? ";

	std::cout << "used " << act.name << "!\n";
}

void damage(action act, player& p1, monster& m1)
{
	int dmg, mod, hmod;
	mod = act.modifier / 5;
	hmod = mod / 2;
	dmg = rand() % mod - hmod;

	if (act.owner == 0)
	{
		dmg = p1.tstrength + dmg;
		dmg = dmg - m1.defense;
		m1.hp = m1.hp - dmg;
		std::cout << "Monster took " << dmg << " damage!\n";
	}
	else if (act.owner == 1)
	{
		dmg = m1.strength + dmg;
		dmg = dmg - p1.tdefense;
		p1.hp = p1.hp - dmg;
		std::cout << p1.name << " took " << dmg << " damage!\n";
	}
	else
		std::cerr << "Error, the action owner was not set correctly.\n";
}

void dmodify(action act, player& p1, monster& m1)
{
	if (act.owner == 0)
	{
		switch (act.subtype)
		{
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
			break;
		}
	}
	else if (act.owner == 1)
	{
		switch (act.subtype)
		{
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
			break;
		}
	}
	else
		std::cerr << "Error, the action owner was not set correctly.\n";
}

void omodify(action act, player& p1, monster& m1)
{
	if (act.owner == 0)
	{
		switch (act.subtype)
		{
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
	}
	else if (act.owner == 1)
	{
		switch (act.subtype)
		{
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
			break;
		}
	}
	else
		std::cerr << "Error, the action owner was not set correctly.\n";
}
