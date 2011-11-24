/*
 * Airport.h
 *
 *  Created on: Nov 23, 2011
 *      Author: dustin
 */

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <vector>
#include "Time.h"
#include "Plane.h"

class Airport {
public:
	Airport(int amountOfRunways);
	virtual ~Airport();

	bool landPlane(Plane * p);

	Time getLastLandingTime();
private:
	//void landPlane(Plane * p);
	Time lastLandingTime;
	std::vector<std::vector<Plane *> *> * runways;
};

#endif /* AIRPORT_H_ */
