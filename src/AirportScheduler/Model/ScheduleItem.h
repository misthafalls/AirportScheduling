/*
 * Schedule.h
 *
 *  Created on: Nov 17, 2011
 *      Author: SANDER
 */

#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "Time.h"
#include "Plane.h"

#include <string>

class ScheduleItem
{
public:
	ScheduleItem(Time & _begin, Time & _end) : begin(_begin), end(_end) {}
	virtual ~ScheduleItem() {}

	const Time & getBegin() { return begin; }
	const Time & getEnd() { return end; }

	virtual std::string toString();

protected:
	Time begin;
	Time end;

};

class SchedulePlane : public ScheduleItem
{
public:
	SchedulePlane(Time & _begin, Time & _end, Plane * _plane) : ScheduleItem(_begin, _end), plane(_plane) {}
	virtual ~SchedulePlane() {}

	virtual std::string toString();

protected:
	Plane * plane;

};

#endif /* SCHEDULE_H_ */
