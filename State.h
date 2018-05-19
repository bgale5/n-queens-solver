#ifndef STATE_H
#define STATE_H
#include <vector>
using Board = std::vector<unsigned int>;


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
	Board queens;
	std::vector<Board> segments;
	int n;
	bool vacant_row(int row);
	public:
	/* Public Member Functions */

	/**
	 * Constructor initialises the board with random queen positions
	 **/
	State(int n);
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

	std::ostream& operator<<(const State&);

	State operator+(const State&); // For the crossover
};

#endif