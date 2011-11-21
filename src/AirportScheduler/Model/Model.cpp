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
	schedulers = new Scheduler();

}

Model::~Model() {
	delete schedulers;
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

	for (std::map<std::string, Plane*>::iterator it = planes.begin(); 
            it != planes.end(); it++ ) {
		Plane * plane = (*it).second;
		planesToSchedule.push_back(plane);
	}
	schedule = schedulers->makeSchedule(planesToSchedule);
}

bool Model::setAlgorithm( AlgorithmType type ) {
    if( type == BRUTEFORCE ) {
        schedulers->setAlgorithm(new Bruteforce());
        return true;
    } else if ( type == PRIORITY ) {
        schedulers->setAlgorithm(new PriorityBased());
        return true;
    }
    return false;
}
