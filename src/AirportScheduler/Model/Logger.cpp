/*
 * Logger.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Logger.h"

#include <iostream>
using namespace std;

void Logger::log(string txt) {
	cout << txt << endl;

	cin.get();
}
