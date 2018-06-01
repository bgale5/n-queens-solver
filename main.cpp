#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	/* int n, int pop_size, int max_generations*/
	Ga solver(20, 12, 1000000);
	//int generations = solver.run();
	double time = solver.time();
	std::cout << "Solution found in " << time << " seconds" << std::endl;
	return 0;
	
	// State a(8);
	// State b(8);
	// State c(8);
	// a.print();
	// b.print();
	// c.absorb(a, b);
	// c.print();
	// c.mutate(100);
	// c.print();
}
