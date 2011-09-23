/*
 * main.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */
#include "Graph/Node.h"
#include "Graph/Edge.h"

#include "Pathfinder.h"
#include <iostream>

void createEdge ( Node* n1, Node* n2, int weight ) {
	if ( n2->x != 3 || ( n2->y == 4 ) ) {
		Edge* ed2 = new Edge(weight, n2);
		n1->addEdge(ed2);
	}
}

std::vector<Node*>* createGraph( int width, int length) {
	std::vector<Node*>* nodes = new std::vector<Node*>();

	//Below here the nodes are being generated
	Node* node = 0;
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < length; j++ ) {
			node = new Node(i, j);
			nodes->push_back(node);
		}
	}

	//Below here the edges of the nodes are being generated
	int max = nodes->size();
	for ( int i = 0; i < max; i++ ) {
		Node* node = nodes->at(i);

		int bottom	= i + 1;
		int top		= i - 1;

		int right	= i + length;
		int left	= i - length;

		//Left
		if ( left >= 0 ) { createEdge( node, nodes->at(left), 10 ); }
		//Right
		if ( right < max ) { createEdge( node, nodes->at(right), 10 ); }

		//Bottom
		if ( bottom < max && (bottom % length) != 0 ) { createEdge( node, nodes->at(bottom), 10); }
		//Top
		if ( top >= 0 && (i % length) != 0 ) { createEdge( node, nodes->at(top), 10); }




//		//Right-bottom
//		if ( (i + length + 1) < max && (i + 1) % length != 0) { createEdge( node, nodes->at(i+length+1), 14); }
//		//Right-top
//		if ( (i + length - 1) < max && i % length != 0 ) { createEdge( node, nodes->at(i+length-1), 14); }
//
//
//		//Left-top
//		if ( (i - length - 1) >= 0 && (i -length - 1) % length != 0 ) { createEdge( node, nodes->at(i-length-1), 14); }
//		//Left-bottom
//		if ( (i - length + 1) >= 0 && (i - length + 1) % length != 0 ) { createEdge( node, nodes->at(i-length+1), 14); }

	}

	return nodes;
}

int main( int argc, const char* argv[] ) {
	std::vector<Node*>* nodes = createGraph(7, 5);
	Node* start = nodes->at(7);

	std::cout << start->toString() << std::endl;

	Node* end = nodes->at(27);

	Pathfinder* find = new Pathfinder(nodes);
	std::stack<Node*>* path = find->getPath(start, end);

	std::cout << "\nPath: " << std::endl;
	while ( !path->empty() ) {
		std::cout << path->top()->toString(false) << std::endl;
		path->pop();
	}

	return 0;
}

