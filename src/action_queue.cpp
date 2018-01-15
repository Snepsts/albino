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

#include <algorithm> //std::sort
#include <deque>

#include "action.h"
#include "action_queue.h"
#include "system.h"

struct algol
{ //sorting algorithm
	bool operator() (const action& x, const action& y) const
	{
		if (x.speed != y.speed) {
			return x.speed > y.speed;
		} else { //x.speed == y.speed
			return x.owner == player;
		}
	}
};

void action_queue::sort()
{
	std::sort(deck.begin(), deck.end(), algol());
}
