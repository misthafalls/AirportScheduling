/*
* Plane.cpp
*
* Created on: Oct 4, 2011
*/

#include "Plane.h"

Plane::~Plane() {
}

Time
Plane::getDeadlineTime( ) {
    unsigned int minLeft = fuel / fuelUsagePerMin;
    Time ret = arrivalTime;
    ret.addMinute( minLeft );
    return ret;
}
