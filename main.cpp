#include <iostream>
#include "State.h"

int main(int argc, char const *argv[])
{
State test(5);
test.randomize();
State test1(5);
test1.randomize();
test1 = test;
test.print();
test1.print();
return 0;
}
