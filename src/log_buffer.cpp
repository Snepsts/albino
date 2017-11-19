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
#include <string>

#include "log_buffer.h"

log_buffer::log_buffer(const uint &rows, const uint &cols)
{
	this->rows = rows; this->cols = cols;
	ecols = cols - 26; //26 because it starts at 23 (0-23 = 24 lines) + 2 for the borders
	erows = rows - 6; //3 for start, 1 line at end, 2 for border. 3 + 1 + 2 = 6
}

void log_buffer::add(const std::string& s)
{
	std::deque<std::string> buffer; //preserve line order from string

	if (s.length() < ecols) {
		backlog.push_front(s);
	} else {
		std::string line = ""; //empty line
		uint lines = 1;

		for (uint i = 0; i < s.size(); i++) {
			std::string word = ""; //empty word

			while (s[i] != ' ' && word.length() <= ecols && i < s.size()) { //while it's a word and fits in our effective size
				word += s[i];
				i++; //increment until word is reached at it's limit
			}

			if (i > ecols * lines) { //multiply by lines to scale for how long the message goes
				buffer.push_back(line);
				line.clear();
				lines++; //there has been another line!
			}

			line += word;
			if (i < ecols * lines) //preserve border on right side
				line += ' ';
		}

		buffer.push_back(line);

		while (!buffer.empty()) { //push the lines from s into backlog in order
			backlog.push_front(buffer.back());
			buffer.pop_back();
		}
	}
}

std::deque<std::string> log_buffer::get_log()
{
	return backlog;
}

void log_buffer::clean_log()
{
	while (backlog.size() > erows)
		backlog.pop_back();
}
