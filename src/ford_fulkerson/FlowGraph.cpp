// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "FlowGraph.h"
#include <memory> //auto_ptr

namespace ford_fulkerson
{

// -----------------------------------------------------------------------------

FlowGraph::FlowGraph( )
{
    m_first = 'z';
    m_last = 'a';
}

// ----------------------------------------------------------------------------

bool
FlowGraph::add_vertex( const char &c )
{
    std::auto_ptr< Vertex > new_vertex ( new Vertex( c ) );
    if( !new_vertex.get( ) ) return false;
//    m_vertices[ c ] = new_vertex.release( );
    std::pair<std::map< const char, Vertex* >::iterator, bool > ret;
    ret = m_vertices.insert( 
        std::pair< const char, Vertex* >( c, new_vertex.release( ) ) );
    return ret.second;
}

// ----------------------------------------------------------------------------

FlowGraph::Edge* 
FlowGraph::Vertex::add_edge( const size_t &value, Vertex* v, Edge::Direction d )
{
    std::auto_ptr< Edge > new_edge ( new Edge( value, *v, *this, d ) );
    if( d == Edge::FORWARD ) {
        new_edge->set_reverse( v->add_edge( value, this, Edge::BACKWARD ) );
        new_edge->get_reverse( )->set_reverse( new_edge.get( ) );
    }
    m_edges.push_back( new_edge.release( ) );
    return m_edges.back( );
}

// ----------------------------------------------------------------------------

bool
FlowGraph::clear_marks( Vertex* v )
{
    if( !v ) v = m_vertices.begin( )->second;
    v->set_mark( false );
    std::list< Edge* >::iterator it = v->get_edges( )->begin( );
    for( it; it != v->get_edges( )->end( ); it++ ) {
        if( (*it)->get_direction( ) == Edge::FORWARD && 
                (*it)->get_to( )->get_mark( ) ) {
            clear_marks( (*it)->get_to( ) );
        }
    }
/**
    std::map< const char, Vertex* >::iterator it = m_vertices.begin( );
    size_t count = 0;
    while( it != m_vertices.end( ) ) {
        (*it).second->set_mark( false );
        count++;
        it = m_vertices.begin( );
        for( size_t t = 0; t < count; t++ ) {
            it++;
        }
    }
**/
    return true;
}

// ----------------------------------------------------------------------------

}
