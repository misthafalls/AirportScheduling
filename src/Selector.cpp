#include "Selector.h"
#include "FitnessFunction.h"
#include <stdlib.h>
#include <vector>
#include "Time.h"
#include "Genome.h"

bool 
RandomSelector::select(std::vector<Genome*>& population, 
                                std::vector<Genome*>& selected,
                                int sum_fitness ) {
    //This makes random safer in random generating.
	srand((unsigned int)time(0));
	//Generate fitness for every genome.

    size_t died = 0;
    while ( died < m_nr_die ) {
        size_t lowest_fitness = -1;
        size_t lowest_index = -1;
        for( size_t t=0;t<population.size();t++){
            if( lowest_fitness > population[t]->get_fitness() ) {
                lowest_fitness = population[t]->get_fitness();
                lowest_index = t;
            }
        }
        population.erase( population.begin()+lowest_index );
        died++;
    }

	
	size_t combined = 0;
	size_t i = 0;
    float threshold = ((float)rand())/RAND_MAX;
	while(combined < m_nr_combine) {
		Genome* genome = population[i];

		float chance = ((float)genome->get_fitness())/sum_fitness;

		if(combined < m_nr_combine && chance <= threshold ) {
            for( size_t t=0;t<selected.size();t++) {
                if( selected[t] == population[i] ) continue;
            }
            selected.push_back( population[i] );
			combined++;
		}
        i++;
        if( i >= population.size( ) ) i = 0;
	}
	return true;
}
