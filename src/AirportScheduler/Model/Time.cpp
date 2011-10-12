/*
 * Time.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: SANDER
 */

#include "Time.h"

#include <stdlib.h>
#include <sstream>

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

unsigned int Time::addHour(unsigned int hours) {
	hour += hours;

	while(hour >= 24) {
		hour -= 24;
	}

	return hour;
}

unsigned int Time::addMinute(unsigned int minutes) {
	minute += minutes;

	while(minute >= 60) {
		addHour(1);

		minute -= 60;
	}

	return minute;
}

string Time::getFormattedTime() {
	stringstream formattedTime;

	formattedTime << hour << ":" << minute;

	return formattedTime.str( );
}

Time Time::operator+(Time & other) {
	Time t(*this);

	t.addHour(other.getHour());
	t.addMinute(other.getMinute());

	return t;
}

bool Time::operator==(Time & other) {
	if(this->hour != other.hour) {
		return false;
	}

	if(this->minute != other.minute) {
		return false;
	}

	return true;
}

bool Time::operator>(Time & other) {
	if(this->hour < other.hour) {
		return false;
	}

	if(this->hour == other.hour) {
		if(this->minute > other.minute) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}

bool Time::operator<(Time & other) {
	if(this->hour > other.hour) {
		return false;
	}

	if(this->hour == other.hour) {
		if(this->minute < other.minute) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}

bool Time::operator>=(Time & other) {
	if(this->hour < other.hour) {
		return false;
	}

	if(this->hour == other.hour) {
		if(this->minute >= other.minute) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}

bool Time::operator<=(Time & other) {
	if(this->hour > other.hour) {
		return false;
	}

	if(this->hour == other.hour) {
		if(this->minute <= other.minute) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}
