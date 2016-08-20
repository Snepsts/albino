#include "monster.h"
#include <iostream>
#include <cstdlib>

using namespace std;

monster::monster()
{
	health = 10; defense = 3; strength = 3; speed = 3; level = 0; hp = health;
}

void monster::spawnmonster(int lvl)
{
	srand(time(0)); //Ensure number is random everytime
	int lvlvar, w, x, y, z;
	w = rand() % 5;
	x = rand() % 3;
	y = rand() % 3;
	z = rand() % 3;
	health = health + w + 1;
	strength = strength + x + 1;
	defense = defense + y + 1;
	speed = speed + z + 1;
	lvlvar = strength + defense + speed;
	level = lvlvar/12;
	hp = health;
	displaymonster();
}

void monster::displaymonster()
{
	cout << "You have encountered a monster that is level " << level << "!" << endl;
}
