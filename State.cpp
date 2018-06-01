#include "State.h"
#include <cstdlib>
#include <iostream>

const double MUTATE_REVERSE_RATE = 0.3;
const double MUTATE_SHUFFLE_RATE = 0.3;
using vect_iter = std::vector<int>::iterator;

State::State(int n, int subset_divisor)
{
	this->n = n;
	this->subset_divisor = subset_divisor;
	queens.resize(n);
	randomize();
}
State::State(const State &s)
{
	n = s.n;
	subset_divisor = s.subset_divisor;
	queens.resize(n);
	fitness.overall = s.fitness.overall;
	fitness.left_total = s.fitness.left_total;
	fitness.right_total = s.fitness.right_total;
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
}

void State::operator=(const State &s)
{
	n = s.n;
	subset_divisor = s.subset_divisor;
	queens.resize(s.n);
	fitness.overall = s.fitness.overall;
	fitness.left_total = s.fitness.left_total;
	fitness.right_total = s.fitness.right_total;
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
}

void State::compute_fitness()
{
	// Initialise
	std::vector<int> left_diagonal(2 * n - 1, 0);
	std::vector<int> right_diagonal(2 * n - 1, 0);
	fitness.overall = 0;
	fitness.left_total = 0;
	fitness.right_total = 0;
	// Find diagonal conflicts
	for (int i = 0; i < n; ++i)
	{
		if (i <= n / 2)
			fitness.left_total++;
		else
			fitness.right_total++;
		left_diagonal[i+queens[i]]++;
		right_diagonal[(n-1)-i+queens[i]]++;
	}
	// Count the diagonal conflicts
	for (int i = 0; i < 2*n-1; i++)
	{
		if (left_diagonal[i] > 1)
			fitness.overall += left_diagonal[i] - 1;
		if (right_diagonal[i] > 1)
			fitness.overall += right_diagonal[i] - 1;
	}
	// Horizontal conflicts
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (queens[i] == queens[j])
				{
					fitness.overall++;
					if (i < n / 2 && j < n / 2)
						fitness.left_total++;
					else if (i > n / 2 && j > n / 2)
						fitness.right_total++;
				}
		}
	}
}

void State::randomize()
{
	for (int i = 0; i < n; i++)
		queens[i] = i;
	std::random_shuffle(queens.begin(), queens.end());
	compute_fitness();
}

void State::mutate(double chance)
{
	if (rand() % 100 < chance)
	{
		queens[rand() % n] = rand() % n;
		compute_fitness();
	}
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
	std::cout << "Overall fitness: " << fitness.overall << std::endl;
	std::cout << "Address: " << this << std::endl;
}

void State::print_vect(const std::vector<int> &v)
{
	std::cout << "[" << std::endl;
	for (int i = 0; i < (int)v.size(); i++)
	{
		std::cout << v[i] << ", ";
		if (i % 10 == 0 && i > 1)
			std::cout << std::endl;
	}
	std::cout << "]" << std::endl;
}

void State::absorb(State parent1, State parent2)
{
	std::fill(queens.begin(), queens.end(), -1);
	if (parent1.fitness.right_total < parent1.fitness.left_total)
		std::reverse(parent1.queens.begin(), parent1.queens.end());
	if (parent2.fitness.right_total < parent2.fitness.left_total)
		std::reverse(parent2.queens.begin(), parent2.queens.end());
	for (int i = 0; i < n / 2; i++)
		queens[i] = parent1.queens[i];
	for (int i = n / 2; i < n; i++)
		queens[i] = parent2.queens[i];
	compute_fitness();
}