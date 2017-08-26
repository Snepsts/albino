/* albino
Copyright (C) 2017 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "player_info.h" //The actual class
#include "class_def.h" //for class info in Title HBox
#include "player.h" //for update function
#include <string> //for class name
#include <iostream> //for cerr

using std::to_string;

player_info::player_info()
: Gtk::Frame("Player Info"),
  main_VBox(Gtk::ORIENTATION_VERTICAL),
  top_HBox(Gtk::ORIENTATION_HORIZONTAL),
  bottom_HBox(Gtk::ORIENTATION_HORIZONTAL)
{
	player_info_main();
}

void player_info::player_info_pack()
{
	main_VBox.set_border_width(10);
	this->add(main_VBox);

	//pack the Horizontal Box containing name and class first
	main_VBox.pack_start(top_HBox, Gtk::PACK_SHRINK);

	//Top HBox
	top_Label_name_Frame.add(top_Label_name);
	top_HBox.pack_start(top_Label_name_Frame, Gtk::PACK_EXPAND_WIDGET);
	top_Label_level_Frame.add(top_Label_level);
	top_HBox.pack_start(top_Label_level_Frame, Gtk::PACK_EXPAND_WIDGET);

	//HP gets it's own thing
	main_VBox.pack_start(hp_Label, Gtk::PACK_EXPAND_WIDGET);

	//pack the Horizontal Box containing stats next
	main_VBox.pack_start(bottom_HBox);

	//Stat HBox
	class_Label_Frame.add(class_Label);
	bottom_HBox.pack_start(class_Label_Frame, Gtk::PACK_EXPAND_WIDGET);
	atk_Label_Frame.add(atk_Label);
	bottom_HBox.pack_start(atk_Label_Frame, Gtk::PACK_EXPAND_WIDGET);
	def_Label_Frame.add(def_Label);
	bottom_HBox.pack_start(def_Label_Frame, Gtk::PACK_EXPAND_WIDGET);
	spd_Label_Frame.add(spd_Label);
	bottom_HBox.pack_start(spd_Label_Frame, Gtk::PACK_EXPAND_WIDGET);
}

void player_info::player_info_main()
{
	player_info_pack();
}

void player_info::update(const player& p1)
{
	//Title HBox
	top_Label_name.set_text("Name: " + p1.getName());

	std::string class_name;

	switch(p1.getClassVar())
	{
		case 1:
			class_name = CLASS_1;
			break;
		case 2:
			class_name = CLASS_2;
			break;
		case 3:
			class_name = CLASS_3;
			break;
		default:
			std::cerr << "Yo there's an error.\n";
			class_name = "Error.";
			break;
	}

	class_Label.set_text(class_name);
	top_Label_level.set_text(to_string(p1.getLevel()));

	hp_Label.set_text("HP: " + to_string(p1.getHP()) + "/" + to_string(p1.getHealth()));

	atk_Label.set_text("STR: " + to_string(p1.getStrength()));
	def_Label.set_text("DEF: " + to_string(p1.getDefense()));
	spd_Label.set_text("SPD: " + to_string(p1.getSpeed()));
}
