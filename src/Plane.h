/*
* Plane.h
*
* Created on: Oct 4, 2011
*/

#ifndef PLANE_H_
#define PLANE_H_

#include "Time.h"

#include <string>

class Plane {

public:
    Plane( ) { crashed = false; };
    virtual ~Plane();

    const std::string getName() const { return name; }
    void setName( std::string &s ) { name = s; }

    //should be const Time
    Time getArrivalTime() const { return arrivalTime; }
    void setArrivalTime( Time &time ) { arrivalTime = time; }

    const Time getScheduledTime() const { return scheduledTime; }
    void setScheduledTime( Time &time ) { scheduledTime = time; }

    const Time getFinalLandingTime() const { return finalLandingTime; }
    void setFinalLandingTime( Time &time ){ finalLandingTime = time; }

    const int getFuel( ) const { return fuel; }
    void setFuel( int i ) { fuel = i; }

    const int getFuelUsage( ) const { return fuelUsagePerMin; }
    void setFuelUsage( int usage ) { fuelUsagePerMin = usage; }

    Time getDeadlineTime( ) ;

    void setCrashed(bool b) { crashed = b; }
    const bool hasCrashed() const { return crashed; }

    void print( );

    const size_t get_fpos( ) const {return fpos;}
    const size_t get_npos( ) const {return npos;}
    
    void set_fpos( size_t t ) { fpos = t; }
    void set_npos( size_t t ) { npos = t; }

private:
    // fpos and npos = min and max value for place in the genome
    size_t fpos; size_t npos;
    std::string name;
    Time arrivalTime;
    Time scheduledTime;
    Time finalLandingTime;
    int fuel;
    int fuelUsagePerMin;

    bool crashed;
};

#endif /* PLANE_H_ */
