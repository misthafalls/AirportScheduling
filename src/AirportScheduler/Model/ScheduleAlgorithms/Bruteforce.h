/*
 * FIFOAlgorithm.h
 *
 *  Created on: Oct 4, 2011
 *      Author: christian
 */

#ifndef BRUTEFORCE_H_
#define BRUTEFORCE_H_

#include "../Algorithm.h"
#include <vector>

class Bruteforce : public Algorithm {

typedef std::vector< Plane* >::iterator plane_iterator;

public:
	Bruteforce();
	virtual ~Bruteforce();

	void schedule(std::vector<Plane*> & planes);

private:
    std::vector<Plane*>::iterator findSafeTime( std::vector<Plane*> & planes, 
                            const std::vector< Plane* >::iterator plane ) const;

    std::vector<Plane*>::iterator rescheduleForPlaneType( 
                            std::vector<Plane*> & planes, 
                            const std::vector< Plane* >::iterator plane,
                            const Time expectedLandingTime ) const;

    size_t rescheduleEqualArrivals( std::vector< Plane* >& planes ) const;
};

#endif /* BRUTEFORCE_H_ */
