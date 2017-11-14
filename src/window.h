#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <string>

class window
{
public:
	window(const int &height, const int &width, const int &starty, const int &startx, const int &color);
	~window();
	void print(const std::string &p);

private:
	void set_color(int color);

	WINDOW *win;
};

#endif //__WINDOW_H__
