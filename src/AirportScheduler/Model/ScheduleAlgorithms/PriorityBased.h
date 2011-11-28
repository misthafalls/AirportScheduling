/*
 * Bruteforce.h
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#ifndef PRIORITYBASED_H_
#define PRIORITYBASED_H_

#include "../Algorithm.h"
#include <vector>
#include "../Airport.h"

class PriorityBased : public Algorithm {

typedef std::vector< Plane* >::iterator plane_iterator;

public:
	PriorityBased();
	virtual ~PriorityBased();

	Airport * scheduleByFuel( Airport * airport );
	std::vector<Plane*> & schedule( std::vector<Plane*> & planes, int lanes, int horizon, int schedulingMinutes);
};

#endif /* PRIORITYBASED_H_ */
