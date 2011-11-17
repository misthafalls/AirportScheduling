/*
 * Schedule.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: SANDER
 */

#include "ScheduleItem.h"

using namespace std;

string ScheduleItem::toString() {
	string ret = begin.getFormattedTime() + " -> " + end.getFormattedTime() + ": Waiting";

	return ret;
}

string SchedulePlane::toString() {
	string ret = begin.getFormattedTime() + " -> " + end.getFormattedTime() + ": " + plane->getName();

	return ret;
}
