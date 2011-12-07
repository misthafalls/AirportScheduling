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

class Genome;
class Gene;

class FitnessFunction {
public:
	FitnessFunction();
	virtual ~FitnessFunction();

	int getFitness(Genome * genome);
};

#endif /* FITNESSFUNCTION_H_ */
