/* albino
Copyright (C) 2018 Michael Ranciglio

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

#include <ncurses.h>
#include <string>
#include <vector>

#include "keys.h"
#include "selection_window.h"

extern uint _ROWS, _COLS;

selection_window::selection_window(std::string title, std::vector<std::string> vec, uint width)
: window(vec.size()+4, width, _ROWS/2-(vec.size()+4)/2, _COLS/2-(width/2), 1) //vec.size()+4 = options + 2 for borders + 2 for title space
{
	size_t center_start = (width / 2) - (title.length() / 2); //algorithm for centering title text
	for (size_t i = 0; i < title.length(); i++) { //print the title
		print_char(title[i], 1, center_start+i);
	}

	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[i].size(); j++) {
			print_char(vec[i][j], i+3, j+4);
		}
	}

	start = 3; //start is starting point of menu options
	lines = vec.size(); //amount of options from the vector
	refresh();
}

selection_window::~selection_window()
{
	//empty for now
}

size_t selection_window::make_selection()
{
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	size_t choice = move_cursor(true);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case _KEY_UP: //259
			choice = move_cursor(true); //move cursor up
			break;

		case _KEY_DOWN: //258
			choice = move_cursor(false); //move cursor down
			break;

		case _KEY_ENTER: //10
		case _KEY_SPACE: //32
			whilevar = true;
			break;

		case _KEY_ESC: //27
			return 0; //exit code
		}
    } while (!whilevar);

	return choice;
}

size_t selection_window::move_cursor(bool is_up)
{
	static size_t choice = start;
	int first = 1;
	int second = first + 1;

	print_char(' ', choice, first);
	print_char(' ', choice, second);

	if (is_up) { //KEY_UP
		if (choice != start) //not at the beginning
			choice--;
	} else { //KEY_DOWN
		if (choice != start + lines - 1) //not at the end
			choice++;
	}

	print_char('-', choice, first);
	print_char('>', choice, second);
	refresh();

	return choice - (start - 1);
}
