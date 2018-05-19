FLAGS=-g -std=gnu++11 -Werror -Wall

nqueens: main.o State.o
	clang++ $(FLAGS) -o nqueens main.o state.o
main.o: main.cpp State.h
	clang++ $(FLAGS) -c main.cpp
State.o:
	clang++ $(FLAGS) -c State.cpp