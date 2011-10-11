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
	Plane(  std::string name, 
            int arrivalTime, 
            PlaneType planeType, 
            int fuel, 
            int fuelUsagePerSec );

	virtual ~Plane();

	std::string getName() { return name; }
    void setName( std::string &s ) { name = s; }

	int getArrivalTime() { return arrivalTime; }
	void setArrivalTime( int &time ) { arrivalTime = time; }

	int getScheduledTime() { return scheduledTime; }
	void setScheduledTime( int &time );

	int getFinalLandingTime() { return finalLandingTime; }
	void setFinalLandingTime( int &time ){ finalLandingTime = time; }

	PlaneType getPlaneType() { return planeType; }
	void setPlaneType( PlaneType &type ){ planeType = type; }

    int getFuel( ) { return fuel; }
    void setFuel( int &i ) { fuel = i; }

    int getFuelUsage( ) { return fuelUsagePerMin; }
    void setFuelUsage( int &usage ) { fuelUsagePerMin = usage; }

private:
    //TODO: change times to new Time class
	std::string name;
	int arrivalTime;
	int scheduledTime;
    // Time that the scheduler sets
    int finalLandingTime;
	PlaneType planeType;
	int fuel;
	int fuelUsagePerMin;
};

#endif /* PLANE_H_ */
