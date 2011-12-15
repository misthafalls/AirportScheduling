/*
* Mutator.cpp
*
* Created on: Dec 7, 2011
*/

#include "Mutator.h"
#include <stdlib.h>

void 
SimpleMutator::mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate) {
    double mutationLength = 2 * mutationRate;
	double mutationStart = 1 - mutationRate;
	srand ( time(NULL) );
    size_t genome_to_mutate = rand( ) % ( genomes.size( ) / 3 );
    size_t genomes_mutated = 0;
	while(genomes_mutated < genome_to_mutate) {
        size_t index = rand( ) % genomes.size( );
        Genome* g = genomes.at( index );

        //Mutate Genome g;
        size_t gene_to_mutate = rand( ) % ( g->get_size( ) );
        size_t genes_mutated = 0;
	    while(genes_mutated < gene_to_mutate) {
            size_t index = rand( ) % (g->get_size( ));
		    mutationRate = 
            ((double)rand())/RAND_MAX * mutationLength + mutationStart;
		    Genome::Gene * gen = g->get_gene(index);
		    Time time = gen->getTime();
		    time.addMinute(
                time.getTimeInMinutes() * mutationRate - 
                        time.getTimeInMinutes());
		    gen->setTime(time);
            genes_mutated++;
	    }
        genomes_mutated++;
	}
}
