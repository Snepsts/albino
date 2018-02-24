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

#include <algorithm> //std::copy
#include <fstream> //global debug log
#include <map> //structure to hold player_classes
#include <ncurses.h>
#include <string>
#include <vector>

#include "base.h" //test
#include "battle.h" //battle call
#include "detailed_selection_window.h" //test
#include "gettext_window.h" //player name input
#include "keys.h" //game_loop
#include "maze.h" //maze/dungeon
#include "maze_window.h" //maze_window object
#include "player.h" //player object
#include "player_class.h" //new player menu
#include "player_window.h" //player_window windoselection
#include "selection_window.h" //main menu
#include "textlog_window.h" //textlog_window object
#include "window.h" //base class for all windows
#include "xml_load.h" //functions to load in game data
#include "universal.h" //version number

extern uint _ROWS;
extern uint _COLS;

std::map<uint, player_class*> p_classes;

//game related functions
bool main_menu(player& p1);
bool new_game_menu(player& p1);
bool pause_game();
bool game_loop(maze_window* mwin, textlog_window* tlwin, player_window* pwin, player* p1, maze* dungeon);

//helping functions
std::vector<std::string> get_main_menu_choices();
std::vector<std::string> get_pause_menu_choices();

//window functions
void backup(std::vector<window*>& v); //stores current window info in cache
void delete_windows(std::vector<window*>& v); //calls all window destructors
void restore(std::vector<window*>& v); //retrieves window info from cache

void game_main()
{
	player p1;
	maze dungeon;

	if (!xml_load_main(p_classes)) //load in xml files
		return; //exit

	if (!main_menu(p1)) { //if they chose to exit
		return; //end it here
	}

	maze_window* mwin = new maze_window(&dungeon);
	textlog_window* tlwin = new textlog_window();
	player_window* pwin = new player_window(&p1);

	pwin->refresh();

	if (game_loop(mwin, tlwin, pwin, &p1, &dungeon)) {
		//do something
	}

	refresh();
	getch();
}

bool game_loop(maze_window* mwin, textlog_window* tlwin, player_window* pwin, player* p1, maze* dungeon)
{
	dungeon->gen_main(); //gen dungeon
	mwin->print();

	std::vector<window*> windows; //collection of primary game windows

	windows.push_back(mwin);
	windows.push_back(tlwin);
	windows.push_back(pwin);

	bool whilevar = true;
	do {
		int x = dungeon->get_x();
		int y = dungeon->get_y();
		int in = getch();

		switch (in) {
		case L_KEY_W:
		case KEY_UP:
			y += 1;
			break;
		case L_KEY_S:
		case KEY_DOWN:
			y -= 1;
			break;
		case L_KEY_A:
		case KEY_LEFT:
			x -= 1;
			break;
		case L_KEY_D:
		case KEY_RIGHT:
			x += 1;
			break;
		}

		int result = dungeon->move(x, y);
		if (result == 1 || result == 2)
			mwin->print();

		if (result == 2)
			whilevar = false;
	} while (whilevar);

	getch(); //wait for user input
	delete_windows(windows);

	return true;
}

bool main_menu(player& p1)
{
	selection_window *menuwin = new selection_window("Welcome", get_main_menu_choices());

	bool whilevar = true;
	bool ret = true;

	do {
		int l = menuwin->make_selection();

		switch (l) {
			case 0:
				ret = false; //exit
				whilevar = false; //end loop
				break;
			case 1:
				menuwin->backup();
				menuwin->clear(); //hide the rest of this window
				if (new_game_menu(p1)) { //if they successfully start a new game
					whilevar = false;
				} else { //they exited out of the window
					menuwin->restore(); //restore the original window
				}
				break;
			case 2:
			case 3:
			case 4:
			default:
				ret = false; //exit
				whilevar = false; //end loop
				break;
		}
	} while (whilevar);

	delete menuwin;

	return ret;
}

bool new_game_menu(player& p1)
{
	std::vector<base*> vec;
	std::vector<player_class*> temp;

	temp = get_vec_from_map(p_classes); //get the list of classes pre-emptively
	for (auto q : temp) {
		vec.push_back(q);
	}

	gettext_window *txtwin = new gettext_window("New Player", "Enter a name:");
	txtwin->backup();
	uint classvar; //class variable to set player's class
	bool whilevar = true;
	do {
		std::string name = txtwin->set_input();

		if (name == "?")
			return false;

		p1.set_name(name);

		detailed_selection_window *dswin = new detailed_selection_window("Pick a class", vec);
		classvar = dswin->get_selection();

		if (classvar == 0) {
			dswin->clear();
			delete dswin;
			txtwin->restore();
		} else {
			whilevar = false;
		}
	} while (whilevar);

	p1.set_class(classvar);

	return true;
}

bool pause_game()
{
	selection_window *pausewin = new selection_window("Paused", get_pause_menu_choices());

	bool whilevar = true;
	bool ret = true;

	do {
		int l = pausewin->make_selection();

		switch (l) {
			case 0:
				ret = false; //exit
				whilevar = false; //end loop
				break;
			case 1:
				whilevar = false; //resume
				break;
			case 2:
				//options menu
				whilevar = false;
				break;
			case 3:
			default:
				ret = false; //exit
				whilevar = false; //end loop
				break;
		}
	} while (whilevar);

	delete pausewin;

	return ret;
}

std::vector<std::string> get_main_menu_choices()
{
	std::vector<std::string> choices;

	choices.push_back("New Game");
	choices.push_back("Other Option");
	choices.push_back("Other Option 2.0");
	choices.push_back("Test");
	choices.push_back("Exit Game");

	return choices;
}

std::vector<std::string> get_pause_menu_choices()
{
	std::vector<std::string> choices;

	choices.push_back("Resume");
	choices.push_back("Options");
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
