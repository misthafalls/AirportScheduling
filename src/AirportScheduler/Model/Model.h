/*
 * Model.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Scheduler.h"

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();

private:
	Scheduler * schedulers;

};

#endif /* MODEL_H_ */
