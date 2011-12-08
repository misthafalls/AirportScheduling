// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#ifndef GENOME_H_
#define GENOME_H_

#include <stdlib.h>
#include "Plane.h"
#include "Time.h"

// Landing duration is two minutes
const static size_t LANDING_WIDTH = 2;

class Genome {
    
    public:
    class Gene {
    public:
        Gene( Plane& p, Time t )
            :
            m_plane( p ), m_time( t )
            { }
        
        const Plane& getPlane( ) { return m_plane; } const

        Time& getTime( ) { return m_time; }
        bool setTime( Time t ) { m_time = t; return true; }

    private:
        const Plane &m_plane;
        Time m_time;

    }; // end Gene
    
    public:
        Genome( size_t genome_size )
            :
            m_size( genome_size )
            { m_genome = (Gene*) malloc( genome_size - 1 ); }

//TODO figure out if position is taken or not
//        bool is_occupied( size_t t ) { return m_genome[ t ] != NULL }

        Gene* get_gene( size_t position ) { 
            if (position>=m_size) return NULL;
            else return &m_genome[ position ]; 
        }
   
    // The array is a genome, m_genome[ 0 ] is first landing position
    // m_genome[ i ] is the i landing position
    // Every position takes LANDING_WIDTH time (see above)
    // TODO: move landingwidth to input variable
    size_t m_size;
    Gene* m_genome;

}; // end Genome

#endif // GENOME_H_

//------------------------------------------------------------------------------
