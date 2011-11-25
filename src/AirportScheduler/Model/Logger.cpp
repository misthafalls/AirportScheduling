/*
 * Logger.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Logger.h"

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>

void Logger::log( std::string txt ) {
	std::cout << txt << std::endl;
}

void Logger::logex(const char * fmt, ...) {
	va_list vl;

	char msg[2048];

	va_start(vl, fmt);
	vsprintf(msg, fmt, vl);
	va_end(vl);

	log(msg);
}

void Logger::wait() {
	std::cin.get();
}
