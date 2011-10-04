/*
 * Plane.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Plane.h"

Plane::Plane(std::string name, int arrivalTime) {
	this->name = name;
	this->arrivalTime = arrivalTime;
}

Plane::~Plane() {
}
