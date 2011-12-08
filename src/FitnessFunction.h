/*
 * FitnessFunction.h
 *
 *  Created on: Dec 7, 2011
 *      Author: christian
 */

#ifndef FITNESSFUNCTION_H_
#define FITNESSFUNCTION_H_

#define CONST_PLANES_CRASHED 5
#define CONST_PLANES_DELAYED 1

#include <cstring>
#include <map>

class Genome;

class FitnessFunction {
public:
	FitnessFunction();
	virtual ~FitnessFunction();

	int getFitness(Genome * genome);
	bool calcTotalFitness(Genome ** genomes, std::size_t m_size);

	int getTotalFitness();
	void resetTotalFitness();
private:
	int total_fitness;
	std::map<Genome *, int> genome_fitness;
};

#endif /* FITNESSFUNCTION_H_ */
