/*
* Time.h
*
* Created on: Oct 11, 2011
* Author: SANDER
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
* @param timeFormatted a formatted time in format: HH:MM, or [DD]HH:MM
*/
Time(std::string timeFormatted);
/**
* Constructor with Time
* @param day the day
* @param hour the hour
* @param minute the minute
*/
Time(int day, int hour, int minute);

/**
* Adds days to the Time
* @param days the amount of days to add
* @return the new day of the Time
*/
int addDay(int days);
/**
* Adds hours to the Time
* @param hours the amount of hours to add
* @return the new hour of the Time
*/
int addHour(int hours);
/**
* Adds minutes to the Time
* @param minutes the amount of minutes to add
* @return the new minute of the Time
*/
int addMinute(int minutes);

/**
* Subtracts days of the Time
* @param days the amount of days to subtract
* @return the new day of the Time
*/
int subDay(int days);
/**
* Subtracts hours of the Time
* @param hours the amount of hours to subtract
* @return the new hour of the Time
*/
int subHour(int hours);
/**
* Subtracts minutes of the Time
* @param minutes the amount of minutes to subtract
* @return the new minute of the Time
*/
int subMinute(int minutes);

/**
* Gets the Day
*/
int getDay() { return day; }
/**
* Gets the Hour
*/
int getHour() { return hour; }
/**
* Gets the Minute
*/
int getMinute() { return minute; }

/**
* Returns a Time Formatted String
* Format: [DD]HH:MM
* @return a string with the formatted time
*/
std::string getFormattedTime();

/**
* Returns a int in minutes
* Format: int
* @return a int in minutes
*/
int getTimeInMinutes();

/**
* Operator +
* Adds two times (this and other) and put it in a new one
* @param other a reference to another Time object
* @return a Time object with the two times added with eachother
*/
Time operator+(Time other);
/**
* Operator -
* Subtracts two times (this and other) and put it in a new one
* @param other a reference to another Time object
* @return a Time object with the two times subtracted with eachother
*/
Time operator-(Time other);

/**
* Operator ==
* Compares if two Times are equal by their times
* @param other a reference to another Time object
* @return true if equals
*/
bool operator==(Time other);
/**
* Operator >
* Compares if this Time is later than other Time
* @param other a reference to another Time object
* @return true if later
*/
bool operator>(Time other);
/**
* Operator <
* Compares if this Time is earlier than other Time
* @param other a reference to another Time object
* @return true if earlier
*/
bool operator<(Time other);
/**
* Operator >=
* Compares if this Time is later than or equal to other Time
* @param other a reference to another Time object
* @return true if later
*/
bool operator>=(Time other);
/**
* Operator <=
* Compares if this Time is earlier than or equal to other Time
* @param other a reference to another Time object
* @return true if earlier
*/
bool operator<=(Time other);

private:
int day;
int hour;
int minute;

};


#endif /* TIME_H_ */
