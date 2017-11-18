#include <ncurses.h>
#include <string>

#include "window.h"

char* string_to_char_array(const std::string &s)
{
	char* c = new char[s.length()]; //allocate memory

	for (uint i = 0; i < s.length(); i++)
		c[i] = s[i]; //assign string to char array

	return c;
}

window::window(const int &height, const int &width, const int &starty, const int &startx, const int &color)
{
	win = newwin(height, width, starty, startx); //make a new window
	box(win, 0, 0); //0, 0 gives default characters for the vertical and
	                //horizontal lines
	wrefresh(win); //show the box
	set_color(color);
}

window::~window()
{
	//we use all these ugly ' ' chars b/c it destroys all of the window sides
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win); //refresh to our empty window we just re-established
	delwin(win); //delete the window
}

void window::print(const std::string &s, const int &y, const int &x)
{
	//wprintw takes a WINDOW* and a const char* argument
	const char *msg = string_to_char_array(s); //turn string to char array

	mvwprintw(win, y, x, msg); //print the message

	delete[] msg; //clear memory
	msg = nullptr; //safely set msg to point at nothing

	wrefresh(win);
}

void window::print_char(const char &c, const int &y, const int &x)
{
	mvwaddch(win, y, x, c);
	wrefresh(win);
}

void window::set_color(int color)
{
	wattron(win, COLOR_PAIR(color)); //set the color
}
