/*
 * Controller.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Model/Model.h"
#include "../View/View.h"

class Controller
{
public:
	Controller(Model * model, View * view);
	virtual ~Controller();

	bool setup();

protected:
	Model * model;
	View * view;
};

#endif /* CONTROLLER_H_ */
