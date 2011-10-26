/*
 * Bruteforce.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#include "Bruteforce.h"

#include "../SortAlgorithms/BubbleSort.h"
#include "../Priority.h"

#include "../Logger.h"

using namespace std;

Bruteforce::Bruteforce() {
	// TODO Auto-generated constructor stub

}

Bruteforce::~Bruteforce() {
	// TODO Auto-generated destructor stub
}

std::vector<Plane*>& Bruteforce::schedule( vector<Plane*> &planes ) {
	BubbleSort * sorter = new BubbleSort();
	Priority * priority = new Priority();

	//Sort planes by Arrival Time
	planes = sorter->scheduleByArrivalTimeAscending(planes);

	//Lists used for Scheduling
	vector<Plane*> arrivedPlanes;
	vector<Plane*> scheduledPlanes;

	//Global Time of System
	Time globalTime;

	while( (!planes.empty()) || (!arrivedPlanes.empty()) ) {
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

				plane->setPriority( priority->getPriority(plane, globalTime) );
			}

			//Sort arrived Planes based on priority, smallest first
			sorter->scheduleByPriorityAscending(arrivedPlanes);

			//Get First Plane from sorted Arrived Plane List
			vector<Plane*>::iterator highestPriorityPlaneIterator = arrivedPlanes.begin();
			Plane * highestPriorityPlane = *highestPriorityPlaneIterator;

			//Add Landing Duration of the Plane to the Global Time
			globalTime.addMinute(highestPriorityPlane->getLandingDuration());

			//Final Scheduled Time of Plane will be the same of the Global Time we just set
			highestPriorityPlane->setFinalLandingTime(globalTime);

			//Add Plane to Scheduled List
			scheduledPlanes.push_back(highestPriorityPlane);

			//Remove Plane from Arrived Plane List
			arrivedPlanes.erase(highestPriorityPlaneIterator);
		} else {
			//Set Global Time to earliest Arrival Time
			globalTime = planes[0]->getArrivalTime();
		}
	}

	delete priority;
	delete sorter;

	planes = scheduledPlanes;

	return planes;
}

