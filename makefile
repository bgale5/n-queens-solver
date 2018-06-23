CFLAGS=-O3 -std=c++11 -Wextra -pedantic -Wno-unused-parameter

nqueens: main.o State.o Ga.o state.h
	clang++ $(CFLAGS) -o nqueens main.o state.o Ga.o
main.o: main.cpp State.h Ga.h main.cpp
	clang++ $(CFLAGS) -c main.cpp
State.o: State.cpp
	clang++ $(CFLAGS) -c State.cpp
Ga.o: Ga.cpp
	clang++ $(CFLAGS) -c Ga.cpp
clean:
	rm nqueens *.o