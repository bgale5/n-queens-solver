#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	if (argc < 2)
	{
		std::cout << "Not enough arguments" << std::endl;
		return 0;
	}
	int n = atoi(argv[1]);
	/* int n, int pop_size, int max_generations*/
	Ga solver(n, 12, 1000000);
	solver.run();
	return 0;
}
