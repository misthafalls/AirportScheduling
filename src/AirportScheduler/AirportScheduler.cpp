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
	Logger::getInstance()->log("hi");
	return true;
}

bool AirportScheduler::readFile( const char* file ) {
    CSVReader reader( model );
    return reader.read_file( file );
}

void AirportScheduler::cleanup() {
}

void AirportScheduler::start() {

}
