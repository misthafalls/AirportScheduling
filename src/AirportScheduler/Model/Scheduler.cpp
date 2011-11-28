/*
 * Scheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Scheduler.h"

std::vector<Plane*> Scheduler::makeSchedule(std::vector<Plane*> list, int lanes, int horizon, int schedulingMinutes, int schedulingOption) {
	list = algorithm->schedule(list, lanes, horizon, schedulingMinutes, schedulingOption);
	return list;
}

void Scheduler::setAlgorithm(Algorithm * a) {
	algorithm = a;
}
