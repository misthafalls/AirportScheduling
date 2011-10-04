/*
 * View.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "../Model/Model.h"

class View
{
public:
	View(Model * model);
	virtual ~View();

	bool setup();

	void print();

protected:
	Model * model;
};

#endif /* VIEW_H_ */
