/*
 * Controller.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Model/Model.h"

class Controller
{
public:
	Controller(Model * model);
	virtual ~Controller();

	bool setup();

protected:
	Model * model;
};

#endif /* CONTROLLER_H_ */
