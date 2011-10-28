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
void startDataEntry( AirportScheduler& as ) {
    std::cout << "Starting manual plane entry.." << std::endl << std::endl;
    bool addMore = true;
    char name[ 256 ]; char time[ 256 ];
    size_t t = 0;
    while ( addMore ) {
        std::cout << "Please enter the flight number:";
        std::cin.getline( name, 256 );
        std::cout << "Please enter the flight arrival time:";
        std::cin.getline( time, 256 );
        //int itime = atoi( time );
        std::string sname( name );
//TODO re-create this to add planes with all variables
//        as.addPlane( sname, itime );
        std::cout << "Plane added, would you like to add more? (y/n)";
        t++;
        char c;
        std::cin >> c;
        if( c != 'y' ) addMore = false;
    }
    std::cout << std::endl << "Added " << t << " planes." << std::endl;
}

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
        for( int t = 1; t < argc; ++t )
        {
            if( !strcmp( argv[ t ], "-f" ) && t + 1 <= argc )
            {
                t++;
                strcpy( filelocation, argv[ t ] );
            }
        }
    }

    bool file_set = false;
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
                file_set = true;
            }
        }
    }
	AirportScheduler airportScheduler;

    //Added for debug purposes; 
//    file_set = true;
//    strcpy( filelocation, "testfile" );
	//Setup
	if (airportScheduler.setup()) {
		//Start
        if( file_set ) {
            airportScheduler.readFile( filelocation );
            std::cout << "File read, would you like to add more planes? (y/n)";
            char c;
            std::cin >> c;
            if( c == 'y' ) { startDataEntry( airportScheduler ); }
        } else {
            startDataEntry( airportScheduler );
        }
		airportScheduler.start( );
	}

	//Cleanup
	airportScheduler.cleanup();

	return 0;
}
