CFLAGS=-g -std=gnu++11 -Wall -Wextra -pedantic

nqueens: main.o State.o state.h
	clang++ $(CFLAGS) -o nqueens main.o state.o
main.o: main.cpp State.h main.cpp
	clang++ $(CFLAGS) -c main.cpp
State.o: State.cpp
	clang++ $(CFLAGS) -c State.cpp