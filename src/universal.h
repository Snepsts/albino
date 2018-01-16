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

#include <string> //version

const std::string VERSION = "0.0.1";

//window constants
const int Y_OFFSET = 3;

//player_info constants
const int PI_HEIGHT = 5;
const int PI_WIDTH = 24;
const int PI_STARTY = Y_OFFSET;
const int PI_STARTX = 0;
const int PI_COLOR = 5;

//maze_window constants
const int MW_HEIGHT = 13;
const int MW_WIDTH = PI_WIDTH;
const int MW_STARTY = Y_OFFSET + PI_HEIGHT;
const int MW_STARTX = PI_STARTX;
const int MW_COLOR = 5;

//text_log constants
const int TL_STARTY = Y_OFFSET;
const int TL_STARTX = PI_WIDTH + 1;
const int TL_COLOR = 5;

#endif //__UNIVERSAL_H__
