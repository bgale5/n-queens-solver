#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	// /* int n, int pop_size, int max_generations*/
	// Ga solver(100, 12, 1000000);
	// //int generations = solver.run();
	// double time = solver.run();
	// std::cout << "Solution found in " << time << " seconds" << std::endl;
	// return 0;
	
	State a(11);
	State b(a.serialize());
	a.print();
	State::print_vect(a.serialize());
	b.print();
}
