/*
 * Node.h
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>

class Edge;

class Node {
public:
	Node(int x, int y);
	virtual ~Node();

	void addEdge( Edge* edge );
	std::vector<Edge*>* getEdges( );

	//toString to print information about this node and its edges
	std::string toString( bool stop = true);

	int x;
	int y;
	Node* parent; //TODO: Temporary for pathfinding, this needs brushing up later!

private:
	std::vector<Edge*>* edges; //The connections to other nodes
};

#endif /* NODE_H_ */
