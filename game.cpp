#include <iostream>
#include <string>
#include <cstdlib>
#include "player.h"

using namespace std;

void display_choices();

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
				cout << "Thanks for playing!" << endl;
				whilevar = false;
				break;
		}
	}while(whilevar);
	
	cout << "There will be more soon!" << endl;
	
	return 0;
}

void display_choices()
{
	cout << "List:" << endl;
	cout << "1 - New Game" << endl;
	cout << "2 - Load Game" << endl;
	cout << "3 - Display Chocies" << endl;
	cout << "4 - Exit Game" << endl;
}