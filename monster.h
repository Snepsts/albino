/* Currently the enemy or thing the player fights is called "monster" this is
subject to change in the future, but for now here's the definition */

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "battle.h"
#include "action.h"

class player; //this is a "forward declaration" (or something like that)
              //basically allows us to use the "friend" functions
class monster
{
public:
	/* default constructor
		Task: To create the "monster" object. Default values are set here and
		can be adjusted as seen fit. */
	monster();

	/* function spawnmonster
		Task: To decide the values to add to the stats. Can and will be adjusted
		to scale with player level, but that'll be later. (I sure do say that often)

		This function takes some rand stuff and adds them to the base stats.
		Right now it uses w, x, y, and z. Those correspond to health, strength,
		defense, and speed respectively. I'm not really sure why I didn't use a
		b c etc instead since that is more flexible but whatever.

		It also sets the hp to the health max since there's not really a better
		way to implement that atm. Also it calls displaymonster at the end. Since
		for now that's the only time we'll use it anyway is after a spawn. */
	void spawnmonster(int lvl);

	/* function displaymonster
		For now this is the text that introduces the monster. However, I will
		change this later as well to be a stat display probably... maybe. */
	void displaymonster();

	/* function isAlive
		Very basic bool, but makes for an easy "ensure all entities are alive"
		check */
	bool isAlive();

	/* function ai_choice
		Not done yet, I have to fix my formatting for all the class .cpp
		documentation anyway... //do later */
	action ai_choice();

	//Friend functions for battle
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
