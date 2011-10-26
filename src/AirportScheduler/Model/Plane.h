/*
 * Plane.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Time.h"

#include <string>

class Plane {
public:
    enum PlaneType {
        CARGO,
        PASSENGER
    };

public:
    Plane( ) { };
    /*TODO: remove?
	Plane(  std::string name, 
            Time arrivalTime, 
            PlaneType planeType, 
            int fuel, 
            int fuelUsagePerSec );
*/
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

    Time getDeadlineTime( ) const;

    void setPriority(int p) { priority = p; }
    int getPriority() { return priority; }

private:
    //TODO: change times to new Time class
	std::string name;
	Time arrivalTime;
	Time scheduledTime;
    // Time that the scheduler sets
    Time finalLandingTime;
	PlaneType planeType;
	int fuel;
	int fuelUsagePerMin;
    int landingDuration;

    int priority;
};

#endif /* PLANE_H_ */
