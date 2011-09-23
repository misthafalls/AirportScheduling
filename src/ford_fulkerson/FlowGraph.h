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
        Edge( const size_t capacity, Vertex& to, Vertex& from )
        :   m_capacity( capacity ), m_to( to ), m_from( from ), m_flow( 0 )
        {
        }
        size_t residual( ) { return m_capacity - m_flow; }
        Vertex* get_to( ) { return &m_to; }
        Vertex* get_from( ) { return &m_from; }

        const size_t m_capacity;
        size_t m_flow;
        Vertex& m_to;
        Vertex& m_from;
    };

    class Vertex
    {
        public:
        
        Vertex( const char name )
        :   m_name( name )
        {
            m_edges.clear( );
            m_mark = false;
        }
        bool add_edge( const size_t &ch, Vertex* v );
        std::list< Edge* > get_edges( ) { return m_edges; }
        void set_mark( bool b ) { m_mark = b; }

        inline bool operator==( Vertex* v ) 
            { return v->m_name == this->m_name; }

        const char m_name;
        bool m_mark;
        std::list< Edge* > m_edges; 

    };

    public:
        FlowGraph( );
        std::map< const char, Vertex* > get_vertices( ) { return m_vertices; }
        bool add_vertex( const char &c );
        Vertex* get_vertex( const char &c ) 
            { return ( m_vertices.find( c ) )->second; }
        bool clear_marks( );

    private: // Members
        std::map< const char, Vertex* > m_vertices;
};

}

#endif // GRAPH_H_
