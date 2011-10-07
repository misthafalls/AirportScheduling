/*
 * View.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "../Model/Model.h"

#include <vector>

class View
{
public:
	View(Model * model);
	virtual ~View();

	bool setup();

	void print();
	void printPlaneList(std::vector<Plane*> & list);

protected:
	Model * model;
};

#endif /* VIEW_H_ */
