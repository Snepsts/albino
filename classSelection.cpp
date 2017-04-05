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

#include "classSelection.h"
#include "classDef.h"

classSelection::classSelection()
: Gtk::Frame("Select a Class"),
  Main_VBox(Gtk::ORIENTATION_VERTICAL),
  Button_Class1(CLASS_1),
  Button_Class2(CLASS_2),
  Button_Class3(CLASS_3)
{
	classSelectionMain();
}

void classSelection::classSelectionPack()
{
	Main_VBox.set_border_width(10);
	this->add(Main_VBox);

	//group them together
	Button_Class2.join_group(Button_Class1);
	Button_Class3.join_group(Button_Class1);

	//pack it all
	Main_VBox.pack_start(Button_Class1, Gtk::PACK_SHRINK);
	Main_VBox.pack_start(Button_Class2, Gtk::PACK_SHRINK);
	Main_VBox.pack_start(Button_Class3, Gtk::PACK_SHRINK);
	Main_VBox.pack_start(labelClass, Gtk::PACK_SHRINK);
}

void classSelection::classSelectionMain()
{
	classSelectionPack();

	Button_Class1.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(labelClass, &classLabel::classDef), 1));
	Button_Class2.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(labelClass, &classLabel::classDef), 2));
	Button_Class3.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(labelClass, &classLabel::classDef), 3));

	labelClass.classDef(1); //default to first class desc
}

int classSelection::getClass()
{
	int r;

	if(Button_Class1.get_active())
		r = 1;
	else if(Button_Class2.get_active())
		r = 2;
	else if(Button_Class3.get_active())
		r = 3;
	else //catch any possible errors with this
		r = 0;

	return r;
}
