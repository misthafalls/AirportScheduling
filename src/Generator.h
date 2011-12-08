// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#include <vector>
#include "Genome.h"
#include "Plane.h"

#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
    
    public:
        Generator( ) { }

        const bool init( std::vector< Genome* > population,
                            const std::vector< Plane* >& planes,
                            size_t landingduration ) const ;
    private:
        
};

#endif // GENERATOR_H_
