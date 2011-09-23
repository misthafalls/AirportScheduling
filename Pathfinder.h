/*
 * Pathfinder.h
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <stack>
#include <vector>

class Node;

class Pathfinder {
public:
	Pathfinder( std::vector<Node*>* graph );
	virtual ~Pathfinder();

	//We have a heuristic calculator which returns absolute values
	int calculateHeuristic( Node* start, Node* end );

	//The algorithm doing the searching and returning a stack with the pad
	std::stack<Node*>* getPath(Node* start, Node* end);

private:
	//Pathfinder knows the graph
	std::vector<Node*>* graph;
};

#endif /* PATHFINDER_H_ */
