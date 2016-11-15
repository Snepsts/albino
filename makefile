OBJS = game.o player.o monster.o action_queue.o battle.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

albino : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o albino.out

game.o : game.cpp player.h battle.h
	$(CC) $(CFLAGS) game.cpp

player.o : player.cpp player.h action.h
	$(CC) $(CFLAGS) player.cpp

monster.o : monster.cpp monster.h action.h
	$(CC) $(CFLAGS) monster.cpp

action_queue.o : action_queue.cpp action_queue.h action.h
	$(CC) $(CFLAGS) action_queue.cpp

battle.o : battle.cpp battle.h player.h monster.h action.h
	$(CC) $(CFLAGS) battle.cpp

clean :
	rm -f *.o *.out *.txt
