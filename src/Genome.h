// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#include "Plane.h"
#include "Time.h"
#include <vector>

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

        bool setTime( Time t ) { m_time = t; return true; }
        private:

        const Plane* m_plane;
        Time m_time;

    }; // end Gene
    
    public:
       Genome( ){;}

        Gene* get_gene( size_t position ) { 
            if (position>=m_genome.size( )) return NULL;
            else return m_genome[ position ]; 
        }

        bool add_gene( const Plane* p, Time t ) {
            m_genome.push_back( new Gene( p, t ) ); }

        size_t get_size( ) { return m_genome.size( ); }
   
    // The array is a genome, m_genome[ 0 ] is first landing position
    // m_genome[ i ] is the i landing position
    private:
    std::vector <Gene*> m_genome;

}; // end Genome

#endif // GENOME_H_

//------------------------------------------------------------------------------
