#ifndef STATE_H
#define STATE_H
#include <vector>
using Board = std::vector<int>;


/* Data Structures */
typedef struct fitness
{
	std::vector<int> left_diagonal;
	std::vector<int> right_diagonal;
	int left_total = 0;
	int right_total = 0;
	int overall = 0;
} Fitness;

/* The State class represents a board configuration */
class State
{
	private:
	/* State data */
	std::vector<int> queens;

	/* Helper functions */
	bool vacant_row(int row, int exclude_col);
	void fill_gaps();
	

	public:
	/* Member variables */
	Fitness fitness;
	int n;
	/* Public Member Functions */
	/**
	 * Constructor initialises the board with random queen positions
	 **/
	State(int n);
	static void print_vect(const std::vector<int> &v);
	/**
	 * Copy constructor for initialising with another object
	 **/
	State(const State &s);

	/**
	 * Returns the number of diagonal conflicts
	 * Fitness value is normalised with respect to length of diagonals
	 * O(n) implementation
	 **/
	void compute_fitness();

	/**
	 * Fill board with random Queens
	 * Produces no horizontal conflicts
	 **/
	void randomize();

	void mutate();

	void absorb(const State &parent1, const State &parent2);

	void print();
	
	void operator=(const State &s); // For assignment
};

#endif
