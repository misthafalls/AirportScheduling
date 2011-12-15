// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------
#include "Genome.h"

bool
Genome::has_plane( const Plane* p ) {
    for( size_t s=0;s<m_genome.size( ); s++) {
        if( m_genome[s]->getPlane( ) == p ) return true;
    }
    return false;
}
