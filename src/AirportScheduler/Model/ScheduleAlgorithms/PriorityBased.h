/*
 * Bruteforce.h
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#ifndef PRIORITYBASED_H_
#define PRIORITYBASED_H_

#include "../Algorithm.h"
#include <vector>

class PriorityBased : public Algorithm {
public:
	PriorityBased();
	virtual ~PriorityBased();

	std::vector<Plane*> & schedule( std::vector<Plane*> & planes );
};

#endif /* PRIORITYBASED_H_ */
