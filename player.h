/* This is the player header. It represents the player class and is basically
the focus of the game. More stuff goes here later blah blah blah */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include "battle.h"
#include "action.h"

class monster;

class player
{
public:
	player();
	void choose_class();
	void level_up();
	void display();
	void save_game();
	void load_game();
	bool isAlive();
	void display_actions();
	void pbattle();
	action choice();
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
	int tstrength;
	int tdefense;
	int tspeed;
 	int classvar;
	int level;
	std::string name;
};

#endif
