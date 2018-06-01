#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	/* int n, int pop_size, int max_generations, int segment_divisor */
	Ga solver(100, 1000, 1000000, 0);
	int generations = solver.run();
	std::cout << "Solution found in " << generations << " iterations" << std::endl;
	return 0;
}
