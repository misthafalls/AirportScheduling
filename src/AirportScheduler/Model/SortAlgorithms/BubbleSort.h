/*
 * BubbleSortAlgorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <vector>
#include "../Plane.h"

class BubbleSort {
public:
	BubbleSort();
	virtual ~BubbleSort();

	std::vector<Plane*> & scheduleByArrivalTimeAscending(std::vector<Plane*> & planes);
	std::vector<Plane*> & scheduleByFinalLandingTimeAscending(std::vector<Plane*> & planes);
	std::vector<Plane*> & scheduleByPriorityAscending(std::vector<Plane*> & planes);
};

#endif /* BUBBLESORT_H_ */
