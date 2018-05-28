#include "Ga.h"
#include <iostream>

using State_ptr = std::shared_ptr<State>;

Ga::Ga(unsigned n, unsigned pop_size, unsigned max_generations)
{
	this->pop_size = pop_size;
	this->pool_size = pop_size + (pop_size * (pop_size - 1)) / 2;
	this->n = n;
	this->max_generations = max_generations;
	population.reserve(pop_size + (pop_size * (pop_size - 1)) / 2);
	init_population();
}


void Ga::init_population()
{
	for (unsigned i = 0; i < pool_size; i++)
		population.push_back(State_ptr(new State(n)));
}

void Ga::crossover_all()
{
	unsigned counter = pop_size;
	for (unsigned i = 0; i < pop_size - 1; i++)
	{
		for (unsigned j = i + 1; j < pop_size; j++)
		{
			State_ptr child = population[counter++];
			child->absorb(*population[i], *population[j]);
		}
	}
}

void Ga::mutate_all()
{
	for (auto &state : population)
		state->mutate();
}

bool comp(const State_ptr s1, const State_ptr s2)
{
	return s1->fitness.overall < s2->fitness.overall;
}

void Ga::run()
{
	for(unsigned generation = 0; generation < max_generations; generation++)
	{
		crossover_all();
		mutate_all();
		std::sort(population.begin(), population.end(), comp);
		world_best = population[0];
		if (world_best->fitness.overall == 0)
			break;
	}
	std::cout << "Best State:" << std::endl;
	world_best->print();
}