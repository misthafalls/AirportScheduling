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

bool Model::addPlane( Plane* plane ) {
    unorderd_planes.push_back( plane );
    return true;
}


void Model::begin(int lanes) {
	schedule = schedulers->makeSchedule( unorderd_planes, lanes);
}
