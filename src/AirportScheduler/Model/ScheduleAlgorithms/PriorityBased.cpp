/*
 * Bruteforce.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#include "PriorityBased.h"

#include "../SortAlgorithms/BubbleSort.h"
#include "../Priority.h"

#include "../Airport.h"
#include "../Logger.h"

using namespace std;

PriorityBased::PriorityBased() {
}

PriorityBased::~PriorityBased() {
}

std::vector<Plane*>& PriorityBased::schedule( vector<Plane*> &planes, int lanes, int horizon, int schedulingMinutes) {
	BubbleSort * sorter = new BubbleSort();
	Priority * priorityCalculator = new Priority();

	//Sort planes by Arrival Time
	planes = sorter->scheduleByArrivalTimeAscending(planes);

	//Lists used for Scheduling
	vector<Plane*> arrivedPlanes;
	vector<Plane*> scheduledPlanes;

	Airport * airport = new Airport(lanes);

	//Global Time of System
	Time schedulingTime;
	Time searchTime;
	Time globalTime;

	while( (!planes.empty()) || (!arrivedPlanes.empty()) ) {
		//Copy Planes to the Arrived Planes List if they've arrived at the Airport
		for(vector<Plane*>::iterator it = planes.begin(); it != planes.end(); ) {
			Plane * plane = *it;

			if(plane->getArrivalTime() <= searchTime) {
				arrivedPlanes.push_back(plane);

				it = planes.erase(it);
			} else {
				it++;
			}
		}

		if(!arrivedPlanes.empty()) {
			//Calculate Priority for each arrived Plane
			for(vector<Plane*>::iterator it = arrivedPlanes.begin(); it != arrivedPlanes.end(); it++) {
				Plane * plane = *it;

				int priority = priorityCalculator->getPriority(plane, globalTime);

				Logger::getInstance()->logex("Priority %s -> %d", plane->getName().c_str(), priority);

				plane->setPriority(priority);
			}

			//Sort arrived Planes based on priority, smallest first
			sorter->scheduleByPriorityAscending(arrivedPlanes);

			//Get First Plane from sorted Arrived Plane List
			vector<Plane*>::iterator highestPriorityPlaneIterator = arrivedPlanes.begin();
			Plane * highestPriorityPlane = *highestPriorityPlaneIterator;

			if( airport->landPlane(highestPriorityPlane) ) {
				globalTime = airport->getLastLandingTime();

				//TODO: What if plane has more then 10 minutes landingTime?
				if(globalTime > schedulingTime) {
					schedulingTime.addMinute(schedulingMinutes);
					searchTime.addMinute(schedulingMinutes);
				}
			}

			//Add Plane to Scheduled List
			scheduledPlanes.push_back(highestPriorityPlane);

			//Remove Plane from Arrived Plane List
			arrivedPlanes.erase(highestPriorityPlaneIterator);
		} else {
			//Set Global Time to earliest Arrival Time
			globalTime = planes[0]->getArrivalTime();
			schedulingTime = globalTime;
			searchTime = globalTime;

			schedulingTime.addMinute(schedulingMinutes);
			searchTime.addMinute(horizon);
		}
	}

	scheduleByFuel(airport);

	delete priorityCalculator;

	planes = sorter->scheduleByFinalLandingTimeAscending(scheduledPlanes);

	delete sorter;

	return planes;
	//TODO: Maybe we want to return the planes in runways and let crashed planes be abandoned!
	//return airport->getRunways();
}

Airport * PriorityBased::scheduleByFuel( Airport * airport ) {
	vector<vector<Plane*>*> * runways = airport->getRunways();
	BubbleSort * sorter = new BubbleSort();

	for(vector<vector<Plane*>*>::iterator runway_it = runways->begin(); runway_it != runways->end(); runway_it++) {
		//TODO: Does copy constructor work with pointers???
		vector<Plane*> reschedule;
		Logger::getInstance()->log("\n");
		Logger::getInstance()->log("Planes in the list");

		for(vector<Plane*>::iterator plane_it = (*runway_it)->begin(); plane_it != (*runway_it)->end(); plane_it++) {
			Logger::getInstance()->logex("  Plane: %s", (*plane_it)->getName().c_str());
			reschedule.push_back((*plane_it));
		}

		reschedule = sorter->scheduleByFinalLandingTimeAscending(reschedule);

		plane_iterator plane_it = reschedule.begin()+1;

		for(plane_iterator plane_it = reschedule.begin()+1; plane_it != reschedule.end(); plane_it++) {
			Logger::getInstance()->logex("Check if Plane %s can be swapped", (*plane_it)->getName().c_str());
			for(plane_iterator p = plane_it-1; p >= reschedule.begin(); p--) {
				//When plane_it reaches a level where finalLandingTime is smaller then arrivalTime break!

				Logger::getInstance()->logex("Plane %s has arrival time %s and uses %d fuel <-> Plane %s has arrival time %s and uses %d fuel",
											(*plane_it)->getName().c_str(),
											(*plane_it)->getArrivalTime().getFormattedTime().c_str(),
											(*plane_it)->getFuelUsage(),
											(*p)->getName().c_str(),
											(*p)->getArrivalTime().getFormattedTime().c_str(),
											(*p)->getFuelUsage());

				//TODO: Not efficient enough, we have to check for fuel usage between arrivaltime and
				//      possible landingtime for the *plane_it!
				if((*plane_it)->getArrivalTime() > (*p)->getArrivalTime()) {
					break;
				} else {
					//Logger::getInstance()->log("WTF IMPOSSIBLE!");
					Time curLandingTime = (*p)->getFinalLandingTime();
					curLandingTime.subMinute((*p)->getLandingDuration());
					curLandingTime.addMinute((*plane_it)->getLandingDuration());

					Time pLandingTime = curLandingTime;
					pLandingTime.addMinute((*p)->getLandingDuration());

					if((*plane_it)->getFuelUsage() > (*p)->getFuelUsage() &&
					   pLandingTime <= (*p)->getDeadlineTime()) {
						Logger::getInstance()->logex("Swapping with %s", (*p)->getName().c_str());
						(*plane_it)->setFinalLandingTime(curLandingTime);
						(*p)->setFinalLandingTime(pLandingTime);
					}
				}
			}
		}
	}

	return airport;
}

