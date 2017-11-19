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

#ifndef __TEXT_LOG_H__
#define __TEXT_LOG_H__

#include <fstream>
#include <ncurses.h>
#include <string>

#include "log_buffer.h"
#include "window.h"

class text_log
{
public:
	text_log(const int &rows, const int &cols);
	~text_log();
	void print(const std::string &s);

private:
	window *win;
	int rows, cols;
	log_buffer *logbuf;
	std::ofstream output;
};

#endif //__TEXT_LOG_H__
