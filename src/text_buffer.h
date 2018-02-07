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

#ifndef __TEXT_BUFFER_H__
#define __TEXT_BUFFER_H__

#include <deque>
#include <string>

class text_buffer
{
public:
	//default constructor
	text_buffer();

	/* function add
	 * Called by the text_log to put the string into the window as a means of
	 * showing the player their past actions.
	 *
	 * This function allows us to break up the string into different "lines" so
	 * to speak. It breaks text up into words, so words do not get broken up by
	 * between lines. The lines are then pushed into and held in the deque in
	 * order that they are broken up into. This allows us to keep track of the
	 * events with ease.
	 *
	 * Calls clean_log upon completion
	 */
	void add(const std::string& s, bool is_reverse = false);
	std::deque<std::string> get_log();
	void clear() { while (!backlog.empty()) backlog.pop_back(); }
private:
	/* function clean_log
	 * This function keeps the log clean according to our number of columns.
	 *
	 * If we have 55 effective columns, and our deque ends up having 59 members,
	 * we will keep popping members off until it's back to 55.
	 *
	 * Called by add
	 */
	void clean_log();

	uint rows, cols, erows, ecols; //erows/cols = effective rows/columns
	std::deque<std::string> backlog;
};

#endif //__TEXT_BUFFER_H__
