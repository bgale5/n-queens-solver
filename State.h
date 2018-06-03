#ifndef STATE_H
#define STATE_H
#include <vector>

/* Data Structures */
typedef struct fitness
{
	int left_total;
	int right_total;
	int overall;
} Fitness;

/* The State class represents a board configuration */
class State
{
	private:
	/* State data */
	std::vector<int> occupied_rows;

	/* Helper functions */
	//bool vacant_row(int row, int exclude_col);
	//void validate();
	int random_vacant_row();
	void validate();


	public:
	/* Member variables */
	Fitness fitness;
	std::vector<int> queens;

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
	State(const std::vector<int> &board);
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

	void mutate(double chance);

	void move(int index, int row);

	//void absorb_diagonal(const State &parent1, const State &parent2);
	void absorb(State parent1, State parent2);
	
	void flip();
	bool vacant(int row);

	void print();
	std::vector<int> serialize();
	
	void operator=(const State &s); // For assignment
};

#endif
