#ifndef STATE_H
#define STATE_H
#include <vector>
using Board = std::vector<unsigned int>;

typedef struct fitness
{
	std::vector<int> left_diagonal;
	std::vector<int> right_diagonal;
	unsigned int overall = 0;

} Fitness;

class State
{
	private:
	Board queens;
	std::vector<Board> segments;
	int n;
	public:
	/* Public Member Functions */

	/**
	 * Constructor
	 **/
	State(int n);
	/**
	 * Returns the number of diagonal conflicts
	 * Fitness value is normalised with respect to length of diagonals
	 * O(n) implementation
	 **/

	void randomize();

	Fitness fitness();

	void mutate();
	
	void shuffle_segments();

	State operator+(const State&); // For the crossover
};
#endif