#!/bin/bash

SH_PREFIX="[SCRIPT]:"
alias s_echo="echo $SH_PREFIX" #declare s_echo to prevent rewriting echo "$SH_PREFIX"

s_echo "Grabbing pugixml from Github..."
git clone https://github.com/zeux/pugixml.git #get pugixml library

s_echo "Setting pugixml to version 1.8"
git -C pugixml checkout v1.8

if [ -d "include" ]; then #if dir "include" exists
	s_echo "Found existing include directory, removing it."
	rm -rf include
fi

s_echo "Creating and populating include directory..."
mkdir include #create dir "include"
cp pugixml/src/*.hpp include/

s_echo "Using cmake to configure pugixml..."
cmake pugixml/CMakeLists.txt
s_echo "Compiling pugixml..."
make -C pugixml

if [ -d "lib" ]; then #if dir "lib" exists
	s_echo "Found existing lib directory, removing it."
	rm -rf lib
fi

s_echo "Creating and populating lib directory..."
mkdir lib #create dir "lib"

cp pugixml/libpugixml.a lib/ #move the static library archive to the lib folder

s_echo "Cleaning up..."
rm -rf pugixml

s_echo "You are ready to code, build or whatever else you wish to do!"
