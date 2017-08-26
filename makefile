# OBJS = game.o player.o monster.o action_queue.o battle.o
OBJS = game.o main_window.o start.o player.o class_def.o class_selection.o player_info.o
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
GFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`

albino : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o albino.out $(GFLAGS)

game.o : game.cpp main_window.h
	$(CC) $(CFLAGS) $(GFLAGS) game.cpp

main_window.o : main_window.cpp main_window.h start.h universal.h class_selection.h player_info.h player.h
	$(CC) $(CFLAGS) $(GFLAGS) main_window.cpp

start.o : start.cpp start.h main_window.h
	$(CC) $(CFLAGS) $(GFLAGS) start.cpp

player.o : player.cpp player.h
	$(CC) $(CFLAGS) $(GFLAGS) player.cpp

class_def.o : class_def.cpp class_def.h
	$(CC) $(CFLAGS) $(GFLAGS) class_def.cpp

class_selection.o : class_selection.cpp class_selection.h class_def.h class_label.h
	$(CC) $(CFLAGS) $(GFLAGS) class_selection.cpp

player_info.o : player_info.cpp player_info.h player.h class_def.h
	$(CC) $(CFLAGS) $(GFLAGS) player_info.cpp
clean :
	rm -f *.o *.out *.txt
