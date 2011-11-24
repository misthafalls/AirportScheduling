/*
 * View.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "View.h"
#include "../Model/Logger.h"

#include "../Model/Logger.h"

View::View(Model * model) {
	this->model = model;
}

View::~View() {
}

bool View::setup() {
	return true;
}

void View::print() {
	printPlaneList(model->getSchedule());
}

void View::printPlaneList(std::vector<Plane*> & list) {
	Logger::getInstance()->log( "Printing Plane List.." );

	int i = 0;
	for(std::vector<Plane*>::iterator it = list.begin(); it != list.end(); it++) {
		i++;

		Plane * plane = *it;

		//Compute Landing Time based on Final Landing Time
		Time landingTime = plane->getFinalLandingTime();
		//landingTime.addMinute(plane->getLandingDuration());

		if(plane->hasCrashed()) {
			Logger::getInstance()->logex( "Plane %02d: %s crashed (Priority: %d) [Deadline: %s]", i,
											plane->getName().c_str(),
											plane->getPriority(),
											plane->getDeadlineTime().getFormattedTime().c_str() );
		} else {
			Logger::getInstance()->logex( "Plane %02d: %s lands at runway %d with time %s (Priority: %d) [Deadline: %s]",
											i,
											plane->getName().c_str(),
											plane->getRunway(),
											landingTime.getFormattedTime().c_str(),
											plane->getPriority(),
											plane->getDeadlineTime().getFormattedTime().c_str() );
		}
	}
}
