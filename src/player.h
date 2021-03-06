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

/* This is the player header. It represents the player class and is basically
the focus of the game. More stuff goes here later blah blah blah */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string> //string

#include "entity.h" //base class
#include "player_class.h" //class of the player

class player : public entity
{
public:
	/* default constructor
		Task: Creates the player object with some base stats, will be adjusting
		these later :) */
	player();

	/* function level_up
		This function ups the level variable and randomly ups stats depending on
		the class
		==============================================================
			todo: simplify the "algorithm" to require less code
		============================================================== */
	void level_up();

	/* function set_class
		This function sets the class based on a classvar, which will lookup the
		class in the p_classes map */
	void set_class(const uint& classvar);

	//accessor for p_class
	player_class get_class() { return p_class; }

private:
	player_class p_class;
};

#endif //__PLAYER_H__
