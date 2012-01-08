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
	FitnessFunction()
    { };

	virtual ~FitnessFunction();

	virtual int calculate_fitness(std::vector<Genome*>& population,
                           bool check_crashes = true ) = 0;

    unsigned int get_number_of_crashes( Genome* g );
protected:
unsigned int m_landing_duration;
unsigned int m_landing_strips;
const static unsigned int PLANE_CRASHED_PENALTY = 500;
const static unsigned int PLANE_DELAY_PENALTY= 1;
const static double FUEL_UNIT_PENALTY = 0.01;
};

class NiceFitnessFunction : public FitnessFunction {
public:
    NiceFitnessFunction( unsigned int ld, unsigned int ls ) 
        { m_landing_duration = ld; m_landing_strips = ls; }

	int calculate_fitness(std::vector<Genome*>& population,
                           bool check_crashes = true );
};

class FuelFitnessFunction : public FitnessFunction {
public:
    FuelFitnessFunction( unsigned int ld, unsigned int ls ) 
        { m_landing_duration = ld; m_landing_strips = ls; }
       
	int calculate_fitness(std::vector<Genome*>& population,
                           bool check_crashes = true );
};

#endif /* FITNESSFUNCTION_H_ */
