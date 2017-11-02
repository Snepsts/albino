/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "action_queue.h"

void action_queue::enqueue(queuetype act)
{
	int newBack = (m_back + 1) % SIZE;

	if (newBack != m_front) { //doesn't fill the queue
		m_array[m_back] = act;
		m_back = newBack;
	}
}

void action_queue::dequeue()
{
	if (!empty())
		m_front = (m_front + 1) % SIZE;
	//else
		//std::cerr << "Error: Attemp to dequeue from action_queue when it's already empty.\n";
}

void action_queue::calculation(action pact, int pspd, action mact, int mspd)
{
	if (pspd < mspd) {
		enqueue(mact);
		enqueue(pact);
	} else {
		enqueue(pact);
		enqueue(mact);
	}
}

void action_queue::clean()
{
	while (!empty())
		dequeue();
}
