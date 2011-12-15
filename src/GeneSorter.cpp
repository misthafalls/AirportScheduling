// Teun van Dingenen
// -----------------------------------------------------------------------------

#include "GeneSorter.h"
#include "Time.h"

bool
GeneSorter::sort( const std::vector< Genome::Gene* >& genes, 
                    std::vector< Genome::Gene* >& sorted ) {
    if( genes.size( ) <= 1 ) {
        sorted = genes; return false;
    }
    int pivot_index = genes.size( ) / 2;
    std::vector< Genome::Gene* > less;
    std::vector< Genome::Gene* > more;
    Time pivot_time = genes[ pivot_index ]->getTime( );
    for( size_t t=0;t<pivot_index; t++) {
        if( genes[ t ]->getTime( ) < pivot_time ) less.push_back( genes[t] );
        else more.push_back( genes[t] );
    }
    for( size_t t=pivot_index+1;t<genes.size(); t++) {
        if( genes[ t ]->getTime( ) < pivot_time ) less.push_back( genes[t] );
        else more.push_back( genes[t] );
    }
    std::vector< Genome::Gene* > lesser;
    std::vector< Genome::Gene* > greater;
    sort( less, lesser );
    sort( more, greater );
    sorted = lesser;
    sorted.push_back( genes[ pivot_index ] );
    for( size_t s=0;s<greater.size( );s++) {
        sorted.push_back( greater[ s ] );
    }
    return true;
}
