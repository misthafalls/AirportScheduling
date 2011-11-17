/*
 * View.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "View.h"

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
	//Print Runway
	printRunway(model->getRunway());

	//Print Algorithm Info
	const AlgorithmInfo & algoInfo = model->getAlgorithm()->getInfo();

	Logger::getInstance()->logex("Number of crashes: %d", algoInfo.numCrashes);
}

void View::printRunway(Runway * runway) {
	Logger::getInstance()->logex("Printing %s..", runway->getName().c_str());

	for(std::vector<ScheduleItem*>::const_iterator it = runway->getSchedule().begin(); it != runway->getSchedule().end(); it++) {
		ScheduleItem * scheduledItem = *it;

		Logger::getInstance()->logex(scheduledItem->toString().c_str());
	}
}
