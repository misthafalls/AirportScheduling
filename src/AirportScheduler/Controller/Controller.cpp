/*
 * Controller.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Controller.h"

Controller::Controller(Model * model, View * view) {
	this->model = model;
	this->view = view;
}

Controller::~Controller() {
}

bool Controller::setup() {

	return true;
}
