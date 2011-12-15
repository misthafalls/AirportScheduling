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


class Genome;

class FitnessFunction {
public:
	FitnessFunction();
	virtual ~FitnessFunction();

	virtual int calculate_fitness(std::vector<Genome*>& population,
						   int landing_strips,
						   int landing_duration) = 0;
};

class NiceFitnessFunction : public FitnessFunction {
public:
	int calculate_fitness(std::vector<Genome*>& population,
						   int landing_strips,
						   int landing_duration);
private:
const static unsigned int CONST_PLANES_CRASHED = 5;
const static unsigned int CONST_PLANES_DELAYED = 1;
};
#endif /* FITNESSFUNCTION_H_ */
