/*
* Mutator.cpp
*
* Created on: Dec 7, 2011
*/

#include "Mutator.h"
#include <stdlib.h>

void Mutator::mutateGenomes(Genome **genomes, int size, double mutationRate) {
	for(int i = 0; i < size; i++) {
		Mutator::mutateGenome(genomes[i], mutationRate);
	}
}

void Mutator::mutateGenome(Genome *g, double mutationRate) {
	srand ( time(NULL) );
	double mutationLength = 2 * mutationRate;
	double mutationStart = 1 - mutationRate;

	for(int i = 0; i < g->get_size(); i++) {
		mutationRate = ((double)rand())/RAND_MAX * mutationLength + mutationStart;

		Genome::Gene * gen = g->get_gene(i);
		Time time = gen->getTime();
		time.addMinute(time.getTimeInMinutes() * mutationRate - time.getTimeInMinutes());

		gen->setTime(time);
	}
}
