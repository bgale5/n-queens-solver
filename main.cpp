#include <iostream>
#include "State.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	State s1(20);
	State s2(20);
	State s3(20);
	std::cout << "S1: " << std::endl;
	s1.print();
	std::cout << "S2: " << std::endl;
	s2.print();
	// std::cout << "S3: " << std::endl;
	// s3.print();
	s3.absorb(s2, s1);
	std::cout << "S3 After Absorbtion:" << std::endl;
	s3.print();
	return 0;
}
