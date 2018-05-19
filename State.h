#ifndef STATE_H
#define STATE_H
#include <vector>
using Board = std::vector<unsigned int>;

std::ostream& operator<<(std::ostream& strm, const State& s)
{
	return strm;
}

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
	friend std::ostream& operator<<(std::ostream& strm, const State& s);
	bool vacant_row(int row);
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

	/**
	 * Fill board with random Queens
	 * Produces no horizontal conflicts
	 **/
	void randomize();

	Fitness fitness();

	void mutate();
	
	void shuffle_segments();

	std::ostream& operator<<(const State&);

	State operator+(const State&); // For the crossover
};
#endif