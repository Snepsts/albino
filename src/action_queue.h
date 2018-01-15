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

#ifndef __ACTION_QUEUE_H__
#define __ACTION_QUEUE_H__

#include "action.h"

typedef action queuetype; //incase the name changes

class action_queue
{
public:
	//basic constructor, does nothing right now
	action_queue() { /*do nothing*/ }

	void enqueue(queuetype act) { deck.push_back(act); }

	void dequeue() { deck.pop_front(); }

	//returns the action in the front of the queue
	queuetype front() { return deck.front(); }

	//returns the action in the back of the queue
	queuetype back() { return m_array[(m_back - 1 + SIZE) % SIZE]; }

	bool empty() { return deck.empty(); }

	// "cleans" the action_queue out
	void clean() { while (!empty()) dequeue(); }

	void sort();

private:
	std::deque<queuetype> deck;
};

#endif
