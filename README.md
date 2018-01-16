# albino
#### By Michael Ranciglio
This is my first independent C++ project that I'm doing purely based on my own interest and betterment as a programmer.

## Building
I build this project using the gcc compiler (g++) and ncurses 6.0 (2016/02/13)

At this point in development, Linux (Ubuntu in particular) is the only OS I can guarantee this builds on. I currently use Linux Mint 18.1 on my laptop and Ubuntu 17.10 on my desktop.

Here's the packages you'll need from the get-go:

`sudo apt install build-essential g++ ncurses-dev git`

That should satisfy the dependencies, if there's any others feel free to let me know so I can add them.

You'll need to clone this git next:

`git clone https://github.com/Snepsts/albino.git`

Then change to the directory you just cloned it to.

If you're in the same dir you just cloned to:

`cd albino`

else:

`cd ~/path/to/albino`

Now here's the cool part, our makefile is cutting edge technology, so there's three options:

* debug
	* has all of the debugging and warnings enabled, also the default option
* test
	* has optimizations and warnings enabled
* release
	* has only optimizations enabled

These options will go after the make command if you know what you're doing. If you don't, just type:

`make`

Boom, albino is compiled. To run it, you'll need to do:

`./albino.out`

And that's all there is to it!

## About
This was originally meant to be a little "game" for having fun with random number generation and simple variable modification.

Now it has expanded to writing objects, making them interact, using a GUI API and perhaps a story. It is more of a text-based RPG/roguelike now. I will continue to pursue my goal of writing underlying basis of the game myself, the only libraries I plan on depending on (besides std::) are the ncurses libraries, and maybe boost. This is all subject to change though.

## Goals

* A balanced system of strength, defense, speed, and other stats.

* Solid classes that are also balanced.

* Progression that feels constant and rewarding.

* A complex combat system that allows for easy modification and flexible arrangements.

* Good, uniform documentation that can be read and understood by most people.

* ncurses implementation.

* Overall, a game that can be considered complete in the simplest of forms.

Bonus Goals (Not necessarily going to happen):

* Magic or some sort of damage independent of strength.

* A story that at least works.

* Bosses.

* Weapons & Armor.

* Another form of Damage/Defense (like magic) along with Standard Damage/Defense (possibilities of hybrid classes and such).

* Other stuff probably.

## License

Copyright (C) 2017-2018 Michael Ranciglio

This program is free software and subject to the terms of Version 3 of the GNU General Public License as published by the Free Software Foundation.

This program comes WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

----

I'll write more here later, but for now, enjoy.
