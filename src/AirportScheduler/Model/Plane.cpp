/*
 * Plane.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Plane.h"

Plane::Plane( std::string name, int arrivalTime, int scheduledTime ) {
	this->name = name;
	this->arrivalTime = arrivalTime;
	this->scheduledTime = scheduledTime;
}

Plane::~Plane( ) {
}

void Plane::setScheduledTime( int time ) {
	scheduledTime = time;
}
