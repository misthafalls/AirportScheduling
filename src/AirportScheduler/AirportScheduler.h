/*
 * AirportScheduler.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef AIRPORTSCHEDULER_H_
#define AIRPORTSCHEDULER_H_

#include "Model/Model.h"
#include "View/View.h"
#include "Controller/Controller.h"

class AirportScheduler {
public:
	AirportScheduler();
	virtual ~AirportScheduler();

	bool setup( AlgorithmType type );
	void cleanup();

	void start(int lanes, int horizon, int schedulingMinutes);

    bool readFile( const char* file ) const;

private:
	Model * model;
	View * view;
	Controller * controller;

};

#endif /* AIRPORTSCHEDULER_H_ */
