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

Genome*
RandomCombinator::combine(Genome *x, Genome *y) {
	srand ( time(NULL) );

	int size = x->get_size( );
	Genome *z = new Genome();

	//double chanceFactor = 0.75;
	for(int i = 0; i < size; i++) {
		if((((double) rand()) / RAND_MAX+1) == 0) {
		//if((((double) rand()) / RAND_MAX+1) < chanceFactor) {
			z->add_gene( x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
		} else {
			z->add_gene( y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
		}
	}

	return z;
}

Genome*
AverageCombinator::combine(Genome *x, Genome *y) {
	srand ( time(NULL) );

	int size = x->get_size( );
	Genome *z = new Genome();

	double chanceFactor = 0.5;
	for(int i = 0; i < size; i++) {
		double chance = (((double) rand()) / RAND_MAX+1);
		if(chance < chanceFactor) {
			double totalTime = x->get_gene(i)->getTime().getTimeInMinutes() + y->get_gene(i)->getTime().getTimeInMinutes();

			Time t;
			t.addMinute(floor((totalTime / 2) + 0.5));
			z->add_gene(x->get_gene(i)->getPlane(), t);
		} else if(chance < 0.75) {
			z->add_gene( x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
		} else {
			z->add_gene( y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
		}
	}

	return z;
}

Genome*
BlockCombinator::combine(Genome *x, Genome *y) {
	srand ( time(NULL) );

	int blockSize = rand() % x->get_size();
	int size = x->get_size( );
	Genome *z = new Genome();

	for(int i = 0; i < blockSize; i++) {
		z->add_gene( x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
	}
	for(int i = blockSize; i < size; i++) {
		z->add_gene( y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
	}

	return z;
}

Genome*
TimeCombinator::combine(Genome *x, Genome *y) {
	srand ( time(NULL) );

	int size = x->get_size( );
	Genome *z = new Genome();

	for(int i = 0; i < size; i++) {
		int dX = x->get_gene(i)->getTime().getTimeInMinutes() - x->get_gene(i)->getPlane()->getScheduledTime().getTimeInMinutes();
		int dY = x->get_gene(i)->getTime().getTimeInMinutes() - x->get_gene(i)->getPlane()->getScheduledTime().getTimeInMinutes();

		if(dX < dY) {
			z->add_gene( x->get_gene(i)->getPlane(), x->get_gene(i)->getTime());
		} else {
			z->add_gene( y->get_gene(i)->getPlane(), y->get_gene(i)->getTime());
		}
	}

	return z;
}
