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

#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <gtkmm.h> //for gtkmm stuff
#include "player.h"

class player_info : public Gtk::Frame
{
public:
	player_info();

	void update(const player& p1);

	//cluster:
	void player_info_pack();
	void player_info_main();

private:
	//main VBox
	Gtk::Box main_VBox;
	Gtk::Box top_HBox, bottom_HBox;

	//top
	Gtk::Label top_Label_name, top_Label_level;
	//between the two
	Gtk::Label hp_Label;
	//bottom
	Gtk::Label class_Label, atk_Label, def_Label, spd_Label;

	//these allow the items to be in visible "boxes"
	Gtk::Frame top_Label_name_Frame, top_Label_level_Frame, hp_Label_Frame, class_Label_Frame,
	           atk_Label_Frame, def_Label_Frame, spd_Label_Frame;
};

#endif //__PLAYER_INFO_H__
