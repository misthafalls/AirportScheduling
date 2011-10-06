/*
 * Plane.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <string>

class Plane {
public:
	Plane( std::string name, int arrivalTime );
	virtual ~Plane( );

	std::string getName( ) { return name; }
	int getArrivalTime( ) { return arrivalTime; }
	void setScheduledArrivalTime( int time );

protected:
	std::string name;
	int arrivalTime;
	int scheduledTime;
};

#endif /* PLANE_H_ */
