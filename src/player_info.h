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

#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>

#include "player.h"
#include "window.h"

class player_info : public window
{
public:
	player_info(player* playa);
	~player_info();
	void refresh();
private:
	void print_name();

	player *p;
};

#endif //__PLAYER_INFO_H__
