//Teun van Dingenen
//Print methods for convinience

#include "Genome.h"
#include <iostream>
#include <stdlib.h>
#include "GeneSorter.h"

#ifndef GENOMEUTILS
#define GENOMEUTILS

class GenomeUtils {

public:
static void print_genome( Genome* g ) {
    std::vector<Genome::Gene*>::iterator gene_iterator =
        g->get_genes( )->begin( );
    while( gene_iterator != g->get_genes( )->end( ) ) {
        std::cout << (*gene_iterator)->getPlane( )->getName( ) << "[D:" <<
            (*gene_iterator)->getPlane( )->getDeadlineTime( ).getFormattedTime( )
            << "] " << (*gene_iterator)->getTime( ).getFormattedTime( ) <<
            std::endl;
        gene_iterator++;
    }
}

static void print_genome_more( Genome* genome, size_t crashes, size_t lanes,
                                size_t landing_dur ) {
    std::vector< Genome::Gene* > sorted_genes;
    GeneSorter::sort( *(genome->get_genes( )), sorted_genes );

    size_t nr_to_early = 0;
    size_t nr_to_late = 0;
    int fuel_used = 0;
    for(size_t t=0;t<sorted_genes.size( );t++) {
        Genome::Gene* gene = sorted_genes[ t ];
        std::cout<<gene->getPlane( )->getName( ) << " Lands at: " <<
            gene->getTime( ).getFormattedTime() << std::endl <<
            "    Deadline is:" << gene->getPlane( )->getDeadlineTime( ).getFormattedTime( ) << std::endl << 
            "    Arrival is: "<< gene->getPlane( )->getArrivalTime( ).getFormattedTime( ) << std::endl;
        const Plane* p = gene->getPlane( );
        if( p->getArrivalTime( ) > gene->getTime( ) ) nr_to_early++;
        if( p->getScheduledTime( ) < gene->getTime( ) ) nr_to_late++;
        //Hack.. niet netjes
        Time important_time = gene->getTime( );
        important_time.addMinute( landing_dur ); 
        size_t max_space = t+lanes;
        if( max_space >= sorted_genes.size( ) ) 
            max_space = sorted_genes.size( ) - 1;
        if( p->getDeadlineTime( ) < gene->getTime( ) )
            std::cout << "Plane has Crashed because it's too late" << std::endl;
        else if ( sorted_genes[ max_space ]->getTime( ) <= important_time )
            if( max_space != t ) 
                std::cout << "Plane has Crashed into next: " << lanes << std::endl;
        int min_in_air = gene->getTime( ).getTimeInMinutes( ) - 
                p->getArrivalTime( ).getTimeInMinutes( );
        fuel_used += min_in_air * p->getFuelUsage( );
        std::cout << std::endl;
    }

    std::cout << "---=== Schedule Stats ===---" << std::endl <<
        "Total Planes crashed:  " << crashes << std::endl <<
        "Total Planes too late: " << nr_to_late << std::endl <<
        "Total Planes to early: " << nr_to_early << std::endl <<
        "Total Fuel used:       " << fuel_used << std::endl;
}

}; // End GenomeUtils

#endif
