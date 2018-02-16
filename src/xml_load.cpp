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

#include <map>
#include <string>

#include "../lib/pugixml.hpp"
#include "helper.h"
#include "player_class.h"
#include "system.h"
#include "xml_load.h"

bool get_player_classes(std::map<int, player_class*>& m, pugi::xml_node& classes);

bool xml_load_main(std::map<int, player_class*>& p_classes)
{
	pugi::xml_document doc;
	//don't need to do ../xml/classes.xml bc executable is not in src, it's in parent
	pugi::xml_parse_result result = doc.load_file("xml/classes.xml");

	if (!result)
		return 1;

	pugi::xml_node classes = doc.child("classes");
	if (!get_player_classes(p_classes, classes))
		return false;

	return true;
}

bool get_player_classes(std::map<int, player_class*>& m, pugi::xml_node& classes)
{
	for (pugi::xml_node c = classes.child("class"); c; c = c.next_sibling("class")) {
		player_class* pc = new player_class();
		pc->set_name(c.attribute("name").as_string());

		auto cc = c.children("property");
		for (auto q : cc) {
			std::string name = q.attribute("name").as_string();
			pugi::xml_attribute value = q.attribute("value");

			if (name == "ctype") {
				pc->ctype = get_ctype_from_str(value.as_string());
			} else if (name == "description") {
				pc->set_desc(value.as_string());
			} else if (name == "atk_mod") {
				pc->atk_mod = value.as_int();
			} else if (name == "def_mod") {
				pc->def_mod = value.as_int();
			} else if (name == "spd_mod") {
				pc->spd_mod = value.as_int();
			} else {
				//error
			}
		}

		m[c.attribute("id").as_int()] = pc; //add it to the map
	}

	return true;
}
