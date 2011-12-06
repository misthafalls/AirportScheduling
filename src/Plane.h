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
    enum PlaneType {
        EMERGENCY,
        MILITARY,
        PASSENGER,
        CARGO
    };

public:
    Plane( ) { priority = -1; crashed = false; };
virtual ~Plane();

std::string getName() { return name; }
    void setName( std::string &s ) { name = s; }

Time getArrivalTime() { return arrivalTime; }
void setArrivalTime( Time &time ) { arrivalTime = time; }

Time getScheduledTime() { return scheduledTime; }
void setScheduledTime( Time &time ) { scheduledTime = time; }

Time getFinalLandingTime() { return finalLandingTime; }
void setFinalLandingTime( Time &time ){ finalLandingTime = time; }

PlaneType getPlaneType() { return planeType; }
void setPlaneType( PlaneType type ){ planeType = type; }

    int getFuel( ) { return fuel; }
    void setFuel( int i ) { fuel = i; }

    int getFuelUsage( ) { return fuelUsagePerMin; }
    void setFuelUsage( int usage ) { fuelUsagePerMin = usage; }

    int getLandingDuration( ) { return landingDuration; }
    void setLandingDuration( int duration ) { landingDuration = duration; }

    int getRunway( ) { return runway; }
    void setRunway( int r ) { runway = r; }

    Time getDeadlineTime( );

    void setPriority(int p) { priority = p; }
    int getPriority() { return priority; }

    void setCrashed(bool b) { crashed = b; }
    bool hasCrashed() { return crashed; }

private:
std::string name;
Time arrivalTime;
Time scheduledTime;

Time finalLandingTime;
PlaneType planeType;

int runway;
int fuel;
int fuelUsagePerMin;
    int landingDuration;

    int priority;
    bool crashed;
};

#endif /* PLANE_H_ */
