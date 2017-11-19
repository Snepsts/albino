/* albino
Copyright (C) 2017 Michael Ranciglio

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

#include <cstdlib> //rand()
#include <fstream> //if & of streams (save_game and load_game)
#include <iostream> //cin & cout
#include <string> //string

#include "player.h"

using std::cout;
using std::cin;

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
	attack.modifier = 20 (20 is the modifier for damage, or would be how much
						strength is added/subtracted if it was of type 1/2)
	attack.owner = 0 (player is the "object" that "owns" this action)
	attack.name = "Attack!"
	attack.desc = " "
*/
action attack = {0, 0, 10, 0, "Attack!", " "};
action boost_def = {1, 1, 3, 0, "Adjust Shield", " "};
action boost_str = {1, 0, 3, 0, "Focus", " "};
action boost_spd = {1, 2, 3, 0, "Agility", " "};
action decay_str = {2, 0, 2, 0, "Shield Bash", " "};

player::player()
{
	health = 10; strength = 5; defense = 5; speed = 5; classvar = 0; level = 0; name = " "; hp = health;
}

void player::choose_class()
{
	int choicevar, choicevar2;
	bool whilevar;

	cout << "Please enter your name: ";
	cin.ignore();
	getline(cin, name);

	do {
		cout << "Choose your class:\n";
		cout << "1 - Knight\n";
		cout << "2 - Placeholder\n";
		cout << "3 - Placeholder\n";

		cin >> choicevar;

		switch(choicevar) { //yeah this big ugly mess needs some revising
		case 1:
			cout << "You have chosen Knight. The knight's stats are: \n";
			cout << "Attack+++\n";
			cout << "Defense++\n";
			cout << "Speed---\n";
			cout << "Are you sure? (Press 1 to confirm, 0 to decline)\n";
			cin >> choicevar2;

			if(choicevar2 == 1) {
				cout << "You have confirmed knight.\n";

				classvar = 1;
				strength = strength + 3;
				defense = defense + 2;
				speed = speed - 3;

				level_up();

				whilevar = false;
			} else {
				cout << "Selection as knight canceled.\n";
				whilevar = true;
			}

			break;
		default:
			cout << "Sorry, that is not a valid choice, please try again.\n";

			whilevar = true;
			break;
		}
	} while (whilevar);
}

void player::level_up() //Ohhh man this is disgusting right now
{
	int x, y, z;

	level++;

	cout << name << " has leveled up to level " << level << '\n';

	switch(classvar) {
	case 1:
		for (int a = 0; a < 3;) { //Three stats per level_up call
			x = rand() % 20; //Gens number between 0-19

			if (0 <= x && x <= 9) { //~50% chance of strength up per try
				strength++;
				cout << "Strength increased by 1! Strength is now " << strength << "!\n";
				a++;
			}

			if (a < 3) { //Check if limit of 3 stats is hit
				y = rand() % 30; //Gens number between 0-29

				if (0 <= y && y <= 9) { //~33% chance of defense per try
					defense++;
					cout << "Defense has increased by 1! Defense is now " << defense << "!\n";
					a++;
				}
			}

			if (a < 3) { //Check if limit of 3 stats is hit
				z = rand() % 50; //Gens number between 0-49

				if (0 <= z && z <= 9) { //~20% chance of speed per try
					speed++;
					cout <<  "Speed has increased by 1! Speed is now " << speed << "!\n";
					a++;
				}
			}
		}

		break;
	default:
		cout << "Something went wrong, exiting program.\n";

		exit(1); //is this portable?
		break;
	}
	hp = health;
}

void player::display()
{
	cout << name << "'s stats:\n";

	switch(classvar) { //there needs to be something better than switch
	case 1:            //statements to accomplish what we're trying to do here
		cout << "Class: Knight \n";
		break;
	default:
		cout << "Something went wrong, exiting program.\n";

		exit(1);
		break;
	}

	cout << "Level: " << level << '\n';
	cout << "Health: " << health << '\n';
	cout << "Strength: " << strength << '\n';
	cout << "Defense: " << defense << '\n';
	cout << "Speed: " << speed << '\n';
}

void player::save_game() //can probably make this a bool too
{
	int choicevar;
	std::ofstream savefile;

	cout << "Save character " << name << "?\n";

	display();

	cout << "Press 1 to confirm, 0 to cancel.\n";
	cin >> choicevar;

	switch(choicevar) {
	case 0:
		cout << "Canceling...\n";
		break;
	case 1:
		savefile.open("save.txt");

		if (savefile.fail()) {
			cout << "Save failed.\n";
			savefile.close();
		} else {
			cout << "Saving";
			savefile << name << "\n\n";
			savefile << classvar << "\n\n";
			cout << ".";
			savefile << level << "\n\n";
			savefile << health << "\n\n";
			cout << ".";
			savefile << strength << "\n\n";
			savefile << defense << "\n\n";
			cout << ".";
			savefile << speed << '\n';
			cout << " Done!\n";
		}

		break;
	default:
		cout << "Invalid selection. Canceling...\n";
		break;
	}
}

bool player::load_game()
{
	std::string temp_name;
	int temp_classvar, temp_level, temp_health, temp_strength, temp_defense, temp_speed, choicevar;

	std::ifstream loadfile;
	loadfile.open("save.txt");

	if(loadfile.fail()) {
		cout << "Failed to load save file. Does a save file exist?\n";
		loadfile.close();
		return false;
	} else {
		//load everything into temporary variables to preview the stats
		loadfile >> temp_name; loadfile >> temp_classvar; loadfile >> temp_level;
		loadfile >> temp_health; loadfile >> temp_strength;
		loadfile >> temp_defense; loadfile >> temp_speed;

		cout << "Name: " << temp_name << '\n';
		if (temp_classvar == 1)
			cout << "Class: Knight\n";
		else if (temp_classvar == 2)
			cout << "Class: Undefined\n";
		else if (temp_classvar == 3)
			cout << "Class: Undefined\n";
		else
			cout << "Class: Error\n";

		cout << "Level: " << temp_level << '\n';
		cout << "Health: " << temp_health << '\n';
		cout << "Stength: " << temp_strength << '\n';
		cout << "Defense: " << temp_defense << '\n';
		cout << "Speed: " << temp_speed << '\n';

		loadfile.close();
		loadfile.ignore();
		loadfile.clear();

		cout << "Load this file? (0 = No, 1 = Yes)\n";
		cin >> choicevar;

		if (choicevar == 0) {
			cout << "Cancelling...\n";
			return false;
		} else {
			name = temp_name;
			classvar = temp_classvar;
			level = temp_level;
			health = temp_health;
			strength = temp_strength;
			defense = temp_defense;
			speed = temp_speed;

			cout << "Load finished!!!\n";
			return true;
		}
	} //end initial else
}

bool player::isAlive()
{
	return (hp > 0);
}

void player::display_actions()
{
	cout << "1 - " << attack.name << '\n'
	     << "2 - " << boost_def.name << '\n'
	     << "3 - " << boost_str.name << '\n'
	     << "4 - " << boost_spd.name << '\n'
	     << "5 - " << decay_str.name << '\n'
	     << "Any other number - Display choices again.\n";
}

void player::pbattle()
{
	tstrength = strength;
	tdefense = defense;
	tspeed = speed;
}

action player::choice()
{
	int choicevar;
	bool whilevar;

	cout << "what will you do?\n";
	do {
		display_actions();

		cin >> choicevar;
		if (0 < choicevar && choicevar < 6)
			whilevar = false;
		else
			whilevar = true;
	} while (whilevar);

	switch (choicevar) {
	case 1:
		return attack;
		break;
	case 2:
		return boost_def;
		break;
	case 3:
		return boost_str;
		break;
	case 4:
		return boost_spd;
		break;
	case 5:
		return decay_str;
		break;
	default:
		return attack;
		break;
	}
}
