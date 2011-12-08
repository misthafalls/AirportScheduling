#include "Selector.h"
#include "Genome.h"
#include "FitnessFunction.h"

Selector::~Selector() {}
bool Selector::getSelected(Genome ** genomes, size_t m_size) {
	//Generate fitness for every genome.
	FitnessFunction fitness;
	fitness.calcTotalFitness(genomes, m_size);

	//This makes random safer in random generating.
	//BTW this is good enough for our little project.
	srand(time(NULL));

	//The to combining genomes are set in the front of the array.
	//The genomes that will be deleted are the last ones.
	int combine = 0, i;
	while(combine < this->combine) {
		Genome * genome = genomes[i];

		int chance = fitness.getFitness(genome) / fitness.getTotalFitness();
		int threshold = ((float)rand())/RAND_MAX;

		if(combine < this->combine) {
			if(chance <= threshold) {
				for(int j = i-1; j >= combine; j--) {
					genomes[j+1] = genomes[j];
				}

				genomes[combine] = genome;

				combine++;
			}
		}

		if(i < m_size)
			i = combine;
	}

	return true;
}
