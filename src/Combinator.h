// Dustin Balentina, 7 December 2011
//------------------------------------------------------------------------------

#ifndef COMBINATOR_H_
#define COMBINATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "Genome.h"
#include "Plane.h"
#include "Time.h"

class Combinator {
private:
	bool contains(Genome *g, Plane *p);
public:
	virtual Genome* combine(Genome *x, Genome *y) = 0;

};

class SimpleCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};

class RandomCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};

class AverageCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};

class BlockCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};

class TimeCombinator : public Combinator {
public:
    Genome* combine(Genome *x, Genome *y );

};
#endif
