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
using namespace std;

void Logger::log(string txt) {
	cout << txt << endl;

	cin.get();
}

void Logger::logex(const char * fmt, ...) {
	va_list vl;

	char msg[2048];

	va_start(vl, fmt);
	vsprintf(msg, fmt, vl);
	va_end(vl);

	log(msg);
}
