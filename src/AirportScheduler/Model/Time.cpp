/*
 * Time.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: SANDER
 */

#include "Time.h"

#include <stdlib.h>

using namespace std;

Time::Time() {
	this->hour = 0;
	this->minute = 0;
}

Time::Time(const Time & c) {
	this->hour = c.hour;
	this->minute = c.minute;
}

Time::Time(std::string timeFormatted) {
	string hourString = "";
	string minuteString = "";

	bool bFoundSeperator = false;
	for(unsigned int i = 0; i < timeFormatted.length(); i++) {
		const char c = timeFormatted[i];

		if(c == ':') {
			bFoundSeperator = true;
			continue;
		}

		if(bFoundSeperator) {
			minuteString.append(1, c);
		} else {
			hourString.append(1, c);
		}
	}

	this->hour = atoi(hourString.c_str());
	this->minute = atoi(minuteString.c_str());
}

Time::Time(unsigned int hour, unsigned int minute) {
	this->hour = hour;
	this->minute = minute;
}

string Time::getFormattedTime() {
	string formattedTime;

	formattedTime = hour + ":" + minute;

	return formattedTime;
}
