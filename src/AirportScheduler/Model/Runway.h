/*
 * Runway.h
 *
 *  Created on: Nov 17, 2011
 *      Author: SANDER
 */

#ifndef RUNWAY_H_
#define RUNWAY_H_

#include "ScheduleItem.h"

#include <string>
#include <vector>

class Runway
{
public:
	Runway(std::string _name) : name(_name) {}
	virtual ~Runway() {}

	std::string getName() { return name; }

	void add(ScheduleItem * scheduleItem) { schedule.push_back(scheduleItem); }
	const std::vector<ScheduleItem*> & getSchedule() { return schedule; }

protected:
	std::string name;
	std::vector<ScheduleItem*> schedule;

};


#endif /* RUNWAY_H_ */
