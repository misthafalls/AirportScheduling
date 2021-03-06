/*
 * Time.cpp
 *
 * Created on: Oct 11, 2011
 * Author: SANDER
 */

#include "Time.h"

#include <stdlib.h>
#include <sstream>
#include <iostream>

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
	if (timeFormatted[0] != '[') {
		bool bFoundSeperator = false;
		for (unsigned int i = 0; i < timeFormatted.length(); i++) {
			const char c = timeFormatted[i];

			if (c == ':') {
				bFoundSeperator = true;
				continue;
			}

			if (bFoundSeperator) {
				minuteString.append(1, c);
			} else {
				hourString.append(1, c);
			}
		}
	} else {
		int seperatorNumber = 0;
		for (unsigned int i = 0; i < timeFormatted.length(); i++) {
			const char c = timeFormatted[i];

			if (c == ':' || c == ']') {
				seperatorNumber++;
				continue;
			}

			if (c == '[') {
				continue;
			}

			if (seperatorNumber == 0) {
				dayString.append(1, c);
			} else if (seperatorNumber == 1) {
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

Time::Time(int day, int hour, int minute) {
	this->day = day;
	this->hour = hour;
	this->minute = minute;
}

int Time::addDay(int days) {
	changeTime(days * 1440);

	return day;
}

int Time::addHour(int hours) {
	changeTime(hours * 60);

	return hour;
}

int Time::addMinute(int minutes) {
	changeTime(minutes);

	return minute;
}

int Time::subDay(int days) {
	changeTime( days * -1440);

	return day;
}

int Time::subHour(int hours) {
	changeTime( hours * -60 );

	return hour;
}

int Time::subMinute(int minutes) {
	changeTime( minutes * -1 );

	return minute;
}

string Time::getFormattedTime() {
	stringstream formattedTime;

	formattedTime << "[" << day << "]";
	formattedTime << ((hour < 10) ? "0" : "") << hour << ":";
	formattedTime << ((minute < 10) ? "0" : "") << minute;

	return formattedTime.str();
}

int Time::getTimeInMinutes() {
	return minute + (hour + day * 24) * 60;
}

Time Time::operator+(Time other) {
	Time t(*this);

	t.changeTime(other.getTimeInMinutes());

	return t;
}

Time Time::operator-(Time other) {
	Time t(*this);

	t.changeTime(other.getTimeInMinutes() * -1);

	return t;
}

bool Time::operator==(Time other) {
	return this->getTimeInMinutes() == other.getTimeInMinutes();
}

bool Time::operator>(Time other) {
	return this->getTimeInMinutes() > other.getTimeInMinutes();
}

bool Time::operator<(Time other) {
	return this->getTimeInMinutes() < other.getTimeInMinutes();
}

bool Time::operator>=(Time other) {
	return this->getTimeInMinutes() >= other.getTimeInMinutes();
}

bool Time::operator<=(Time other) {
	return this->getTimeInMinutes() <= other.getTimeInMinutes();
}

bool Time::changeTime(int p_minute) {
	int time_in_minutes = getTimeInMinutes() + p_minute;

	day = (time_in_minutes) / 1440;

	time_in_minutes -= (time_in_minutes >= 0) ? day * 1440 : (day - 1) * 1440;

	hour = time_in_minutes / 60;
	minute = time_in_minutes - hour * 60;

	return true;
}

/*void Time::operator=( Time& other ) {
 day = other.getDay( );
 hour = other.getHour( );
 minute = other.getMinute( );
 }*/
