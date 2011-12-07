/*
* Plane.h
*
* Created on: Oct 4, 2011
*/

#ifndef PLANE_H_
#define PLANE_H_

#include "Time.h"

#include <string>

class Plane {

public:
    Plane( ) { crashed = false; };
    virtual ~Plane();

    std::string getName() { return name; }
    void setName( std::string &s ) { name = s; }

    Time getArrivalTime() { return arrivalTime; }
    void setArrivalTime( Time &time ) { arrivalTime = time; }

    Time getScheduledTime() { return scheduledTime; }
    void setScheduledTime( Time &time ) { scheduledTime = time; }

    Time getFinalLandingTime() { return finalLandingTime; }
    void setFinalLandingTime( Time &time ){ finalLandingTime = time; }

    int getFuel( ) { return fuel; }
    void setFuel( int i ) { fuel = i; }

    int getFuelUsage( ) { return fuelUsagePerMin; }
    void setFuelUsage( int usage ) { fuelUsagePerMin = usage; }

    Time getDeadlineTime( );

    void setCrashed(bool b) { crashed = b; }
    bool hasCrashed() { return crashed; }

private:
    std::string name;
    Time arrivalTime;
    Time scheduledTime;
    Time finalLandingTime;
    int fuel;
    int fuelUsagePerMin;

    bool crashed;
};

#endif /* PLANE_H_ */
