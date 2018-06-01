#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	/* int n, int pop_size, int max_generations*/
	Ga solver(8, 12, 1000000);
	int generations = solver.run();
	std::cout << "Solution found in " << generations << " iterations" << std::endl;
	return 0;
}
