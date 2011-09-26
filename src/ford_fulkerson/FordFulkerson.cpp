// Teun van Dingenen
// -----------------------------------------------------------------------------

#include "FordFulkerson.h"

namespace ford_fulkerson {

std::map< FlowGraph::Vertex*, FlowGraph::Edge* >
FordFulkerson::init( FlowGraph::Vertex* source, FlowGraph::Vertex* sink )
{
    return breadthFirstSearch( source, sink );
}

std::map< FlowGraph::Vertex*, FlowGraph::Edge* >
FordFulkerson::breadthFirstSearch( FlowGraph::Vertex* source, 
                            FlowGraph::Vertex* sink )
{
    g.clear_marks( source );
    std::queue< FlowGraph::Vertex* > queue; //FIFO queue
    std::map< FlowGraph::Vertex*, FlowGraph::Edge* > visited;
    queue.push( source );
    queue.front( )->set_mark( true );
    while( !queue.empty( ) ) {
        FlowGraph::Vertex *v = queue.front( );
        queue.pop( );
        if( v == sink ) break;
        std::list< FlowGraph::Edge* >* edges = v->get_edges( );
        for( std::list< FlowGraph::Edge* >::iterator it = edges->begin( );
                it != edges->end( );
                it++ ) {
            if( ( *it )->residual( ) <= 0 ) continue;
            if( !( ( *it )->get_to( )->m_mark && 
                    ( *it )->get_from( )->m_mark ) ) {
                FlowGraph::Vertex* to_add;
                if( ( *it )->get_from( ) == v ) 
                        to_add = ( *it )->get_to( );
                else to_add = ( *it )->get_from( );
                to_add->m_mark = true;
                queue.push( to_add );
                visited[ to_add ] = *it;
            }
        }
    }
    std::map< FlowGraph::Vertex*, FlowGraph::Edge* > path;
    if( !visited[ sink ] ) return path;
    for( FlowGraph::Vertex* v = sink; 
            v != source; 
            v = visited[ v ]->get_from( ) ) {
        std::pair< std::map< FlowGraph::Vertex*, 
                                FlowGraph::Edge* >::iterator,bool > ret;
        ret = path.insert( std::pair< FlowGraph::Vertex*, 
                                FlowGraph::Edge* >( v, visited[ v ] ) );
        if( ret.second == false ) {
            v = visited[ v ]->get_to( );
            ret = path.insert( std::pair< FlowGraph::Vertex*, 
                                FlowGraph::Edge* >( v, visited[ v ] ) );
            if( ret.second == false ) {
                //std::cout << "ERROR: path visit didn't work" << std::endl;
            }
        }
    }
    return path;
}

size_t 
FordFulkerson::process_path( std::map< FlowGraph::Vertex*, 
                                FlowGraph::Edge* > p )
{
    size_t res = 0xFFFF;
    std::map< FlowGraph::Vertex*, FlowGraph::Edge* >::iterator it; 
    for( it = p.begin( ); it != p.end( ); it++ ) {
        size_t edge_res = (*it).second->residual( );
        if( edge_res < res ) res = edge_res;
    }
    for( it = p.begin( ); it != p.end( ); it++ ) {
        size_t edge_res = (*it).second->residual( );
        if( (*it).second->get_direction( ) == FlowGraph::Edge::FORWARD ) 
                (*it).second->m_flow += res;
        else if ( (*it).second->get_direction( ) == FlowGraph::Edge::BACKWARD ) 
                (*it).second->get_reverse( )->m_flow -= res;
    }
    return res;
}

}
