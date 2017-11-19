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

#include <cstdlib> //srand() and rand()
#include <ctime> //time(0)
#include <iostream> //cin & cout
#include <ncurses.h>

#include "battle.h" //battle call
#include "maze.h" //maze/dungeon
#include "maze_window.h" //maze_window object
#include "player.h" //player object
#include "text_log.h" //text_log object
#include "window.h"

using std::cout;
using std::cin;

void init(); //run this first
void init_colors(); //initialize colors
void display_choices();

//Note to self keep main clean, it's really easy to clutter it up

int main()
{
	init(); //run this first

	int rows, cols; //to store number of rows and cols of screen

	init(); //initialize

	getmaxyx(stdscr, rows, cols); //get number of rows and cols
	attron(COLOR_PAIR(1));
	printw("There are %d rows and %d cols", rows, cols);
	refresh();

	if (true) { //do this so destructor is called at the end of the if
		window *player_info = new window(5, 23, 3, 0, 7);
		//window *maze = new window(12, 23, 8, 0, 5);
		maze dungeon;
		dungeon.gen_main();
		maze_window *mze = new maze_window(&dungeon);
		text_log *txt = new text_log(rows, cols);

		txt->print("Lots and lots and lots and lots and lots and lost and lots and lots and lots and lots of text.");
		//txt->print("Test2\n");
		mze->print();
		player_info->print("Test");
		player_info->print("Test 2");

		refresh();

		getch(); //wait for user input
	}

	endwin(); //end ncurses mode

	return 0;
}

void init()
{
	initscr(); //start curses mode
	start_color(); //enable color functionality
	//cbreak(); //line buffering disabled
	init_colors(); //initialize color pairings
	refresh(); //let it all be SEEEN
}

void init_colors()
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_YELLOW, COLOR_WHITE);
}

/*
int main()
{
	srand(time(0)); //Ensure number is random everytime

	player p1;
	int choicevar;
	bool whilevar;

	do {
		cout << "What would you like to do?\n";
		cout << "1 - New Game\n";
		cout << "2 - Load Game\n";
		cout << "3 - Exit Game\n";

		cin >> choicevar;

		switch(choicevar) {
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
	} while (whilevar);

	do {
		display_choices();
		cin >> choicevar;

		switch(choicevar) {
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
	} while (whilevar);

	cout << "There will be more soon!\n";

	return 0;
}

*/

void display_choices()
{
	cout << "What would you like to do now?\n";
	cout << "1 - Save Game\n";
	cout << "2 - Load Game\n";
	cout << "3 - Display Character Information\n";
	cout << "4 - Exit Game\n";
	cout << "5 - Battle (Alpha mode)\n";
}
