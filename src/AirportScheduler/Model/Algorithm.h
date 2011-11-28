/*
 * Algorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "Plane.h"
#include <vector>

class Algorithm
{
public:
	Algorithm() { };
	virtual ~Algorithm() { };

	virtual std::vector<Plane*> & schedule(std::vector<Plane*> & planes, int lanes, int horizon, int schedulingMinutes, int schedulingOption) = 0;
};

#endif /* ALGORITHM_H_ */
