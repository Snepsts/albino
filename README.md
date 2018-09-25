# albino
#### By Michael Ranciglio
This is my first independent C++ project that I'm doing purely based on my own interest and betterment as a programmer.

## About
This was originally meant to be a little "game" for having fun with random number generation and simple variable modification.

Now it has expanded to writing objects, making them interact, using a GUI library and implementing design patterns.
 
In terms of game genres it is closest to an RPG/roguelike hybrid.

Like I said before, this is for my betterment as a programmer. Therefore I am writing this with minimal libraries in mind.

## Tools/Dependencies
I am currently developing this project using [CLion by JetBrains](https://www.jetbrains.com/clion/).

Dependencies as of this writing:
* Any version of the gcc compiler (g++) supporting C++ 14
* ncurses 6.0 (2016/02/13)
* cmake 3.10 (3.10.2-1ubuntu2)

## Libraries
This project uses [pugixml](https://github.com/zeux/pugixml) to traverse the files in the xml folder. It is fast, easy to use, and most importantly open source. It is all licensed under the MIT license.

Big time thanks to [zeux](https://github.com/zeux) for programming this awesome XML parsing library!

## Building
At this point in development, Linux (Ubuntu in particular) is the only OS I can guarantee this builds on. I currently use Ubuntu 18.04 on my development machines.

Here's the packages you'll need from the get-go:

`sudo apt install build-essential g++ ncurses-dev git cmake`

That should satisfy the dependencies, if there's any others feel free to let me know so I can add them.

You'll need to clone this git next:

`git clone https://github.com/Snepsts/albino.git`

Then change to the directory you just cloned it to.

If you're in the same dir you just cloned to:

`cd albino`

else:

`cd ~/path/to/albino`

Next, you'll need to set up the external libraries the project depends on. To do this, type:

`sh run_me_first.sh`

This only needs to be run once, unless you remove or mess with anything in the lib or include folder.

Next you'll type:

`cmake CMakeLists.txt`

This will prepare the make file. Afterwards, type:

`make`

Boom, albino is compiled. To run it, you'll need to do:

`./albino`

And that's all there is to it!

## Other notes about running
If you are using CLion like I am, you may find some frustrations with debugging/running. You'll want to attach run it in a terminal, hit attach to a local process from the CLion run menu, and choose the albino option.

This article may help: https://www.jetbrains.com/help/clion/2016.2/attaching-to-local-process.html

## Goals
* A balanced meta game system.

    * Class types that have a rock, paper, scissors-y feel.

    * Classes that are balanced and provide somewhat different play styles.

* Progression that feels constant and rewarding.

* A complex combat system that allows for easy modification and flexible arrangements.

* Good, uniform documentation that can be read and understood by most people.

* ncurses implementation.

* Overall, a game that can be considered complete in the simplest of forms.

## License
Copyright (C) 2017-2018 Michael Ranciglio

This program is free software and subject to the terms of Version 3 of the GNU General Public License as published by the Free Software Foundation.

This program comes WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
