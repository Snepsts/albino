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
#include "classSelection.h"
#include "playerInfo.h"

class player; //forward declare

class mainWindow : public Gtk::Window
{
public:
	//Default constructor (Calls Main Menu currently):
	mainWindow();

	//Destructor
	virtual ~mainWindow() = default;

	//mainMenu cluster:
	void mainMenuPack();
	void mainMenuMain();
	void mainMenuUnpack();

	//charCreate cluster:
	void charCreatePack();
	void charCreateMain(player& p1);
	void charCreateSend(player& p1); //Send player info and call unpack
	void charCreateUnpack(player& p1); //Takes player so it can pass it to gameMenu

	//gameMenu cluster:
	void gameMenuPack();
	void gameMenuMain(player& p1);

protected:
	//Signal handlers:
	//Main Menu:
	void on_exit_button_clicked();
	void on_newgame_button_clicked();
	void on_loadgame_button_clicked();

	//Child widgets:
	//Main Menu
	Gtk::Frame mainMenu_Frame; //title
	Gtk::Box mainMenu_VBox; //vertical
	Gtk::Button mainMenu_Button_NewGame, mainMenu_Button_LoadGame,
	            mainMenu_Button_Exit;
	Gtk::Label mainMenu_Info; //info label containing version, repo link, etc.

	//Create character
	Gtk::Frame charCreate_Frame; //title
	Gtk::Box charCreate_VBox; //vertical
	Gtk::Entry charCreate_NameEntry;
	classSelection charCreate_classSelect; //class selection module
	//Gtk::Label m_Label_Hack; //stupid label we use to get rid of whitespace
	Gtk::Button charCreate_Button_Accept;

	//Game Menu
	Gtk::Frame gameMenu_Frame; //title
	Gtk::Box gameMenu_VBox; //vertical "dad" box
	Gtk::Box gameMenu_Top_HBox, gameMenu_Bottom_HBox; //primary horizontal boxes

	Gtk::Box gameMenu_TStatus_VBox, gameMenu_TSecond_VBox; //the two verticle boxes of top box
	Gtk::Box gameMenu_TSecOption_HBox; //the horizontal box of top second
	//Bottom box of game menu
	//stuff will go here later

	//Game Menu widgets
	//Frames for stuff
	playerInfo gameMenu_PlayerInfo; //player info frame
	Gtk::Frame gameMenu_Maze_Frame, gameMenu_Msglog_Frame;

};

#endif //__MAIN_WINDOW_H__
