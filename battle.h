/* Declaration of the battle function
	There's probably a better way to do this but I'll do it here for now.

	As a notice: the battle function is only in it's first functional state.
	There will be many changes towards the entire functionality of this function
	(for example, not being limited to a 1 on 1 battle, more streamlined to include
	all sorts of different effects/calculations, and a more modular approach with
	more fancy function calls)

	For now it works and the focus will be on the entirety of the game including
	the battle function and it's components.
*/

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "player.h"
#include "monster.h"

/* function battle (friend of monster and player)
	Task: To house the many functions of a "battle" where the player object
	interacts with the monster object. Also to do it all in the right order.

	Takes the argument "player p1" by reference so it can modify the player's
	stats within it's functional limits.

	It is a friend function with player and monster only to access their speed
	for the two parameters of the "calculation" function (action_queue) right now.
	This will probably change in the near future.

	This function will explicitly call displayact before it's carried out,
	then it will evaluate the type of the action with a switch-case, and call:
	damage if the action is of type 0,
	dmodify if the action is of type 1, or
	omodify if the action is of type 2.

	Therefore there is little to no need for additional calls to the other
	functions.

	todo:
		- Make it so damage is not subtracted if it's less than 1 (say took no
		  damage instead)
*/
void battle(player& p1);

/* function displayact (friend of player)
	Task: To simply do some text output of the action being done. For example:
	if it's a monster-owned action, it'll say "Monster used >attack name here<!"

	Takes the player as a parameter soley to give off the player's name.

	Takes the action parameter so it knows what the action is called and who owns
	it.
*/
void displayact(action act, player& p1);

/* function damage (friend of monster and player)
	Task: To apply the damage calculation with the user's strength and reciever's
	defense (whenever the action's type is 0)

	Takes the action as a parameter so it knows who is attacking and it's modifier.

	Takes the player and monster by reference so it can modify hp and as a friend
	for access to strength and defense.

	It also does some tricky stuff with calculation to make the battle a little
	more interesting, and that will need a LOT of tweaking, but that's a lower
	level priority. Overall this function is decent enough and probably won't
	require anymore basic functionality changes until the whole battle system is
	revised later on.
*/
void damage(action act, player& p1, monster& m1);

/* function dmodify (friend of monster and player)
	Task: To add the modifier to the appropriate player/monster stat.

	Takes the action as a parameter to get the subtype and the modifier value.

	Takes the player/monster to add their respective stats with the modifier.

	Upon deciding which subtype is used and who owns the action, the function then
	does "mod + stat" to improve the stat. Pretty basic stuff, right?

	todo:
		- Add text for improving the stats so the player knows what's up.
		- Do some proper code and create class functions for the functionality
		  to clean up the code (call functions for each case-switch instead of
		  doing it all right there.)
	    - Possibly something easier/nicer than case-switch/if else statements???

	This function is VERY sloppy right now, as it is a friend just to do some
	basic adding shit. It also uses a lot of repetitive code that looks ugly
	(looking at you, excessive case-switch statements) and could probably be
	implemented better with class functions for the player/monster.
*/
void dmodify(action act, player& p1, monster& m1);

/* function omodify (friend of monster and player)
	Task: To subtract the modifier from the appropriate player/monster stat.

	...basically what you just read in omodify (unless you skipped to here for
	some reason) but with subtraction instead

	Takes the action as a parameter to get the subtype and the modifier value.

	Takes the player/monster to add their respective stats with the modifier.

	Upon deciding which subtype is used and who owns the action, the function then
	does "stat - mod" to decay the value of the stat. Pretty basic stuff, right?

	todo:
		- Do some proper code and create class functions for the functionality
		  to clean up the code (call functions for each case-switch instead of
		  doing it all right there.)
	    - Possibly something easier/nicer than case-switch/if else statements???

	This function is VERY sloppy right now, as it is a friend just to do some
	basic subbing shit. It also uses a lot of repetitive code that looks ugly
	(looking at you, excessive case-switch statements) and could probably be
	implemented better with class functions for the player/monster.
*/
void omodify(action act, player& p1, monster& m1);

#endif
