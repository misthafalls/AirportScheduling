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
	//get list from Model

	//print Plane list
}

void View::printPlaneList(std::vector<Plane*> & list) {
	Logger::getInstance()->log( "Printing Plane List.." );

	int i = 0;
	for (std::vector<Plane*>::iterator it = list.begin(); it != list.end(); it++) {
		i++;

		Plane * plane = *it;

		Logger::getInstance()->logex( "Plane %d: %s", i, plane->getName().c_str() );
	}
}
