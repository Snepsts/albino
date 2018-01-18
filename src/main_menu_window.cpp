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

#include "main_menu_window.h"

main_menu_window::main_menu_window(const uint &rows, const uint &cols, std::vector<std::string> vec)
: window(vec.size()+2, 22, rows/2-vec.size()/2, cols/2-10, 1) //vec.size()+2 = options + 2 for borders
{
	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[i].size(); j++) {
			print_char(vec[i][j], i+1, j+4);
		}
	}

	lines = vec.size();
	refresh();
}

main_menu_window::~main_menu_window()
{
	//empty for now
}

size_t main_menu_window::make_selection()
{
	size_t choice = 1;
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	int first = 1;
	int second = first + 1;

	print_char('-', choice, first);
	print_char('>', choice, second);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case 259: //up
			if (choice == 1)
				break;

			print_char(' ', choice, first);
			print_char(' ', choice, second);
			choice--;

			break;

		case 258: //down
			if (choice == lines)
				break;

			print_char(' ', choice, first);
			print_char(' ', choice, second);
			choice++;

			break;

		case 10: //enter
		case 32: //space
			whilevar = true;

			break;
		}
		print_char('-', choice, first);
		print_char('>', choice, second);
		refresh();
    } while (!whilevar);

	return choice;
}
