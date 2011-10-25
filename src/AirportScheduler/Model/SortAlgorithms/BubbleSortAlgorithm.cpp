/*
 * BubbleSortAlgorithm.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#include "BubbleSortAlgorithm.h"
#include "../Logger.h"

BubbleSortAlgorithm::BubbleSortAlgorithm( ) : Algorithm( ) { }

BubbleSortAlgorithm::~BubbleSortAlgorithm( ) { }

std::vector<Plane*>& BubbleSortAlgorithm::schedule( std::vector<Plane*> &planes ) {
	int n = planes.size( );
	int j = 0;
	bool swapped = true;
	while ( swapped ) {
		swapped = false;
		j++;
		for ( int i = 0; i < n - j; i++ ) {
            Time a; Time b;
            a = planes.at( i )->getArrivalTime( );
            b = planes.at( i + 1 )->getArrivalTime( ); 
			if ( a > b ) {
				Plane* tmp = planes.at( i );
				planes.at( i ) = planes.at( i+1 );
				planes.at( i+1 ) = tmp;
				swapped = true;
				Logger::getInstance( )->log( 
                    tmp->getName( ) + 
                        " swap with " + 
                        planes.at( i )->getName( ) );
			}
		}
	}

	return planes;
}
