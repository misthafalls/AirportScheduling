// Teun van Dingenen, 7 December 2011
//------------------------------------------------------------------------------

#include "Generator.h"
#include <iostream>
#include <stdlib.h>

//------------------------------------------------------------------------------

const bool
Generator::init( std::vector< Genome* > population, 
                    const std::vector< Plane* >& planes,
                    size_t landingduration ) const {
    size_t number_planes = planes.size();
    srand((unsigned)time(0));

    //for every member of the population
    for( size_t t = 0; t < population.size( ); t++ ) {
        Genome* genome = population[ t ];
        bool taken_positions[ number_planes ];
        for( size_t b=0;b<number_planes;b++ ) taken_positions[b]=false;

        //for every plane: make a gene
        for( size_t s = 0; s < number_planes; s++ ) {
            const Plane* p = planes[s];
            int random = rand( ); 
//      Not using min / max, generating complete random
//            int min = p->get_fpos();
//            int max = p->get_npos();
//            if( max > number_planes ) max = number_planes;

            // 0 =< random < number_planes
            random = random % number_planes;
//            size_t tries = 0;
            while( taken_positions[random] ) {
                random++;
                if( random > number_planes ) random = 0;
            }
            taken_positions[random] = true;
            //TODO: calculate landingtime
            Time time = p->getArrivalTime( );
            time.addMinute( random*landingduration );
            std::cout << "Setting planenr: " << s << "to " << 
                time.getFormattedTime( ) << std::endl;
            genome->add_gene( p, time );
        }
    }
}
