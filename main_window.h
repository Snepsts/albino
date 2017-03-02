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

#include <gtkmm.h>
#include "class_selection.h"

class player; //forward declare

class main_window : public Gtk::Window
{
public:
	//Default constructor (Main Menu):
	main_window();

	//Destructor
	virtual ~main_window();

	//Transition out of Main Menu:
	void end_main_menu();

	//"Create a character" interface
	void create_char(player& p1);

	//Send the player information and call the end of the create_char screen
	void send_player_info(player& p1);

	//remove the create a new character frame
	void end_create_char();

	//initialize some game stuff
	void initialize_game();

	//start the game menu up
	void game_menu();

protected:
	//Signal handlers:
	//Main Menu:
	void on_exit_button_clicked();
	void on_newgame_button_clicked();
	void on_loadgame_button_clicked();

	//Child widgets:
	//Main
	Gtk::Box m_Main_VBox; //vertical

	//Main Menu
	Gtk::Frame m_MainMenu; //title
	Gtk::Box m_MainMenu_VBox; //vertical
	Gtk::Button m_Button_NewGame, m_Button_LoadGame, m_Button_Exit;
	Gtk::Label m_Label_Info;

	//Create character
	Gtk::Frame m_CreateCharacter; //title
	Gtk::Box m_CreateCharacter_VBox; //vertical
	Gtk::Entry m_Name_Entry;
	class_selection m_Class_Selection; //class selection module
	Gtk::Label m_Label_Hack; //stupid label we use to get rid of whitespace
	Gtk::Button m_Button_Accept;

	//Game Menu
	Gtk::Frame m_GameMenu; //title
	Gtk::Box m_GameMenu_VBox; //vertical
};

#endif //__MAIN_WINDOW_H__
