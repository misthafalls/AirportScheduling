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

	unsigned int time = 0;

	for( int i = 0; i < planes.size( ); i++ ) {
		unsigned int arrTime = planes[i]->getArrivalTime( );

		//5 is a relative safety time differences between planes
		unsigned int safetyTime = time + 5;

		if( arrTime >= time && arrTime <= ( safetyTime ) ) {
			planes[i]->setScheduledArrivalTime( safetyTime );
			time = safetyTime;
		} else {
			time = arrTime;
		}
	}

	return planes;
}
