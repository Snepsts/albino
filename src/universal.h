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

#ifndef __UNIVERSAL_H__
#define __UNIVERSAL_H__

#include <string> //version

const std::string VERSION = "0.0.1";

//window constants
const uint Y_OFFSET = 3;

//player_info constants
const uint PI_HEIGHT = 5;
const uint PI_WIDTH = 24;
const uint PI_STARTY = Y_OFFSET;
const uint PI_STARTX = 0;
const uint PI_COLOR = 5;

//maze_window constants
const uint MW_HEIGHT = 13;
const uint MW_WIDTH = PI_WIDTH;
const uint MW_STARTY = Y_OFFSET + PI_HEIGHT;
const uint MW_STARTX = PI_STARTX;
const uint MW_COLOR = 5;

//text_log constants
const uint TL_STARTY = Y_OFFSET;
const uint TL_STARTX = PI_WIDTH + 1;
const uint TL_COLOR = 5;

//gettext_window constants
const uint GTW_HEIGHT = 8;
const uint GTW_WIDTH = 22;
const uint GTW_COLOR = 1;

//detailed_selection_window constants
const uint DSW_HEIGHT = 13;
const uint DSW_WIDTH = 36;

#endif //__UNIVERSAL_H__
