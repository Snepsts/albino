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

#include <string>
#include <vector>

#include "base.h"
#include "detailed_selection_window.h"
#include "helper.h" //selection
#include "keys.h"
#include "textlog_window.h"
#include "universal.h"

//TODO: make this look less insane

extern uint _ROWS;
extern uint _COLS;

uint get_detailed_window_height(std::vector<std::string> vec) { return (vec.size()+2 < DSW_HEIGHT) ? vec.size()+2 : DSW_HEIGHT; }
uint get_detailed_window_width(std::vector<std::string> vec) { return get_selection_width(vec) + DSW_WIDTH; }
std::vector<std::string> base_to_string(std::vector<base*> vec);

detailed_selection_window::detailed_selection_window(std::string title, std::vector<base*> vec)
: window(DSW_HEIGHT, get_detailed_window_width(base_to_string(vec)), _ROWS/2-get_detailed_window_height(base_to_string(vec))/2,
_COLS/2-get_detailed_window_width(base_to_string(vec))/2, 1)
{
	uint win_height = get_detailed_window_height(base_to_string(vec));
	uint win_width = get_detailed_window_width(base_to_string(vec));
	uint select_width = get_selection_width(base_to_string(vec));
	uint select_height = win_height - 2;
	uint select_starty = _ROWS / 2 - win_height / 2 + 1;
	uint select_startx = _COLS / 2 - win_width / 2 + 1;

	select = new selection_window(select_height, select_width, select_starty, select_startx, 1, base_to_string(vec));
	info = new textlog_window(DSW_HEIGHT-2, 24, select_starty, select_startx+select_width);

	choices = vec;
}

detailed_selection_window::~detailed_selection_window()
{
	delete select;
	delete info;
}

std::vector<std::string> base_to_string(std::vector<base*> vec)
{
	std::vector<std::string> strvec;

	for (size_t i = 0; i < vec.size(); i++) {
		strvec.push_back(vec[i]->get_name());
	}

	return strvec;
}

//TODO: boilerplate from selection_window, make it reusable later
size_t detailed_selection_window::get_selection()
{
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	size_t choice = select->move_cursor(true);
	size_t prev_choice = choice; //check to prevent user print spamming
	print_desc(choice);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case _KEY_UP: //259
			choice = select->move_cursor(true); //move cursor up
			if (choice != prev_choice) { //prevent repetitive print spams
				info->clean();
				print_desc(choice);
			}
			break;

		case _KEY_DOWN: //258
			choice = select->move_cursor(false); //move cursor down
			if (choice != prev_choice) { //prevent repetitive print spams
				info->clean();
				print_desc(choice);
			}
			break;

		case _KEY_ENTER: //10
		case _KEY_SPACE: //32
			whilevar = true;
			break;

		case _KEY_ESC: //27
			return 0; //exit code
		}

		prev_choice = choice;
	} while (!whilevar);

	return choice;
}

void detailed_selection_window::print_desc(size_t choice)
{
	std::string msg = choices[choice-1]->to_string();
	std::vector<std::string> vec = get_clean_vec(str_to_vec(msg), DSW_WIDTH-4);

	for (auto q : vec)
		info->print(q, true);
}
