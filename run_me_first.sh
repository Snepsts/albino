#!/bin/bash

SH_PREFIX="[SCRIPT]:"
alias s_echo="echo $SH_PREFIX" #declare s_echo to prevent rewriting echo "$SH_PREFIX"

s_echo "Grabbing pugixml from Github..."
git clone https://github.com/zeux/pugixml.git #get pugixml library

s_echo "Setting pugixml to version 1.8"
git -C pugixml checkout v1.8

if [ -d "lib" ]; then #if dir "lib" exists
	s_echo "Found existing lib directory, removing it."
	rm -rf lib
fi

s_echo "Creating and populating lib directory..."
mkdir lib #create dir "lib"
cp pugixml/src/pugixml.hpp lib/ #move the required header file to the lib folder
cp pugixml/src/pugiconfig.hpp lib/ #move the header that the other header requires to lib

s_echo "Compiling pugixml object file..."
g++ -std=c++11 -c pugixml/src/pugixml.cpp
s_echo "Creating static library object..."
ar -cvq libpugixml-1.8.a pugixml.o

mv libpugixml-1.8.a lib/ #move it to lib dir

s_echo "Cleaning up..."
rm -rf pugixml
rm pugixml.o

s_echo "You are ready to code, build or whatever else you wish to do!"
