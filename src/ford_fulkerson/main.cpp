// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "FlowGraph.h"
#include "FordFulkerson.h"
#include <string.h>
#include <iostream>

#define USE_DEBUG_PRINT 1

void print_help( ) {
    std::cout << "Ford-Fulkerson algorithm demo by Teun van Dingenen" << 
            std::endl;
    //TODO: insert options for custom graph creation
}

// ----------------------------------------------------------------------------

// Default graph:
//      b.
//    /'| \
//  a'  |  'd
//   \  |  /
//    `.c./

ford_fulkerson::FlowGraph
createDefaultFlowGraph( )
{
    ford_fulkerson::FlowGraph g;
    g.add_vertex( 'a' ); // 0
    g.add_vertex( 'b' ); // 1
    g.add_vertex( 'c' ); // 2
    g.add_vertex( 'd' ); // 3
    g.get_vertex( 'a' )->add_edge( 2, g.get_vertex( 'b' ) ); 
    g.get_vertex( 'a' )->add_edge( 4, g.get_vertex( 'c' ) );
    g.get_vertex( 'b' )->add_edge( 2, g.get_vertex( 'd' ) );
    g.get_vertex( 'c' )->add_edge( 1, g.get_vertex( 'b' ) );
    g.get_vertex( 'c' )->add_edge( 5, g.get_vertex( 'd' ) );
    return g;
}

// ----------------------------------------------------------------------------

int main( int argc, char* argv[ ] )
{
    ford_fulkerson::FlowGraph g = createDefaultFlowGraph( );
    ford_fulkerson::FordFulkerson f(g);
    std::map< ford_fulkerson::FlowGraph::Vertex*, 
                ford_fulkerson::FlowGraph::Edge* > path;
    size_t flow;
    while( !( path = f.init( g.get_vertex( 'a' ), 
                g.get_vertex( 'd' ) ) ).empty( ) ) {
        std::cout << "Found Path!!" << std::endl;
        std::map< ford_fulkerson::FlowGraph::Vertex*, 
                ford_fulkerson::FlowGraph::Edge* >::iterator it =
                path.begin( );
        while( it != path.end( ) ) {
            std::cout << "Vertex: " << (*it).first->m_name <<
                " Edge: " << (*it).second->m_capacity << std::endl; 
            it++;
        }
        flow += f.process_path( path );
   }
   std::cout << "Max flow = " << flow << std::endl;
   return 0;
}
