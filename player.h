/* This is the player header. It represents the player class and is basically
the focus of the game. More stuff goes here later blah blah blah */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string> //string
#include "battle.h" //battle functions (friend function declarations)
#include "action.h" //action object

class monster;	//this is a "forward declaration" (or something like that)
                //basically allows us to use the "friend" functions

class player
{
public:
	/* default constructor
		Task: Creates the player object with some base stats, will be adjusting
		these later :) */
	player();

	/* function choose_class
		Task: Has the player set the name and class of the character, then levels
		the character up 3 times.
		It does the following:
			- Allows the player to name himself/herself
			- Gives the player a choice between X classes
			- Overwrites the name and the class. Will probably seperate these
			  later. */
	void choose_class();

	/* function level_up
		This function ups the level variable and randomly ups stats depending on
		the class
		==============================================================
			todo: simplify the "algorithm" to require less code
		============================================================== */
	void level_up();

	/* function display
		Displays the player's stats with their name and class. */
	void display();

	/* function save_game
		Task: To save the player's stats/name/etc. Will also include progress
		probably at some point when that is included.

		Okay, here's where the coding starts (lol "starts") to get kinda sloppy.
		So it saves stats in a certain order to the file and the load_game
		function will load them in that same order, however everytime we add a new
		stat it will require changes in BOTH functions, so...
			todo: find a better method to save/load game stats.
			 	Perhaps streamline the order of stats in a single function? */
	void save_game();

	/* function load_game
		Task: To load the player's stats/name/etc. Will also include progress
		probably at some point when that is included.

		Returns true if successful, otherwise returns false.

		As I stated above, will probably streamline the order-part into one function
		later.
		See "save_game" */
	bool load_game();

	/* function isAlive
		Very basic bool, but makes for an easy "ensure player is alive" check */
	bool isAlive();

	/* function display_actions
		Task: To display the list of actions available to the player */
	void display_actions();

	/* function pbattle
		Task: To preform the pre/post battle step (to reset the temp battle
		variables) */
	void pbattle();

	/* function choice
	Task: To return the choice chosen by the player

	Asks for input on the choices and then returns it based on what the number
	the player inputs */
	action choice();

	//friend functions for the battle function set
	friend void battle(player& p1);
	friend void displayact(action act, player& p1);
	friend void damage(action act, player& p1, monster& m1);
	friend void dmodify(action act, player& p1, monster& m1);
	friend void omodify(action act, player& p1, monster& m1);

private:
	int health;
	int hp;
	int strength;
 	int defense;
 	int speed;
 	int classvar;
	int level;
	std::string name;
	/* tvariables are the temporary variables to be used in all battle related
	functions. This ensures the player's stat altercations will only be during
	the battle and are set to the default value at the beginning and end of each
	battle function call. */
	int tstrength;
	int tdefense;
	int tspeed;
};

#endif
