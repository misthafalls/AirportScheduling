#include "Selector.h"
#include "FitnessFunction.h"
#include <stdlib.h>
#include <vector>
#include "Time.h"
#include "Genome.h"
#include <ctime>

#include <iostream>

bool
RouletteSelector::select(std::vector<Genome*>& population,
								std::vector<Genome*>& selected,
								int sum_fitness ) {
	//This makes random safer in random generating.
	srand((unsigned int)time(0));

	size_t do_not_combine = 0;
	int combine_fitness = sum_fitness;

	//This list will eventually represent the indexes for genomes to combine.
	std::vector<int> to_combine(population.size(), 0);
	for( size_t i = 0; i < to_combine.size(); i++ )
		to_combine.push_back(i);

	while ( do_not_combine < population.size() - m_nr_combine ) {
		int select = (int) ((float)rand())/RAND_MAX * combine_fitness;
		int selected_genome = -1;

		int start_fitness = 0;
		for( size_t i = 0; i < to_combine.size(); i++ ) {
			if( select >= start_fitness &&
				select < start_fitness + population[to_combine[i]]->get_fitness()) {
				selected_genome = i;
				break;
			}
			start_fitness = start_fitness + population[to_combine[i]]->get_fitness();
		}

		if( selected_genome != -1) {
			combine_fitness -= population[to_combine[selected_genome]]->get_fitness();
			to_combine.erase( to_combine.begin() + selected_genome );
			do_not_combine++;
		}
	}

	for( size_t i = 0; i < to_combine.size(); i++ )
		selected.push_back( population[to_combine[i]] );

	size_t died = 0;
	while ( died < m_nr_die ) {
		int select = (int) ((float)rand())/RAND_MAX * sum_fitness;
		int delete_genome = -1;

		int start_fitness = 0;
		for( size_t i = 0; i < population.size(); i++ ) {
			if( select >= start_fitness &&
				select < start_fitness + population[i]->get_fitness()) {
				delete_genome = i;
				break;
			}
			start_fitness = start_fitness + population[i]->get_fitness();
		}

		if( delete_genome != -1) {
			sum_fitness -= population[delete_genome]->get_fitness();
			//TODO: Memory Leak!!! But also dangerous to perform delete, because of possible combinator action!
			population.erase( population.begin() + delete_genome );
			died++;
		}
	}
	return true;
}

bool
FittestSelector::select(std::vector<Genome*>& population,
                                std::vector<Genome*>& selected,
                                int sum_fitness ) {

//	for(int i = 0; i < population.size(); i++)
//		std::cout << "Start: " << i << " " << population[i]->get_fitness() << std::endl;

	//Very easy code, get the lowest fitness (in our case highest)
	//and remove it from the population.
	//TODO: Memory leak alert! Genome pointer stays there.
	size_t died = 0;
	while ( died < m_nr_die ) {
		int lowest_fitness = -1;
		size_t lowest_index = -1;
		for( size_t t=0;t<population.size();t++){
			if( lowest_fitness < population[t]->get_fitness() ) {
				lowest_fitness = population[t]->get_fitness();
				lowest_index = t;
			}
		}
		population.erase( population.begin()+lowest_index );
		died++;
	}

	std::vector<size_t> index_population;
	for(size_t i = 0; i < population.size(); i++) {
		index_population.push_back(i);
	}

	//Now get the highest fitness and put it into the select.
	size_t to_combine = 0;
	while ( to_combine < m_nr_combine ) {
		int highest_fitness = sum_fitness + 1;
		size_t highest_index = -1;

		for( size_t i = 0; i < index_population.size(); i++ ) {
			if( highest_fitness > population[index_population[i]]->get_fitness() ) {
				highest_fitness = population[index_population[i]]->get_fitness();
				highest_index = i;
			}
		}

		selected.push_back( population[index_population[highest_index]] );
		index_population.erase(index_population.begin() + highest_index);
		to_combine++;
	}

	return true;
}

bool
TournamentSelector::select(std::vector<Genome*>& population,
                                std::vector<Genome*>& selected,
                                int sum_fitness ) {
	//This makes random safer in random generating.
	srand((unsigned int)time(0));

	size_t died = 0;
	size_t to_combine = 0;
	while ( died < m_nr_die || to_combine < m_nr_combine ) {
		size_t population_size = population.size();

		size_t start_subset = (int) rand() % population_size;
		size_t end_subset   = (int) rand() % population_size;

		// When start and end are the same, then the random
		// generate gave us a unworkable subset.
		if( start_subset == end_subset ) {
			continue;
		//When start is bigger then end then swap them
		} else if( start_subset > end_subset ) {
			size_t tmp = start_subset;
			start_subset = end_subset;
			start_subset = tmp;
		}

		std::cout << "Population: " << population_size << " Start: " << start_subset << " End: " << end_subset << std::endl;

		if( died < m_nr_die ) {
			int lowest_fitness = -1;
			size_t lowest_index = -1;

			for( size_t i = start_subset; i < end_subset; i++ ) {
				if( lowest_fitness > population[i]->get_fitness() ) {
					lowest_fitness = population[i]->get_fitness();
					lowest_index = i;
				}
			}

			population.erase( population.begin()+lowest_index );
			died++;
		}
		if( to_combine < m_nr_combine ) {
			int highest_fitness = sum_fitness + 1;
			size_t highest_index = -1;

			for( size_t i = 0; i < population.size(); i++ ) {
				if( highest_fitness < population[i]->get_fitness() ) {
					highest_fitness = population[i]->get_fitness();
					highest_index = i;
				}
			}

			selected.push_back( population[highest_index] );
			to_combine++;
		}
	}

	return true;
}
