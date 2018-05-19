#include "State.h"
#include <cstdlib>
State::State(int n)
{
	this->n = n;
	this->queens.reserve(n);
	this->randomize();
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
	Fitness fit = {left_diagonal, right_diagonal, total};
	return fit;
}

bool State::vacant_row(int row)
{
	for (int i = 0; i < n; i++)
	{
		if (queens[i] == row)
			return false;
	}
	return true;
}

void State::randomize()
{
	for (int i = 0; i < n; i++)
	{
		int row;
		do
		{
			row = rand() % n;
		} while (!vacant_row(row));
		queens[i] = row;
	}
}