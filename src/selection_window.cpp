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

#include "helper.h" //get_center_start
#include "keys.h"
#include "selection_window.h"

extern uint _ROWS, _COLS;

//default window
selection_window::selection_window(std::string title, std::vector<std::string> vec, const uint& size)
: window(size+6, get_selection_width(vec), _ROWS/2-(vec.size()+4)/2, _COLS/2-(get_selection_width(vec)/2), 1) //size+6 = options + 2 for borders + 2 for title space + 2 for extstr
{
	start = 4; //start is starting point of menu options
	choice = start;
	menu = new selection_menu(vec, size);

	soft_print(title, 1, get_center_start(get_selection_width(vec), title));
	print_choices(); //also calls refresh

	lines = size; //amount of options from the vector
}

selection_window::selection_window(const uint& size, const uint &width, const int &starty, const int &startx, const int &color, std::vector<std::string> vec)
: window(size+2, width, starty, startx, color)
{
	start = 2; //start is starting point of menu options
	choice = start;
	menu = new selection_menu(vec, size-2);

	print_choices(); //also calls refresh

	lines = size-2; //amount of options from the vector
}

selection_window::~selection_window()
{
	delete menu;
}

size_t selection_window::make_selection()
{
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	size_t selection = move_cursor(true);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case _KEY_UP: //259
			selection = move_cursor(true); //move cursor up
			break;

		case _KEY_DOWN: //258
			selection = move_cursor(false); //move cursor down
			break;

		case _KEY_ENTER: //10
		case _KEY_SPACE: //32
			whilevar = true;
			break;

		case _KEY_ESC: //27
			return 0; //exit code
		}
    } while (!whilevar);

	return selection;
}

size_t selection_window::move_cursor(bool is_up)
{
	int first = 1;
	int second = first + 1;

	clean(2);
	soft_print_char(' ', choice, first);
	soft_print_char(' ', choice, second);

	if (is_up) { //KEY_UP
		if (choice != start) //not at the beginning
			choice--;
		menu->move_cursor_up();
	} else { //KEY_DOWN
		if (choice != start + lines - 1) //not at the end
			choice++;
		menu->move_cursor_down();
	}

	soft_print_char('-', choice, first);
	soft_print_char('>', choice, second);
	print_choices(); //also calls refresh

	return menu->get_selection();
}

void selection_window::print_choices()
{
	std::string msg = menu->get_ext_str(true);
	set_color(2);
	soft_print(msg, start-1, get_center_start(get_width(), msg));
	set_color(1);

	std::vector<std::string> vec = menu->get_menu();

	uint width_start = 4;
	print_vector(vec, start, width_start);

	msg = menu->get_ext_str(false);
	set_color(2);
	soft_print(msg, get_height()-2, get_center_start(get_width(), msg));
	set_color(1);

	refresh_win();
}
