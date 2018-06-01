#include "Ga.h"
#include <iostream>

using State_ptr = std::shared_ptr<State>;

Ga::Ga(int n, int pop_size, int max_generations, int segment_divisor)
{
	this->pop_size = pop_size;
	this->segment_divisor = segment_divisor;
	this->pool_size = 2 * pop_size;
	this->n = n;
	this->max_generations = max_generations;
	population.reserve(pool_size);
	init_population();
}


void Ga::init_population()
{
	for (int i = 0; i < pool_size; i++)
		population.push_back(State_ptr(new State(n, segment_divisor)));
}

void Ga::crossover_all()
{
	for (int i = pool_size - 1; i > pop_size; i--)
	{
		State_ptr parent1 = population[rand() % pop_size];
		State_ptr parent2 = population[rand() % pop_size];
		population[i]->absorb(*parent1, *parent2);
	}
}

void Ga::mutate_all()
{
	// for (int i = 0; i < pool_size; i++)
	// 	population[i]->mutate(10);
	for (int i = 0; i < pop_size; i++)
	{
		int j = i + pop_size;
		population[j] = population[i];
		population[j]->mutate(100);
	}
}

bool comp(const State_ptr s1, const State_ptr s2)
{
	return s1->fitness.overall < s2->fitness.overall;
}

int Ga::run()
{
	int generation;
	for(generation = 0; generation < max_generations; generation++)
	{
		// if (generation % 100 == 0 && generation > 1)
		// {
		// 	std::cout << "Generation: " << generation << std::endl;
		// 	world_best->print();
		// }
		crossover_all();
		mutate_all();
		std::sort(population.begin(), population.end(), comp);
		population[pool_size - 1]->randomize();
		world_best = population[0];
		if (world_best->fitness.overall == 0)
			break;
	}
	std::cout << "Best State:" << std::endl;
	world_best->print();
	return generation;
}