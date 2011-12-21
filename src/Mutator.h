// Dustin Balentina, 7 December 2011
//------------------------------------------------------------------------------

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include "Genome.h"
#include "Plane.h"
#include "Time.h"

class Mutator {
public:
	virtual void mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate) = 0;
protected:
static const unsigned int MAX_MUTATION_MIN = 10;
};

class SimpleMutator : public Mutator {
public:
    void mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate);
};

class SubtractTimeMutator : public Mutator {
public:
    void mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate);
};

class AddTimeMutator : public Mutator {
public:
    void mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate);
};

class ComboMutator : public Mutator {
public:
    void mutateGenomes(std::vector<Genome*>& genomes, 
                                double mutationRate);
};

#endif
