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
	 * @param timeFormatted a formatted time in format: MM:SS
	 */
	Time(std::string timeFormatted);
	/**
	 * Constructor with Time
	 * @param minute the minute
	 * @param second the second
	 */
	Time(unsigned int minute, unsigned int second);

	/**
	 * Gets the Minute
	 */
	unsigned int getMinute() { return minute; }
	/**
	 * Gets the Second
	 */
	unsigned int getSecond() { return second; }

	/**
	 * Returns a Time Formatted String
	 * Format: MM:SS
	 * @return a string with the formatted time
	 */
	std::string getFormattedTime();

private:
	unsigned int minute;
	unsigned int second;

};


#endif /* TIME_H_ */
