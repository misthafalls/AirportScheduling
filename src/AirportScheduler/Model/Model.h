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
#include <vector>

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();
    //TODO remove, outdated
    bool addPlane( std::string name, int arrivalTime );
    bool addPlane( Plane *p );

    void begin();

    std::vector<Plane*> & getSchedule() { return schedule; }

private:
	Scheduler * schedulers;

	std::map<std::string, Plane*> planes;

	std::vector<Plane*> schedule;

};

#endif /* MODEL_H_ */
