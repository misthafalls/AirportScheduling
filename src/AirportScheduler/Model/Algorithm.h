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
	virtual std::vector<Plane*>& schedule( std::vector<Plane*>& planes ) = 0;
	virtual ~Algorithm( ) {};
};

#endif /* ALGORITHM_H_ */
