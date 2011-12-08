// Dustin Balentina, 7 December 2011
//------------------------------------------------------------------------------

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include "Genome.h"
#include "Plane.h"
#include "Time.h"

class Mutator {
public:
	void mutateGenomes(Genome **genomes, int size, double mutationRate);
	void mutateGenome(Genome *g, double mutationRate);

};

#endif
