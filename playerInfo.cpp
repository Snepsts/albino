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

#include "playerInfo.h" //The actual class
#include "classDef.h" //for class info in Title HBox
#include "player.h" //for update function
#include <string> //for class name
#include <iostream> //for cerr

using std::to_string;

playerInfo::playerInfo()
: Gtk::Frame("Player Info"),
  Main_VBox(Gtk::ORIENTATION_VERTICAL),
  Top_HBox(Gtk::ORIENTATION_HORIZONTAL),
  Bottom_HBox(Gtk::ORIENTATION_HORIZONTAL)
{
	playerInfoMain();
}

void playerInfo::playerInfoPack()
{
	Main_VBox.set_border_width(10);
	this->add(Main_VBox);

	//pack the Horizontal Box containing name and class first
	Main_VBox.pack_start(Top_HBox, Gtk::PACK_SHRINK);

	//Top HBox
	labelName_Frame.add(labelName);
	Top_HBox.pack_start(labelName_Frame, Gtk::PACK_EXPAND_WIDGET);
	labelLevel_Frame.add(labelLevel);
	Top_HBox.pack_start(labelLevel_Frame, Gtk::PACK_EXPAND_WIDGET);

	//HP gets it's own thing
	Main_VBox.pack_start(labelHP, Gtk::PACK_EXPAND_WIDGET);

	//pack the Horizontal Box containing stats next
	Main_VBox.pack_start(Bottom_HBox);

	//Stat HBox
	labelClass_Frame.add(labelClass);
	Bottom_HBox.pack_start(labelClass_Frame, Gtk::PACK_EXPAND_WIDGET);
	labelSTR_Frame.add(labelSTR);
	Bottom_HBox.pack_start(labelSTR_Frame, Gtk::PACK_EXPAND_WIDGET);
	labelDEF_Frame.add(labelDEF);
	Bottom_HBox.pack_start(labelDEF_Frame, Gtk::PACK_EXPAND_WIDGET);
	labelSPD_Frame.add(labelSPD);
	Bottom_HBox.pack_start(labelSPD_Frame, Gtk::PACK_EXPAND_WIDGET);
}

void playerInfo::playerInfoMain()
{
	playerInfoPack();
}

void playerInfo::update(const player& p1)
{
	//Title HBox
	labelName.set_text("Name: " + p1.getName());

	std::string className;

	switch(p1.getClassVar())
	{
		case 1:
			className = CLASS_1;
			break;
		case 2:
			className = CLASS_2;
			break;
		case 3:
			className = CLASS_3;
			break;
		default:
			std::cerr << "Yo there's an error.\n";
			className = "Error.";
			break;
	}

	labelClass.set_text(className);
	labelLevel.set_text(to_string(p1.getLevel()));

	labelHP.set_text("HP: " + to_string(p1.getHP()) + "/" + to_string(p1.getHealth()));

	labelSTR.set_text("STR: " + to_string(p1.getStrength()));
	labelDEF.set_text("DEF: " + to_string(p1.getDefense()));
	labelSPD.set_text("SPD: " + to_string(p1.getSpeed()));
}
