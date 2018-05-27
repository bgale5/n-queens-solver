#include <iostream>
#include "State.h"

int main(int argc, char const *argv[])
{
	State test(6);
	test.randomize();
	test.print();
	test.compute_fitness();
	Fitness fit = test.fitness;
	std::cout << "Left diagonal:" << std::endl;
	State::print_vect(fit.left_diagonal);
	std::cout << "Right diagonal:" << std::endl;
	State::print_vect(fit.right_diagonal);
	std::cout << "Overall fitness: " << fit.overall << std::endl;
	return 0;
}
