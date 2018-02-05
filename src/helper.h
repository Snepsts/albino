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

#ifndef __HELPER_H__
#define __HELPER_H__

//helper helps me reuse code

#include <vector>
#include <string>

inline uint get_center_start(const uint width, std::string msg) { return (width / 2) - (msg.length() /2); }
uint get_selection_width(std::vector<std::string> vec);

#endif //__HELPER_H__
