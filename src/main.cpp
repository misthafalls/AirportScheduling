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
#include "GeneSorter.h"

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

void printGenome( Genome* genome ) {
    std::vector< Genome::Gene* > sorted_genes;
    GeneSorter::sort( *(genome->get_genes( )), sorted_genes );

    size_t nr_crash = 0;
    size_t nr_to_early = 0;
    size_t nr_to_late = 0;
    int fuel_used = 0;
    for(size_t t=0;t<sorted_genes.size( );t++) {
        Genome::Gene* gene = sorted_genes[ t ];
        std::cout<<gene->getPlane( )->getName( ) << " Lands at: " <<
            gene->getTime( ).getFormattedTime() << std::endl <<
            "    Deadline is:" << gene->getPlane( )->getDeadlineTime( ).getFormattedTime( ) << std::endl << 
            "    Arrival is: "<< gene->getPlane( )->getArrivalTime( ).getFormattedTime( ) << std::endl << std::endl;
        const Plane* p = gene->getPlane( );
        if( p->getArrivalTime( ) > gene->getTime( ) ) nr_to_early++;
        if( p->getDeadlineTime( ) < gene->getTime( ) ) nr_crash++;
        if( p->getScheduledTime( ) < gene->getTime( ) ) nr_to_late++;
        int min_in_air = gene->getTime( ).getTimeInMinutes( ) - 
                p->getArrivalTime( ).getTimeInMinutes( );
        fuel_used += min_in_air * p->getFuelUsage( );
    }
    std::cout << "---=== Schedule Stats ===---" << std::endl <<
        "Total Planes crashed:  " << nr_crash << std::endl <<
        "Total Planes too late: " << nr_to_late << std::endl <<
        "Total Planes to early: " << nr_to_early << std::endl <<
        "Total Fuel used:       " << fuel_used << std::endl;
}

int main( int argc, char* argv[ ] )
{
    char filelocation[ 256 ];
//TODO create lanes abilities
//    int lanes = 0; 
    size_t population_size = -1;
    size_t landingduration = -1;
    size_t max_generations = -1;
    size_t nr_lanes = -1;
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
            else if( !strcmp( argv[ t ], "-l" ) ) {
                if( t+1 >= argc ) printHelp( );
                t++;
                nr_lanes = atoi( argv[ t ] );
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
    if( nr_lanes == -1 )
    {
        std::cout << "No number lanes given, ASSUMING CONTROL!" << 
            std::endl << "Setting nr lanes: 1" << std::endl;
        nr_lanes = 1;
    }
    //BEWARE: this vector takes ownership of planes!
    std::vector< Plane* > planes;
    

    CSVReader reader;
// DEBUG
    if( reader.readFile( "testfile", planes ) ) {
//    if( reader.readFile( filelocation, planes ) ) {
        std::cout << "Input file read succesfully" << std::endl;
    } else {
        std::cout << "Input file not read correctly, " <<
            "are you sure the path is correct?" << std::endl;
        exit( 0 );
    }
    size_t number_of_planes = planes.size( );

    //Calc deadline for all
    //TODO Move to CSVReader??
    for(std::vector< Plane* >::iterator p=planes.begin( ); 
        p!=planes.end( );p++) (*p)->calcDeadlineTime( );

    std::vector <Genome*> population;

    //setup generation 0
    Generator g;
    g.init( population, population_size, planes );

    //MAIN LOOP
    size_t generations = 0;
    size_t number_to_combine = 20;
    size_t number_to_die = number_to_combine / 2;
    Selector* s = new RandomSelector(number_to_combine, number_to_die);
    Mutator* m = new SimpleMutator( );
//    FitnessFunction* f = new NiceFitnessFunction( );
    FitnessFunction* f = new FuelFitnessFunction( landingduration, nr_lanes );
    SimpleCombinator c; int sum_fitness;
    while( generations < max_generations ) {
        //TODO move construction
        std::vector< Genome* > selected;
        sum_fitness = f->calculate_fitness( population );
        s->select( population, selected, sum_fitness );
        //TODO:Move choice who mother and father
        for( size_t t=0;t<number_to_die;t++) {
            Genome* mother = selected[ t ];
            Genome* father = selected[ t+10 ];
            Genome* child = c.combine( mother, father );
            population.push_back( child );
        }
        m->mutateGenomes( population, 0.05 );
        if( population.size( ) != population_size ) {
            std::cout << "ERROR: Something went wrong, " << 
                "population size not stable" << std::endl;
            return 0;
        }
        generations++;
    }

    //Choose genome for print
    f->calculate_fitness(population );
    size_t highest_fitness = -1; size_t index;
    for(size_t t=0;t<population.size();t++){
        size_t fitness = population[t]->get_fitness();
        if( fitness < highest_fitness || highest_fitness == -1 ) {
            highest_fitness = fitness;
            index = t;
        }
    }
    Genome* best_genome = population[ index ];
    printGenome( best_genome );
        
    //Cleanup
    for( std::vector<Plane*>::iterator it = planes.begin( );
            it!=planes.end( ); it++ ) delete (*it);
    for( std::vector<Genome*>::iterator it = population.begin( );
            it!=population.end( ); it++ ) delete (*it);
    return 0;
}
