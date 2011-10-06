/*
 * Model.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Scheduler.h"

#include <map>
#include <string>

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();
    bool addPlane( std::string name, int arrivalTime );

private:
	Scheduler * schedulers;

	std::map<std::string, Plane*> planes;

};

#endif /* MODEL_H_ */
