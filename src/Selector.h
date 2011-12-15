/*
 * Selector.h
 *
 *  Created on: Dec 7, 2011
 *      Author: christian / teun
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <vector>

class Genome;

class Selector {
public:
	Selector(unsigned int c, unsigned int d) 
        : 
        m_nr_combine(c),
		m_nr_die(d) {};

	virtual bool select(std::vector<Genome*>& genomes, 
                            std::vector< Genome* >& selected ) = 0;
protected:
    unsigned int m_nr_combine;
    unsigned int m_nr_die;
};

class RandomSelector : public Selector {
public:
    //take parent Constructor

	bool select(std::vector<Genome*>& population, 
                            std::vector< Genome* >& selected ); 
};
#endif /* SELECTOR_H_ */
