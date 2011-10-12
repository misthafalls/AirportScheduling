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
	this->day = 0;
	this->hour = 0;
	this->minute = 0;
}

Time::Time(const Time & c) {
	this->day = c.day;
	this->hour = c.hour;
	this->minute = c.minute;
}

Time::Time(std::string timeFormatted) {
	string dayString = "0";
	string hourString = "0";
	string minuteString = "0";

	//HH:MM format?
	if(timeFormatted[0] != '[') {
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
	} else {
		int seperatorNumber = 0;
		for(unsigned int i = 0; i < timeFormatted.length(); i++) {
			const char c = timeFormatted[i];

			if(c == ':' || c == ']') {
				seperatorNumber++;
				continue;
			}

			if(c == '[') {
				continue;
			}

			if(seperatorNumber == 0) {
				dayString.append(1, c);
			} else if(seperatorNumber == 1) {
				hourString.append(1, c);
			} else {
				minuteString.append(1, c);
			}
		}
	}

	this->day = atoi(dayString.c_str());
	this->hour = atoi(hourString.c_str());
	this->minute = atoi(minuteString.c_str());
}

Time::Time(unsigned int day, unsigned int hour, unsigned int minute) {
	this->day = day;
	this->hour = hour;
	this->minute = minute;
}

unsigned int Time::addDay(unsigned int days) {
	day += days;

	return day;
}

unsigned int Time::addHour(unsigned int hours) {
	hour += hours;

	while(hour >= 24) {
		addDay(1);

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

	formattedTime << "[" << day << "]" << hour << ":" << minute;

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
