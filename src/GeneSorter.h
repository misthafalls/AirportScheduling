// Teun van Dingenen
// -----------------------------------------------------------------------------


#ifndef GENESORTER_H_
#define GENESORTER_H_

#include <vector>
#include "Genome.h"

class GeneSorter {

public:
    //Sorts genes and places them in "sorted"
    static bool sort( const std::vector< Genome::Gene* >& genes,
                        std::vector< Genome::Gene* >& sorted );

};
// -----------------------------------------------------------------------------

#endif
