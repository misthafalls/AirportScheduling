// Teun van Dingenen
// -----------------------------------------------------------------------------
#include <map>
#include <list>
#include <cstddef>

#ifndef FLOWGRAPH_H_
#define FLOWGRAPH_H_

namespace ford_fulkerson
{

class FlowGraph
{
    public: //internal classes
    class Vertex;
    class Edge
    {
        public:

        enum Direction {
            FORWARD,
            BACKWARD
        };

        Edge( const size_t capacity, Vertex& to, Vertex& from, Direction d )
        :   m_capacity( capacity ), 
            m_to( to ), 
            m_from( from ), 
            m_flow( 0 ),
            m_dir( d )
        {
        }
        size_t residual( ) { return m_capacity - m_flow; }
        Vertex* get_to( ) { return &m_to; }
        Vertex* get_from( ) { return &m_from; }
        Direction get_direction( ) { return m_dir; }
        void set_reverse( Edge* edge ) { m_reverse_edge = edge; }
        Edge* get_reverse( ) { return m_reverse_edge; }

        const size_t m_capacity;
        int m_flow;
        Vertex& m_to;
        Vertex& m_from;
        Direction m_dir;
        Edge* m_reverse_edge;
    };

    class Vertex
    {
        public:
        
        Vertex( const char name )
        :   m_name( name ), m_mark( false )
        {
            m_edges.clear( );
        }
        Edge* add_edge( const size_t &ch, Vertex* v, Edge::Direction d );
        std::list< Edge* >* get_edges( ) { return &m_edges; }
        bool get_mark( ) { return m_mark; }
        void set_mark( bool b ) { m_mark = b; }

        inline bool operator==( Vertex* v ) 
            { return v->m_name == this->m_name; }

        const char m_name;
        bool m_mark;
        std::list< Edge* > m_edges; 

    };

    public:
        FlowGraph( );
        std::map< const char, Vertex* >* get_vertices( ) { return &m_vertices; }
        bool add_vertex( const char &c );
        Vertex* get_vertex( const char &c ) 
            { return ( m_vertices.find( c ) )->second; }
        bool clear_marks( Vertex* v = 0 );

    private: // Members
        std::map< const char, Vertex* > m_vertices;
        char m_first;
        char m_last;
};

}

#endif // GRAPH_H_
