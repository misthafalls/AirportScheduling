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

        const bool init( Genome* population, const size_t population_size,
            const std::vector< Plane* >& planes ) const ;
    private:
        
};

#endif // GENERATOR_H_
