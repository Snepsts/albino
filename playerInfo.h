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

#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include <gtkmm.h> //for gtkmm stuff
#include "player.h"

class playerInfo : public Gtk::Frame
{
public:
	playerInfo();

	void update(const player& p1);

	//cluster:
	void playerInfoPack();
	void playerInfoMain();

private:
	//main VBox
	Gtk::Box Main_VBox;
	Gtk::Box Top_HBox, Bottom_HBox;

	//top
	Gtk::Label labelName, labelLevel;
	//between the two
	Gtk::Label labelHP;
	//bottom
	Gtk::Label labelClass, labelSTR, labelDEF, labelSPD;

	//these allow the items to be in visible "boxes"
	Gtk::Frame labelName_Frame, labelLevel_Frame, labelHP_Frame, labelClass_Frame,
	           labelSTR_Frame, labelDEF_Frame, labelSPD_Frame;
};

#endif //__PLAYERINFO_H__
