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

#include "text_buffer.h"
#include "universal.h"

extern uint _ROWS, _COLS;

text_buffer::text_buffer(const uint& rows, const uint& cols)
{
	this->rows = rows;
	this->cols = cols;
	ecols = cols-2;
	erows = rows-2;
}

void text_buffer::add(const std::string& s, bool is_reverse)
{
	std::deque<std::string> buffer; //preserve line order from string

	if (s.length() < ecols) {
		(is_reverse) ? backlog.push_back(s) : backlog.push_front(s);
	} else {
		std::string line = ""; //empty line
		std::string word = "";
		uint lines = 1;

		for (size_t i = 0; i < s.size(); i++) {
			word += s[i];
			if (s[i] == ' ') {
				line += word;
				word.clear();
			}
			if (!(line.length()+word.length() < ecols)) {
				buffer.push_back(line);
				line.clear();
				lines++;
			}
		}

		if (word.length() > 0)
			line += word;

		buffer.push_back(line);

		while (!buffer.empty()) { //push the lines from s into backlog in order
			//(is_reverse) ? backlog.push_back(buffer.back()) : backlog.push_front(buffer.back());
			if (is_reverse) {
				backlog.push_back(buffer.front());
				buffer.pop_front();
			} else {
				backlog.push_front(buffer.back());
				buffer.pop_back();
			}
		}
	}
}

std::deque<std::string> text_buffer::get_log()
{
	return backlog;
}

void text_buffer::clean_log()
{
	while (backlog.size() > erows)
		backlog.pop_back();
}
