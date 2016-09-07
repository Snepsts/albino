#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "player.h"

using namespace std;

//IMPORTANT
//NEXT THING I DO: Bring the old summaries from player/monster (in the cpp)
//to the header file. ALSO DO FORMATTING CORRECTLY
//IMPORTANT

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
action jew = attack;

/* Constructor
	Creates the player object with some base stats, will be adjusting these later :)
*/
player::player()
{
	health = 10; strength = 5; defense = 5; speed = 5; classvar = 0; level = 0; name = " "; hp = health;
}

/* Choose_class
	This is the create character/new game function for now, it does the following:
		-Allows the player to name himself/herself
		-Gives the player a choice between X classes
		-Overwrites the name and the class. Will probably seperate these later.
*/
void player::choose_class()
{
	int choicevar, choicevar2;
	bool whilevar;

	cout << "Please enter your name: ";
	cin.ignore();
	getline(cin, name);

	do
	{
		cout << "Choose your class: " << endl;
		cout << "1 - Knight" << endl;
		cout << "2 - Mage" << endl;
		cout << "3 - Rogue" << endl;

		cin >> choicevar;

		switch(choicevar)
		{
		case 1:
			cout << "You have chosen Knight. The knight's stats are: " << endl;
			cout << "Attack+++" << endl;
			cout << "Defense++" << endl;
			cout << "Speed---" << endl;
			cout << "Are you sure? (Press 1 to confirm, 0 to decline)" << endl;
			cin >> choicevar2;

			if(choicevar2 == 1)
			{
				cout << "You have confirmed knight." << endl;

				classvar = 1;
				strength = strength + 3;
				defense = defense + 2;
				speed = speed - 3;

				level_up();

				whilevar = false;
			}

			else
			{
				cout << "Selection as knight canceled." << endl;

				whilevar = true;
			}

			break;

		default:
			cout << "Sorry, that is not a valid choice, please try again." << endl;

			whilevar = true;
			break;
		}
	} while(whilevar);
}

/* Level_up
	This function ups the level variable and randomly ups stats depending on the class
		==============================================================
			todo: simplify the "algorithm" to require less code
		==============================================================
*/
void player::level_up()
{
	int x, y, z;

	level++;

	cout << name << " has leveled up to level " << level << endl;

	switch(classvar)
	{
	case 1:
		for (int a = 0; a < 3;) //Three stats per level_up call
		{
			x = rand() % 20; //Gens number between 0-19

			if (0 <= x && x <= 9) //~50% chance of strength up per try
			{
				strength++;
				cout << "Strength increased by 1! Strength is now " << strength << "!" << endl;
				a++;
			}

			if (a < 3) //Check if limit of 3 stats is hit
			{
				y = rand() % 30; //Gens number between 0-29

				if (0 <= y && y <= 9) //~33% chance of defense per try
				{
					defense++;
					cout << "Defense has increased by 1! Defense is now " << defense << "!" << endl;
					a++;
				}
			}

			if (a < 3) //Check if limit of 3 stats is hit
			{
				z = rand() % 50; //Gens number between 0-49

				if (0 <= z && z <= 9) //~20% chance of speed per try
				{
					speed++;
					cout <<  "Speed has increased by 1! Speed is now " << speed << "!" << endl;
					a++;
				}
			}
		}
		break;

	default:
		cout << "Something went wrong, exiting program." << endl;

		exit(1);
		break;
	}
	hp = health;
}

/* Display
	Displays the player's stats with their name and class.
*/
void player::display()
{
	cout << name << "'s stats: " << endl;
	switch(classvar)
	{
	case 1:
		cout << "Class: Knight " << endl;
		break;

	default:
		cout << "Something went wrong, exiting program." << endl;

		exit(1);
		break;
	}

	cout << "Level: " << level << endl;
	cout << "Health: " << health << endl;
	cout << "Strength: " << strength << endl;
	cout << "Defense: " << defense << endl;
	cout << "Speed: " << speed << endl;
}

/* save_game
	Okay, here's where the coding starts to get kinda sloppy.
	So it saves stats in a certain order to the file and the load_game
	function will load them in that same order, however everytime we add a new
	stat it will require changes in BOTH functions, so...
		todo: find a better method to save/load game stats
*/
void player::save_game()
{
	int choicevar;
	ofstream savefile;

	cout << "Save character " << name << "?" << endl;

	display();

	cout << "Press 1 to confirm, 0 to cancel." << endl;
	cin >> choicevar;

	switch(choicevar)
	{
	case 0:
		cout << "Canceling..." << endl;
		break;

	case 1:
		savefile.open("save.txt");

		if (savefile.fail())
		{
			cout << "Save failed." << endl;
			savefile.close();
		}

		else
		{
			cout << "Saving";
			savefile << name << endl << endl;
			savefile << classvar << endl << endl;
			cout << ".";
			savefile << level << endl << endl;
			savefile << health << endl << endl;
			cout << ".";
			savefile << strength << endl << endl;
			savefile << defense << endl << endl;
			cout << ".";
			savefile << speed << endl;
			cout << " Done!" << endl;
		}
		break;

	default:
		cout << "Invalid selection. Canceling..." << endl;
		break;
	}
}

/* Load_game
	See "Save_game"
*/
void player::load_game()
{
	string tname;
	int tclassvar, tlevel, thealth, tstrength, tdefense, tspeed, choicevar;

	ifstream loadfile;
	loadfile.open("save.txt");

	if(loadfile.fail())
	{
		cout << "Failed to load save file. Does a save file exist?\nCreating new character..." << endl;
		loadfile.close();
		choose_class(); //ensure if the load file doesn't exist that the player creates one
	}

	else
	{
		loadfile >> tname; loadfile >> tclassvar; loadfile >> tlevel; loadfile >> thealth; loadfile >> tstrength; loadfile >> tdefense; loadfile >> tspeed;
		cout << "Name: " << tname << endl;
		if (tclassvar == 1)
		cout << "Class: Knight" << endl;
		else if (tclassvar == 2)
		cout << "Class: ..wtf" << endl;
		else if (tclassvar == 3)
		cout << "Class: ..wtf" << endl;
		else
		cout << "Class: Error" << endl;
		cout << "Level: " << tlevel << endl;
		cout << "Health: " << thealth << endl;
		cout << "Stength: " << tstrength << endl;
		cout << "Defense: " << tdefense << endl;
		cout << "Speed: " << tspeed << endl;
		loadfile.close();
		loadfile.ignore();
		loadfile.clear();
		cout << "Load this file? (0 = No, 1 = Yes)" << endl;
		cin >> choicevar;

		if (choicevar == 0)
		{
			cout << "Cancelling..." << endl;
		}

		else
		{
			name = tname;
			classvar = tclassvar;
			level = tlevel;
			health = thealth;
			strength = tstrength;
			defense = tdefense;
			speed = tspeed;

			cout << "Load finished!!!" << endl;
		}
	}
}

/* isAlive
	Very basic bool, but makes for an easy "ensure all entities are alive" check
*/
bool player::isAlive()
{
	return (hp > 0);
}

void player::display_actions()
{
	cout << "1 - " << attack.name << "\n"
		 << "2 - " << boost_def.name << "\n"
		 << "3 - " << boost_str.name << "\n"
		 << "4 - " << boost_spd.name << "\n"
		 << "5 - " << decay_str.name << "\n"
		 << "Any other number - Display choices again.\n";
}

void player::prebattle()
{
	tstrength = strength;
	tdefense = defense;
	tspeed = speed;
}

void player::postbattle()
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
	do
	{
		display_actions();
		cin >> choicevar;
		if (0 < choicevar && choicevar < 6)
			whilevar = false;
		else
			whilevar = true;
	}while(whilevar);

	switch (choicevar)
	{
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

void player::testattack()
{
	cout << attack.name << '\n' << attack.type << '\n' << attack.subtype << '\n' << attack.modifier << '\n';
}
