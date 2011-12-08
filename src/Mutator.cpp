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
	double mutation;
	int size = g->get_size();

	for(int i = 0; i < size; i++) {
		//randomize to chance of a mutation occurring
		double toMutate = rand();
		if(toMutate > 0.5) {
			//randomize random number between 0 and mutationRate
            // ERROR: INVALID OPERANDS OF TYPES 'INT' AND 'DOUBLE'
//			mutation = rand() % mutationRate;
			//set correct amount of mutation
			if(toMutate > 0.75) {
				mutation = 1 + mutation;
			} else {
				mutation = 1 - mutation;
			}
			//get the next Gene
			Genome::Gene *gen = g->get_gene(i);
			//get time of next Gene in minutes
			//int time = gen->getTime().getTimeInMinutes();
			//calculate mutated time
			//int mutatedTime = (int) (((double) time) * mutation);
			//set mutated time to Gene
            // ERROR: INVALED CONVERSION FROM INT TO CONST CHAR
//            Time newtime = Time( mutatedTime - time );
			//gen->setTime(newtime);
		}
	}
}
