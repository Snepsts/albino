/* Currently the enemy or thing the player fights is called "monster" this is
subject to change in the future, but for now here's the definition */

#ifndef __MONSTER_H__
#define __MONSTER_H__

class monster
{
public:
	monster();
	void spawnmonster(int lvl);
	void displaymonster();

private:
	int health;
    int hp;
	int strength;
	int defense;
	int speed;
	int level;
};

#endif
