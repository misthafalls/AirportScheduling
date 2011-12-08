/*
* Combinator.cpp
*
* Created on: Dec 7, 2011
*/

#include "Combinator.h"

Genome* Combinator::combinate(Genome *x, Genome *y) {
	int size = x.m_size;
	Genome *z = new Genome(size);
	for(int i = 0; i < size; i++) {
		if(i % 2 == 0) {
			//add gene from x to z at index i
			z->set_gene(i, x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
		} else {
			//add gene from y to z at index i
			z->set_gene(i, y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
		}
	}

	return z;
}
