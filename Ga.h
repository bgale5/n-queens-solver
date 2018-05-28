#ifndef GA_H
#define GA_H

#include "State.h"

class Ga
{
	public:
	/* Member Variables */
	unsigned pop_size;
	unsigned pool_size;
	unsigned n;
	unsigned max_generations;
	std::vector<std::shared_ptr<State> > population;
	std::vector<std::shared_ptr<State> > pool;
	std::shared_ptr<State> world_best;

	/* Member Functions */
	Ga(unsigned n, unsigned pop_size, unsigned max_genrations);
	void run();
	void init_population();
	static State *find_best_state(std::vector<State> pop);
	void crossover_all();
	void mutate_all();
};

#endif