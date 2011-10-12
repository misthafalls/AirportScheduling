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
	 * Adds hours to the Time
	 * @param hours the amount of hours to ad
	 * @return the new hour of the Time
	 */
	unsigned int addHour(unsigned int hours);
	/**
	 * Adds minutes to the Time
	 * Adds hours if the minute passes the hour
	 * @param minutes the amount of minutes to add
	 * @return the new minute of the Time
	 */
	unsigned int addMinute(unsigned int minutes);

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

	/**
	 * Operator +
	 * Adds two times (this and other) and put it in a new one
	 * @param other a reference to another Time object
	 * @return a Time object with the two times added with eachother
	 */
	Time operator+(Time & other);

	/**
	 * Compares if two Times are equal by their times
	 * @param other a reference to another Time object
	 * @return true if equals
	 */
	bool operator==(Time & other);
	/**
	 * Compares if this Time is later than other Time
	 * @param other a reference to another Time object
	 * @return true if later
	 */
	bool operator>(Time & other);
	/**
	 * Compares if this Time is earlier than other Time
	 * @param other a reference to another Time object
	 * @return true if earlier
	 */
	bool operator<(Time & other);
	/**
	 * Compares if this Time is later than or equal to other Time
	 * @param other a reference to another Time object
	 * @return true if later
	 */
	bool operator>=(Time & other);
	/**
	 * Compares if this Time is earlier than or equal to other Time
	 * @param other a reference to another Time object
	 * @return true if earlier
	 */
	bool operator<=(Time & other);

private:
	unsigned int hour;
	unsigned int minute;

};


#endif /* TIME_H_ */
