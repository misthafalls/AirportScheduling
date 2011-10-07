/*
 * Plane.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <string>
#include <time.h>

class Plane {
//TODO: Lege (default) constructor; expectedTime, planetype, 
//      fuel{remaining & usage}
public:
    enum PlaneType {
        CARGO,
        PASSENGER
    };

	Plane(std::string name, int arrivalTime, int scheduledTime);
	virtual ~Plane();

	std::string getName( ) { return name; }
	int getArrivalTime( ) { return arrivalTime; }
	int getScheduledTime() { return scheduledTime; }
	void setScheduledTime( int time );

private:
	std::string name;
	int arrivalTime;
	int scheduledTime;
};

#endif /* PLANE_H_ */
