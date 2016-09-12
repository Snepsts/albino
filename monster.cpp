#include "monster.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Action definitions
/* Definition layout:
	action action_name = {type, subtype, modifier, owner, name, desc}

	For reference:
	type is what kind of action it is
	subtype is what it modifies (if it's a modifier instead of attack)
	modifier is how much it modifies (damage/strength/defense/speed)
	owner is who owns it (0 = player, 1 = monster)
	name is it's name and desc is it's description

	For example:
	attack.type = 0 (damaging/attacking/offensive)
	attack.subtype = 0 (would modify strength if it was of type 1 or 2)
	attack.modifier = 10 (10 is the modifier for damage, or would be how much
						strength is added/subtracted if it was of type 1/2)
	attack.owner = 1 (monster is the "object" that "owns" this action)
	attack.name = "Attack!"
	attack.desc = " "
*/
action mattack = {0, 0, 10, 1, "Slash", " "};
action mboost_def = {1, 1, 3, 1, "Adjust Claws", " "};
action mboost_str = {1, 0, 3, 1, "Focus", " "};
action mboost_spd = {1, 2, 3, 1, "Agility", " "};
action mstr_decay = {2, 0, 2, 1, "Shield Bash", " "};

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

bool monster::isAlive()
{
	return (hp > 0);
}

action monster::ai_choice()
{
	return mattack;
}
