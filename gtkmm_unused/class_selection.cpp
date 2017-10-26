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

#include "class_selection.h"
#include "class_def.h"

class_selection::class_selection()
: Gtk::Frame("Select a Class"),
  main_VBox(Gtk::ORIENTATION_VERTICAL),
  class1_Button(CLASS_1),
  class2_Button(CLASS_2),
  class3_Button(CLASS_3)
{
	class_selection_main();
}

void class_selection::class_selection_pack()
{
	main_VBox.set_border_width(10);
	this->add(main_VBox);

	//group them together
	class2_Button.join_group(class1_Button);
	class3_Button.join_group(class1_Button);

	//pack it all
	main_VBox.pack_start(class1_Button, Gtk::PACK_SHRINK);
	main_VBox.pack_start(class2_Button, Gtk::PACK_SHRINK);
	main_VBox.pack_start(class3_Button, Gtk::PACK_SHRINK);
	main_VBox.pack_start(class_Label, Gtk::PACK_SHRINK);
}

void class_selection::class_selection_main()
{
	class_selection_pack();

	class1_Button.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(class_Label, &class_label::get_def), 1));
	class2_Button.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(class_Label, &class_label::get_def), 2));
	class3_Button.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(class_Label, &class_label::get_def), 3));

	class_Label.get_def(1); //default to first class desc
}

int class_selection::get_class()
{
	int r;

	if(class1_Button.get_active())
		r = 1;
	else if(class2_Button.get_active())
		r = 2;
	else if(class3_Button.get_active())
		r = 3;
	else //catch any possible errors with this
		r = 0;

	return r;
}
