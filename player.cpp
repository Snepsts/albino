#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "player.h"

using namespace std;

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
}

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

void player::load_game()
{
	string tname;
	int tclassvar, tlevel, thealth, tstrength, tdefense, tspeed, choicevar;

	ifstream loadfile;
	loadfile.open("save.txt");

	if(loadfile.fail())
	{
		cout << "Failed to load save file. Does a save file exist?" << endl;
		loadfile.close();
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

void player::battleinfo()
{
	cout << "Player: " << name << endl;
	cout << "Current HP: " << hp << endl;
}

void player::getinfo(int& a, int& b, int& c)
{
	strength = a; defense = b; speed = c;
}
