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


#include "gettext_window.h"
#include "keys.h"
#include "universal.h"

char interpret_char(int ch);

extern uint _ROWS;
extern uint _COLS;

gettext_window::gettext_window(std::string title, std::string desc)
: window(GTW_HEIGHT, GTW_WIDTH, (int)(_ROWS-GTW_HEIGHT)/2, (int)(_COLS-GTW_WIDTH)/2, 1)
{
	uint start = (GTW_WIDTH / 2) - (title.length() / 2); //algorithm for centering title text
	for (size_t i = 0; i < title.length(); i++) { //print the title
		print_char(title[i], 1, start+i);
	}

	for (size_t i = 0; i < desc.length(); i++) {
		print_char(desc[i], 3, 1+i);
	}

	input = "";
	/* box numbers are as follows:
		3 because top line + bottom line + one empty line for name entry
		GTW_WIDTH - 4 because we want to give 2 spaces to fit in the current box, and 2 more for uniformity
		_ROWS + GTW_HEIGHT / 2 - 3 all divdied by 2 = total rows + the current height of the box (cut in two)
		  minus three so we're always one above the bottom line of GTW, all cut in two so it's in the center.
		_COLS - (GTW_WIDTH-4) / 2 basically, we're just putting it in the center - the four we gave it width-wise
	*/
	box = new window(3, GTW_WIDTH-4, (int)(_ROWS+GTW_HEIGHT/2-3)/2, (int)(_COLS-(GTW_WIDTH-4))/2, GTW_COLOR);
}

gettext_window::~gettext_window()
{
	delete box;
}

bool gettext_window::set_input()
{
	input = ""; //empty
	bool whilevar = true;
	int box_it = 1;

	do {
		int in = getch();
		char ch = interpret_char(in);

		switch (ch) {
			case '\\': //unrecognized, skip
				break;
			case '-': //backspace
				if (input.length() > 0 && box_it > 1) { //if there is something to backspace
					input.erase(input.end() - 1);
					box->print_char(' ', 1, box_it-1);
					box_it--;
				}
				break;
			case ']': //exit
				return false;
				break;
			case '[': //done, unless nothing was entered
				whilevar = !(input.length() > 0); //if input has at least one char, end loop
				break;
			default:
				if (input.length() < GTW_WIDTH-6) {
					input += ch;
					box->print_char(ch, 1, box_it);
					box_it++;
				}
				break;
		}
	} while (whilevar);

	return true;
}

std::string gettext_window::get_input()
{
	return input;
}

char interpret_char(int ch)
{
	char retval;

	switch (ch) {
		case L_KEY_A: retval = 'a'; break;
		case U_KEY_A: retval = 'A'; break;
		case L_KEY_B: retval = 'b'; break;
		case U_KEY_B: retval = 'B'; break;
		case L_KEY_C: retval = 'c'; break;
		case U_KEY_C: retval = 'C'; break;
		case L_KEY_D: retval = 'd'; break;
		case U_KEY_D: retval = 'D'; break;
		case L_KEY_E: retval = 'e'; break;
		case U_KEY_E: retval = 'E'; break;
		case L_KEY_F: retval = 'f'; break;
		case U_KEY_F: retval = 'F'; break;
		case L_KEY_G: retval = 'g'; break;
		case U_KEY_G: retval = 'G'; break;
		case L_KEY_H: retval = 'h'; break;
		case U_KEY_H: retval = 'H'; break;
		case L_KEY_I: retval = 'i'; break;
		case U_KEY_I: retval = 'I'; break;
		case L_KEY_J: retval = 'j'; break;
		case U_KEY_J: retval = 'J'; break;
		case L_KEY_K: retval = 'k'; break;
		case U_KEY_K: retval = 'K'; break;
		case L_KEY_L: retval = 'l'; break;
		case U_KEY_L: retval = 'L'; break;
		case L_KEY_M: retval = 'm'; break;
		case U_KEY_M: retval = 'M'; break;
		case L_KEY_N: retval = 'n'; break;
		case U_KEY_N: retval = 'N'; break;
		case L_KEY_O: retval = 'o'; break;
		case U_KEY_O: retval = 'O'; break;
		case L_KEY_P: retval = 'p'; break;
		case U_KEY_P: retval = 'P'; break;
		case L_KEY_Q: retval = 'q'; break;
		case U_KEY_Q: retval = 'Q'; break;
		case L_KEY_R: retval = 'r'; break;
		case U_KEY_R: retval = 'R'; break;
		case L_KEY_S: retval = 's'; break;
		case U_KEY_S: retval = 'S'; break;
		case L_KEY_T: retval = 't'; break;
		case U_KEY_T: retval = 'T'; break;
		case L_KEY_U: retval = 'u'; break;
		case U_KEY_U: retval = 'U'; break;
		case L_KEY_V: retval = 'v'; break;
		case U_KEY_V: retval = 'V'; break;
		case L_KEY_W: retval = 'w'; break;
		case U_KEY_W: retval = 'W'; break;
		case L_KEY_X: retval = 'x'; break;
		case U_KEY_X: retval = 'X'; break;
		case L_KEY_Y: retval = 'y'; break;
		case U_KEY_Y: retval = 'Y'; break;
		case L_KEY_Z: retval = 'z'; break;
		case U_KEY_Z: retval = 'Z'; break;
		case _KEY_0: retval = '0'; break;
		case _KEY_1: retval = '1'; break;
		case _KEY_2: retval = '2'; break;
		case _KEY_3: retval = '3'; break;
		case _KEY_4: retval = '4'; break;
		case _KEY_5: retval = '5'; break;
		case _KEY_6: retval = '6'; break;
		case _KEY_7: retval = '7'; break;
		case _KEY_8: retval = '8'; break;
		case _KEY_9: retval = '9'; break;
		case _KEY_SPACE: retval = ' '; break;

		case _KEY_ESC: retval = ']'; break; //']' == go back
		case _KEY_ENTER: retval = '['; break; //'[' == done
		case _KEY_BCKSPC: retval = '-'; break; //'-' == backspace
		default: retval = '\\'; break; //'\\' == ignore
	}

	return retval;
}
