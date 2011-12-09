/*
 * Selector.h
 *
 *  Created on: Dec 7, 2011
 *      Author: christian
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <cstring>
#include <vector>

class Genome;

class Selector {
public:
	Selector(size_t c, size_t d) 
        : 
        m_nr_combine(c),
		m_nr_die(d) {};

	virtual ~Selector();

	bool getSelected(std::vector<Genome*>& genomes);

    size_t get_to_combine_index( size_t t ) { return m_to_combine[ t ]; }
private:
    size_t m_nr_combine;
    size_t m_nr_die;

	std::vector<size_t> m_to_combine;
};

#endif /* SELECTOR_H_ */
