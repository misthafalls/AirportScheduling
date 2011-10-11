/*
 * Time.h
 *
 *  Created on: Oct 11, 2011
 *      Author: SANDER
 */

#ifndef TIME_H_
#define TIME_H_

#include <string>

class Time {
public:
	/**
	 * Default Constructor
	 */
	Time();
	/**
	 * Copy Constructor
	 * @param c Time instance to copy
	 */
	Time(const Time & c);
	/**
	 * Constructor with Formatted Time
	 * @param timeFormatted a formatted time in format: HH:MM
	 */
	Time(std::string timeFormatted);
	/**
	 * Constructor with Time
	 * @param hour the hour
	 * @param minute the minute
	 */
	Time(unsigned int hour, unsigned int minute);

	/**
	 * Gets the Hour
	 */
	unsigned int getHour() { return hour; }
	/**
	 * Gets the Minute
	 */
	unsigned int getMinute() { return minute; }

	/**
	 * Returns a Time Formatted String
	 * Format: HH:MM
	 * @return a string with the formatted time
	 */
	std::string getFormattedTime();

	//TODO Operator Overloading ++ > < etc

private:
	unsigned int hour;
	unsigned int minute;

};


#endif /* TIME_H_ */
