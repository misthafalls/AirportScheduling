/*
 * Priority.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#include "Priority.h"

Priority::Priority() {
}

Priority::~Priority() {
}

int Priority::getPriority(Plane* plane, Time globalTime) {
	Time deadline = plane->getDeadlineTime();

	//Time arrivalTime = plane->getArrivalTime();
	//Time scheduledTime = plane->getScheduledTime();
	//Time diff = scheduledTime - arrivalTime;

	//deadline = deadline + diff;
	deadline = deadline - globalTime;

	return deadline.getTimeInMinutes() - plane->getLandingDuration();
}
