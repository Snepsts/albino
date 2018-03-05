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

#include <deque>
#include <fstream>
#include <ncurses.h>
#include <string>

#include "text_buffer.h"
#include "textlog_window.h"
#include "universal.h"

extern uint _ROWS, _COLS;

textlog_window::textlog_window()
: window(_ROWS - Y_OFFSET, _COLS - TL_STARTX, TL_STARTY, TL_STARTX, 1) //set the window parameters
{
	output.open("output.txt"); //open the output log file stream
	logbuf = new text_buffer(get_height(), get_width()); //create the log buffer
}

textlog_window::textlog_window(const uint &height, const uint &width, const int &starty, const int &startx)
: window(height, width, starty, startx, 1)
{
	logbuf = new text_buffer(height, width);
}

textlog_window::~textlog_window()
{
	delete logbuf; //clean up the text_buffer
	output.close(); //close the output file
}

void textlog_window::add_to_log(const std::string &s, bool is_reverse)
{
	clean(1);
	output << s << '\n';
	logbuf->add(s, is_reverse);

	int y = 1;
	for (auto q : logbuf->get_log()) {
		soft_print(q, y, 1);
		y++;
	}

	refresh();
}

void textlog_window::clean_log()
{
	clean();
	logbuf->clear();
}
