/*
 * Bruteforce.h
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#ifndef PRIORITYBASED_H_
#define PRIORITYBASED_H_

#include "../Algorithm.h"
#include "../Runway.h"

#include <vector>

class PriorityBased : public Algorithm {
public:
	PriorityBased();
	virtual ~PriorityBased();

	virtual void clean();
	virtual void schedule(std::vector<Plane*> & planes);
	Plane* landPlane(std::vector<Plane*>::iterator & highestPriorityPlaneIterator, Time & timeToLand);

protected:
	Time timeHorizon;

	Time globalTime;

	std::vector<Plane*> arrivedPlanes;

};

#endif /* PRIORITYBASED_H_ */
