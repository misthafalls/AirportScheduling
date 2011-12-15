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

void
Plane::calcDeadlineTime( ) {
    unsigned int minLeft = fuel / fuelUsagePerMin;
    deadlineTime = arrivalTime;
    deadlineTime.addMinute( minLeft );
}

void
Plane::print( ) {
    std::cout << "Printing plane: " << name << std::endl <<
        "    " << "ArrivalTime: " << arrivalTime.getFormattedTime( ) << std::endl <<
        "    " << "ScheduledTime: " << scheduledTime.getFormattedTime( ) << std::endl <<
       "    " << "Fuel level: " << fuel << std::endl <<
        "    " << "Fuel Usage: " << fuelUsagePerMin << std::endl;
}
