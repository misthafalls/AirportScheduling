// Teun van Dingenen
// -----------------------------------------------------------------------------

#include "Controller.h"
#include <iostream>
#include <stdlib.h>


bool
Controller::is_feasible( Genome* g, size_t landingduration ) {
    size_t genome_size = g->get_size( );
    size_t errors = 0;
    for( size_t t = 0; t<genome_size; t++) {
        Genome::Gene* gene = g->get_gene( t );
        const Plane* p = gene->getPlane( );
        Time time = gene->getTime( );
        if( p->getArrivalTime( ) > time ) {
            return false;
        }
    }
    return true;
}

