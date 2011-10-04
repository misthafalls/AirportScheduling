/*
 * Model.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Scheduler.h"

#include <vector>

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();

private:
	Scheduler * schedulers;

	std::vector<Plane> planes;

};

#endif /* MODEL_H_ */
