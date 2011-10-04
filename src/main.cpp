/*
 * main.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "AirportScheduler/AirportScheduler.h"

int main()
{
	//Initialize Thread
	//TODO

	//Construct
	AirportScheduler * airportScheduler = new AirportScheduler();

	//Setup
	if (airportScheduler->setup()) {
		//Start
		airportScheduler->start();
	}

	//Cleanup
	airportScheduler->cleanup();

	//Deconstruct
	delete airportScheduler;

	return 0;
}
