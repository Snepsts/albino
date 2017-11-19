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

#include <deque>
#include <fstream>
#include <ncurses.h>
#include <string>

#include "text_log.h"

text_log::text_log(const int &rows, const int &cols)
{
	this->rows = rows; this->cols = cols; //set the rows and cols
	win = new window(rows - 4, cols - 24, 3, 24, 7); //set the window parameters
	output.open("output.txt"); //open the output log file stream
	logbuf = new log_buffer(rows, cols); //create the log buffer
}

text_log::~text_log()
{
	delete win; //clean up the window (call dat destructor, baby)
	delete logbuf; //clean up the log_buffer
	output.close(); //close the output file
}

void text_log::print(const std::string &s)
{
	output << s << '\n';
	logbuf->add(s);

	int x = 1;
	int y = 1;
	for (auto q : logbuf->get_log()) {
		for (auto c : q) {
			win->print_char(c, y, x);
			x++;
		}
		y++;
		x = 1;
	}
}
