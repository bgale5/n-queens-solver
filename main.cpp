#include <iostream>
#include "State.h"

int main(int argc, char const *argv[])
{
	State test1(6);
	test1.print();
	std::cout << std::endl;
	State test2(6);
	test2.print();
	std::cout << std::endl;
	State test3(6);
	test3.print();
	std::cout << std::endl;
	return 0;
}
