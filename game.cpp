#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void choose_class(int &classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level); //choose class function

void level_up(int classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level); //level up function

void display_char(int classvar, int char_strength, int char_defense, int char_speed, int char_level, double char_health, string char_name); //display character information function

int main()
{
	double char_health = 10;
	int char_level = 0;
	int char_strength, char_defense, char_speed, classvar;
	string char_name;
	
	srand(time(0)); //Ensure number is random everytime
	
	cout << "Enter your character name (No spaces): ";
	cin >> char_name;
	
	choose_class(classvar, char_strength, char_defense, char_speed, char_level);
	
	display_char(classvar, char_strength, char_defense, char_speed, char_level, char_health, char_name);
	
	cout << "That is all for now, there will be more soon." << endl;
	
	return 0;
}

void choose_class(int &classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level)
{
	int choicevar, choicevar2;
	bool whilevar;
	
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
				char_strength = 5;
				char_defense = 4;
				char_speed = 1;
				
				level_up(classvar, char_strength, char_defense, char_speed, char_level);
				
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

void level_up(int classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level)
{
	int x, y, z;
	
	char_level++;
	
	switch(classvar)
	{
	case 1:
		for (int a = 0; a < 3;) //Three stats per level_up call
		{
			x = rand() % 20; //Gens number between 0-19
			
			if (0 <= x && x <= 9) //~50% chance of strength up per try
			{
				char_strength++;
				cout << "Strength increased by 1! Stength is now " << char_strength << "!" << endl;
				a++;
			}
			
			if (a < 3) //Check if limit of 3 stats is hit
			{
				y = rand() % 30; //Gens number between 0-29
				
				if (0 <= y && y <= 9) //~33% chance of defense per try
				{
					char_defense++;
					cout << "Defense has increased by 1! Defense is now " << char_defense << "!" << endl;
					a++;
				}
			}
			
			if (a < 3) //Check if limit of 3 stats is hit
			{
				z = rand() % 50; //Gens number between 0-49
				
				if (0 <= z && z <= 9) //~20% chance of speed per try
				{
					char_speed++;
					cout <<  "Speed has increased by 1! Speed is now " << char_speed << "!" << endl;
					a++;
				}
			}
		}
		
		break;
	default:
		cout << "Something went wrong, exiting program." << endl;
		
		exit(0);
		
		break;
	}
}

void display_char(int classvar, int char_strength, int char_defense, int char_speed, int char_level, double char_health, string char_name)
{
	cout << char_name << "'s stats: " << endl;
	cout << "Level: " << char_level << endl;
	switch(classvar)
	{
	case 1:
		cout << "Class: Knight " << endl;
		
		break;
	default:
		cout << "Something went wrong, exiting program." << endl;
		
		exit(0);
		
		break;
	}
	cout << "Health: " << char_health << "/10" << endl;
	cout << "Strength: " << char_strength << endl;
	cout << "Defense: " << char_defense << endl;
	cout << "Speed: " << char_speed << endl;
}

