/*
* Combinator.cpp
*
* Created on: Dec 7, 2011
*/

#include "Combinator.h"

Genome* 
SimpleCombinator::combine(Genome *x, Genome *y) {
	int size = x->get_size( );
	Genome *z = new Genome();
	for(int i = 0; i < size; i++) {
		if(i % 2 == 0) {
			//add gene from x to z at index i
			z->add_gene( x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
		} else {
			//add gene from y to z at index i
			z->add_gene( y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
		}
	}
	return z;
}
