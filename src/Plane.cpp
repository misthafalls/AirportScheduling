/*
* Plane.cpp
*
* Created on: Oct 4, 2011
*/

#include "Plane.h"
#include <stdlib.h>
#include <iostream>

Plane::~Plane() {
}

Time
Plane::getDeadlineTime( ) {
    unsigned int minLeft = fuel / fuelUsagePerMin;
    Time ret = arrivalTime;
    ret.addMinute( minLeft );
    return ret;
}

void
Plane::print( ) {
    std::cout << "Printing plane: " << name << std::endl <<
        "    " << "ArrivalTime: " << arrivalTime.getFormattedTime( ) << std::endl <<
        "    " << "ScheduledTime: " << scheduledTime.getFormattedTime( ) << std::endl <<
        "    " << "FinalLandingTime: " << finalLandingTime.getFormattedTime( ) << std::endl <<
        "    " << "Fuel level: " << fuel << std::endl <<
        "    " << "Fuel Usage: " << fuelUsagePerMin << std::endl <<
        "    " << "Crashed? : " << crashed << std::endl;
}
