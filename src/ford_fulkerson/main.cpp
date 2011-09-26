// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "FlowGraph.h"
#include "FordFulkerson.h"
#include <string.h>
#include <iostream>
#include <assert.h>

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
    if( !g.add_vertex( 'a' ) ) { assert( 0 ); }
    if( !g.add_vertex( 'b' ) ) { assert( 0 ); }
    if( !g.add_vertex( 'c' ) ) { assert( 0 ); }
    if( !g.add_vertex( 'd' ) ) { assert( 0 ); }
    g.get_vertex( 'a' )->add_edge( 2, 
            g.get_vertex( 'b' ), ford_fulkerson::FlowGraph::Edge::FORWARD ); 
    g.get_vertex( 'a' )->add_edge( 3, 
        g.get_vertex( 'c' ), ford_fulkerson::FlowGraph::Edge::FORWARD );
    g.get_vertex( 'b' )->add_edge( 3, 
        g.get_vertex( 'd' ), ford_fulkerson::FlowGraph::Edge::FORWARD );
    g.get_vertex( 'c' )->add_edge( 2, 
        g.get_vertex( 'b' ), ford_fulkerson::FlowGraph::Edge::FORWARD );
    g.get_vertex( 'c' )->add_edge( 2, 
        g.get_vertex( 'd' ), ford_fulkerson::FlowGraph::Edge::FORWARD );
    return g;
}

// ----------------------------------------------------------------------------

int main( int argc, char* argv[ ] )
{
    ford_fulkerson::FlowGraph g = createDefaultFlowGraph( );
    ford_fulkerson::FordFulkerson f(g);
    std::map< ford_fulkerson::FlowGraph::Vertex*, 
                ford_fulkerson::FlowGraph::Edge* > path;
    size_t flow = 0;
    size_t round = 0;
    while( !( path = f.init( g.get_vertex( 'a' ), 
                g.get_vertex( 'd' ) ) ).empty( ) ) {
        std::cout << "Found Augumented Path!!" << std::endl;
        std::map< ford_fulkerson::FlowGraph::Vertex*, 
                ford_fulkerson::FlowGraph::Edge* >::iterator it =
                path.begin( );
        while( it != path.end( ) ) {
            std::cout << "Vertex: " << (*it).first->m_name <<
                " Edge: " << (*it).second->m_flow << std::endl; 
            it++;
        }
        flow += f.process_path( path );
        round++;
   }
   std::cout << "Max flow = " << flow << std::endl;
   std::map< const char, ford_fulkerson::FlowGraph::Vertex* >::iterator it;
   it = g.get_vertices( )->begin( );
   for( it; it != g.get_vertices( )->end( ); it++ ) {
        std::cout << "Flow from Vertice: " << it->first << " is: ";
        std::list< ford_fulkerson::FlowGraph::Edge* >::iterator e_it;
        e_it = it->second->get_edges( )->begin( );
        size_t edge_flow = 0;
        for( e_it; e_it != it->second->get_edges( )->end( ); e_it++ ) {
            if( (*e_it)->get_direction( ) == 
                ford_fulkerson::FlowGraph::Edge::FORWARD )
                edge_flow += (*e_it)->m_flow;
        }
        std::cout << edge_flow << std::endl;
    }
    return 0;
}
