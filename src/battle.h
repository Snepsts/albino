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

/* Declaration of the battle function
	There's probably a better way to do this but I'll do it here for now.

	As a notice: the battle function is only in it's first functional state.
	There will be many changes towards the entire functionality of this function
	(for example, not being limited to a 1 on 1 battle, more streamlined to include
	all sorts of different effects/calculations, and a more modular approach with
	more fancy function calls)

	For now it works and the focus will be on the entirety of the game including
	the battle function and it's components.
*/

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <vector>

#include "entity.h" //base class for player & monster
#include "monster.h" //monster object
#include "player.h" //player object

//main for the battle functions takes a vector with two entities
void battle_main(std::vector<entity*> vec);

#endif //__BATTLE_H__
