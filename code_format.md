The actual format for the code will go here when I figure out the actual rules
I set for myself/the code. I have a format, but it's just kinda the way I've
always coded, I'm not sure how it's actually defined or how to write it out atm.

```c
//TODO: Either adopt a better code style or figure out what I use
```

# Code Format
## Naming Conventions
This project uses snake_case.

GUI code has a bit of a difference/a few exceptions.

* Names are always descriptive of where they come from/are referring to.

* Names that are describing Gtk objects will have those words capitalized. Ex:

Gtk::**Frame** game\_menu\_**Frame**\_maze;

* Box will have a capital *V* or *H* before the word Box to denote *Horizontal*
or *Vertical* status. Ex:

Gtk::**Box** game\_menu\_**VBox**;

That's the jist of it.

## Organization
Regarding GUI code, the game's sections (e.g. the main menu, or the character
creation screen) are broken up into "clusters". These clusters usually have 3
parts, but can have more.

These parts are usually:

* name\_of\_screen\_pack

* name\_of\_screen\_main

* name\_of\_screen\_unpack

Example:

```c
//main_menu cluster:
void main_menu_pack();
void main_menu_main();
void main_menu_unpack();
```

There are no real rules dictating arguments to these functions or how many there
can be. If it takes arguments it's probably modifying them (like the player).

Another example:

```c
//char_create cluster:
void char_create_pack();
void char_create_main(player& p1); //Needs player for send and unpack
void char_create_send(player& p1); //Send player info and call unpack
void char_create_unpack(player& p1); //Passes player to game_menu
```

Notice that one rule stays consistent; pack always comes first and unpack always
comes last.

When implementing them, main is the only one that is called by any other
function. The main function then calls pack at the beginning and unpack at the
end, along with anything else that qualifies for a separate function.

It is also important to note that the actual widgets that make up the clusters
are organized as such as well. Example:

```c
//Main Menu
Gtk::Frame main_menu_Frame; //title
Gtk::Box main_menu_VBox; //vertical
Gtk::Button main_menu_Button_new_game, main_menu_Button_load_game,
			main_menu_Button_exit;
Gtk::Label main_menu_Label_info; //info label containing version, link, etc.
```
