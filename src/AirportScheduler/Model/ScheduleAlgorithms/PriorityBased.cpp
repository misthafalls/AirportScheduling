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
	timeHorizon = Time(0, 1, 0);
}

PriorityBased::~PriorityBased() {
}

void PriorityBased::clean() {
	Algorithm::clean();

	globalTime = Time(0, 0, 0); //Reset Global Time
}

void PriorityBased::schedule(vector<Plane*> & planes) {
	clean();

	BubbleSort * sorter = new BubbleSort();
	Priority * priorityCalculator = new Priority();

	//Sort planes by Arrival Time
	planes = sorter->scheduleByArrivalTimeAscending(planes);

	while( (!planes.empty()) || (!arrivedPlanes.empty()) ) {
		if(!arrivedPlanes.empty()) {
			//Calculate Priority for each arrived Plane
			for(vector<Plane*>::iterator it = arrivedPlanes.begin(); it != arrivedPlanes.end(); it++) {
				Plane * plane = *it;

				int priority = priorityCalculator->getPriority(plane, globalTime);

				plane->setPriority(priority);
			}

			//Sort arrived Planes based on priority, smallest first
			sorter->scheduleByPriorityAscending(arrivedPlanes);

			//Get First Plane from sorted Arrived Plane List
			vector<Plane*>::iterator highestPriorityPlaneIterator = arrivedPlanes.begin();
			//Plane * highestPriorityPlane = *highestPriorityPlaneIterator;

			//Is arrival time of highest priority plane later than global time then wait
//			if(highestPriorityPlane->getArrivalTime() > globalTime) {
//				//Runway wait..
//
//				globalTime = highestPriorityPlane->getArrivalTime();
//			}

//			Time loopTime = globalTime;
//			while(highestPriorityPlane->getArrivalTime() < loopTime) {
//				highestPriorityPlaneIterator++;
//				Plane * loopPlane = *highestPriorityPlaneIterator;
//
//				if(loopPlane->getArrivalTime() + loopPlane->getLandingDuration() < highestPriorityPlane->getArrivalTime()) {
//					setLandingTime(loopPlane, loopTime);
//				}
//			}

			//globalTime = highestPriorityPlane->getArrivalTime();

			landPlane(highestPriorityPlaneIterator, globalTime);
		} else {
			//Set Global Time to earliest Arrival Time
			globalTime = planes[0]->getArrivalTime();
		}

		//Copy Planes to the Arrived Planes List if they've arrived at the Airport
		for(vector<Plane*>::iterator it = planes.begin(); it != planes.end(); ) {
			Plane * plane = *it;

			Time horizon = globalTime + timeHorizon;
			if(plane->getArrivalTime() <= horizon) {
				arrivedPlanes.push_back(plane);

				it = planes.erase(it);
			} else {
				it++;
			}
		}
	}

	delete priorityCalculator;
	delete sorter;
}

Plane * PriorityBased::landPlane(vector<Plane*>::iterator & highestPriorityPlaneIterator, Time & timeToLand) {
	Plane * plane = *highestPriorityPlaneIterator;

	if( plane->getArrivalTime() > globalTime )
	{
		Time endTime = plane->getArrivalTime();
		ScheduleItem * scheduledItem = new ScheduleItem(globalTime, endTime);
		runway->add(scheduledItem);

		globalTime = plane->getArrivalTime();
	}

	Time beginLandTime = timeToLand;

	//Compute Final Landing Time
	Time finalLandingTime;
	finalLandingTime.addMinute(globalTime.getTimeInMinutes() + plane->getLandingDuration());

	//Final landing time is higher than deadline time
	if(finalLandingTime > plane->getDeadlineTime()) {
		//Crashed
		plane->setCrashed(true);

		//Remember
		info.numCrashes++;
	} else {
		//Final Scheduled Time of Plane will be the current Global Time
		plane->setFinalLandingTime(globalTime);

		//Add Landing Duration of the Plane to the Global Time
		globalTime.addMinute(plane->getLandingDuration());

		//Add Plane to Scheduled List
		SchedulePlane * scheduledPlane = new SchedulePlane(beginLandTime, finalLandingTime, plane);
		runway->add(scheduledPlane);
	}

	//Remove Plane from Arrived Plane List
	arrivedPlanes.erase(highestPriorityPlaneIterator);

	return plane;
}

