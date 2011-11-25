/*
 * AirportScheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "AirportScheduler.h"
#include "Model/Logger.h"
#include <ctime>

AirportScheduler::AirportScheduler() {
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);
}

AirportScheduler::~AirportScheduler() {
	delete controller;
	delete view;
	delete model;
}

bool AirportScheduler::setup( AlgorithmType type ) {
	return model->setAlgorithm( type );
}

bool AirportScheduler::readFile( const char* file ) const {
    CSVReader reader( model );
    return reader.readFile( file );
}

void AirportScheduler::cleanup() {
}

void AirportScheduler::start() {
	model->begin();
	view->print();
	//Logger::getInstance()->wait();
}
