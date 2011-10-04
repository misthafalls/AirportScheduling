/*
 * Controller.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Controller.h"

Controller::Controller(Model * model) {
	this->model = model;
}

Controller::~Controller() {
}

bool Controller::setup() {

	return true;
}
