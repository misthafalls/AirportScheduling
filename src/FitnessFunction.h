/*
 * FitnessFunction.h
 *
 *  Created on: Dec 7, 2011
 *      Author: christian
 */

#ifndef FITNESSFUNCTION_H_
#define FITNESSFUNCTION_H_

#include <map>
#include <vector>

#define CONST_PLANES_CRASHED 5
#define CONST_PLANES_DELAYED 1

class Genome;

class FitnessFunction {
public:
	FitnessFunction();
	virtual ~FitnessFunction();

	int calculate_fitness(std::vector<Genome*>& population,
						   int landing_strips,
						   int landing_duration);
};

#endif /* FITNESSFUNCTION_H_ */
