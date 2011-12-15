// Dustin Balentina, 7 December 2011
//------------------------------------------------------------------------------

#ifndef COMBINATOR_H_
#define COMBINATOR_H_

#include "Genome.h"
#include "Plane.h"
#include "Time.h"

class Combinator {
public:
	virtual Genome* combine(Genome *x, Genome *y) = 0;

};

class SimpleCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};
#endif
