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

#ifndef __UNIVERSAL_H__
#define __UNIVERSAL_H__

/* The current purpose of this file is to have a couple of cross file constants.
 * One of these is the default random engine, another would be the version
 * number. Also, all of the window start positions and sizes can go here, too.
 * This fixed a lot of problems I was experiencing when developing the maze.
 * Maybe I was just developing it wrong though???
 */

#include <ctime> //time(nullptr) (for default_random_engine)
#include <random> //default_random_engine
#include <string> //version

const std::string VERSION = "0.0.1";

std::default_random_engine rand_albino(time(nullptr));

#endif
