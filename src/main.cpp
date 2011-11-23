/*
 * main.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "AirportScheduler/AirportScheduler.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main( int argc, char* argv[ ] )
{
	//Command Line parameters check
    char filelocation[256];
    if( argc == 1 )
    {
        std::cout << "Usage: -f [testfile]" << std::endl;    
    }
    else
    {
        for( int t = 1; t < argc; ++t )
        {
            if( !strcmp( argv[ t ], "-f" ) && t + 1 <= argc )
            {
                t++;
                strcpy( filelocation, argv[ t ] );
            }
        }
    }

    bool fileSet = false;
    if( argc == 2 && !strcmp( argv[ 1 ], "-h" ) )
    {
        // TODO: add more help text
        std::cout << "Usage: -f [testfile]" << std::endl;    
    }
    else 
    {
        for( int t = 1; t < argc; ++t )
        {
            if( !strcmp( argv[ t ], "-f" ) && t + 1 <= argc )
            {
                t++;
                strcpy( filelocation, argv[ t ] );
                fileSet = true;
            }
        }
    }

	AirportScheduler airportScheduler;

	//Setup
	if (airportScheduler.setup()) {
		//Start
        if (fileSet) {
            airportScheduler.readFile(filelocation);
    		airportScheduler.start();
        }
	}

	//Cleanup
	airportScheduler.cleanup();

	//Exit
	cout << "Press enter to exit..." << endl;
	cin.get();

	return 0;
}
