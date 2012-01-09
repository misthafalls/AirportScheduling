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
#include "GenomeUtils.h"

enum FUNCTION {
    DEFAULT_FUNCTION,
    TIME_FUNCTION,
    FUEL_FUNCTION
};

enum SELECTOR {
    DEFAULT_SELECTOR,
    FITTEST_SELECTOR,
    TOURNAMENT_SELECTOR,
    ROULETTE_SELECTOR
};

enum MUTATOR {
    DEFAULT_MUTATOR,
    SIMPLE_MUTATOR,
    SUBTRACT_MUTATOR,
    ADD_MUTATOR,
    COMBO_MUTATOR
};

enum COMBINATOR {
	DEFAULT_COMBINATOR,
	SIMPLE_COMBINATOR,
	RANDOM_COMBINATOR,
	AVERAGE_COMBINATOR,
	BLOCK_COMBINATOR,
	TIME_COMBINATOR
};

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
    std::cout << "AirportScheduler [ parameters ] [<file name>]";
    printNewLineAndIndent( 0 );
    std::cout << "Available Parameters:";
    printNewLineAndIndent( 4 );
    std::cout << "[-P <population_size> ]  Set number of genomes to create" <<
        "Must be between 25 and 250";
    printNewLineAndIndent( 4 );
    std::cout << "[-L <landing duration> ]  Set duration of landing sequence";
    printNewLineAndIndent( 4 );
    std::cout << "[-D <death_toll> ]  Set number of deaths per generation";
    printNewLineAndIndent( 4 );
    std::cout << "[-l <number> ]  Set number of lanes available at airport";
    printNewLineAndIndent( 4 );
    std::cout << "[-F <function> ]  Set fitness function can be: FUEL or TIME";
    printNewLineAndIndent( 4 );
    std::cout << "[-S <selector> ]  Set selector can be: RANDOM";
    printNewLineAndIndent( 4 );
    std::cout << "[-M <mutator> ]  Set mutator can be: SIMPLE, SUBTRACT, ADD or COMBO";
    printNewLineAndIndent( 4 );
    std::cout << "[-C <combinator> ]  Set combinator can be: SIMPLE, RANDOM, AVERAGE, BLOCK or TIME";
    std::cout << std::endl;
    exit( 0 );
}

int main( int argc, char* argv[ ] )
{
    char filelocation[ 256 ];
    unsigned int population_size = -1;
    unsigned int landingduration = -1;
    unsigned int max_generations = -1;
    unsigned int nr_lanes = -1;
    unsigned int number_to_die = -1; 

    SELECTOR s = DEFAULT_SELECTOR;
    MUTATOR m = DEFAULT_MUTATOR;
    FUNCTION f = DEFAULT_FUNCTION;
    COMBINATOR c = DEFAULT_COMBINATOR;

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
            else if( !strcmp( argv[ t ], "-D" ) ) {
                if( t+1 >= argc ) printHelp( );
                t++;
                number_to_die = atoi( argv[ t ] );
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
            else if( !strcmp( argv[ t ], "-F" ) ) {
                //Set fitness function
                if( t+1 >= argc ) printHelp( );
                t++;
                if( !strcmp( argv[ t ], "FUEL" ) ) {
                    f = FUEL_FUNCTION;
                } else if ( !strcmp( argv[ t ], "TIME" ) ) {
                    f = TIME_FUNCTION;
                }
            }
            else if( !strcmp( argv[ t ], "-M" ) ) {
                //Set mutator
                if( t+1 >= argc ) printHelp( );
                t++;
                if( !strcmp( argv[ t ], "SIMPLE" ) ) {
                    m = SIMPLE_MUTATOR;
                } else if ( !strcmp( argv[ t ], "SUBTRACT" ) ) {
                    m = SUBTRACT_MUTATOR;
                } else if ( !strcmp( argv[ t ], "ADD" ) ) {
                    m = ADD_MUTATOR;
                } else if ( !strcmp( argv[ t ], "COMBO" ) ) {
                    m = COMBO_MUTATOR;
                }
           }
           else if( !strcmp( argv[ t ], "-S" ) ) {
                //Set selector
                if( t+1 >= argc ) printHelp( );
                t++;
                if( !strcmp( argv [ t ], "FITTEST" ) ) {
                    s = FITTEST_SELECTOR;
                } else if( !strcmp( argv [ t ], "TOURNAMENT" ) ) {
                	s = TOURNAMENT_SELECTOR;
                } else if( !strcmp( argv [ t ], "ROULETTE" ) ) {
                	s = ROULETTE_SELECTOR;
                }
           }
           else if( !strcmp( argv[ t ], "-C" ) ) {
				if( t+1 >= argc ) printHelp( );
				t++;
				if( !strcmp( argv [ t ], "SIMPLE" ) ) {
					c = SIMPLE_COMBINATOR;
				} else if( !strcmp( argv [ t ], "RANDOM" ) ) {
					c = RANDOM_COMBINATOR;
				} else if( !strcmp( argv [ t ], "AVERAGE" ) ) {
					c = AVERAGE_COMBINATOR;
				} else if( !strcmp( argv [ t ], "BLOCK" ) ) {
					c = BLOCK_COMBINATOR;
				} else if( !strcmp( argv [ t ], "TIME" ) ) {
					c = TIME_COMBINATOR;
				}
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
            std::endl << "Setting max generations: 1000" << std::endl;
        max_generations = 1000;
    }
    if( nr_lanes == -1 )
    {
        std::cout << "No number lanes given, ASSUMING CONTROL!" << 
            std::endl << "Setting nr lanes: 1" << std::endl;
        nr_lanes = 1;
    }
    if( number_to_die == -1 )
    {
        number_to_die = population_size / 5;
        std::cout << "No dead-toll given, using default: \"population / 5 \" "
            << " = " << number_to_die << std::endl;
    } else if( number_to_die > (population_size / 2 ) ) {
        number_to_die = population_size / 5;
        std::cout << "Dead-toll too high, using default: \"population / 5 \" "
            << " = " << number_to_die << std::endl;
    }
    unsigned int number_to_combine = number_to_die * 2;
    FitnessFunction* function;
    Mutator* mutator;
    Selector* selector;
    Combinator* combinator;
    switch( f ) {
        case TIME_FUNCTION:
            function = new NiceFitnessFunction( landingduration, nr_lanes );
            break;
        case DEFAULT_FUNCTION:
            std::cout << "No fitness function set, using default: " <<
                "FuelFitnessFunction" << std::endl;
        case FUEL_FUNCTION:
            function = new FuelFitnessFunction( landingduration, nr_lanes );
            break;
    }
    switch( m ) {
        case SIMPLE_MUTATOR:
            mutator = new SimpleMutator( );
            break;
        case SUBTRACT_MUTATOR:
            mutator = new SubtractTimeMutator( );
            break;
        case ADD_MUTATOR:
            mutator = new AddTimeMutator( );
            break;
        case DEFAULT_MUTATOR:
            std::cout << "No mutator set, using default: " <<
                "ComboMutator" << std::endl;
         case COMBO_MUTATOR:
            mutator = new ComboMutator( );
            break;
    }
    switch( s ) {
        case DEFAULT_SELECTOR:
            std::cout << "No selector set, using default: " <<
                "FittestSelector" << std::endl;
        case FITTEST_SELECTOR:
            selector = new FittestSelector( number_to_combine, number_to_die );
            break;
        case TOURNAMENT_SELECTOR:
        	selector = new TournamentSelector( number_to_combine, number_to_die );
        	break;
        case ROULETTE_SELECTOR:
        	selector = new RouletteSelector( number_to_combine, number_to_die );
        	break;
    }
    switch( c ) {
    	case DEFAULT_COMBINATOR:
    		std::cout << "No combinator set, using default: " <<
    	                "SimpleCombinator" << std::endl;
    	case SIMPLE_COMBINATOR:
    		combinator = new SimpleCombinator();
    		break;
    	case AVERAGE_COMBINATOR:
    		combinator = new AverageCombinator();
    		break;
    	case RANDOM_COMBINATOR:
    		combinator = new RandomCombinator();
    		break;
    	case BLOCK_COMBINATOR:
    		combinator = new BlockCombinator();
    		break;
    	case TIME_COMBINATOR:
    		combinator = new TimeCombinator();
    		break;
    }

    //BEWARE: this vector takes ownership of planes!
    std::vector< Plane* > planes;
    
    CSVReader reader;
// DEBUG
//    if( reader.readFile( "testfile_fatty", planes ) ) {
    if( reader.readFile( filelocation, planes ) ) {
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

    std::vector<Genome*> population;

    //setup generation 0
    Generator g;
    g.init( population, population_size, planes );

    //MAIN LOOP
    size_t generations = 0;
    int sum_fitness;
    while( generations < max_generations ) {
        //TODO move construction
        std::vector< Genome* > selected;
        sum_fitness = function->calculate_fitness( population );
        selector->select( population, selected, sum_fitness );
        //TODO:Move choice who mother and father
        for( size_t t=0;t<number_to_die;t++) {
            Genome* mother = selected[ t ];
            Genome* father = selected[ t+10 ];
            Genome* child = combinator->combine( mother, father );
            population.push_back( child );
        }
        mutator->mutateGenomes( population, 1 );
        if( population.size( ) != population_size ) {
            std::cout << "ERROR: Something went wrong, " <<
                "population size not stable" << std::endl;
            return 0;
        }
        generations++;
    }

    //Choose genome for print
    function->calculate_fitness(population );
    size_t highest_fitness = -1; size_t index;
    for(size_t t=0;t<population.size();t++){
        size_t fitness = population[t]->get_fitness();
        if( fitness > highest_fitness || highest_fitness == -1 ) {
            highest_fitness = fitness;
            index = t;
        }
    }
    Genome* best_genome = population[ index ];
    size_t crashes = function->get_number_of_crashes( best_genome );
    GenomeUtils::print_genome_more( best_genome, crashes );
        
    //Cleanup
    for( std::vector<Plane*>::iterator it = planes.begin( );
            it!=planes.end( ); it++ ) delete (*it);
    for( std::vector<Genome*>::iterator it = population.begin( );
            it!=population.end( ); it++ ) delete (*it);
    return 0;
}
