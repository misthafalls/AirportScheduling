// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "FlowGraph.h"
#include <memory> //auto_ptr

namespace ford_fulkerson
{

// -----------------------------------------------------------------------------

FlowGraph::FlowGraph( )
{
}

// ----------------------------------------------------------------------------

bool
FlowGraph::add_vertex( const char &c )
{
    std::auto_ptr< Vertex > new_vertex ( new Vertex( c ) );
    if( !new_vertex.get( ) ) return false;
    m_vertices[ c ] = new_vertex.release( );
    return true;
}

// ----------------------------------------------------------------------------

bool 
FlowGraph::Vertex::add_edge( const size_t &value, Vertex* v)
{
    std::auto_ptr< Edge > new_edge ( new Edge( value, *v, *this ) );
    if( !new_edge.get( ) ) return false;
    v->m_edges.push_back( new_edge.get( ) );
    m_edges.push_back( new_edge.release( ) );
    return true;
}

// ----------------------------------------------------------------------------

bool
FlowGraph::clear_marks( )
{
    std::map< const char, Vertex* >::iterator it; 
    while( it != m_vertices.end( ) ) {
//    for( it = m_vertices.begin( ); it != m_vertices.end( ); it++ ) { 
        (*it).second->set_mark( false );
        it++;
    }
}

// ----------------------------------------------------------------------------

}
