// Teun van Dingenen
// -----------------------------------------------------------------------------

#include "Controller.h"
#include <iostream>
#include <stdlib.h>


bool
Controller::is_feasible( Genome* g, size_t landingduration ) {
    size_t genome_size = g->get_size( );
    for( size_t t = 0; t<genome_size; t++) {
        Genome::Gene* gene = g->get_gene( t );
        const Plane* p = gene->getPlane( );
        Time time = gene->getTime( );
        if( p->getArrivalTime( ) > time ) {
            std::cout << p->getArrivalTime( ).getFormattedTime( ) << " > " <<
                time.getFormattedTime( ) << std::endl;
            return false;
        }
        for( size_t s = t+1; s<genome_size; s++ ) {
            Time footime = time;
            time.addMinute( landingduration );
            Time doubleTime = g->get_gene( s )->getTime( );
            if( doubleTime < time && doubleTime > footime ) {
                std::cout << doubleTime.getFormattedTime( ) << " < " <<
                    time.getFormattedTime( ) << " and " << 
                    doubleTime.getFormattedTime( ) << " > " <<
                    footime.getFormattedTime( ) << std::endl;
                return false;
            }
        }
    }
    return true;
}

