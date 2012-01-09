// Teun van Dingenen, 7 December 2011
//------------------------------------------------------------------------------

#include "Generator.h"
#include <memory>
#include "Controller.h"
#include <stdlib.h>
#include <ctime>
//------------------------------------------------------------------------------

const bool
Generator::init( std::vector< Genome* >& population, size_t todo,
                    const std::vector< Plane* >& planes ) const {
    srand((unsigned)time(0));
    Controller c;
    //for every member of the population
    size_t t = 0;
    while( t < todo ) {
        std::auto_ptr< Genome > genome( new Genome( ) ); 

        //for every plane: make a gene
        for( size_t s = 0; s < planes.size( ); s++ ) {
            Plane* p = planes.at( s );
            Time a = p->getArrivalTime( );
            Time b = p->getDeadlineTime( );
            Time c = b - a;
            int minutes = c.getTimeInMinutes( );
            int random = rand( ) % minutes;
            c = a; c.addMinute( random );
            genome->add_gene( p, c );
        }
        population.push_back( genome.release( ) );
        t++;
    }
}
