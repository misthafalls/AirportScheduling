/*
 * View.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "View.h"

View::View(Model * model) {
	this->model = model;
}

View::~View() {
}

bool View::setup() {
	return true;
}

void View::print() {
}
