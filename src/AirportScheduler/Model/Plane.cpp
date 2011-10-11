/*
 * Plane.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Plane.h"

using namespace std;

Plane::Plane(std::string name, int arrivalTime, PlaneType planeType, int fuel, int fuelUsagePerSec ) {
	this->name = name;
	this->arrivalTime = arrivalTime;
	this->planeType = planeType;
	this->fuel = fuel;
	this->fuelUsagePerSec = fuelUsagePerSec;

	this->scheduledTime = 0;
}

Plane::~Plane() {
}

void Plane::setScheduledTime(int time) {
	scheduledTime = time;
}
