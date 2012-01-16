#include "FitnessFunction.h"
#include "Genome.h"
#include "GeneSorter.h"
#include "GenomeUtils.h"

#define PRINT_DEBUG 0

#if PRINT_DEBUG
#include <iostream>
#endif


FitnessFunction::~FitnessFunction() {}

unsigned int
FitnessFunction::get_number_of_crashes( Genome* g ) {
    size_t nr_crashes = 0;
    std::vector< Genome::Gene* > sorted;
    GeneSorter::sort( *(g->get_genes( )), sorted );
    for( size_t t=0; t<sorted.size( );t++ )
    {
        size_t max_planes = t+m_landing_strips;
        if( max_planes >= sorted.size( ) ) max_planes = sorted.size( )-1;
        if( sorted[t]->getTime( ) > sorted[t]->getPlane( )->getDeadlineTime( ) )
        {
#if PRINT_DEBUG
            std::cout << sorted[t]->getPlane( )->getName( ) <<
                "is too late" << std::endl;
#endif
            nr_crashes++;
        }
        else if( ( ( sorted[max_planes]->getTime( ).getTimeInMinutes( ) 
                    - sorted[t]->getTime( ).getTimeInMinutes( ) )
                  < m_landing_duration ) 
                  && t != max_planes ) {
            //If interval < landing duration, both planes crash
#if PRINT_DEBUG
            std::cout << "Multiple planes too close:" << std::endl;
            for( size_t s=t; s<=max_planes;s++ )
                std::cout << sorted[s]->getPlane( )->getName( ) << ":";
            std::cout << std::endl;
            std::cout << "max_planes [" << max_planes << "] - " << "t [" << 
                t << " ]" << std::endl;
#endif
            nr_crashes+=(max_planes - t) + 1;
            t+=(max_planes -t);
        }
    }
#if PRINT_DEBUG
    std::cout << "Tested Genome: " << std::endl;
    print_genome( g );
    std::cout << "Found: " << nr_crashes << " crashes." << std::endl;
    std::cout << "------------------------------------" << std::endl;
#endif
    return nr_crashes;
}

int 
NiceFitnessFunction::calculate_fitness(std::vector<Genome*>& population,
                                        bool check_crashes ) {
    //TODO Use get_number_of_crashes AND bool check_crashes
    //TODO Should become: "TimeFitnessFunction"
	std::vector<Genome::Gene*> genes;
	Genome * genome;

	int sum_fitness = 0;

	for(unsigned int i = 0; i < population.size( ); i++) {
		genome = population[i];

		GeneSorter::sort((*genome->get_genes()), genes);

		int sum_crashes = 0;
		int sum_planes_delayed = 0;

		int same_landingtime_planes = 0;
		std::vector<Time> previous_times;
		int clear_previous_time = -1;

		for(std::vector<Genome::Gene*>::const_iterator gene = genes.begin();
			gene != genes.end(); ++gene) {
			const Plane* plane = (*gene)->getPlane();
			Time current_time = (*gene)->getTime();
			current_time.subMinute(m_landing_duration);

			if (plane->getDeadlineTime() > current_time) {
				++sum_crashes;
			} else {
				//BEGIN_CRASH
				//The following checks if the plane will crash and burn!
				previous_times.push_back((*gene)->getTime());
				for(unsigned int i = 0; i < previous_times.size(); i++) {
					if(current_time < previous_times[i]) {
						if(same_landingtime_planes == m_landing_strips) {
							++sum_crashes;
							break; //Stop the loop, because plane crashed!
						}
						++same_landingtime_planes;
					} else {
						clear_previous_time = i;
					}
				}
				//END_CRASH

				if(clear_previous_time != -1)
					previous_times.erase(previous_times.begin(), previous_times.begin()+clear_previous_time);

				same_landingtime_planes = 0;
				if (plane->getScheduledTime() < current_time)
					++sum_planes_delayed;
			}
		}

		int genome_fitness = sum_crashes * PLANE_CRASHED_PENALTY +
							 sum_planes_delayed * PLANE_DELAY_PENALTY;

		genome->set_fitness(genome_fitness);

		sum_fitness += genome_fitness;
	}
	return sum_fitness;
}

int
FuelFitnessFunction::calculate_fitness( std::vector<Genome*>& population,
                                        bool check_crashes )
{
    int sum_of_fitness;
    std::vector<Genome*>::iterator genome_iterator = population.begin( );

    while( genome_iterator != population.end( ) )
    {
        size_t nr_crashes;
        size_t fitness; 
        if( check_crashes )
            nr_crashes = get_number_of_crashes( (*genome_iterator ) );

        std::vector<Genome::Gene*>::iterator gene_iterator;
        for( gene_iterator = (*genome_iterator)->get_genes( )->begin( );
                gene_iterator != (*genome_iterator)->get_genes( )->end( );
                gene_iterator++ )
            {
                Time a = (*gene_iterator)->getTime( );
                Time b = (*gene_iterator)->getPlane( )->getArrivalTime( );
                if( a < b ) {
#if PRINT_DEBUG
                    std::cout << "MAJOR ERROR, ARRIVAL < LANDING" << std::endl;
#endif
                    fitness+=1000;
                }
                else{ 
                    b = b - a;
                    int time_in_air = b.getTimeInMinutes( );
                    fitness += (time_in_air * 
                               (*gene_iterator)->getPlane( )->getFuelUsage( ) );
                }
        }
        fitness *= FUEL_UNIT_PENALTY;
        fitness += (nr_crashes * PLANE_CRASHED_PENALTY);
        (*genome_iterator)->set_fitness( fitness );
        sum_of_fitness += fitness;
        fitness = 0;
        genome_iterator++;
    }
    return sum_of_fitness;
}

