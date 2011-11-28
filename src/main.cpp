/*
* main.cpp
*
* Created on: Oct 4, 2011
* Author: SANDER
*/

#include "AirportScheduler/AirportScheduler.h"
#include "string.h"
#include <iostream>
#include <stdlib.h>

inline void printNewLineAndIndent( int indent ) {
    std::cout << std::endl;
    for( int i = 0; i < indent; i++ ) {
        std::cout << " ";
    }
}

void printHelp( ) {
    std::cout << "Usage: ";
    printNewLineAndIndent( 4 );
    std::cout << "AirportScheduler [-Ap] [-Ab] [-h] [-Cd <importance>] \\";
    printNewLineAndIndent( 8 );
    std::cout << "[-Cf <importance>] [-H <minutes>] [-L <number>] [-Sm <minutes>] \\";
    printNewLineAndIndent( 8 );
    std::cout << "[<file name>]";
    printNewLineAndIndent( 0 );
    std::cout << "Where:";
    printNewLineAndIndent( 4 );
    std::cout << "-Ap use the Priority-based algorithm";
    printNewLineAndIndent( 4 );
    std::cout << "-Ab use the BruteForce algorithm";
    printNewLineAndIndent( 4 );
    std::cout << "-h print this help text";
    printNewLineAndIndent( 0 );
    printNewLineAndIndent( 0 );
    std::cout <<"Priority-Based specific commands";
    printNewLineAndIndent( 4 );
    std::cout << "-H <minutes> Set the horizon of in minutes"
        << " (default 30)";
    printNewLineAndIndent( 4 );
    std::cout << "-L <number> Set the number of Airport Lanes " <<
        "(default 1, Max 10)";
    printNewLineAndIndent( 4 );
    std::cout << "-Sm <minutes> Set the schedulingMinutes in minutes"
		<< " (default 10)";
	printNewLineAndIndent( 4 );
    //std::cout << "-Cd <importance> Modify the importance of delay-time";
	std::cout << "-Cd Activate delay-time scheduling, cannot work with -Cf";
    printNewLineAndIndent( 4 );
   // std::cout << "-Cf <importance> Modify the importance of fuel consumption";
    std::cout << "-Cf Activate fuel saving scheduling, cannot work with -Cd";
    printNewLineAndIndent( 4 );
    printNewLineAndIndent( 0 );
    std::cout << "Note that the usage of the -Cd,-Cf -Sm and -H parameters only ";
    printNewLineAndIndent( 4 );
    std::cout << "have effect on the Priority-based algorithm." ;
    printNewLineAndIndent( 4 );
    std::cout << "The imput of <importance> must be an integer between";
    printNewLineAndIndent( 4 );
    std::cout << "0 and 100, default is 1. Please note that these values";
    printNewLineAndIndent( 4 );
    std::cout << "are relative to each other. This means the following";
    printNewLineAndIndent( 4 );
    std::cout << "inputs are the same:";
    printNewLineAndIndent( 8 );
    std::cout << "AirportScheduler -Ap -Cf 1 -Cd 1 <filename>";
    printNewLineAndIndent( 8 );
    std::cout << "AirportScheduler -Ap -Cf 29 -Cd 29 <filename>";
    printNewLineAndIndent( 0 );
    printNewLineAndIndent( 0 );
    std::cout << "Examples:";
    printNewLineAndIndent( 4 );
    std::cout << "Use the Priority based algorithm with a horizon of 15 ";
    printNewLineAndIndent( 4 );
    std::cout << "minutes. The fuel / delay ratio is 2/10, and the" <<
        "inputfile is: testFile.";
    printNewLineAndIndent( 8 );
    std::cout << "AirportScheduler -Ap -H 15 -Cf 20 -Cd 100 testfiles/testFile";
    printNewLineAndIndent( 0 );
    printNewLineAndIndent( 4 );
    std::cout << "Use the Bruteforce algorithm with inputfile: bigTestfile:";
    printNewLineAndIndent( 8 );
    std::cout << "AirportScheduler -Ab testfiles/bigTestfile";
    printNewLineAndIndent( 0 );
    exit( 0 );
}

int main( int argc, char* argv[ ] )
{
//Initialize Thread
//TODO
    char filelocation[ 256 ];
    AlgorithmType type;
    int horizon = 30; int lanes = 0; int schedulingMinutes = 10;
    int schedulingOption = 0;
    size_t fuelImportance = 0; size_t delayImportance = 0;
    bool isTypeSet = false;
    if( argc == 1 )
    {
        printHelp( );
    }
    else // Get input parameters
    {
        //get File
        strcpy( filelocation, argv[ argc-1 ] );
        for( int t = 1; t < argc-1; ++t )
        {
            if( !strcmp( argv[ t ], "-Ap" ) )
            {
                type = PRIORITY;
                isTypeSet = true;
            }
            else if( !strcmp( argv[ t ], "-Ab" ) )
            {
                std::cout << "type bruteforce set" << std::endl;
                type = BRUTEFORCE;
                isTypeSet = true;
            }
            else if( !strcmp( argv[ t ], "-H" ) )
            {
                if( t+1 >= argc ) printHelp( );
                t++;
                horizon = atoi( argv[ t ] );
            }
            else if( !strcmp( argv[ t ], "-Sm" ) )
			{
				if( t+1 >= argc ) printHelp( );
				t++;
				schedulingMinutes = atoi( argv[ t ] );
			}
            else if( !strcmp( argv[ t ], "-Cd" ) )
            {
                schedulingOption = 2;
            }
            else if( !strcmp( argv[ t ], "-Cf" ) )
            {
            	schedulingOption = 1;
            }
            else if( !strcmp( argv[ t ], "-L" ) )
            {
                if( t+1 >= argc ) printHelp( );
                t++;
                lanes = atoi( argv[ t ] );
            }
            else if( !strcmp( argv[ t ], "-h" ) )
            {
                printHelp( );
            }
        }
    }
    //Check input
    if( !isTypeSet )
    {
        std::cout << "No Algorithm selected" << std::endl;
        printHelp( );
    }
    else if( type == BRUTEFORCE )
    {
        if( fuelImportance != 0 || delayImportance != 0 )
        {
            std::cout << "Warning: Bruteforce algorithm does not support " <<
                "criteria based scheduling" << std::endl;
        }
        else if( lanes != 0 )
        {
            std::cout << "Warning: Bruteforce algorithm does not support " <<
                "multiple Lanes" << std::endl;
        }
        else if( horizon != 0 )
        {
            std::cout << "Warning: Bruteforce algorithm does not support " <<
                "horizon input; Horizon is always maximum" << std::endl;
        }
        else if( schedulingMinutes != 0 )
		{
			std::cout << "Warning: Bruteforce algorithm does not support " <<
				"scheduling minutes input" << std::endl;
		}
    }
    else if ( type == PRIORITY )
    {
        if( fuelImportance == 0 )
        {
            std::cout << "Warning: No value for fuel importance found." <<
                std::endl << " Using value 1." << std::endl;
            fuelImportance = 1;
        } else {
            if( fuelImportance < 0 || fuelImportance > 100 ) {
                std::cout << "ERROR: Fuel Importance level invalid" <<
                    std::endl;
                exit( 0 );
            }
        }
        if ( delayImportance == 0 )
        {
            std::cout << "Warning: No value for delay importance found." <<
                std::endl << " Using value 1." << std::endl;
            delayImportance = 1;
        } else {
            if( delayImportance < 0 || delayImportance > 100 ) {
                std::cout << "ERROR: Delay Importance level invalid" <<
                    std::endl;
                exit( 0 );
            }
        }
        if( lanes == 0 )
        {
            std::cout << "Warning: No value for lane count found." <<
                std::endl << " Using value 1." << std::endl;
            lanes = 1;
        } else {
            if( lanes > 10 ) {
                std::cout << "ERROR too many lanes" << std::endl;
            }
        }
        if( horizon == 0 )
        {
            std::cout << "Warning: No value for horizon found." <<
                std::endl << " Using value 0." << std::endl;
        }
        if( schedulingMinutes == 0 )
		{
			std::cout << "Warning: No value for scheduling minutes found." <<
				std::endl << " Using value 0." << std::endl;
		}
    }

AirportScheduler airportScheduler;
    //Setup
if ( airportScheduler.setup( type ) ) {
        if( airportScheduler.readFile( filelocation ) )
        {
//Start
            airportScheduler.start(lanes, horizon, schedulingMinutes, schedulingOption);
        }
        else
        {
            std::cout << "Unable to open input file" << std::endl;
        }
} else {
        std::cout << "Failed to setup scheduler" << std::endl;
    }
//Cleanup
airportScheduler.cleanup();

return 0;
}


