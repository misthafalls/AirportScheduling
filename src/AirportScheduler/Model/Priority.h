/*
 * Priority.h
 *
 *  Created on: Oct 25, 2011
 *      Author: christian
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "Plane.h"
#include "Time.h"

class Priority {
public:
	Priority();
	virtual ~Priority();

	int getPriority(Plane * plane, Time globalTime);
};

#endif /* PRIORITY_H_ */
