/*
 * FIFOAlgorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#ifndef FIFOALGORITHM_H_
#define FIFOALGORITHM_H_

#include "../Algorithm.h"
#include <vector>

class FIFOAlgorithm : public Algorithm {
public:
	FIFOAlgorithm();
	virtual ~FIFOAlgorithm();

	std::vector<Plane*> & schedule( std::vector<Plane*> & planes );
    std::vector<Plane*>::iterator findSafeTime( std::vector<Plane*> & planes, 
                            std::vector< Plane* >::iterator plane ) const;
};

#endif /* FIFOALGORITHM_H_ */
