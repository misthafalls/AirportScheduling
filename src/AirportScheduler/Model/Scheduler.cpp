/*
 * Scheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Scheduler.h"

std::vector<Plane*> Scheduler::makeSchedule(std::vector<Plane*> list, int lanes, int horizon, int schedulingMinutes) {
	list = algorithm->schedule(list, lanes, horizon, schedulingMinutes);
	return list;
}

void Scheduler::setAlgorithm(Algorithm * a) {
	algorithm = a;
}
