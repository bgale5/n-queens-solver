#include "State.h"
#include <cstdlib>
#include <iostream>
State::State(int n)
{
	this->n = n;
	queens.reserve(n);
	//this->randomize();
}

State::State(const State& s)
{
	n = s.n;
	queens.reserve(n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
}

Fitness State::fitness()
{
	std::vector<int> left_diagonal(2*n-1);
	std::vector<int> right_diagonal(2*n-1);
	for (int i = 0; i <= n; ++i)
	{
		left_diagonal[i + queens[i]]++;
		right_diagonal[n - i +queens[i]];
	}
	int counter = 0;
	int total = 0;
	for (int i = 0; i < 2*n-1; ++i)
	{
		if (left_diagonal[i] > 1)
			counter += left_diagonal[i] - 1;
		if (right_diagonal[i] > 1)
			counter += right_diagonal[i] - 1;
		total += counter / (n - abs(i - n));
	}
	Fitness fit;
	fit.left_diagonal = left_diagonal;
	fit.right_diagonal = right_diagonal;
	fit.overall = total;
	return fit;
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
		int a, b, c, d;
		a = queens[0];
		b = queens[1];
		c = queens[2];
		d = queens[3];
	}
}

State State::operator<<(const State& s)
{
	State child(n); // Start with a copy of the current state.
	child.queens = this->queens;
	//int l = 1 + rand() % (n - 1);
	//int r = 1 + rand() % (n - 1);
	int l = 1;
	int r = 4;
	if (r < l)
		std::swap(l, r);
	std::copy(s.queens.begin()+l, s.queens.begin()+r, child.queens.begin()+l);
	return child;
}

void State::operator=(const State& s)
{
	n = s.n;
	queens.resize(s.n);
	for (int i=0; i<s.n; i++)
		queens[i] = s.queens[i];
}

void State::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << (queens[j] == i ? "Q   " : "*   ");
		std::cout << std::endl << std::endl;
	}
	for (int i = 0; i < n; i++)
		std::cout << queens[i] << ", ";
	std::cout << std::endl;
}
