#include <iostream>
#include "State.h"
#include "Ga.h"

int main(int argc, char const *argv[])
{
	Ga solver(20, 20, 10000);
	solver.run();
	return 0;
}
