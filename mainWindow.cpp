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

#include "mainWindow.h" //class def
#include "start.h" //start game funcs for newgame/loadgame buttons
#include "universal.h" //version string
#include "classSelection.h" //classSelection calls for charCreate
#include "playerInfo.h" //playerInfo for gameMenu
#include "player.h" //set_player in charCreate
#include <string> //info on main menu

/* mainWindow default constructor
	We start the game here, so we construct it around the main menu
*/
mainWindow::mainWindow()
: mainMenu_Frame("Main Menu"), //main menu
  mainMenu_VBox(Gtk::ORIENTATION_VERTICAL),
  mainMenu_Button_NewGame("New Game"),
  mainMenu_Button_LoadGame("Load Game"),
  mainMenu_Button_Exit("Exit"),
  charCreate_Frame("Create a New Character"), //create character
  charCreate_VBox(Gtk::ORIENTATION_VERTICAL),
  charCreate_Button_Accept("Accept"),
  gameMenu_Frame("Placeholder"), //game menu
  gameMenu_VBox(Gtk::ORIENTATION_VERTICAL),
  gameMenu_Top_HBox(Gtk::ORIENTATION_HORIZONTAL),
  gameMenu_Bottom_HBox(Gtk::ORIENTATION_HORIZONTAL),
  gameMenu_TStatus_VBox(Gtk::ORIENTATION_VERTICAL),
  gameMenu_TSecond_VBox(Gtk::ORIENTATION_VERTICAL),
  gameMenu_TSecOption_HBox(Gtk::ORIENTATION_HORIZONTAL),
  gameMenu_Maze_Frame("Maze"),
  gameMenu_Msglog_Frame("Message Log")
{
	set_title("albino"); //set the game title
	mainMenuMain(); //go to mainMen
}

void mainWindow::mainMenuPack()
{
	add(mainMenu_Frame); //add our main menu frame to the window

	//set main menu box and add it to the frame
	mainMenu_VBox.set_border_width(10); //NOTE: the mainMenu_VBox is where all
	mainMenu_Frame.add(mainMenu_VBox);  //of the magic happens

	//pack buttons into box
	mainMenu_VBox.pack_start(mainMenu_Button_NewGame, Gtk::PACK_SHRINK);
	mainMenu_VBox.pack_start(mainMenu_Button_LoadGame, Gtk::PACK_SHRINK);
	mainMenu_VBox.pack_start(mainMenu_Button_Exit, Gtk::PACK_SHRINK);

	//pack our information label
	mainMenu_VBox.pack_start(mainMenu_Info, Gtk::PACK_SHRINK);

	show_all_children();
}

void mainWindow::mainMenuMain()
{
	mainMenuPack();

	//button signals
	mainMenu_Button_NewGame.signal_clicked().connect(
		sigc::mem_fun(*this, &mainWindow::on_newgame_button_clicked));
	mainMenu_Button_LoadGame.signal_clicked().connect(
		sigc::mem_fun(*this, &mainWindow::on_loadgame_button_clicked));
	mainMenu_Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &mainWindow::on_exit_button_clicked));

	//set the info for the main menu
	std::string info = "Version " + VERSION + "\nBuilt on " + __DATE__ +
	                   " at " + __TIME__ + ".\nCreated by Michael Ranciglio\n" +
	                   "Sources can be found at: https://github.com/Snepsts/albino";

	//add it to the label
	mainMenu_Info.set_text(info);
}

void mainWindow::mainMenuUnpack()
{
	remove();
}

void mainWindow::on_newgame_button_clicked()
{
	start_game(false, *this);
}

void mainWindow::on_loadgame_button_clicked()
{
	start_game(true, *this);
}

void mainWindow::on_exit_button_clicked()
{
	hide(); //exits game
}

void mainWindow::charCreatePack()
{
	//add create character frame to this window
	add(charCreate_Frame);

	//set create character box and add it to the frame
	charCreate_VBox.set_border_width(10);
	charCreate_Frame.add(charCreate_VBox);

	//pack entry, selections, label and accept button into box
	charCreate_VBox.pack_start(charCreate_NameEntry, Gtk::PACK_SHRINK);
	charCreate_VBox.pack_start(charCreate_classSelect);
	//charCreate_VBox.pack_start(m_Label_Hack, Gtk::PACK_SHRINK);
	charCreate_VBox.pack_start(charCreate_Button_Accept, Gtk::PACK_EXPAND_WIDGET);

	show_all_children();
}

void mainWindow::charCreateMain(player& p1)
{
	charCreatePack();

	//Entry for entering a name
	charCreate_NameEntry.set_max_length(50); //limit name size
	charCreate_NameEntry.set_placeholder_text("Enter a name.");

	//The following set text is what we use to keep the window at a minimum width
	//m_Label_Hack.set_text("--------------------------------------------------------------");

	//bind the accept button to an external function
	charCreate_Button_Accept.signal_clicked().connect(sigc::bind<player>(
		sigc::mem_fun(*this, &mainWindow::charCreateSend), p1)
	);
}

void mainWindow::charCreateSend(player& p1)
{
	p1.set_player(charCreate_classSelect.getClass(), charCreate_NameEntry.get_text());
	p1.display();
	charCreateUnpack(p1);
}

void mainWindow::charCreateUnpack(player& p1)
{
	remove();
	gameMenuMain(p1);
}

void mainWindow::gameMenuPack()
{
	add(gameMenu_Frame);
	gameMenu_Frame.add(gameMenu_VBox); //add the main VBox

	//pack our two main boxes
	gameMenu_VBox.pack_start(gameMenu_Top_HBox, Gtk::PACK_SHRINK, 10);
	gameMenu_VBox.pack_start(gameMenu_Bottom_HBox, Gtk::PACK_SHRINK, 10);

	//pack the sub boxes of Top
	gameMenu_Top_HBox.pack_start(gameMenu_TStatus_VBox, Gtk::PACK_SHRINK, 10);
	gameMenu_Top_HBox.pack_start(gameMenu_TSecond_VBox, Gtk::PACK_SHRINK, 10);

	gameMenu_TStatus_VBox.pack_start(gameMenu_PlayerInfo, Gtk::PACK_SHRINK, 10);

	gameMenu_TSecond_VBox.pack_start(gameMenu_Msglog_Frame, Gtk::PACK_EXPAND_WIDGET, 10);
	gameMenu_TSecond_VBox.pack_start(gameMenu_TSecOption_HBox, Gtk::PACK_SHRINK, 10);

	show_all_children();
}

void mainWindow::gameMenuMain(player& p1)
{
	gameMenuPack();

	gameMenu_PlayerInfo.update(p1); //set the first values
}
