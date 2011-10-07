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
const static size_t ARGUMENT_COUNT = 6;

//Temporary test structures : move to correct place in source

enum PlaneType {
    CARGO,
    PASSENGER
};

public:
// TODO: implement when Plane struct is finished
//    CSVReader( std::map< std::string, Plane > );
    CSVReader( ){ };

    CSVReader( Model* model )
        :
        mModel( model )
    { };

    bool readFile( const char* file ) const;

    bool setModel( Model* model ) { mModel = model; return true; };

private:
    bool processLine( const std::string& line ) const;

private: //member values
    Model* mModel;
};

#endif // CSVREADER_H_
