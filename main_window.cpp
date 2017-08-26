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
#include "start.h" //start game funcs for newgame/loadgame buttons
#include "universal.h" //version string
#include "class_selection.h" //classSelection calls for char_create
#include "player_info.h" //playerInfo for game_menu
#include "player.h" //set_player in char_create
#include <string> //info on main menu

/* main_window default constructor
	We start the game here, so we construct it around the main menu
*/
main_window::main_window()
: main_menu_Frame("Main Menu"), //main menu
  main_menu_VBox(Gtk::ORIENTATION_VERTICAL),
  main_menu_Button_new_game("New Game"),
  main_menu_Button_load_game("Load Game"),
  main_menu_Button_exit("Exit"),
  char_create_Frame("Create a New Character"), //create character
  char_create_VBox(Gtk::ORIENTATION_VERTICAL),
  char_create_Button_accept("Accept"),
  game_menu_Frame("Placeholder"), //game menu
  game_menu_VBox(Gtk::ORIENTATION_VERTICAL),
  game_menu_HBox_top(Gtk::ORIENTATION_HORIZONTAL),
  game_menu_HBox_bottom(Gtk::ORIENTATION_HORIZONTAL),
  game_menu_VBox_top_status(Gtk::ORIENTATION_VERTICAL),
  game_menu_VBox_top_second(Gtk::ORIENTATION_VERTICAL),
  game_menu_HBox_top_second_option(Gtk::ORIENTATION_HORIZONTAL),
  game_menu_Frame_maze("Maze"),
  game_menu_Frame_msglog("Message Log")
{
	set_title("albino"); //set the game title
	main_menu_main(); //go to main_menu_main
}

void main_window::main_menu_pack()
{
	add(main_menu_Frame); //add our main menu frame to the window

	//set main menu box and add it to the frame
	main_menu_VBox.set_border_width(10); //NOTE: the main_menu_VBox is where all
	main_menu_Frame.add(main_menu_VBox);  //of the magic happens

	//pack buttons into box
	main_menu_VBox.pack_start(main_menu_Button_new_game, Gtk::PACK_SHRINK);
	main_menu_VBox.pack_start(main_menu_Button_load_game, Gtk::PACK_SHRINK);
	main_menu_VBox.pack_start(main_menu_Button_exit, Gtk::PACK_SHRINK);

	//pack our information label
	main_menu_VBox.pack_start(main_menu_Label_info, Gtk::PACK_SHRINK);

	show_all_children();
}

void main_window::main_menu_main()
{
	main_menu_pack();

	//button signals
	main_menu_Button_new_game.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_newgame_button_clicked));
	main_menu_Button_load_game.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_loadgame_button_clicked));
	main_menu_Button_exit.signal_clicked().connect(
		sigc::mem_fun(*this, &main_window::on_exit_button_clicked));

	//set the info for the main menu
	std::string info = "Version " + VERSION + "\nBuilt on " + __DATE__ +
	                   " at " + __TIME__ + ".\nCreated by Michael Ranciglio\n" +
	                   "Sources can be found at: https://github.com/Snepsts/albino";

	//add it to the label
	main_menu_Label_info.set_text(info);
}

void main_window::main_menu_unpack()
{
	remove();
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
	hide(); //exits game
}

void main_window::char_create_pack()
{
	//add create character frame to this window
	add(char_create_Frame);

	//set create character box and add it to the frame
	char_create_VBox.set_border_width(10);
	char_create_Frame.add(char_create_VBox);

	//pack entry, selections, label and accept button into box
	char_create_VBox.pack_start(char_create_Entry_name, Gtk::PACK_SHRINK);
	char_create_VBox.pack_start(char_create_class_select);
	//char_create_VBox.pack_start(m_Label_Hack, Gtk::PACK_SHRINK);
	char_create_VBox.pack_start(char_create_Button_accept, Gtk::PACK_EXPAND_WIDGET);

	show_all_children();
}

void main_window::char_create_main(player& p1)
{
	char_create_pack();

	//Entry for entering a name
	char_create_Entry_name.set_max_length(50); //limit name size
	char_create_Entry_name.set_placeholder_text("Enter a name.");

	//The following set text is what we use to keep the window at a minimum width
	//m_Label_Hack.set_text("--------------------------------------------------------------");

	//bind the accept button to an external function
	char_create_Button_accept.signal_clicked().connect(sigc::bind<player>(
		sigc::mem_fun(*this, &main_window::char_create_send), p1)
	);
}

void main_window::char_create_send(player& p1)
{
	p1.set_player(char_create_class_select.get_class(), char_create_Entry_name.get_text());
	p1.display();
	char_create_unpack(p1);
}

void main_window::char_create_unpack(player& p1)
{
	remove();
	game_menu_main(p1);
}

void main_window::game_menu_pack()
{
	add(game_menu_Frame);
	game_menu_Frame.add(game_menu_VBox); //add the main VBox

	//pack our two main boxes
	game_menu_VBox.pack_start(game_menu_HBox_top, Gtk::PACK_SHRINK, 10);
	game_menu_VBox.pack_start(game_menu_HBox_bottom, Gtk::PACK_SHRINK, 10);

	//pack the sub boxes of Top
	game_menu_HBox_top.pack_start(game_menu_VBox_top_status, Gtk::PACK_SHRINK, 10);
	game_menu_HBox_top.pack_start(game_menu_VBox_top_second, Gtk::PACK_SHRINK, 10);

	game_menu_VBox_top_status.pack_start(game_menu_player_info, Gtk::PACK_SHRINK, 10);

	game_menu_VBox_top_second.pack_start(game_menu_Frame_msglog, Gtk::PACK_EXPAND_WIDGET, 10);
	game_menu_VBox_top_second.pack_start(game_menu_HBox_top_second_option, Gtk::PACK_SHRINK, 10);

	show_all_children();
}

void main_window::game_menu_main(player& p1)
{
	game_menu_pack();

	game_menu_player_info.update(p1); //set the first values
}
