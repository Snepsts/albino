/* This is the player header. It represents the player class and is basically
the focus of the game. More stuff goes here later blah blah blah */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

using namespace std;

class player
{
public:
  player();
  void choose_class();
  void level_up();
  void display();
  void save_game();
  void load_game();

private:
  int health;
  int strength;
  int defense;
  int speed;
  int classvar;
	int level;
  string name;
};

#endif