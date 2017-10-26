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

#ifndef __CLASS_LABEL_H__
#define __CLASS_LABEL_H__

#include <gtkmm/label.h>
#include "class_def.h"

class class_label : public Gtk::Label //This is just a wrapper for a label
{
public:
	class_label()
	{
		this->set_line_wrap(); //make line wrap when window shrinks
	}

	virtual ~class_label() = default;

	//This allows us to dynamically update the text with just one call on our end
	void get_def(int classvar)
	{
		this->set_text(class_info(classvar));
	}
};

#endif //__CLASS_LABEL_H__
