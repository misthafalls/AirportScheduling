/*
 * Model.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Model.h"
#include <memory>

#include "ScheduleAlgorithms/Bruteforce.h"
#include "ScheduleAlgorithms/PriorityBased.h"

Model::Model() {
	//algorithm = new Bruteforce();
	algorithm = new PriorityBased();

	runway = new Runway("Runway 1");
}

Model::~Model() {
	delete runway;
	delete algorithm;
}

bool Model::setup() {
	return true;
}

bool Model::addPlane( Plane *p ) {
    planes[ p->getName( ) ] = p;
    return true;
}

void Model::begin() {
	std::vector<Plane*> planesToSchedule;

	for(std::map<std::string, Plane*>::iterator it = planes.begin(); it != planes.end(); it++) {
		Plane * plane = (*it).second;

		planesToSchedule.push_back(plane);
	}

	algorithm->addRunway(runway);
	algorithm->schedule(planesToSchedule);
}
