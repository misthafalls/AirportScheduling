/*
 * Edge.h
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <string>

class Node;

class Edge {
public:
	Edge(int weight, Node* node);
	virtual ~Edge();

	//toString to print information about this edge
	std::string toString();

private:
	int weight;
	Node* node;
};

#endif /* EDGE_H_ */
