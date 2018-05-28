#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	Ga solver(30, 100, 1000);
	unsigned generations = solver.run();
	std::cout << "Solution found in " << generations << " iterations" << std::endl;
	return 0;
}
