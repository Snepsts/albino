#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "battle.h"

using std::cout;
using std::cin;

void display_choices();

//Note to self keep main clean, it's really easy to clutter it up

int main()
{
	srand(time(0)); //Ensure number is random everytime

	player p1;
	int choicevar;
	bool whilevar;

	do
	{
		cout << "What would you like to do?\n";
		cout << "1 - New Game\n";
		cout << "2 - Load Game\n";
		cout << "3 - Exit Game\n";

		cin >> choicevar;

		switch(choicevar)
		{
		case 1:
			p1.choose_class();
			whilevar = false;
			break;

		case 2:
			if(p1.load_game()) //if it is successful in loading the file, exit
				whilevar = false;
			else //otherwise stay in the initial loop
				whilevar = true;
			break;

		case 3:
			cout << "Thank you for playing!\n";
			whilevar = false;
			return 0;
			break;

		default:
			cout << "Not a valid option.\n";
			whilevar = true;
			break;
		}
	}while(whilevar);

	do
	{
		display_choices();
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
			cout << "Thanks for playing!\n";
			whilevar = false;
			break;

		case 5:
			cout << "Prepare for battle!\n";
			battle(p1);
			whilevar = true;
			break;

		default:
			cout << "Not a vaild option.\n";
			whilevar = true;
			break;
		}
	}while(whilevar);

	cout << "There will be more soon!\n";

	return 0;
}

void display_choices()
{
	cout << "What would you like to do now?\n";
	cout << "1 - Save Game\n";
	cout << "2 - Load Game\n";
	cout << "3 - Display Character Information\n";
	cout << "4 - Exit Game\n";
	cout << "5 - Battle (Alpha mode)\n";
}
