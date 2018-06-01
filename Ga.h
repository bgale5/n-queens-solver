#ifndef GA_H
#define GA_H

#include "State.h"

class Ga
{
	public:
	/* Member Variables */
	int pop_size;
	int pool_size;
	int n;
	int max_generations;
	std::vector<std::shared_ptr<State> > population;
	std::vector<std::shared_ptr<State> > pool;
	std::shared_ptr<State> world_best;

	/* Member Functions */
	Ga(int n, int pop_size, int max_genrations);
	int run();
	void init_population();
	static State *find_best_state(std::vector<State> pop);
	void crossover_all();
	void mutate_all();
};

#endif