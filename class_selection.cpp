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
  m_Class_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Class1(CLASS_1),
  m_Class2(CLASS_2),
  m_Class3(CLASS_3)
{
	m_Class_VBox.set_border_width(10);
	this->add(m_Class_VBox);

	//group them together
	m_Class2.join_group(m_Class1);
	m_Class3.join_group(m_Class1);

	m_Class1.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(m_Label_Class, &class_label::class_def), 1));
	m_Class2.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(m_Label_Class, &class_label::class_def), 2));
	m_Class3.signal_clicked().connect(sigc::bind<int>(
		sigc::mem_fun(m_Label_Class, &class_label::class_def), 3));

	//m_Class1.set_active(); //default to first choice
	m_Label_Class.class_def(1); //default to first class desc

	m_Class_VBox.pack_start(m_Class1, Gtk::PACK_SHRINK);
	m_Class_VBox.pack_start(m_Class2, Gtk::PACK_SHRINK);
	m_Class_VBox.pack_start(m_Class3, Gtk::PACK_SHRINK);
	m_Class_VBox.pack_start(m_Label_Class, Gtk::PACK_SHRINK);
}

int class_selection::class_choice()
{
	int r;

	if(m_Class1.get_active())
		r = 1;
	else if(m_Class2.get_active())
		r = 2;
	else if(m_Class3.get_active())
		r = 3;
	else
		r = 0;

	return r;
}
