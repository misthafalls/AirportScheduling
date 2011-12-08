// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#include "Plane.h"
#include "Time.h"
#include <stdlib.h>
#include <iostream>

#ifndef GENOME_H_
#define GENOME_H_

class Genome {
    
    public:
    class Gene {

        public:
        Gene( const Plane* p, Time t )
            :
            m_plane( p ), m_time( t )
            { }
        
        const Plane* getPlane( ) { return m_plane; } const

        Time& getTime( ) { return m_time; }
        bool setTime( Time t ) { m_time = t; }

        private:
        const Plane* m_plane;
        Time m_time;

    }; // end Gene
    
    public:
        Genome( size_t genome_size )
            :
            m_size( genome_size )
            { 
                m_genome = (Gene*) malloc( genome_size );
                if (m_genome == NULL ) { 
                    std::cout << "UNABLE TO ALLOCATE MEM" << std::endl;
                }
             }

        Gene* get_gene( size_t position ) { 
            if (position>=m_size) return NULL;
            else return &m_genome[ position ]; 
        }

        bool set_gene( size_t position, const Plane* p, Time t ) {
            m_genome[ position ] = Gene( p, t ); }
   
    // The array is a genome, m_genome[ 0 ] is first landing position
    // m_genome[ i ] is the i landing position
    private:
    size_t m_size;
    Gene* m_genome;

}; // end Genome

#endif // GENOME_H_

//------------------------------------------------------------------------------
