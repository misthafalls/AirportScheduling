/*
 * Bruteforce.cpp
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#include "Bruteforce.h"
#include "../SortAlgorithms/BubbleSortAlgorithm.h"

#if PRINT_DEBUG
#include <iostream>
#endif

Bruteforce::Bruteforce() {
	// TODO Auto-generated constructor stub

}

Bruteforce::~Bruteforce() {
	// TODO Auto-generated destructor stub
}

std::vector<Plane*>& Bruteforce::schedule( std::vector<Plane*> &planes ) {
	Algorithm* arrivalTimeSort = new BubbleSortAlgorithm( );

	planes = arrivalTimeSort->schedule( planes );


    //First plane can land at it's earliest convience
	Time lastPlane = planes[ 0 ]->getArrivalTime( );
    planes[ 0 ]->setFinalLandingTime( lastPlane );

    lastPlane = planes[ 0 ]->getFinalLandingTime( );
    unsigned int lastDuration = planes[ 0 ]->getLandingDuration( );

#if PRINT_DEBUG
    std::cout << "First Plane scheduled to: " << lastPlane.getFormattedTime( )
        << std::endl << "Starting loop with: "
        << std::endl << "  lastPlane (Time): " << lastPlane.getFormattedTime( )
        << std::endl << "  lastDuration (int): " << lastDuration << std::endl;
#endif

	for( unsigned int i = 1; i < planes.size( ); i++ ) {
        Time earliestLandingTime = lastPlane;
        earliestLandingTime.addMinute( lastDuration );

        Time currentPlaneArrival = planes[ i ]->getArrivalTime( );
        if( earliestLandingTime < currentPlaneArrival ) {
            planes[ i ]->setFinalLandingTime( currentPlaneArrival );
        } else {
            planes[ i ]->setFinalLandingTime( earliestLandingTime );
        }
#if PRINT_DEBUG
        std::cout << "Plane nr: " << i << " set to: " <<
            planes[ i ]->getFinalLandingTime( ).getFormattedTime( )
                << std::endl;
#endif

        if( planes[ i ]->getDeadlineTime( ) < earliestLandingTime ) {
#if PRINT_DEBUG
            std::cout << "Plane: " << planes[ i ]->getName( ) << " has crashed"
                << std::endl;
#endif
        }
        lastPlane = planes[ i ]->getFinalLandingTime( );
        lastDuration = planes[ i ]->getLandingDuration( );
#if PRINT_DEBUG
    std::cout << "Going to: " << i+1 << " with following values: " <<
        std::endl << "  lastPlane (Time) " << lastPlane.getFormattedTime( ) <<
        std::endl << "  lastDuration (int) " << lastDuration << std::endl;
#endif
	}

	return planes;
}

