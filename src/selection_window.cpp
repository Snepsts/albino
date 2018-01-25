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
	uint start = (width / 2) - (title.length() / 2); //algorithm for centering tilte text
	for (size_t i = 0; i < title.length(); i++) { //print the title
		print_char(title[i], 1, start+i);
	}

	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[i].size(); j++) {
			print_char(vec[i][j], i+3, j+4);
		}
	}

	lines = vec.size();
	refresh();
}

selection_window::~selection_window()
{
	//empty for now
}

size_t selection_window::make_selection()
{
	size_t start = 3; //starting line for choices
	size_t choice = start;
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	int first = 1;
	int second = first + 1;

	print_char('-', choice, first);
	print_char('>', choice, second);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case _KEY_UP: //259
			if (choice == start)
				break;

			print_char(' ', choice, first);
			print_char(' ', choice, second);
			choice--;

			break;

		case _KEY_DOWN: //258
			if (choice == start + lines - 1)
				break;

			print_char(' ', choice, first);
			print_char(' ', choice, second);
			choice++;

			break;

		case _KEY_ENTER: //10
		case _KEY_SPACE: //32
			whilevar = true;
			break;

		case _KEY_ESC: //27
			return 0; //exit code
		}
		print_char('-', choice, first);
		print_char('>', choice, second);
		refresh();
    } while (!whilevar);

	return choice - 2; //start is 3 so 1st choice, 1 = 3 - 2
}
