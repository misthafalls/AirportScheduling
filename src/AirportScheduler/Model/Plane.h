/*
 * Plane.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Time.h"

#include <string>

class Plane {
public:
    enum PlaneType {
        CARGO,
        PASSENGER
    };

public:
	Plane(std::string name, int arrivalTime, PlaneType planeType, int fuel, int fuelUsagePerSec );
	virtual ~Plane();

	std::string getName() { return name; }
	int getArrivalTime() { return arrivalTime; }

	int getScheduledTime() { return scheduledTime; }
	void setScheduledTime(int time);

private:
	std::string name;
	int arrivalTime;
	PlaneType planeType;
	int fuel;
	int fuelUsagePerSec;



	int scheduledTime;

};

#endif /* PLANE_H_ */
