/*
 * Model.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Model.h"
#include "ScheduleAlgorithms/FIFOAlgorithm.h"

Model::Model() {
	schedulers = new Scheduler();
	schedulers->setAlgorithm(new FIFOAlgorithm());
}

Model::~Model() {
	delete schedulers;
}

bool Model::setup() {
	return true;
}
