/*
 * AirportScheduler.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "AirportScheduler.h"

#include "Model/Logger.h"
#include "FileIO/CSVReader.h"

AirportScheduler::AirportScheduler() {
	model = new Model();
	view = new View(model);
	controller = new Controller(model);
}

AirportScheduler::~AirportScheduler() {
	delete controller;
	delete view;
	delete model;
}

bool AirportScheduler::setup() {
	Logger::getInstance()->log("AirportScheduler::setup()");
	return true;
}

bool AirportScheduler::readFile( const char* file ) const {
    CSVReader reader( model );
    return reader.readFile( file );
}

bool AirportScheduler::addPlane( std::string name, int time ) const {
    return model->addPlane( name, time, 0 );
}

void AirportScheduler::cleanup() {
}

void AirportScheduler::start() {
	model->begin();

	view->print();

	Logger::getInstance()->wait();
}
