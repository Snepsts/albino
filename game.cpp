#include <iostream>
#include <string>
#include <cstdlib>
#include "player.h"
#include "monster.h"

using namespace std;

void display_choices();

void battle(player& p1, monster& m1);

int main()
{
	srand(time(0)); //Ensure number is random everytime

	player p1;
	int choicevar;
	bool whilevar;

	cout << "What would you like to do?" << endl;
	cout << "List:" << endl;
	cout << "1 - New Game" << endl;
	cout << "2 - Load Game" << endl;
	cout << "3 - Exit Game" << endl;

	do
	{
		cin >> choicevar;

		switch(choicevar)
		{
		case 1:
			p1.choose_class();
			whilevar = false;
			break;

		case 2:
			p1.load_game();
			whilevar = false;
			break;

		case 3:
			cout << "Thank you for playing!" << endl;
			whilevar = false;
			exit(0);
			break;

		default:
			cout << "Not a valid option." << endl;
			whilevar = true;
			break;
		}
	}while(whilevar);

	cout << "What would you like to do now?" << endl;
	display_choices();

	do
	{
		cin >> choicevar;

		switch(choicevar)
		{
		case 1:
			p1.save_game();
			whilevar = true;
			break;

		case 2:
			p1.load_game();
			whilevar = true;
			break;

		case 3:
			p1.display();
			whilevar = true;
			break;

		case 4:
			display_choices();
			whilevar = true;
			break;

		case 5:
			cout << "Thanks for playing!" << endl;
			whilevar = false;
			break;

		default:
			cout << "Not a vaild option." << endl;
			whilevar = true;
			break;
		}
	}while(whilevar);

	cout << "There will be more soon!" << endl;

	return 0;
}

void display_choices()
{
	cout << "List:" << endl;
	cout << "1 - Save Game" << endl;
	cout << "2 - Load Game" << endl;
	cout << "3 - Display Character Information" << endl;
	cout << "4 - Display Choices" << endl;
	cout << "5 - Exit Game" << endl;
}

void battle(player& p1, monster& m1)
{
	int gofirst, pstr, pdef, pspd, mstr, mdef, mspd;
	m1.spawnmonster();
	do
	{
		p1.battleinfo();
		m1.battlefino();
		switch(battlemenu();)
		{
		case 1:
			p1.getinfo(pstr, pdef, pspd);
			m1.getinfo(mstr, mdef, mspd);
			gofirst = pspd - mspd;

			if (gofirst > 0)
			{
				m1.hp - damagephase(pstr, mdef);
				cout << "Monster takes " << damagephase(pstr, mdef) << " damage!" << endl;
				if (m1.hp > 0)
				{
					p1.hp - damagephase(mstr, pdef);
					cout << "Player takes " << damagephase(mstr, pdef) << " damage!" << endl;
				}
			}

			else if (gofirst <= 0)
			{
				p1.hp - damagephase(mstr, pdef);
				cout << "Player takes " << damagephase(mstr, pdef) << " damage!" << endl;
				if (p1.hp > 0)
				{
					m1.hp - damagephase(pstr, mdef);
					cout << "Monster takes " << damagephase(pstr, mdef) << " damage!" << endl;
				}
			}

			else
			{
				cout << "Error: Problem in speed calculation." << endl;
				exit(1);
			}
			break;

		default:
			cout << "Error: Something went wrong with selecting your battle choice." << endl;
			exit(1);
		}
	}while(p1.hp > 0 && m1.hp > 0);

	if (p1.hp <= 0)
	{
		cout << "You lost, game over I guess." << endl;
		cout << "I'll figure out how to handle this later. For now just leave the game." << endl;
	}

	else if (m1.hp <= 0)
	{
		cout << "Congrats! You defeated the monster!" << endl;
		cout << "This is the part where I'd give you xp, but I haven't implemented that yet. So yeah." << endl;
	}
}

int battlemenu()
{
	int choicevar;
	cout << "What would you like to do?" << endl;
	cout << "1 - Attack" << endl;
	cout << "2 - Placeholder" << endl;
	cout << "3 - Another Placeholder" << endl;
	cout << "4 - You really just have to attack" << endl;
	do
	{
		cin >> choicevar;
	}while(choicevar < 1 || choicevar > 4);

	return choicevar;
}

int damagephase(int 1str, int 2def)
{
	int dmg;
	dmg = 1str - (2def/1str);
	if (dmg <= 0)
		dmg = 1;
	return dmg;
}
