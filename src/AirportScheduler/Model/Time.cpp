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
	this->minute = 0;
	this->second = 0;
}

Time::Time(const Time & c) {
	this->minute = c.minute;
	this->second = c.second;
}

Time::Time(std::string timeFormatted) {
	string minuteString = "";
	string secondString = "";

	bool bFoundSeperator = false;
	for(unsigned int i = 0; i < timeFormatted.length(); i++) {
		const char c = timeFormatted[i];

		if(c == ':') {
			bFoundSeperator = true;
			continue;
		}

		if(bFoundSeperator) {
			secondString.append(1, c);
		} else {
			minuteString.append(1, c);
		}
	}

	this->minute = atoi(minuteString.c_str());
	this->second = atoi(secondString.c_str());
}

Time::Time(unsigned int minute, unsigned int second) {
	this->minute = minute;
	this->second = second;
}

string Time::getFormattedTime() {
	string formattedTime;

	formattedTime = minute + second;

	return formattedTime;
}
