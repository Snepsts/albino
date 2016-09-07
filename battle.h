/* Declaration of the battle function
	There's probably a better way to do this but I'll do it here for now.
*/

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "player.h"
#include "monster.h"

void battle(player& p1);
void displayact(action act, player& p1);
void damage(action act, player& p1, monster& m1);
void dmodify(action act, player& p1, monster& m1);
void omodify(action act, player& p1, monster& m1);

#endif
