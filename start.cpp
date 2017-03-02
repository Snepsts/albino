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

#include "start.h"
#include "main_window.h"
#include "player.h"
#include <iostream>

void start_game(bool load, main_window& mw)
{
	player p1;

	if(load)
	{
		if(!p1.load_game())
			goto NEWGAME; //Yeah yeah I know it's bad practice whatever
	}
	else
	{
		NEWGAME: //in the long term it saves code tho
		mw.end_main_menu();
		mw.create_char(p1);
	}

	//mw.main_game_menu
}

void initialize()
{

}
