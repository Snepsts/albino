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
	void battleinfo();
	void getinfo(int& a, int& b, int& c)
	int hp;

private:
	int health;
	int strength;
	int defense;
	int speed;
	int level;
}

#endif
