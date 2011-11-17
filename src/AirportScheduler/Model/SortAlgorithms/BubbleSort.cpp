/*
 * BubbleSortAlgorithm.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#include "BubbleSort.h"

#include "../Logger.h"

BubbleSort::BubbleSort( ) { }

BubbleSort::~BubbleSort( ) { }

std::vector<Plane*>& BubbleSort::scheduleByArrivalTimeAscending( std::vector<Plane*> &planes ) {
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
				//Logger::getInstance( )->log( tmp->getName( ) + " swap with " + planes.at( i )->getName( ) );
			}
		}
	}

	return planes;
}

std::vector<Plane*>& BubbleSort::scheduleByPriorityAscending( std::vector<Plane*> &planes ) {
	int n = planes.size( );
	int j = 0;
	bool swapped = true;
	while ( swapped ) {
		swapped = false;
		j++;
		for ( int i = 0; i < n - j; i++ ) {
            int a, b;
            a = planes.at( i )->getPriority( );
            b = planes.at( i + 1 )->getPriority( );
			if ( a > b ) {
				Plane* tmp = planes.at( i );
				planes.at( i ) = planes.at( i+1 );
				planes.at( i+1 ) = tmp;
				swapped = true;
			}
		}
	}

	return planes;
}
