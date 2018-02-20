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

//base class for items, attacks, and maybe other stuff in the future

#ifndef __BASE_H__
#define __BASE_H__

#include <string>

class base
{
public:
	base() { name = "null"; desc = "null"; }
	base(std::string name, std::string desc) { this->name = name; this->desc = desc; }
	virtual std::string to_string() { return name + ":\n" + desc; }
	void set_name(const std::string& name) { this->name = name; }
	void set_desc(const std::string& desc) { this->desc = desc; }
	void set_base(const std::string& name, const std::string& desc) { this->name = name; this->desc = desc; }
	std::string get_name() const { return name; }
	std::string get_desc() const { return desc; }
private:
	std::string name;
	std::string desc;
};

#endif //__BASE_H__
