/*
 * Model.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Algorithm.h"
#include "Runway.h"

#include <map>
#include <string>
#include <vector>

class Model
{
public:
	Model();
	virtual ~Model();

	bool setup();
    bool addPlane(Plane * p);

    void begin();

    Algorithm * getAlgorithm() { return algorithm; }
    Runway * getRunway() { return runway; }

private:
	Algorithm * algorithm;

	std::map<std::string, Plane*> planes;

	Runway * runway;

};

#endif /* MODEL_H_ */
