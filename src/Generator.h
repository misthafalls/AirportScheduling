// Teun van Dingenen, 6 December 2011
//------------------------------------------------------------------------------

#ifndef GENERATOR_H_
#define GENERATOR_H_

const static size_t POPULATION_SIZE = 50;

class Generator {
    
    public:
        Generator( ) { }

        bool init( Genome*& population, size_t population_size,
            std::vector< Plane* >& planes ){ return true; }

    private:
        
};

#endif // GENERATOR_H_
