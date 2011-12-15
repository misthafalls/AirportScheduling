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
    Plane( ) { is_deadline_set = false; }
    virtual ~Plane();

    const std::string getName() const { return name; }
    void setName( std::string &s ) { name = s; }

    //should be const Time
    Time getArrivalTime() const { return arrivalTime; }
    void setArrivalTime( Time &time ) { arrivalTime = time; }

    Time getScheduledTime() const { return scheduledTime; }
    void setScheduledTime( Time &time ) { scheduledTime = time; }

    const int getFuel( ) const { return fuel; }
    void setFuel( int i ) { fuel = i; }

    const int getFuelUsage( ) const { return fuelUsagePerMin; }
    void setFuelUsage( int usage ) { fuelUsagePerMin = usage; }

    Time getDeadlineTime( ) const{ return deadlineTime; } 
    void calcDeadlineTime( );

    void print( );

private:
    std::string name;
    Time arrivalTime;
    Time scheduledTime;
    Time deadlineTime;
    bool is_deadline_set;
    int fuel;
    int fuelUsagePerMin;
};

#endif /* PLANE_H_ */
