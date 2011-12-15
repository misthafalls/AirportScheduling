#include "FitnessFunction.h"
#include "Genome.h"
#include <map>
#include <vector>

FitnessFunction::FitnessFunction() {}

FitnessFunction::~FitnessFunction() {
	resetTotalFitness();
}

int FitnessFunction::getFitness(Genome * genome) {
	//This function will insure that fitness does not get recalculated everytime!
	if(genome_fitness.find(genome) != genome_fitness.end()) {
		return genome_fitness.at(genome);
	}

	int total_crashes = 0;
	int total_delayed_planes = 0;

	for(unsigned int i = 0; i < genome->get_size( ); i++) {
		Genome::Gene * gene = genome->get_gene(i);
		const Plane* plane = gene->getPlane();

		if (plane->getDeadlineTime() > gene->getTime()) ++total_crashes;
		if (plane->getScheduledTime() < gene->getTime()) ++total_delayed_planes;
	}

	int genome_fitness = 
        total_crashes * CONST_PLANES_CRASHED + total_delayed_planes * 
                CONST_PLANES_DELAYED;

	total_fitness += genome_fitness;

	return genome_fitness;
}

bool FitnessFunction::calcTotalFitness(std::vector< Genome*> genomes) {
	for(unsigned int i = 0; i < genomes.size( ); i++) {
		Genome * genome = genomes[i];
		genome_fitness.insert( std::pair<Genome *, int>(genome, getFitness(genome)));
	}
	return true;
}

int FitnessFunction::getTotalFitness() {
	return total_fitness;
}

void FitnessFunction::resetTotalFitness() {
	total_fitness = 0;
	genome_fitness.clear();
}
