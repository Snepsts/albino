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

#ifndef __CLASS_SELECTION_H__
#define __CLASS_SELECTION_H__

#include <gtkmm.h>
#include "class_label.h"

class class_selection : public Gtk::Frame
{
public:
	class_selection();
	~class_selection() = default;

	//return int representing class
	int get_class();

	//cluster:
	void class_selection_pack();
	void class_selection_main();

protected:
	Gtk::Box main_VBox;
	Gtk::RadioButton class1_Button, class2_Button, class3_Button;
	class_label class_Label; //dynamic label to change with classes
};

#endif //__CLASS_SELECTION_H__
