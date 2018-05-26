#ifndef STATE_H
#define STATE_H
#include <vector>
using Board = std::vector<int>;


/* Data Structures */
typedef struct fitness
{
	std::vector<int> left_diagonal;
	std::vector<int> right_diagonal;
	int overall = 0;

} Fitness;

/* The State class represents a board configuration */
class State
{
	private:
	std::vector<int> queens;
	int n;
	bool vacant_row(int row, int col);
	public:
	/* Public Member Functions */

	/**
	 * Constructor initialises the board with random queen positions
	 **/
	State(int n);

	/**
	 * Copy constructor for initialising with another object
	 **/
	State(const State& s);

	/**
	 * Returns the number of diagonal conflicts
	 * Fitness value is normalised with respect to length of diagonals
	 * O(n) implementation
	 **/
	Fitness fitness();

	/**
	 * Fill board with random Queens
	 * Produces no horizontal conflicts
	 **/
	void randomize();


	void mutate();
	
	void shuffle_segments();

	void print();

	State operator<<(const State& s); // For the crossover
	State operator^(const State& s); // For other crossover method
	void operator=(const State& s); // For assignment
};

#endif