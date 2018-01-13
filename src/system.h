/* albino
Copyright (C) 2018 Michael Ranciglio

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

//header that contains types for the whole system (entity, action, battle)

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

enum action_t { attack, heal, item }; //type of action
enum class_t { null = -1, melee, ranged, magic }; //attack or class type
enum owner_t { player, monster }; //origin of action taker

#endif //__SYSTEM_H__
