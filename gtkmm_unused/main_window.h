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

#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

/* Forward on this code organization:
Currently the idea is to organize it for all constant functions (default
construct, etc) first, then main menu, then class create, etc. In order of
appearance.
Each code appearance starts with it's "pack" function, which is the boring part
where stuff gets packed in for that "phase". Then it'll have it's various other
functions, and end with an "unpack" function.
*/

#include <gtkmm.h>
#include "class_selection.h"
#include "player_info.h"

class player; //forward declare

class main_window : public Gtk::Window
{
public:
	//Default constructor (Calls Main Menu currently):
	main_window();

	//Destructor
	virtual ~main_window() = default;

	//main_menu cluster:
	void main_menu_pack();
	void main_menu_main();
	void main_menu_unpack();

	//char_create cluster:
	void char_create_pack();
	void char_create_main(player& p1); //Needs player for send and unpack
	void char_create_send(player& p1); //Send player info and call unpack
	void char_create_unpack(player& p1); //Passes player to game_menu

	//game_menu cluster:
	void game_menu_pack();
	void game_menu_main(player& p1);

protected:
	//Signal handlers:
	//Main Menu:
	void on_exit_button_clicked();
	void on_newgame_button_clicked();
	void on_loadgame_button_clicked();

	//Child widgets:
	//Main Menu
	Gtk::Frame main_menu_Frame; //title
	Gtk::Box main_menu_VBox; //vertical
	Gtk::Button main_menu_Button_new_game, main_menu_Button_load_game,
	            main_menu_Button_exit;
	Gtk::Label main_menu_Label_info; //info label containing version, link, etc.

	//Create character
	Gtk::Frame char_create_Frame; //title
	Gtk::Box char_create_VBox; //vertical
	Gtk::Entry char_create_Entry_name; //Entry for the character's name
	class_selection char_create_class_select; //class selection module
	//Gtk::Label m_Label_Hack; //stupid label we use to get rid of whitespace
	Gtk::Button char_create_Button_accept;

	//Game Menu
	Gtk::Frame game_menu_Frame; //title
	Gtk::Box game_menu_VBox; //vertical "dad" box
	Gtk::Box game_menu_HBox_top, game_menu_HBox_bottom; //primary horizontal boxes

	Gtk::Box game_menu_VBox_top_status, game_menu_VBox_top_second; //the two verticle boxes of top box
	Gtk::Box game_menu_HBox_top_second_option; //the horizontal box of top second
	//Bottom box of game menu
	//stuff will go here later

	//Game Menu widgets
	//Frames for stuff
	player_info game_menu_player_info; //player info frame
	Gtk::Frame game_menu_Frame_maze, game_menu_Frame_msglog;
};

#endif //__MAIN_WINDOW_H__
