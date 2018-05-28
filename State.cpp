#include "State.h"
#include <cstdlib>
#include <iostream>

const double MUTATION_RATE = 0.1;

State::State(int n)
{
	this->n = n;
	queens.resize(n);
	randomize();
}
State::State(const State &s)
{
	n = s.n;
	queens.resize(n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
	copy_fitness(s);
}

void State::compute_fitness()
{
	fitness.left_diagonal.resize(2*n-1);
	fitness.right_diagonal.resize(2*n-1);
	std::fill(fitness.left_diagonal.begin(), fitness.left_diagonal.end(), 0);
	std::fill(fitness.right_diagonal.begin(), fitness.right_diagonal.end(), 0);
	fitness.overall = 0;
	fitness.left_total = 0;
	fitness.right_total = 0;
	for (int i = 0; i < n; ++i)
	{
		fitness.left_diagonal[i+queens[i]]++;
		fitness.right_diagonal[(n-1)-i+queens[i]]++;
	}
	for (int i = 0; i < 2*n-1; i++)
	{
		if (fitness.left_diagonal[i] > 1)
		{
			fitness.overall += fitness.left_diagonal[i] - 1;
			fitness.left_total += fitness.left_diagonal[i];
		}	
		if (fitness.right_diagonal[i] > 1)
		{
			fitness.overall += fitness.right_diagonal[i] - 1;
			fitness.right_total += fitness.right_diagonal[i];
		}		
	}
}

bool State::vacant_row(int row, int exclude_col)
{
	for (int i = 0; i < n; i++)
	{
		if (queens[i] == row && i != exclude_col)
			return false;
	}
	return true;
}

void State::randomize()
{
	for (int i = 0; i < n; i++)
	{
		int row = rand() % n;
		while(!vacant_row(row, i))
			row = rand() % n;
		queens[i] = row;
	}
	compute_fitness();
}

void State::mutate()
{
	double chance = (double)rand() / (double)RAND_MAX;
	if (chance > MUTATION_RATE)
		std::reverse(queens.begin(), queens.end());
	compute_fitness();
}

void State::operator=(const State &s)
{
	n = s.n;
	queens.resize(s.n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
	copy_fitness(s);
}

void State::copy_fitness(const State &s)
{
	fitness.overall = s.fitness.overall;
	fitness.left_total = s.fitness.left_total;
	fitness.right_total = s.fitness.right_total;
	fitness.left_diagonal.resize(s.fitness.left_diagonal.size());
	fitness.right_diagonal.resize(s.fitness.right_diagonal.size());
	for (int i = 0; i < s.n * 2 - 1; i++)
	{
		fitness.left_diagonal[i] = s.fitness.left_diagonal[i];
		fitness.right_diagonal[i] = s.fitness.right_diagonal[i];
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
	for (const auto &val : v)
		std::cout << val << ", " << std::endl;
	std::cout << "]" << std::endl;
}

void State::fill_gaps()
{
	for(int i = 0; i < n; i++)
	{
		if (queens[i] != -1)
			continue; // Not a gap
		int row = rand() % n;
		while(!vacant_row(row, i))
			row = rand() % n;
		queens[i] = row;
	}
}

void State::absorb(const State &parent1, const State &parent2)
{
	
	std::fill(queens.begin(), queens.end(), -1);
	const State *best = &parent1, *worst = &parent2;
	for (int i = 0; i < n*2-1; i++)
	{
		int wfl = worst->fitness.left_diagonal[i];
		int bfl = best->fitness.left_diagonal[i];
		if ((wfl < bfl && wfl > 0) || (wfl == 1) || bfl == 0)
		{
			std::swap(best, worst);
			//std::cout << "Diag: " << i << " Best: " << best << std::endl;
		}
		for (int j=0; j < n; j++)
		{
			int row = i - j;
			if (row < 0)
				break; // This diagonal is done.
			if (row >= n)
				continue; // Diagonal hasn't begun yet.
			if (best->queens[j] == row && vacant_row(row, j))
				queens[j] = row;
		}
	}
	fill_gaps();
	compute_fitness();
}