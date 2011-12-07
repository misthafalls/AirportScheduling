#include "FitnessFunction.h"
#include "Genome.h"

FitnessFunction::FitnessFunction() {}

FitnessFunction::~FitnessFunction() {}

int FitnessFunction::getFitness(Genome * genome) {
	int total_crashes = 0;
	int total_delayed_planes = 0;

	for(unsigned int i = 0; i < genome->m_size; i++) {
		Genome::Gene * gene = genome->get_gene(i);
		Plane plane = gene->getPlane();

		if (plane.getDeadlineTime() > gene->getTime()) ++total_crashes;
		if (plane.getScheduledTime() < gene->getTime()) ++total_delayed_planes;
	}

	int genome_fitness = total_crashes * CONST_PLANES_CRASHED + total_delayed_planes * CONST_PLANES_DELAYED;

	total_fitness += genome_fitness;

	return genome_fitness;
}

int FitnessFunction::getTotalFitness() {
	return total_fitness;
}

void FitnessFunction::resetTotalFitness() {
	total_fitness = 0;
}
