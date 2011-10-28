/*
 * Bruteforce.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#include "PriorityBased.h"

#include "../SortAlgorithms/BubbleSort.h"
#include "../Priority.h"

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

	//Global Time of System
	Time globalTime;

	while( (!planes.empty()) || (!arrivedPlanes.empty()) ) {
		//Copy Planes to the Arrived Planes List if they've arrived at the Airport
		for(vector<Plane*>::iterator it = planes.begin(); it != planes.end(); ) {
			Plane * plane = *it;

			if(plane->getArrivalTime() <= globalTime) {
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

			//Compute Final Landing Time
			Time finalLandingTime;
			finalLandingTime.addMinute(globalTime.getTimeInMinutes() + highestPriorityPlane->getLandingDuration());

			//Priority is lower than 0?
			if(finalLandingTime > highestPriorityPlane->getDeadlineTime()) {
				//Crashed
				highestPriorityPlane->setCrashed(true);
			} else {
				//Final Scheduled Time of Plane will be the current Global Time
				highestPriorityPlane->setFinalLandingTime(globalTime);

				//Add Landing Duration of the Plane to the Global Time
				globalTime.addMinute(highestPriorityPlane->getLandingDuration());
			}

			//Add Plane to Scheduled List
			scheduledPlanes.push_back(highestPriorityPlane);

			//Remove Plane from Arrived Plane List
			arrivedPlanes.erase(highestPriorityPlaneIterator);
		} else {
			//Set Global Time to earliest Arrival Time
			globalTime = planes[0]->getArrivalTime();
		}
	}

	delete priorityCalculator;
	delete sorter;

	planes = scheduledPlanes;

	return planes;
}

