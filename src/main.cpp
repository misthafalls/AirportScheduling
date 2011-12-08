// Teun van Dingenen
//------------------------------------------------------------------------------

#include "string.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Plane.h"
#include "CSVReader.h"
#include "Genome.h"
#include "Generator.h"
#include "Controller.h"

inline void printNewLineAndIndent( int indent ) {
    std::cout << std::endl;
    for( int i = 0; i < indent; i++ ) {
        std::cout << " ";
    }
}

//TODO update helptext
void printHelp( ) {
    std::cout << "Usage: ";
    printNewLineAndIndent( 4 );
    std::cout << "AirportScheduler [-P <population_size> ] [<file name>]";
    printNewLineAndIndent( 0 );
    std::cout << "Where:";
    printNewLineAndIndent( 4 );
    std::cout << "[-P <population_size> ]  Set number of genomes to create" <<
        "Must be between 25 and 250";
    std::cout << std::endl;
    exit( 0 );
}

int main( int argc, char* argv[ ] )
{
    char filelocation[ 256 ];
//TODO create lanes abilities
//    int lanes = 0; 
    size_t population_size = -1;
    size_t landingduration = -1;
    if( argc == 1 )
    {
//        printHelp( );
    }
    else // Get input parameters
    {
        //get File
        strcpy( filelocation, argv[ argc-1 ] );
        for( int t = 1; t < argc-1; ++t )
        {
            if( !strcmp( argv[ t ], "-P" ) )
            {
                if( t+1 >= argc ) printHelp( );
                t++;
                population_size = atoi( argv[ t ] );
            }
            else if( !strcmp( argv[ t ], "-L" ) ) {
                if( t+1 >= argc ) printHelp( );
                t++;
                landingduration = atoi( argv[ t ] );
            }
        }
    }
    //Check validity
    if( population_size == -1 )
    {
        std::cout << "No population size given, ASSUMING CONTROL!" << 
            std::endl << "Setting population size: 50" << std::endl;
        population_size = 50;
    }
    if( landingduration == -1 )
    {
        std::cout << "No landing duration given, ASSUMING CONTROL!" << 
            std::endl << "Setting landing duration: 5" << std::endl;
        landingduration = 5;
    }
    //BEWARE: this vector takes ownership of planes!
    std::vector< Plane* > planes;

    CSVReader reader;
    if( reader.readFile( "testfile", planes ) ) {
        std::cout << "Input file read succesfully" << std::endl;
    } else {
        std::cout << "Input file not read correctly, " <<
            "are you sure the path is correct?" << std::endl;
        exit( 0 );
    }
    size_t number_of_planes = planes.size( );

    Time first_time = planes[ 0 ]->getArrivalTime( );
    for(size_t t=1;t<number_of_planes;t++) {
        if( planes[ t ]->getArrivalTime( ) < first_time) 
            first_time = planes[ t ]->getArrivalTime( ); 
    }
    std::cout << "First time = " << first_time.getFormattedTime( ) << std::endl;

    std::vector<Plane*>::iterator it = planes.begin( );
    while( it != planes.end( ) ) {
        Time t = first_time;
        size_t pos = 0;
        while( t < (*it)->getArrivalTime( ) ) {
            t.addMinute( landingduration );
            pos++;
        }
        if( pos == 0 ) (*it)->set_fpos( pos );
        else (*it)->set_fpos( pos-1 );

        Time d = (*it)->getDeadlineTime( );
        while( t < d ) {
            t.addMinute(landingduration);
            pos++;
        }
        (*it)->set_npos( pos-1 );
        it++;
    }
    std::cout << planes.size( ) << std::endl;
    for( size_t t = 0; t < planes.size( ); t++ )
    {
        planes[t]->print();
        std::cout << "Earliest pos: " << planes[t]->get_fpos( ) << std::endl;
        std::cout << "Last pos: " << planes[t]->get_npos() <<std::endl;
    }

    std::vector <Genome*> population;

    //initialize
    size_t t;
    for( t=0;t<population_size;t++) {
        population.push_back( new Genome( ) );
    }
    std::cout << "Initialized " << t << " Genomes" << std::endl;

    Generator g;
    g.init( population, planes, landingduration);
    Controller c;
    int nonfeas=0;
    for( t=0;t<population_size;t++) {
        if( !c.is_feasible( population[ t ], landingduration ) ) nonfeas++;
    }
    std::cout << nonfeas << " are non feasible!" << std::endl;
    return 0;
}
