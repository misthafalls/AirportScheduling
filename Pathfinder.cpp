/*
 * Pathfinder.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#include "Pathfinder.h"
#include "Graph/Node.h"
#include "Graph/Edge.h"

#include <map>
typedef std::pair<Node*, int> mnode;

#include <iostream>
#include <cstdlib>

Pathfinder::Pathfinder( std::vector<Node*>* graph ) {
	this->graph = graph;
}

Pathfinder::~Pathfinder() {
}

//Manhattan Method for a heuristic
int Pathfinder::calculateHeuristic( Node* a, Node* b) {
	return 10 * ( abs( a->x - b->x ) + abs( a->y - b->y ) );
}

std::stack<Node*>* Pathfinder::getPath ( Node* start, Node* end ) {
	std::map<Node*, int>* open = new std::map<Node*, int>();
	std::map<Node*, int>* closed = new std::map<Node*, int>();
	open->insert( mnode( start, 0 ) );

	Node* node = 0;
	while( ! open->empty() ) {
		int f = -1;
		//Search for lowest F node in open list
		for ( std::map<Node*, int>::iterator it = open->begin(); it != open->end(); ++it ) {
			if ( f == -1 || it->second < f ) {
//				std::cout << f << " -> " << it->second << " " << it->first->toString(false) << std::endl;
				f = it->second;
				node = it->first;
			}
		}
		std::cout << "Checked " << node->toString(false) << std::endl;
		//break;

		if( node == end ) {
			break;
		}

		open->erase( node );
		closed->insert( mnode(node, 0) );

		std::vector<Edge*>* edges = node->getEdges();

//		std::cout << "Parent " << node->toString(false) << std::endl;

		for ( std::vector<Edge*>::iterator eds = edges->begin(); eds != edges->end(); ++eds ) {
			Node* nNode = (*eds)->getNode();
			if ( closed->find( nNode ) == closed->end() ) {
//				std::cout << "- Add " << nNode->toString(false) << std::endl;
				//If not on the closed list, then it can be on the open list or not.
				//So we need to recalculate it again and if the path is quicker edit it.
				int g = (*eds)->getWeight();
				int h = calculateHeuristic( nNode, end );
				int f = g + h;

				//TODO: Not efficient enough, instead of remembering F we also need to remember H!
				std::map<Node*, int>::iterator itFound = open->find( nNode );

				//Only insert if not found in open list and the old F value is higher!
				if ( ( itFound != open->end() && (*itFound).second > f ) || itFound == open->end() ) {
					open->erase(nNode);
					open->insert( mnode ( (*eds)->getNode(), f ) );

					nNode->parent = node;
					//std::cout << "Parent " << node->toString(false) << " -> " << nNode->toString(false) << " :: " << f << "=" << g << "+" << h << std::endl;
				}
			}
		}
	}

	std::stack<Node*>* path = new std::stack<Node*>();
	if ( node == end) {
		path->push( node );

		while( node != start ) {
			node = node->parent;
			path->push( node );
		}
	}

	return path;
}
