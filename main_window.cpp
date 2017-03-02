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

#include "main_window.h" //class def
#include <string> //info on main menu
#include "start.h" //start game funcs for newgame/loadgame buttons
#include "universal.h" //version string
#include "class_selection.h" //class_selection calls for create_char
#include "player.h" //set_player in create_char

/* main_window default constructor
	We start the game here, so we construct it around the main menu
*/
main_window::main_window()
: m_Main_VBox(Gtk::ORIENTATION_VERTICAL), //main
  m_MainMenu("Main Menu"), //main menu
  m_MainMenu_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_NewGame("New Game"),
  m_Button_LoadGame("Load Game"),
  m_Button_Exit("Exit"),
  m_CreateCharacter("Create a New Character"), //create character
  m_CreateCharacter_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Accept("Accept")
{
	set_title("albino");
	add(m_Main_VBox);

	//pack main menu frame
	m_Main_VBox.pack_start(m_MainMenu, Gtk::PACK_SHRINK, 10);

	//set main menu box and add it to the frame
	m_MainMenu_VBox.set_border_width(10);
	m_MainMenu.add(m_MainMenu_VBox);

	//button signals
	m_Button_NewGame.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_newgame_button_clicked));
	m_Button_LoadGame.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_loadgame_button_clicked));
	m_Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_exit_button_clicked));

	//pack buttons into box
	m_MainMenu_VBox.pack_start(m_Button_NewGame, Gtk::PACK_SHRINK);
	m_MainMenu_VBox.pack_start(m_Button_LoadGame, Gtk::PACK_SHRINK);
	m_MainMenu_VBox.pack_start(m_Button_Exit, Gtk::PACK_SHRINK);

	//set the info for the main menu
	std::string info = "Version " + VERSION + "\nBuilt on " + __DATE__ +
	                   " at " + __TIME__ + ".\nCreated by Michael Ranciglio\n" +
	                   "Sources can be found at: https://github.com/Snepsts/albino";

	//add it to the label
	m_Label_Info.set_text(info);

	//pack it
	m_MainMenu_VBox.pack_start(m_Label_Info, Gtk::PACK_SHRINK);

	show_all_children();
}

void main_window::on_newgame_button_clicked()
{
	start_game(false, *this);
}

void main_window::on_loadgame_button_clicked()
{
	start_game(true, *this);
}

void main_window::on_exit_button_clicked()
{
	hide();
}

main_window::~main_window()
{
}

void main_window::end_main_menu()
{
	m_Main_VBox.remove(m_MainMenu);
}

void main_window::create_char(player& p1)
{
	//pack create character frame
	m_Main_VBox.pack_start(m_CreateCharacter, Gtk::PACK_SHRINK, 10);

	//set create character box and add it to the frame
	m_CreateCharacter_VBox.set_border_width(10);
	m_CreateCharacter.add(m_CreateCharacter_VBox);

	//Entry for entering a name
	m_Name_Entry.set_max_length(50); //limit name size
	m_Name_Entry.set_placeholder_text("Enter a name.");

	//The following set text is what we use to keep the window at a minimum width
	m_Label_Hack.set_text("--------------------------------------------------------------");
/*
	m_Button_Accept.signal_clicked().connect(sigc::bind<std::string>(
		sigc::bind<int>(sigc::mem_fun(p1, &player::set_player),
			m_Class_Selection.class_choice()),
			m_Name_Entry.get_text())
	);
*/
/*
	m_Button_Accept.signal_clicked().connect(sigc::bind<int>(
		sigc::bind<Glib::ustring>(sigc::mem_fun(&p1, &player::set_player),
			m_Name_Entry.get_text()),
			m_Class_Selection.class_choice())
	);
*/
	m_Button_Accept.signal_clicked().connect(sigc::bind<player>(
		sigc::mem_fun(*this, &main_window::send_player_info), p1)
	);
	//pack entry, selections, label and accept button into box
	m_CreateCharacter_VBox.pack_start(m_Name_Entry, Gtk::PACK_SHRINK);
	m_CreateCharacter_VBox.pack_start(m_Class_Selection);
	m_CreateCharacter_VBox.pack_start(m_Label_Hack, Gtk::PACK_SHRINK);
	m_CreateCharacter_VBox.pack_start(m_Button_Accept, Gtk::PACK_EXPAND_WIDGET);

	show_all_children();
}

void main_window::send_player_info(player& p1)
{
	p1.set_player(m_Class_Selection.class_choice(), m_Name_Entry.get_text());
	p1.display();
	end_create_char();
}

void main_window::end_create_char()
{
	m_Main_VBox.remove(m_CreateCharacter);
}

void main_window::initialize_game()
{
	//I forgot what was going to go here
}

void main_window::game_menu()
{

}
