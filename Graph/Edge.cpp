/*
 * Edge.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: christian
 */

#include "Edge.h"
#include "Node.h"

#include <sstream>

Edge::Edge( int weight, Node* node) {
	this->weight = weight;
	this->node = node;
}

Edge::~Edge() {
}

std::string Edge::toString() {
	std::stringstream weight;
	weight << this->weight;
	return "Edge to " + this->node->toString(false) + " has weight " + weight.str();
}
