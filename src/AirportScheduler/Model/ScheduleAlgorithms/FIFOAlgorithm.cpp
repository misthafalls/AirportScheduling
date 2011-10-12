/*
 * FIFOAlgorithm.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#include "FIFOAlgorithm.h"
#include "../SortAlgorithms/BubbleSortAlgorithm.h"

FIFOAlgorithm::FIFOAlgorithm( ) : Algorithm( ) { }
FIFOAlgorithm::~FIFOAlgorithm( ) { }

std::vector<Plane*>& FIFOAlgorithm::schedule( std::vector<Plane*> &planes ) {
	Algorithm* arrivalTimeSort = new BubbleSortAlgorithm( );

	planes = arrivalTimeSort->schedule( planes );

	Time time( "00:00");

	for( unsigned int i = 0; i < planes.size( ); i++ ) {
		Time arrTime = planes[i]->getArrivalTime( );

		//5 is a relative safety time differences between planes
//		Time safetyTime = time + 5;
        Time safetyTime;
        safetyTime.addMinute( ( time.getMinute( ) + 5 ) );

		if( arrTime >= time && arrTime <= ( safetyTime ) ) {
			planes[i]->setScheduledTime( safetyTime );
			time = safetyTime;
		} else {
			time = arrTime;
		}
	}

	return planes;
}
