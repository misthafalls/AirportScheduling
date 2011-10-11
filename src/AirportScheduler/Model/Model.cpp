/*
 * Model.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Model.h"
#include <memory>
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

bool Model::addPlane( std::string name, int arrivalTime ) {
    std::auto_ptr< Plane > newPlane ( new Plane( name, arrivalTime, Plane::CARGO, 0, 0 ) );
    if( !newPlane.get( ) ) return false;// No plane created.. error!
    planes[ name ] = newPlane.release( );
    return true;
}

bool Model::addPlane( Plane *p ) {
    planes[ p->getName( ) ] = p;
    return true;
}

void Model::begin() {
	std::vector<Plane*> planesToSchedule;

	for (std::map<std::string, Plane*>::iterator it = planes.begin(); it != planes.end(); it++ ) {
		Plane * plane = (*it).second;

		planesToSchedule.push_back(plane);
	}

	schedule = schedulers->makeSchedule(planesToSchedule);
}
