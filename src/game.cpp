/* albino
Copyright (C) 2017-2018 Michael Ranciglio

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

#include <fstream> //global debug log
#include <ncurses.h>
#include <string>
#include <vector>

#include "battle.h" //battle call
#include "main_menu_window.h" //main menu
#include "maze.h" //maze/dungeon
#include "maze_window.h" //maze_window object
#include "player.h" //player object
#include "player_window.h" //player_window window object
#include "textlog_window.h" //textlog_window object
#include "window.h" //base class for all windows
#include "universal.h" //version number

void print_first(int rows, int cols); //get initial print stuff out of main
std::vector<std::string> get_choices();

//window functions
void backup(std::vector<window*>& v); //stores current window info in cache
void delete_windows(std::vector<window*>& v); //calls all window destructors
void restore(std::vector<window*>& v); //retrieves window info from cache

void game_main()
{
	int rows, cols; //to store number of rows and cols of screen
	getmaxyx(stdscr, rows, cols); //get number of rows and cols
	print_first(rows, cols);

	player p1;
	maze dungeon;
	dungeon.gen_main(); //gen dungeon

	maze_window *mwin = new maze_window(&dungeon);
	textlog_window *tlwin = new textlog_window(rows, cols);
	player_window *pwin = new player_window(&p1);
	std::vector<window*> windows; //collection of primary game windows

	windows.push_back(mwin);
	windows.push_back(tlwin);
	windows.push_back(pwin);

	backup(windows);

	main_menu_window *menuwin = new main_menu_window(rows, cols, get_choices());
	int l = menuwin->make_selection();

	switch (l) {
		case 1:
			//new game
			break;
		case 2:
		case 3:
		case 4:
		default:
			//quit
			break;
	}

	delete menuwin;

	restore(windows);

	tlwin->print("Lots and lots and lots and lots and lots and lost and lots and lots and lots and lots of text.");
	mwin->print();
	pwin->refresh();
	mwin->test();

	refresh();
	getch(); //wait for user input
	delete_windows(windows);
}

void print_first(int rows, int cols)
{
	attron(COLOR_PAIR(7)); //color the top red
	std::string msg = "albino version: " + VERSION + " There are %d rows and %d cols";
	printw(msg.c_str(), rows, cols);
	attron(COLOR_PAIR(1)); //change back to white for redrawing windows
	refresh();
}

std::vector<std::string> get_choices()
{
	std::vector<std::string> choices;

	choices.push_back("New Game");
	choices.push_back("Other Option");
	choices.push_back("Other Option 2.0");
	choices.push_back("Exit Game");

	return choices;
}

void backup(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		v[i]->backup();
	}
}

void restore(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		v[i]->restore();
	}
}

void delete_windows(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		delete v[i];
	}
}
