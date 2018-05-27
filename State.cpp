#include "State.h"
#include <cstdlib>
#include <iostream>

State::State(int n)
{
	this->n = n;
	queens.resize(n);
	randomize();
	//compute_fitness();
}

State::State(const State& s)
{
	n = s.n;
	queens.resize(n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
	compute_fitness();
}

void State::compute_fitness()
{
	fitness.left_diagonal.resize(2*n-1, 0);
	fitness.right_diagonal.resize(2*n-1, 0);
	fitness.overall = 0;
	for (int i = 0; i < n; ++i)
	{
		fitness.left_diagonal[i+queens[i]]++;
		fitness.right_diagonal[(n-1)-i+queens[i]]++;
	}
	for (int i = 0; i < 2*n-1; i++)
	{
		if (fitness.left_diagonal[i] > 1)
			fitness.overall += fitness.left_diagonal[i] - 1;
		if (fitness.right_diagonal[i] > 1)
			fitness.overall += fitness.right_diagonal[i] - 1;
	}
}

bool State::vacant_row(int row, int col)
{
	for (int i = 0; i < n; i++)
	{
		if (i == col)
			continue;
		if (queens[i] == row)
			return false;
	}
	return true;
}

void State::randomize()
{
	for (int i = 0; i < n; i++)
	{
		int stuck = 0;
		int row = rand() % n;
		while(!vacant_row(row, i))
		{
			row = rand() % n;
			stuck++;
		}
		stuck = 0;
		queens[i] = row;
	}
}

void State::operator=(const State& s)
{
	n = s.n;
	queens.resize(s.n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
	compute_fitness();
}

void State::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << (queens[j] == i ? "Q   " : "*   ");
		std::cout << std::endl << std::endl;
	}
	print_vect(queens);
}

void State::print_vect(const std::vector<int>& v)
{
	std::cout << "[" << std::endl;
	for (const auto& val : v)
		std::cout << val << ", " << std::endl;
	std::cout << "]" << std::endl;
}
