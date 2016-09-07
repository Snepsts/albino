/* Currently the enemy or thing the player fights is called "monster" this is
subject to change in the future, but for now here's the definition */

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "battle.h"
#include "action.h"

class player;

class monster
{
public:
	monster();
	void spawnmonster(int lvl);
	void displaymonster();
	bool isAlive();
	action ai_choice();
	friend void battle(player& p1);
	friend void damage(action act, player& p1, monster& m1);
	friend void dmodify(action act, player& p1, monster& m1);
	friend void omodify(action act, player& p1, monster& m1);

private:
	int health;
	int hp;
	int strength;
	int defense;
	int speed;
	int level;
};

#endif
