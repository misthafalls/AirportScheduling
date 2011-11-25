/*
 * Scheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Scheduler.h"

std::vector<Plane*> Scheduler::makeSchedule(std::vector<Plane*> list, int lanes) {
	list = algorithm->schedule(list, lanes);
	return list;
}

void Scheduler::setAlgorithm(Algorithm * a) {
	algorithm = a;
}
