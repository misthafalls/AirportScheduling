// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#ifndef GENOME_H_
#define GENOME_H_

class Genome {
    
    public:
    class Gene {

        Gene( Plane& p, Time t )
            :
            m_plane( p ), m_time( t )
            { }
        
        const Plane& getPlane( ) { return m_plane } const;

        Time& getTime( ) { return &m_time };
    private:
        const Plane &m_plane;
        Time m_time;

    } // end Gene
   
    //TODO map<Plane, Time>
    // Fixed timeslot width

} // end Genome

#endif // GENOME_H_

//------------------------------------------------------------------------------
