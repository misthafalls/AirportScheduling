/*
 * Scheduler.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Algorithm.h"
#include "Plane.h"

#include <vector>

class Scheduler
{
public:
	Scheduler() {};
	virtual ~Scheduler() {};

	void setAlgorithm(Algorithm * algorithm);
	//void setTime(unsigned int time);

	std::vector<Plane*> makeSchedule(std::vector<Plane*> list);

protected:
	unsigned int time;

	Algorithm * algorithm;
};


#endif /* SCHEDULER_H_ */
