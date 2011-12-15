#include "Selector.h"
#include "Genome.h"
#include "FitnessFunction.h"
#include <stdlib.h>

Selector::~Selector() {}
bool Selector::getSelected(std::vector<Genome*>& genomes) {
	//Generate fitness for every genome.
	FitnessFunction fitness;
	int sum_fitness = fitness.calculate_fitness(genomes, 1, 5); //TODO landingduration is hardcoded!!

    size_t died = 0;
    while ( died < m_nr_die ) {
        size_t lowest_fitness = -1;
        size_t lowest_index = -1;
        for( size_t t=0;t<genomes.size();t++){
            if( lowest_fitness > genomes[t]->get_fitness() ) {
                lowest_fitness = genomes[t]->get_fitness();
                lowest_index = t;
            }
        }
        genomes.erase( genomes.begin()+lowest_index );
        died++;
    }

	//This makes random safer in random generating.
	srand(time(NULL));

	size_t combined = 0;
	size_t i = 0;
    float threshold = ((float)rand())/RAND_MAX;
	while(combined < m_nr_combine) {
		Genome* genome = genomes[i];

		float chance = ((float)genome->get_fitness())/sum_fitness;

		if(combined < m_nr_combine && chance <= threshold ) {
            for( size_t t=0;t<m_to_combine.size();t++) {
                if( m_to_combine[t] == i ) continue;
            }
            m_to_combine.push_back( i );
			combined++;
		}
        i++;
        if( i >= genomes.size( ) ) i = 0;
	}
    
	return true;
}
