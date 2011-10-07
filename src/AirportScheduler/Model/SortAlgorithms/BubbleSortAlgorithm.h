/*
 * BubbleSortAlgorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#ifndef BUBBLESORTALGORITHM_H_
#define BUBBLESORTALGORITHM_H_

#include "../Algorithm.h"

class BubbleSortAlgorithm: public Algorithm {
public:
	BubbleSortAlgorithm();
	virtual ~BubbleSortAlgorithm();

	std::vector<Plane*>& schedule(std::vector<Plane*> &planes);
};

#endif /* BUBBLESORTALGORITHM_H_ */
