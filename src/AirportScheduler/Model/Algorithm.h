/*
 * Algorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "Plane.h"
#include "Runway.h"

#include <vector>

struct AlgorithmInfo
{
public:
	int numCrashes;
};

class Algorithm
{
public:
	Algorithm() {}
	virtual ~Algorithm() {}

	virtual void clean();
	virtual void schedule(std::vector<Plane*> & planes) = 0;

	void addRunway(Runway * runway) { this->runway = runway; }

	const AlgorithmInfo & getInfo() { return info; }

protected:
	AlgorithmInfo info;

	Runway * runway;

};

#endif /* ALGORITHM_H_ */
