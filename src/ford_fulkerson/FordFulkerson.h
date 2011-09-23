// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "FlowGraph.h"
#include <map>
#include <list>
#include <cstddef>
#include <queue>

#ifndef FORDFULKERSON_H_
#define FORDFULKERSON_H_

namespace ford_fulkerson
{

class FordFulkerson {

    public:
        FordFulkerson( FlowGraph fg )
            :
            g(fg)
        { }
        std::map< FlowGraph::Vertex*, FlowGraph::Edge* >
            init( FlowGraph::Vertex* source, FlowGraph::Vertex* sink );

        size_t process_path( std::map< FlowGraph::Vertex*, 
                FlowGraph::Edge* > p );

    private:
        std::map< FlowGraph::Vertex*, FlowGraph::Edge* >
            breadthFirstSearch( FlowGraph::Vertex* source, 
                            FlowGraph::Vertex* sink );

         FlowGraph &g;
        
};
}

#endif // GRAPH_H_
