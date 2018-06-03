#include "State.h"
#include <cstdlib>
#include <iostream>

const double MUTATE_REVERSE_RATE = 0.3;
const double MUTATE_SHUFFLE_RATE = 0.3;
using vect_iter = std::vector<int>::iterator;

State::State(int n)
{
	this->n = n;
	queens.resize(n);
	occupied_rows.resize(n, 0);
	randomize();
}
State::State(const State &s)
{
	n = s.n;
	queens.resize(n);
	occupied_rows.resize(n, 0);
	fitness.overall = s.fitness.overall;
	fitness.left_total = s.fitness.left_total;
	fitness.right_total = s.fitness.right_total;
	for (int i=0; i<s.n; i++)
	{
		queens[i] = s.queens[i];
		occupied_rows[i] = s.occupied_rows[i];
	}
}

void State::operator=(const State &s)
{
	n = s.n;
	queens.resize(s.n);
	occupied_rows.resize(n, 0);
	fitness.overall = s.fitness.overall;
	fitness.left_total = s.fitness.left_total;
	fitness.right_total = s.fitness.right_total;
	for (int i=0; i<s.n; i++)
	{
		queens[i] = s.queens[i];
		occupied_rows[i] = s.occupied_rows[i];
	}
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
}

void State::move(int index, int row)
{
	if (queens[index] != -1)
		occupied_rows[queens[index]]--;
	queens[index] = row;
	occupied_rows[row]++;
}

void State::randomize()
{
	for (int i = 0; i < n; i++)
		queens[i] = i;
	std::random_shuffle(queens.begin(), queens.end());
	std::fill(occupied_rows.begin(), occupied_rows.end(), 1);
	compute_fitness();
}

void State::mutate(double chance)
{
	if (rand() % 100 < chance)
	{
		vect_iter first = queens.begin() + rand() % n;
		vect_iter second = queens.begin() + rand() % n;
		std::swap(*first, *second);
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

std::vector<int> State::serialize()
{
	std::vector<int> board;
	board.reserve(2 * n + 4);
	// Get the metadata
	board.push_back(n);
	board.push_back(fitness.left_total);
	board.push_back(fitness.right_total);
	board.push_back(fitness.overall);
	// Get the queens
	for (auto &q : queens)
		board.push_back(q);
	// Get the occupied rows
	for (auto &o : occupied_rows)
		board.push_back(o);
	return board;
}

State::State(const std::vector<int> &board)
{
	// Unpack the metadata
	n = board[0];
	queens.reserve(n);
	occupied_rows.reserve(n);	
	fitness.left_total = board[1];
	fitness.right_total = board[2];
	fitness.overall = board[3];
	// Unpack the queens
	for (int i = 4; i < n + 4; i++)
		queens.push_back(board[i]);
	// Unpack the occupied rows
	for (int i = 4 + n; i < 2 * n + 4; i++)
		occupied_rows.push_back(board[i]);
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
	std::fill(occupied_rows.begin(), occupied_rows.end(), 0);
	int split_point =  rand() % n;// n / 2;
	for (int i = 0; i < split_point; i++)
		move(i, parent1.queens[i]);
	for (int i = split_point; i < n; i++)
		move(i, parent2.queens[i]);
	validate();
	compute_fitness();
}

int State::random_vacant_row()
{
	int row = rand() % n;
	do
	{
		row = (row + 1) % n;
	} while (occupied_rows[row] != 0);
	return row;
}

void State::validate()
{
	std::vector<int> indices;
	for (int i = 0; i < n; i++)
		indices.push_back(i); 
	std::random_shuffle(indices.begin(), indices.end()); // Random order to remove bias
	for (int &i : indices)
	{
		if (occupied_rows[queens[i]] > 1)
			move(i, random_vacant_row());
	}
}

void State::flip()
{
	std::reverse(queens.begin(), queens.end());
	std::reverse(occupied_rows.begin(), occupied_rows.end());
	std::swap(fitness.left_total, fitness.right_total);
}

bool State::vacant(int row)
{
	if (row == -1)
		return true;
	return ~occupied_rows[row];
}