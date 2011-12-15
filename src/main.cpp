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
#include "Combinator.h"
#include "Selector.h"
#include "FitnessFunction.h"
#include "Mutator.h"

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
    size_t max_generations = -1;
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
            else if( !strcmp( argv[ t ], "-G" ) ) {
                if( t+1 >= argc ) printHelp( );
                t++;
                max_generations = atoi( argv[ t ] );
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
    if( max_generations == -1 )
    {
        std::cout << "No max generations given, ASSUMING CONTROL!" << 
            std::endl << "Setting max generations: 100" << std::endl;
        max_generations = 100;
    }
    //BEWARE: this vector takes ownership of planes!
    std::vector< Plane* > planes;
    

    CSVReader reader;
    if( reader.readFile( filelocation, planes ) ) {
        std::cout << "Input file read succesfully" << std::endl;
    } else {
        std::cout << "Input file not read correctly, " <<
            "are you sure the path is correct?" << std::endl;
        exit( 0 );
    }
    size_t number_of_planes = planes.size( );
    std::vector< Plane* >::iterator p;
    //Calc deadline for all
    //TODO Move to CSVReader??
    for( p=planes.begin( ); p!=planes.end( );p++) (*p)->calcDeadlineTime( );

    Time first_time = planes[ 0 ]->getArrivalTime( );
    for(size_t t=1;t<number_of_planes;t++) {
        if( planes[ t ]->getArrivalTime( ) < first_time) 
            first_time = planes[ t ]->getArrivalTime( ); 
    }
    std::cout << "First time = " << first_time.getFormattedTime( ) << std::endl;
    std::vector<Plane*>::iterator it = planes.begin( );

    std::vector <Genome*> population;

    //initialize
    Generator g;
    g.init( population, population_size, planes, landingduration, first_time);
//    Controller c;
//    int nonfeas=0;
//    for( t=0;t<population_size;t++) {
//        if( !c.is_feasible( population[ t ], landingduration ) ) nonfeas++;
//    }
//    std::cout << nonfeas << " are non feasible!" << std::endl;
    
    //MAIN LOOP
    //FitnessFunction ff;
    size_t generations = 0;
    size_t number_to_combine = 20;
    size_t number_to_die = number_to_combine / 2;
    while( generations < max_generations ) {
//        if( !ff.calcTotalFitness( population ) ){
//            std::cout << "ERROR while calculating fitness of generation: " <<
//                generations << std::endl;
//            return 0;
//       }
        Selector s = Selector(number_to_combine, number_to_die);
        s.getSelected( population );
        Combinator c;
        for( size_t t=0;t<number_to_die;t++) {
            Genome* mother = population[ s.get_to_combine_index( t ) ];
            Genome* father = population[ s.get_to_combine_index( t+10 ) ];
            Genome* child = c.combine( mother, father );
            population.push_back( child );
        }
        Mutator m;
        m.mutateGenomes( population, 0.05 );
        if( population.size( ) != population_size ) {
            std::cout << "ERROR: Something went wrong, " << 
                "population size not stable" << std::endl;
            return 0;
        }
        std::cout << "Completed generation: " << generations << std::endl;
        generations++;
    }
    FitnessFunction f;
    f.calcTotalFitness(population);
    size_t highest_fitness = 0; size_t index;
    for(size_t t=0;t<population.size();t++){
        size_t fitness = f.getFitness( population[t] );
        if( fitness > highest_fitness ) {
            highest_fitness = fitness;
            index = t;
        }
    }
    Genome* best_genome = population[ index ];
    size_t nr_crash = 0;
    size_t nr_to_early = 0;
    size_t nr_to_late = 0;
    size_t fuel_used = 0;
    for(size_t t=0;t<best_genome->get_size( );t++) {
        Genome::Gene* gene = best_genome->get_gene( t );
        std::cout<<gene->getPlane( )->getName( ) << " Lands at: " <<
            gene->getTime( ).getFormattedTime() << std::endl <<
            "    Deadline is:" << gene->getPlane( )->getDeadlineTime( ).getFormattedTime( ) << std::endl << 
            "    Arrival is: "<< gene->getPlane( )->getArrivalTime( ).getFormattedTime( ) << std::endl << std::endl;
        const Plane* p = gene->getPlane( );
        if( p->getArrivalTime( ) > gene->getTime( ) ) nr_to_early++;
        if( p->getDeadlineTime( ) < gene->getTime( ) ) nr_crash++;
        if( p->getScheduledTime( ) < gene->getTime( ) ) nr_to_late++;
        size_t min_in_air = gene->getTime( ).getTimeInMinutes( ) - 
                p->getArrivalTime( ).getTimeInMinutes( );
        fuel_used += min_in_air * p->getFuelUsage( );
    }
    std::cout << "---=== Schedule Stats ===---" << std::endl <<
        "Total Planes crashed:  " << nr_crash << std::endl <<
        "Total Planes too late: " << nr_to_late << std::endl <<
        "Total Planes to early: " << nr_to_early << std::endl <<
        "Total Fuel used:       " << fuel_used << std::endl;
        
    return 0;
}
