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

#include "system.h"

#include <map>
#include <string>
#include <vector>

inline uint get_center_start(const uint width, std::string msg) { return (width / 2) - (msg.length() /2); }
uint get_selection_width(std::vector<std::string> vec);
std::vector<std::string> str_to_vec(std::string str); //turns '\n's into multiple strings
class_t get_ctype_from_str(const std::string& str); //string to class_t
std::string get_str_from_ctype(const class_t& ctype); //class_t to string

template <class T>
std::vector<T> get_vec_from_map(std::map<uint, T> m)
{
	std::vector<T> vec;

	for (auto q : m)
		vec.push_back(q.second);

	return vec;
}

#endif //__HELPER_H__
