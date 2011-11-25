/*
 * View.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "View.h"
#include "../Model/Logger.h"
#include <iostream>
#include <stdlib.h>

View::View(Model * model) {
	this->model = model;
}

View::~View() {
}

bool View::setup() {
	return true;
}

void View::print() {
	printScheduleStatistics(model->getSchedule());
}

inline void printIndent( size_t t ) {
    for( size_t a = 0; a < t; a++ ) { std::cout << " "; }
}

void View::printPlaneInfo( Plane* p, Stats& stats ) {
    Time final_landing_time = p->getFinalLandingTime( );
    Time arrival_time = p->getArrivalTime( );
    Time time_in_air = final_landing_time - arrival_time;

    std::cout << "Print info on plane: " << p->getName( ) << std::endl;
    printIndent( 4 ); 
    std::cout << "Plane has ";
    if( p->hasCrashed( ) ) { 
        stats.number_crashes++;
        std::cout << "crashed ";
    } else {
        std::cout << "landed on runway: " << p->getRunway( ) << " ";
    }
    std::cout << "at: " << final_landing_time.getFormattedTime( ) << 
        " and was initially scheduled for: " << 
            p->getScheduledTime( ).getFormattedTime( ) << std::endl;
    
    size_t fuel_usage = time_in_air.getTimeInMinutes( ) * p->getFuelUsage( );
    stats.fuel_usage_total += fuel_usage;

    printIndent( 4 ); 
    std::cout << "Plane used: " << fuel_usage << " gallons of fuel over a time of: " <<
        time_in_air.getFormattedTime( ) << " in the air" << std::endl;

    printIndent( 4 );
    Time t;
    std::cout << "Plane was ";
    if( p->getScheduledTime( ) < final_landing_time ) {
        t = final_landing_time - p->getScheduledTime( ); 
        std::cout << t.getTimeInMinutes( ) << " minutes late" << std::endl;
        stats.number_planes_delay++;
        stats.total_minutes_delay += t.getTimeInMinutes( );
    } else if ( p->getScheduledTime( ) > final_landing_time ){
        t = p->getScheduledTime( ) - final_landing_time;
        std::cout << t.getTimeInMinutes( ) << " minutes early" << std::endl;
        stats.number_planes_early++;
        stats.total_minutes_early += t.getTimeInMinutes( );
    } else {
        std::cout << "exactly on time" << std::endl;
        stats.number_on_time++;
    }
    printIndent( 4 );
    std::cout << "The deadline was: " << p->getDeadlineTime( ).getFormattedTime( ) <<
        " and the arrival at the airport was at: " << arrival_time.getFormattedTime( )
            << std::endl << std::endl;
}

void View::printScheduleStatistics( std::vector<Plane*> & planes ) {
    Stats stats;

    std::cout << "Scheduler has finished it's job, printing outcome..." <<
        std::endl << std::endl;
    std::vector< Plane* >::iterator it;
    for( it = planes.begin( ); it != planes.end( ); it++ ) {
        printPlaneInfo( (*it), stats );
    }

    //TODO for entire schedule:
    // number planes 
    // gemiddelde planes per 30 min
//    size_t number_per_half_hour = #$%^&*(;
    // totale fuel usage
    // # vliegtuigen met delay
    // totale hoeveelheid delay
    // aantal vliegtuigen te vroeg (# en %)
    // totale hoeveelheid te vroeg
    // aantal crashed (# en %)
    // aantal vliegtuigen precies op tijd (# en %)
    // runtijd van scheduler
    int total_planes = planes.size( );
    std::cout << "--== Schedule statistics ==--" << std::endl;
    std::cout << "Total Number of Planes: " << total_planes << std::endl;
    //TODO average
    std::cout << "Average planes per half hour: UNAVAILABLE" << std::endl;
    std::cout << "Total fuel used by all planes: " << stats.fuel_usage_total 
        << std::endl;
    double percentage_delayed = (double)stats.number_planes_delay / 
        (double)total_planes * 100;
    std::cout << "Number of planes delayed: " << stats.number_planes_delay 
        << " (=" << percentage_delayed << "% )" << std::endl;
    printIndent( 4 );
    std::cout << "Total delay time: " << stats.total_minutes_delay << std::endl;
    double percentage_early = (double)stats.number_planes_early / 
        (double)total_planes * 100;
    std::cout << "Number of planes early: " << stats.number_planes_early
        << " (=" << percentage_early << "% )" << std::endl;
    printIndent( 4 );
    std::cout << "Total early time: " << stats.total_minutes_early << std::endl;
    double percentage_crashed = (double)stats.number_crashes / 
        (double)total_planes * 100;
    std::cout << "Total number crashes: " << stats.number_crashes 
        << " (=" << percentage_crashed << "% )" << std::endl;
    std::cout << "Planes exactly on time: " << stats.number_on_time << std::endl;
    std::cout << "Runtime for algorithm: UNAVAILABLE" << std::endl;
}
