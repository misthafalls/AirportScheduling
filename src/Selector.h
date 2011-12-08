/*
 * Selector.h
 *
 *  Created on: Dec 7, 2011
 *      Author: christian
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <cstring>

class Genome;

class Selector {
public:
	Selector(int c, int d) : combine(c),
							 die(d) {};
	virtual ~Selector();

	bool getSelected(Genome ** genomes, std::size_t m_size);
private:
	int combine;
	int die;
};

#endif /* SELECTOR_H_ */
