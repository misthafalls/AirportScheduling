// Teun van Dingenen
// -----------------------------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include "../Model/Model.h"

#ifndef CSVREADER_H_
#define CSVREADER_H_

class CSVReader {

const static size_t BUFFERSIZE = 1024;
const static size_t ARGUMENT_COUNT = 5;

public:

    CSVReader( ){ };

    CSVReader( Model* model )
        :
        mModel( model )
    { };

    bool readFile( const char* file );

private:
    bool processLine( const std::string& line );

private: //member values
    Model* mModel;
};

#endif // CSVREADER_H_
