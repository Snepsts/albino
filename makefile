OBJS = game.o player.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

albino : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o albino

game.o : game.cpp player.h
	$(CC) $(CFLAGS) game.cpp

player.o : player.cpp player.h
	$(CC) $(CFLAGS) player.cpp
