/*
 * Scheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Scheduler.h"
#include "ScheduleAlgorithms/FIFOAlgorithm.h"

std::vector<Plane*> Scheduler::makeSchedule(std::vector<Plane*> list) {
	list = algorithm->schedule(list);
	return list;
}

void Scheduler::setAlgorithm(Algorithm * a) {
	algorithm = a;
}
