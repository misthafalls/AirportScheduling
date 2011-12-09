/*
* Mutator.cpp
*
* Created on: Dec 7, 2011
*/

#include "Mutator.h"
#include <stdlib.h>

void Mutator::mutateGenomes(std::vector<Genome*>& genomes, double mutationRate) {
	srand ( time(NULL) );
    size_t nr_to_mutate = rand( ) % ( genomes.size( ) / 3 );
    size_t nr_mutated = 0;
	while(nr_mutated < nr_to_mutate) {
        size_t index = rand( ) % genomes.size( );
		Mutator::mutateGenome(genomes[index], mutationRate);
        nr_mutated++;
	}
}

void Mutator::mutateGenome(Genome *g, double mutationRate) {
	srand ( time(NULL) );
	double mutationLength = 2 * mutationRate;
	double mutationStart = 1 - mutationRate;

    size_t nr_to_mutate = rand( ) % ( g->get_size( ) );
    size_t nr_mutated = 0;
	while(nr_mutated < nr_to_mutate) {
        size_t index = rand( ) % (g->get_size( ));
		mutationRate = 
            ((double)rand())/RAND_MAX * mutationLength + mutationStart;
		Genome::Gene * gen = g->get_gene(index);
		Time time = gen->getTime();
		time.addMinute(
            time.getTimeInMinutes() * mutationRate - time.getTimeInMinutes());
		gen->setTime(time);
        nr_mutated++;
	}
}
