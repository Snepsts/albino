# Code Format
We're using K&R style for the code. K&R are right.
## Naming Conventions
This project uses snake_case.
## Tabs or Spaces?
Tabs. A tab represents one level of indentation, and will be treated as such.
Do you like 2 space tabs? Cool, you can set your editor to represent tabs as 2
spaces so I don't have to see that garbage.
## Documentation Standards
Important documentation (the stuff found in header files) will be structured like so:

* First line (the /* ) will state what we are talking about (function, struct, etc) and the name of it.
* The next line will be a brief description of what we are describing.
* This splits if it's a structure or a function:
	* Structure: each data field will be explained with it's options.
		* An exception to this is if it's an enum explained somewhere else.
	* Function: (not all are always included, but will always be in this order)
		* More in-depth detail on the function.
		* Explanation of parameters.
		* Explanation of what it returns.

Function example:
```cpp
/* function get_directions
 * A function that grabs all available directions from a block.
 *
 * Takes an x and a y, and checks the adjacent blocks (assuming they're IN
 * the array) to see if they're open. If they are open, it adds chars to
 * represent open directions (u for up, d for down, r for right, and l for
 * left) to a string.
 *
 * Also takes a bool "isGen" to see if it was called from gen_main or not.
 * This defaults to false so you don't have to worry about passing a bool.
 * The purpose of this bool is if it's called for generation purposes, we
 * need to check for two "Unassigned"s, otherwise we're looking for "Open"
 * blocks.
 *
 * It returns said string containing all available directions.
 */
std::string get_directions(const int& x, const int& y, bool isGen = false) const;
```

Structure example:
```cpp
/* structure action
 * This structure represents the actions (selections) made by monsters/players.
 *
 * AType: Action type, one of three options:
 *  - Attack: Does damage to the opposing entity.
 *  - Heal: Adds health or removes negative status effects from the entity.
 *  - Item: Currently unused ask me about it later.
 * CType: Class type, one of four options:
 *  - Null: No specific class type or doesn't apply.
 *  - Melee: Does extra damage to ranged type entities.
 *  - Ranged: Does extra damage to magic type entities.
 *  - Magic: Does extra damage to melee type entities.
 * Intensity: Amplifies the damage an attack does.
 * Owner: This represents who is doing the move, it is an index in the vector
 * Target: This represents who is being targetted by the move. Vector index.
 * Name: This will be a basic name for the attack.
 * Desc: The description for the attack, not used currently but will make a
 *       standard for it eventually.
*/

struct action
{
	action_t atype;
	class_t ctype;
	ushort intensity;
	size_t owner, target;
	int speed;
	std::string name;
	std::string desc;
};
```
