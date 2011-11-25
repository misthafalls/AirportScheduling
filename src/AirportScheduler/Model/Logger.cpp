/*
 * Logger.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Logger.h"

#define PRINT_DEBUG 0

#include <time.h>
#include <stdarg.h>
#include <iostream>
#if PRINT_DEBUG
#include <stdio.h>
#endif
using namespace std;

void Logger::log(string txt) {
#if PRINT_DEBUG
	cout << txt << endl;
#endif
}

void Logger::logex(const char * fmt, ...) {
#if PRINT_DEBUG
	va_list vl;

	char msg[2048];

	va_start(vl, fmt);
	vsprintf(msg, fmt, vl);
	va_end(vl);

	log(msg);
#endif
}

void Logger::wait() {
	cin.get();
}
