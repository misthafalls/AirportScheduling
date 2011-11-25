/*
 * Model.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Scheduler.h"

#include "../Values.h"
#include <string>
#include <vector>

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();
    
    bool setAlgorithm( AlgorithmType type );

    bool addPlane( Plane* plane );
    void begin();

    std::vector<Plane*>& getSchedule() { return schedule; }

private:
	Scheduler * schedulers;
	std::vector<Plane*> unorderd_planes;
	std::vector<Plane*> schedule;
};

#endif /* MODEL_H_ */
