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
	virtual void schedule(std::vector<Plane*> & planes, Runway * runway) = 0;

	const AlgorithmInfo & getInfo() { return info; }

protected:
	AlgorithmInfo info;

};

#endif /* ALGORITHM_H_ */
