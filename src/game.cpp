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
#include "player_info.h" //player_info window object
#include "text_log.h" //text_log object
#include "window.h"
#include "universal.h" //version number

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
	std::string msg = "albino version: " + VERSION + " There are %d rows and %d cols";
	printw(msg.c_str(), rows, cols);
	refresh();

	if (true) { //do this so destructor is called at the end of the if
		//window *player_info = new window(5, 23, 3, 0, 7);
		//window *maze = new window(12, 23, 8, 0, 5);
		player p1;
		maze dungeon;
		dungeon.gen_main();
		maze_window *mze = new maze_window(&dungeon);
		text_log *txt = new text_log(rows, cols);
		player_info *plyr_nfo = new player_info(&p1);

		txt->print("Lots and lots and lots and lots and lots and lost and lots and lots and lots and lots of text.");
		mze->print();
		plyr_nfo->refresh();

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

void display_choices()
{
	cout << "What would you like to do now?\n";
	cout << "1 - Save Game\n";
	cout << "2 - Load Game\n";
	cout << "3 - Display Character Information\n";
	cout << "4 - Exit Game\n";
	cout << "5 - Battle (Alpha mode)\n";
}
