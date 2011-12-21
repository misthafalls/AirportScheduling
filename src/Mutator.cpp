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
            //TODO Hoe later het vliegtuig gescheduled is, 
                    // hoe groter de mutatie is. dit is niet wenselijk!!!
		    time.addMinute(
                time.getTimeInMinutes() * mutationRate - 
                        time.getTimeInMinutes());
            if( time < gen->getPlane( )->getArrivalTime( ) )
                time = gen->getPlane( )->getArrivalTime( );
		    gen->setTime(time);
            genes_mutated++;
	    }
        genomes_mutated++;
	}
}

void 
AddTimeMutator::mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate) {
    unsigned int max_mutation = MAX_MUTATION_MIN*mutationRate;
	srand ( time(NULL) );
    std::vector<Genome*>::iterator genome_iterator = genomes.begin( );
    std::vector<Genome::Gene*>::iterator gene_iterator;
    while( genome_iterator != genomes.end( ) ) {
        gene_iterator = (*genome_iterator)->get_genes( )->begin( );
        //TODO doet de compiler dit netjes?
        while( gene_iterator != (*genome_iterator)->get_genes( )->end( ) ) {
            Time t = (*gene_iterator)->getTime( );
            size_t to_add = rand( ) % max_mutation;
            t.addMinute( to_add );
            if( t < (*gene_iterator)->getPlane( )->getDeadlineTime( ) ){
                (*gene_iterator)->setTime( t );
            }
            gene_iterator++;
        }
        genome_iterator++;
    }
}

void 
SubtractTimeMutator::mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate) {
    unsigned int max_mutation = MAX_MUTATION_MIN*mutationRate;
	srand ( time(NULL) );
    std::vector<Genome*>::iterator genome_iterator = genomes.begin( );
    std::vector<Genome::Gene*>::iterator gene_iterator;
    while( genome_iterator != genomes.end( ) ) {
        gene_iterator = (*genome_iterator)->get_genes( )->begin( );
        //TODO doet de compiler dit netjes?
        while( gene_iterator != (*genome_iterator)->get_genes( )->end( ) ) {
            Time t = (*gene_iterator)->getTime( );
            size_t to_subtract = rand( ) % max_mutation;
            t.subMinute( to_subtract );
            if( t < (*gene_iterator)->getPlane( )->getArrivalTime( ) ){
                (*gene_iterator)->setTime( t );
            }
            gene_iterator++;
        }
        genome_iterator++;
    }
}

void
ComboMutator::mutateGenomes( std::vector<Genome*>& genomes,
                                double mutationRate ) {
    srand( time( NULL ) );
    std::vector<Genome*> add;
    std::vector<Genome*> subtract;
    std::vector<Genome*>::iterator genome_iterator = genomes.begin( );
    while( genome_iterator != genomes.end( ) ) {
        //50-50 verdeling
        int random = rand( ) % 2;
        if( !random ) add.push_back( *genome_iterator );
        else subtract.push_back( *genome_iterator );
        genome_iterator++;
    }
    Mutator* m = new AddTimeMutator( ); 
    m->mutateGenomes( add, mutationRate );
    delete m;
    m = new SubtractTimeMutator( ); 
    m->mutateGenomes( subtract, mutationRate );
    delete m;
}

