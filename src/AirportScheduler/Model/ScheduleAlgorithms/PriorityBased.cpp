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

std::vector<Plane*>& PriorityBased::schedule( vector<Plane*> &planes ) {
	BubbleSort * sorter = new BubbleSort();
	Priority * priorityCalculator = new Priority();

	//Sort planes by Arrival Time
	planes = sorter->scheduleByArrivalTimeAscending(planes);

	//Lists used for Scheduling
	vector<Plane*> arrivedPlanes;
	vector<Plane*> scheduledPlanes;

	Airport * airport = new Airport(2);

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

			while(globalTime < schedulingTime && !arrivedPlanes.empty()) {
				airport->landPlane(highestPriorityPlane);
				globalTime = airport->getLastLandingTime();

				//Add Plane to Scheduled List
				scheduledPlanes.push_back(highestPriorityPlane);

				//Remove Plane from Arrived Plane List
				arrivedPlanes.erase(highestPriorityPlaneIterator);
			}

//			if( airport->landPlane(highestPriorityPlane) ) {
//				globalTime = airport->getLastLandingTime();
//
//				//TODO: What if plane has more then 10 minutes landingTime?
//				if(globalTime > schedulingTime) {
					schedulingTime.addMinute(10);
					searchTime.addMinute(10);
//				}
//			}

//			//Compute Final Landing Time
//			Time finalLandingTime;
//			finalLandingTime.addMinute(globalTime.getTimeInMinutes() + highestPriorityPlane->getLandingDuration());
//
//			//Priority is lower than 0?
//			if(finalLandingTime > highestPriorityPlane->getDeadlineTime()) {
//				//Crashed
//				highestPriorityPlane->setCrashed(true);
//			} else {
//				//Final Scheduled Time of Plane will be the current Global Time
//				highestPriorityPlane->setFinalLandingTime(globalTime);
//
//				//Add Landing Duration of the Plane to the Global Time
//				globalTime.addMinute(highestPriorityPlane->getLandingDuration());
//			}


		} else {
			//Set Global Time to earliest Arrival Time
			globalTime = planes[0]->getArrivalTime();
			schedulingTime = globalTime;
			searchTime = globalTime;

			schedulingTime.addMinute(10);
			searchTime.addMinute(30);
		}
	}

	delete priorityCalculator;
	delete sorter;

	planes = scheduledPlanes;

	return planes;
	//TODO: Maybe we want to return the planes in runways and let crashed planes be abandoned!
	//return airport->getRunways();
}

