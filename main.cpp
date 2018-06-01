#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Ga solver(20, 100, 1000, 4);
	int generations = solver.run();
	std::cout << "Solution found in " << generations << " iterations" << std::endl;
	return 0;
}
