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

#include "pugixml.hpp"
#include "helper.h"
#include "move_battle.h"
#include "player_class.h"
#include "system.h"
#include "xml_load.h"

bool get_player_classes(std::map<uint, player_class*>& m, pugi::xml_node& classes);
bool get_moves(std::map<uint, move_battle*>& m, pugi::xml_node& moves);

bool xml_load_main(std::map<uint, player_class*>& p_classes,
                   std::map<uint, move_battle*>& b_moves)
{
	pugi::xml_document doc;
	//don't need to do ../xml/classes.xml bc executable is not in src, it's in parent
	pugi::xml_parse_result result = doc.load_file("xml/classes.xml");

	if (!result)
		return false;

	pugi::xml_node classes = doc.child("classes");
	if (!get_player_classes(p_classes, classes))
		return false;

	result = doc.load_file("xml/moves.xml");

	if (!result)
		return false;

	pugi::xml_node moves = doc.child("moves");
	if (!get_moves(b_moves, moves))
		return false;

	return true;
}

bool get_player_classes(std::map<uint, player_class*>& m, pugi::xml_node& classes)
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
			} else if (name == "moves") {
				std::string nums = value.as_string(); //pair(1,1 2,2 3,3)
				for (size_t i = 0; i < nums.length(); i += 4) //4 spaces apart
					pc->move_list.push_back(std::make_pair<uint, uint>(i, i+2));
			} else {
				return false; //error
			}
		}

		m[c.attribute("id").as_int()] = pc; //add it to the map
	}

	return true;
}

bool get_moves(std::map<uint, move_battle*>& m, pugi::xml_node& moves)
{
	for (pugi::xml_node mv = moves.child("move"); mv; mv = mv.next_sibling("move")) {
		move_battle* curr = new move_battle(); //couldn't think of a better name
		curr->set_name(mv.attribute("name").as_string());

		auto props = mv.children("property");
		for (auto q : props) {
			std::string name = q.attribute("name").as_string();
			pugi::xml_attribute value = q.attribute("value");

			if (name == "ctype") {
				curr->ctype = get_ctype_from_str(value.as_string());
			} else if (name == "description") {
				curr->set_desc(value.as_string());
			} else if (name == "modifier") {
				curr->modifier = value.as_int();
			} else if (name == "cost") {
				curr->cost = value.as_int();
			} else {
				//return false; //error
			}
		}

		m[mv.attribute("id").as_int()] = curr;
	}

	return true;
}
