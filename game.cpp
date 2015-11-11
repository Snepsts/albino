#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

void choose_class(int &classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level); //choose class function

void level_up(int classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level); //level up function

void display_char(int classvar, int char_strength, int char_defense, int char_speed, int char_level, double char_health, string char_name); //display character information function

void save_game(int classvar, int char_strength, int char_defense, int char_speed, int char_level, double char_health, string char_name); //save game function

void load_game(int &classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level, double &char_health, string &char_name); //load game function

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

void save_game(int classvar, int char_strength, int char_defense, int char_speed, int char_level, double char_health, string char_name)
{
	int choicevar;
	ofstream savefile;
	
	cout << "Save character " << char_name << "?" << endl;
	
	display_char(classvar, char_strength, char_defense, char_speed, char_level, char_health, char_name);
	
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
				savefile << classvar << endl << endl;
				savefile << char_strength << endl << endl;
				cout << ".";
				savefile << char_defense << endl << endl;
				savefile << char_speed << endl << endl;
				cout << ".";
				savefile << char_level << endl << endl;
				savefile << char_health << endl << endl;
				cout << ".";
				savefile << char_name << endl;
				cout << " Done!" << endl;
			}
			break;
			
		default:
			cout << "Invalid selection. Canceling..." << endl;
			break;
	}
}

void load_game(int &classvar, int &char_strength, int &char_defense, int &char_speed, int &char_level, double &char_health, string &char_name)
{
	double b;
	string c;
	int d;
	
	ifstream loadfile;
	loadfile.open("save.txt");
	
	if(loadfile.fail())
	{
		cout << "Failed to load save file. Does a save file exist?" << endl;
		loadfile.close();
	}
	
	else
	{
		for(int a = 0; a < 6; a++)
		{
			loadfile >> b;
			
			switch(a)
			{
				case 0:
					if (b == 1)
						cout << "Class: Knight" << endl;
					if (b == 2)
						cout << "Class: Mage" << endl;
					if (b == 3)
						cout << "Class: Rogue" << endl;
					break;
					
				case 1:
					cout << "Strength: " << b << endl;
					break;
					
				case 2:
					cout << "Defense: " << b << endl;
					break;
					
				case 3:
					cout << "Speed: " << b << endl;
					break;
					
				case 4:
					cout << "Level: " << b << endl;
					break;
					
				case 5:
					cout << "Health: " << b << endl;
					break;
					
				default:
					cout << "End of information stream..." << endl;
					break;
			}
		}
		loadfile >> c;
		cout << "Name: " << c << endl;
		
		loadfile.close();
		loadfile.ignore();
		loadfile.clear();
		
		cout << "Would you like to load this file? (1 = Yes, 0 = No)" << endl;
		cin >> d;
		if (d == 1)
		{
			loadfile.open("save.txt");
			
			if (loadfile.fail())
			{
				cout << "Save file failed to open. Canceling..." << endl;
				loadfile.close();
			}
			
			else
			{
				cout << "Loading file...";
				
				for(int a = 0; a < 6; a++)
				{
					loadfile >> b;
					
					switch(a)
					{	
						case 0:
							classvar = b;
							break;
							
						case 1:
							char_strength = b;
							break;
							
						case 2:
							char_defense = b;
							break;
							
						case 3:
							char_speed = b;
							break;
							
						case 4:
							char_level = b;
							break;
							
						case 5:
							char_health = b;
							break;
					}
				}
				loadfile >> c;
				char_name = c;
				
				cout << " Done!" << endl;
				cout << "File successfully loaded!" << endl;
				
				loadfile.close();
			}
		}
		else
		{
			cout << "Cancelling..." << endl;
		}
	}
}
