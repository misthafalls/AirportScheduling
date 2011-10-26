/*
 * Priority.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#define PRINT_DEBUG 1

#include "Priority.h"
#if PRINT_DEBUG
#include <iostream>
#endif

//Prioriteit is deadline - verstreken tijd - landingduration

Priority::Priority() {
	// TODO Auto-generated constructor stub

}

Priority::~Priority() {
	// TODO Auto-generated destructor stub
}

int Priority::getPriority(Plane* plane, Time globalTime) {
#if PRINT_DEBUG
	std::cout << "GlobalTime: " << globalTime.getFormattedTime() << std::endl;
	std::cout << "Deadline: " << plane->getDeadlineTime().getFormattedTime() << std::endl;
	std::cout << "LandingDuration: " << plane->getLandingDuration() << std::endl;
#endif
	Time deadline = plane->getDeadlineTime() - globalTime;
	return deadline.getTimeInMinutes() - plane->getLandingDuration();
}
