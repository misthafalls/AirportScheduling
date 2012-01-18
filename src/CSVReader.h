// Teun van Dingenen
// -----------------------------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <vector>
#include "Plane.h"

#ifndef CSVREADER_H_
#define CSVREADER_H_

class CSVReader {

const static size_t BUFFERSIZE = 1024;
const static size_t ARGUMENT_COUNT = 5;

public:

    CSVReader( ){ };

    bool readFile( const char* file, std::vector< Plane* >& planes,
                    unsigned int max_planes );

private:
    bool processLine( const std::string& line, std::vector< Plane* >& planes );

private: //member values

};

#endif // CSVREADER_H_
