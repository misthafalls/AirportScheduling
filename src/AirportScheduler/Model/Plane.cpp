/*
 * Plane.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Plane.h"

using namespace std;
/*
Plane::Plane(std::string n, int aTime, PlaneType pType, int f, int fuelUsage )
    :
    name( n ),
    arrivalTime( aTime ),
    planeType( pType ),
    fuel( f ),
    fuelUsagePerMin( fuelUsage )
{
}
*/
Plane::~Plane() {
}

Time
Plane::getDeadlineTime( ) const {
    unsigned int minLeft = fuel / fuelUsagePerMin;
    Time ret = arrivalTime;
    ret.addMinute( minLeft );
    return ret;
}

