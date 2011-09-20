/*
 * Node.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#include "Node.h"
#include "Edge.h"

#include <sstream>

Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
	this->edges = new std::vector<Edge*>();
}

Node::~Node() {
	for ( std::vector<Edge*>::iterator edge = this->edges->begin(); edge != this->edges->end(); ++edge ) {
		delete (*edge);
	}
	delete edges;
}

void Node::addEdge(Edge* edge) {
	this->edges->push_back(edge);
}

std::vector<Edge*>* Node::getEdges() {
	return this->edges;
}

std::string Node::toString( bool stop ) {
	std::stringstream x;
	x << this->x;
	std::stringstream y;
	y << this->y;

	std::string str = "Node with coordinate (" + x.str() + ", " + y.str() + ")";

	if(stop) {
		str += "\n";
		for ( std::vector<Edge*>::iterator edge = this->edges->begin(); edge != this->edges->end(); ++edge ) {
			str += "\t" + (*edge)->toString() + "\n";
		}
	}
	return str;
}


