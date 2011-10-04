/*
 * Logger.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger {
public:
	static Logger * getInstance() { static Logger l; return &l; }

	void log(std::string txt);

};

#endif /* LOGGER_H_ */
