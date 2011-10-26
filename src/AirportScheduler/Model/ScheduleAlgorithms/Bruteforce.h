/*
 * Bruteforce.h
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_

#include "../Algorithm.h"
#include <vector>

class Bruteforce : public Algorithm {
public:
	Bruteforce();
	virtual ~Bruteforce();

	std::vector<Plane*> & schedule( std::vector<Plane*> & planes );
};

#endif /* BRUTEFORCE_H_ */
