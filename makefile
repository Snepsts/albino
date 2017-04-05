# OBJS = game.o player.o monster.o action_queue.o battle.o
OBJS = game.o mainWindow.o start.o player.o classDef.o classSelection.o playerInfo.o
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
GFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`

albino : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o albino.out $(GFLAGS)

game.o : game.cpp mainWindow.h
	$(CC) $(CFLAGS) $(GFLAGS) game.cpp

mainWindow.o : mainWindow.cpp mainWindow.h start.h universal.h classSelection.h playerInfo.h player.h
	$(CC) $(CFLAGS) $(GFLAGS) mainWindow.cpp

start.o : start.cpp start.h mainWindow.h
	$(CC) $(CFLAGS) $(GFLAGS) start.cpp

player.o : player.cpp player.h
	$(CC) $(CFLAGS) $(GFLAGS) player.cpp

classDef.o : classDef.cpp classDef.h
	$(CC) $(CFLAGS) $(GFLAGS) classDef.cpp

classSelection.o : classSelection.cpp classSelection.h classDef.h classLabel.h
	$(CC) $(CFLAGS) $(GFLAGS) classSelection.cpp

playerInfo.o : playerInfo.cpp playerInfo.h player.h classDef.h
	$(CC) $(CFLAGS) $(GFLAGS) playerInfo.cpp
clean :
	rm -f *.o *.out *.txt
