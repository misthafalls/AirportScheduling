/*
 * Airport.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: dustin
 */

#include "Airport.h"
#include "Logger.h"

#include <iostream>

using namespace std;

Airport::Airport(int amountOfRunways) {
	runways = new vector<vector<Plane *> *>();
	for(int i = 0; i < amountOfRunways; i++) {
		runways->push_back(new vector<Plane *>());
	}
}

Airport::~Airport() {

}

//void Airport::landPlane(Plane * p) {
//
//}

Time Airport::getLastLandingTime() {
	return lastLandingTime;
}

vector<vector<Plane *> *> * Airport::getRunways() {
	return runways;
}

bool Airport::landPlane(Plane * p) {
	vector<Plane *> * runway = 0;
	int runwayNumber = 0;

	Time landingOpportunity;
	int runwayNumberTemp = 1;
	for(vector<vector<Plane *> *>::iterator rIt = runways->begin(); rIt != runways->end(); rIt++) {
		Time temp = ( (*rIt)->size() == 0 ) ? p->getArrivalTime() : (*rIt)->back()->getFinalLandingTime();

		if(lastLandingTime > temp) {
			lastLandingTime = temp;
		}

		if(landingOpportunity > temp || runway == 0) {
			Logger::getInstance()->logex("plane: %s =>landingOpportunity: %s, temp: %s",
										 p->getName().c_str(),
										 landingOpportunity.getFormattedTime().c_str(),
										 temp.getFormattedTime().c_str());
			landingOpportunity = temp;
			runwayNumber = runwayNumberTemp;
			runway = (*rIt);
		}

		runwayNumberTemp++;
	}

//	Logger::getInstance()->logex("before LandingOpportunity: %s",
//										 landingOpportunity.getFormattedTime().c_str());
//
	landingOpportunity.addMinute(p->getLandingDuration());
//
//	Logger::getInstance()->logex("after runway: %d",runwayNumber);

	if(landingOpportunity < p->getArrivalTime()) {
		landingOpportunity = p->getArrivalTime();
	}

	if(landingOpportunity > p->getDeadlineTime()) {
		p->setCrashed(true);
		return false;
	}

	p->setFinalLandingTime(landingOpportunity);
	p->setRunway(runwayNumber);
	runway->push_back(p);

	return true;
}


