/*
 * main.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "AirportScheduler/AirportScheduler.h"
#include "string.h"
#include <iostream>

int main( int argc, char* argv[ ] )
{
	//Initialize Thread
	//TODO
    char filelocation[ 256 ];
    if( argc == 1 )
    {
        std::cout << "Usage: -f [testfile]" << std::endl;    
    }
    else 
    {
        for( size_t t = 1; t < argc; ++t )
        {
            if( !strcmp( argv[ t ], "-f" ) && t + 1 <= argc )
            {
                t++;
                strcpy( filelocation, argv[ t ] );
            }
        }
    }
	//Construct
	AirportScheduler * airportScheduler = new AirportScheduler();

	//Setup
	if (airportScheduler->setup()) {
		//Start
		airportScheduler->start();
	}

	//Cleanup
	airportScheduler->cleanup();

	//Deconstruct
	delete airportScheduler;

	return 0;
}
