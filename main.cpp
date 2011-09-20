/*
 * main.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */
#include "Graph/Node.h"
#include "Graph/Edge.h"
#include <iostream>

void createEdge ( Node* n1, Node* n2, int weight ) {
//	std::cout << n1->toString() << " " << n2->toString() << std::endl;

//	Edge* ed1 = new Edge(weight, n1);
//	std::cout << ed1->toString() << std::endl;
	Edge* ed2 = new Edge(weight, n2);
//	std::cout << ed2->toString() << std::endl;
	n1->addEdge(ed2);
//	std::cout << "First edge added" << std::endl;
//	n2->addEdge(ed1);
//	std::cout << "Second edge added" << std::endl;

//	std::cout << n1->toString() << " " << n2->toString() << std::endl;
}

void createEdges( std::vector<Node*>* nodes ) {

}

int main( int argc, const char* argv[] ) {
	std::vector<Node*>* nodes = new std::vector<Node*>();

	//Values for the size of the graph (square)
	int x = 5;
	int y = 7;

	//Below here the nodes are being generated
	Node* node = 0;
	for ( int i = 0; i < x; i++ ) {
		for ( int j = 0; j < y; j++ ) {
			node = new Node(i, j);
			nodes->push_back(node);
		}
	}

	//Below here the edges of the nodes are being generated
	int max = nodes->size();
	for ( int i = 0; i < max; i++ ) {
		Node* node = nodes->at(i);

		if ( ( i + 5 ) < max ) {
			createEdge( node, nodes->at(i+5), 10);
		}
		if( ( i + 1 ) < max ) {
			createEdge( node, nodes->at(i+1), 10);
		}

		if( ( i - 5 ) >= 0 ) {
			createEdge( node, nodes->at(i-5), 10);
		}
		if( ( i - 1 ) >= 0 ) {
			createEdge( node, nodes->at(i-1), 10);
		}
	}

	std::cout << nodes->at(7)->toString() << std::endl;

	return 0;
}

