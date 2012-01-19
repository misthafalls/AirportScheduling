// Teun van Dingenen
//------------------------------------------------------------------------------

#include "string.h"
#include <time.h>
#include <iostream>
#include <sstream>
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

#define EXTRA_MEASUREMENTS 1

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

timespec get_time_diff( timespec& time1, timespec& time2 ) {
    timespec ret;
	if ((time2.tv_nsec-time1.tv_nsec)<0) {
		ret.tv_sec = time2.tv_sec-time1.tv_sec-1;
		ret.tv_nsec = 1000000000 + time2.tv_nsec - time1.tv_nsec;
	} else {
		ret.tv_sec = time2.tv_sec-time1.tv_sec;
		ret.tv_nsec = time2.tv_nsec-time1.tv_nsec;
	}
    time1.tv_sec = 0;
    time1.tv_nsec = 0;
    time2.tv_sec = 0;
    time2.tv_nsec = 0;
    return ret;
}

#ifdef EXTRA_MEASUREMENTS

inline void add_time_to( timespec& add_to, timespec& to_add ) {
    add_to.tv_sec += to_add.tv_sec;
    add_to.tv_nsec += to_add.tv_nsec;
    if( add_to.tv_nsec > 1000000000 ) {
        add_to.tv_nsec -= 1000000000;
        add_to.tv_sec += 1;
    }
}

#endif

inline void printNewLineAndIndent( int indent ) {
    std::cout << std::endl;
    for( int i = 0; i < indent; i++ ) {
        std::cout << " ";
    }
}

inline std::string get_settings_string( FUNCTION f, MUTATOR m, SELECTOR s,
                                            COMBINATOR c ) {
    // creates string format:
    // FUNCTION,MUTATOR,SELECTOR,COMBINATOR
    std::ostringstream r ( std::ostringstream::out);
    switch ( f ) {
        case TIME_FUNCTION:
            r << "TIME";
            break;
        case FUEL_FUNCTION:
            r << "FUEL";
            break;
        default:
            r << "UNKNOWN";
            break;
    }
    r << ",";

    switch ( m ) {
        case SIMPLE_MUTATOR:
            r << "SIMPLE";
            break;
        case SUBTRACT_MUTATOR:
            r << "SUBTRACT";
            break;
        case ADD_MUTATOR:
            r << "ADD";
            break;
        case COMBO_MUTATOR:
            r << "COMBO";
            break;
        default:
            r << "UNKNOWN";
            break;
    }
    r << ",";

    switch ( s ) {
        case FITTEST_SELECTOR:
            r << "FITTEST";
            break;
        case TOURNAMENT_SELECTOR:
            r << "TOURNAMENT";
            break;
        case ROULETTE_SELECTOR:
            r << "ROULETTE";
            break;
        default:
            r << "UNKNOWN";
            break;
    }
    r << ",";
    switch ( c ) {
	    case SIMPLE_COMBINATOR:
            r << "SIMPLE";
            break;
	    case RANDOM_COMBINATOR:
            r << "RANDOM";
            break;
	    case AVERAGE_COMBINATOR:
            r << "AVERAGE";
            break;
	    case BLOCK_COMBINATOR:
            r << "BLOCK";
            break;
	    case TIME_COMBINATOR:
            r << "TIME";
            break;
        default:
            r << "UNKNOWN";
            break;
    }
    return r.str( );
}

//TODO update helptext
void printHelp( ) {
    std::cout << "Usage: ";
    printNewLineAndIndent( 4 );
    std::cout << "AirportScheduler [ parameters ] [<file name>]";
    printNewLineAndIndent( 0 );
    std::cout << "Available Parameters:";
    printNewLineAndIndent( 4 );
    std::cout << "-v                       be verbose";
    printNewLineAndIndent( 4 );
    std::cout << "-csv                     give output for statistics";
    printNewLineAndIndent( 4 );
    std::cout << "--no-results             do not give results in file";
    printNewLineAndIndent( 4 );
    std::cout << "[-P <population_size> ]  Set number of genomes to create" <<
        "Must be between 25 and 250";
    printNewLineAndIndent( 4 );
    std::cout << "[-p <max planes>]       Set maximum number of planes to read";
    printNewLineAndIndent( 4 );
    std::cout << "[-L <landing duration> ]  Set duration of landing sequence";
    printNewLineAndIndent( 4 );
    std::cout << "[-D <death_toll> ]  Set number of deaths per generation";
    printNewLineAndIndent( 4 );
    std::cout << "[-l <number> ]  Set number of lanes available at airport";
    printNewLineAndIndent( 4 );
    std::cout << "[-F <function> ]  Set fitness function can be: FUEL or TIME";
    printNewLineAndIndent( 4 );
    std::cout << "[-S <selector> ]  Set selector can be: FITTEST, TOURNAMENT, ROULETTE";
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
    unsigned int max_planes = -1;
    unsigned int nr_lanes = -1;
    unsigned int number_to_die = -1; 
    bool be_verbose = false;
    bool print_for_csv = false;
    bool print_results = true;

    SELECTOR s = DEFAULT_SELECTOR;
    MUTATOR m = DEFAULT_MUTATOR;
    FUNCTION f = DEFAULT_FUNCTION;
    COMBINATOR c = DEFAULT_COMBINATOR;

    if( argc == 1 )
    {
        printHelp( );
    }
    else // Get input parameters
    {
        //get File
        if( !strcmp( argv[ 1 ], "-h" ) ) 
                printHelp( );
        strcpy( filelocation, argv[ argc-1 ] );
        for( int t = 1; t < argc-1; ++t )
        {
            if( !strcmp( argv[ t ], "-P" ) )
            {
                if( t+1 >= argc ) printHelp( );
                t++;
                population_size = atoi( argv[ t ] );
            }else if( !strcmp( argv[ t ], "-v" ) ) {
                be_verbose = true;
            }else if( !strcmp( argv[ t ], "-csv" ) ) {
                print_for_csv = true;
            }else if( !strcmp( argv[ t ], "--no-results" ) ) {
                print_results = false;
            }else if( !strcmp( argv[ t ], "-D" ) ) {
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
            else if( !strcmp( argv[ t ], "-p" ) ) {
                if( t+1 >= argc ) printHelp( );
                t++;
                max_planes = atoi( argv[ t ] );
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
        if( be_verbose ) {
        std::cout << "No population size given, ASSUMING CONTROL!" << 
            std::endl << "Setting population size: 50" << std::endl;
        }
        population_size = 50;
    }
    if( landingduration == -1 )
    {
        if( be_verbose ) {
        std::cout << "No landing duration given, ASSUMING CONTROL!" << 
            std::endl << "Setting landing duration: 5" << std::endl;
        }
        landingduration = 5;
    }
    if( max_generations == -1 )
    {
        if( be_verbose ) {
        std::cout << "No max generations given, ASSUMING CONTROL!" << 
            std::endl << "Setting max generations: 1000" << std::endl;
        }
        max_generations = 1000;
    }
    if( nr_lanes == -1 )
    {
        if( be_verbose ) {
        std::cout << "No number lanes given, ASSUMING CONTROL!" << 
            std::endl << "Setting nr lanes: 1" << std::endl;
        }
        nr_lanes = 1;
    }
    if( number_to_die == -1 )
    {
        number_to_die = population_size / 5;
        if( be_verbose ) {
        std::cout << "No dead-toll given, using default: \"population / 5 \" "
            << " = " << number_to_die << std::endl;
        }
    } else if( number_to_die > (population_size / 2 ) ) {
        number_to_die = population_size / 5;
        if( be_verbose ) {
        std::cout << "Dead-toll too high, using default: \"population / 5 \" "
            << " = " << number_to_die << std::endl;
        }
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
            if( be_verbose ) {
            std::cout << "No fitness function set, using default: " <<
                "FuelFitnessFunction" << std::endl;
            }
            f = FUEL_FUNCTION;
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
            if( be_verbose ) {
            std::cout << "No mutator set, using default: " <<
                "ComboMutator" << std::endl;
            }
            m = COMBO_MUTATOR;
         case COMBO_MUTATOR:
            mutator = new ComboMutator( );
            break;
    }
    switch( s ) {
        case DEFAULT_SELECTOR:
            if( be_verbose ) {
            std::cout << "No selector set, using default: " <<
                "RouletteSelector" << std::endl;
            }
            s = ROULETTE_SELECTOR;
        case ROULETTE_SELECTOR:
        	selector = new RouletteSelector( number_to_combine, number_to_die );
        	break;
        case FITTEST_SELECTOR:
            selector = new FittestSelector( number_to_combine, number_to_die );
            break;
        case TOURNAMENT_SELECTOR:
        	selector = new TournamentSelector( number_to_combine, number_to_die );
        	break;
    }
    switch( c ) {
    	case DEFAULT_COMBINATOR:
            if( be_verbose ) {
    		std::cout << "No combinator set, using default: " <<
    	                "AverageCombinator" << std::endl;
            }
            c = AVERAGE_COMBINATOR;
    	case AVERAGE_COMBINATOR:
    		combinator = new AverageCombinator();
    		break;
    	case SIMPLE_COMBINATOR:
    		combinator = new SimpleCombinator();
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
    if( reader.readFile( filelocation, planes, max_planes ) ) {
        if( be_verbose ) {
        std::cout << "Input file read succesfully" << std::endl;
        }
    } else {
        if( be_verbose ) {
        std::cout << "Input file not read correctly, " <<
            "are you sure the path is correct?" << std::endl;
        }
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


    //Time measurement variables
    timespec time1, time2;
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &time1);

#if EXTRA_MEASUREMENTS
    timespec fitness_t, fitness_time1, fitness_time2;
    timespec select_t, select_time1, select_time2;
    timespec mutate_t, mutate_time1, mutate_time2;
    timespec combine_t, combine_time1, combine_time2;
    fitness_t.tv_sec = 0;
    fitness_t.tv_nsec = 0;

    select_t.tv_sec = 0;
    select_t.tv_nsec = 0;

    mutate_t.tv_sec = 0;
    mutate_t.tv_nsec = 0;

    combine_t.tv_sec = 0;
    combine_t.tv_nsec = 0;
#endif
   

    //MAIN LOOP
    size_t generations = 0;
    unsigned long int sum_fitness;
    while( generations < max_generations ) {
        //TODO move construction
        std::vector< Genome* > selected;
#if EXTRA_MEASUREMENTS
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &fitness_time1);
#endif
        sum_fitness = function->calculate_fitness( population );
#if EXTRA_MEASUREMENTS
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &fitness_time2);
    timespec a = get_time_diff( fitness_time1, fitness_time2 );
    add_time_to( fitness_t, a );
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &select_time1);
#endif
        selector->select( population, selected, sum_fitness );
#if EXTRA_MEASUREMENTS
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &select_time2);
    timespec b = get_time_diff( select_time1, select_time2 );
    add_time_to( select_t, b );
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &combine_time1);
#endif
        //TODO:Move choice who mother and father
        for( size_t t=0;t<number_to_die;t++) {
            Genome* mother = selected[ t ];
            Genome* father = selected[ number_to_combine - t - 1 ];
            Genome* child = combinator->combine( mother, father );
            population.push_back( child );
        }
#if EXTRA_MEASUREMENTS
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &combine_time2);
    timespec c = get_time_diff( combine_time1, combine_time2 );
    add_time_to( combine_t, c );
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &mutate_time1);
#endif
        mutator->mutateGenomes( population, 1 );
#if EXTRA_MEASUREMENTS
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &mutate_time2);
    timespec d = get_time_diff( mutate_time1, mutate_time2 );
    add_time_to( mutate_t, d );
#endif
        if( population.size( ) != population_size ) {
            if( be_verbose ) {
            std::cout << "ERROR: Something went wrong, " <<
                "population size not stable" << std::endl;
            }
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
    if( print_results ) 
        GenomeUtils::print_genome_more( best_genome, crashes, nr_lanes, 
                                        landingduration );
    
    //End time measurement
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &time2 );
    
    timespec dur = get_time_diff( time1, time2 );

    if( be_verbose ) {
    std::cout << "Duration: " << dur.tv_sec << ":" << dur.tv_nsec << 
        " seconds" << std::endl;
    }

    //CSV statistics
    //FORMAT: FITNESSFUNCTION, MUTATOR, SELECTOR, COMBINATOR, POPULATIONSIZE,
    //      MAX_GENERATION, NR_PLANES, TIME (in seconds)
    if( print_for_csv ) {
        std::cout << get_settings_string( f,m,s,c ) << "," << population_size <<
            "," << max_generations << "," << planes.size( ) << "," <<
            dur.tv_sec << "." << dur.tv_nsec << "," <<
            "fit," << fitness_t.tv_sec << "." << fitness_t.tv_nsec << "," <<
            "sel," << select_t.tv_sec << "." << select_t.tv_nsec << "," <<
            "com," << combine_t.tv_sec<< "." << combine_t.tv_nsec << "," <<
            "mut," << mutate_t.tv_sec << "." << mutate_t.tv_nsec << "," <<
            std::endl;
    }

    //Cleanup
    for( std::vector<Plane*>::iterator it = planes.begin( );
            it!=planes.end( ); it++ ) delete (*it);
    for( std::vector<Genome*>::iterator it = population.begin( );
            it!=population.end( ); it++ ) delete (*it);
    return 0;
}
