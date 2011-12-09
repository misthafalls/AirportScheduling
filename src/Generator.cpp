// Teun van Dingenen, 7 December 2011
//------------------------------------------------------------------------------

#include "Generator.h"
#include <iostream>
#include <stdlib.h>
#include "Controller.h"

//------------------------------------------------------------------------------

const bool
Generator::init( std::vector< Genome* >& population, size_t todo,
                    const std::vector< Plane* >& planes,
                    size_t landingduration, Time first_time ) const {
    srand((unsigned)time(0));
    Controller c;
    //for every member of the population
    size_t t = 0;
    while( t < todo ) {
        Genome* genome = new Genome( ); 
        bool taken_positions[ planes.size( ) ];
        for( size_t b=0;b<planes.size( );b++ ) taken_positions[b]=false;

        //for every plane: make a gene
        for( size_t s = 0; s < planes.size( ); s++ ) {
            const Plane* p = planes[s];
            int random = rand( ); 
            int min = p->get_fpos();
            int max = p->get_npos();
            if( max > planes.size( ) ) max = planes.size( );

            // 0 =< random < number_planes
            random = random % max + min;
            while( taken_positions[random] ) {
                random++;
                if( random > planes.size() ) random = 0;
            }
            taken_positions[random] = true;
            Time time = first_time;
            time.addMinute( random*landingduration );
            genome->add_gene( p, time );
        }
        if ( c.is_feasible( genome, landingduration ) ) {
            population.push_back( genome ); t++;
        } else {
            delete genome;
        }
        std::cout << "Done: " << t << " Genomes." << std::endl;
    }
}
