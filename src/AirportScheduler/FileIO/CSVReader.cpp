// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define PRINT_DEBUG 0


// -----------------------------------------------------------------------------

bool CSVReader::readFile( const char* file ){
    char buffer[ BUFFERSIZE ];
    std::ifstream inFile;

    inFile.open( file, std::ios::binary );
    if( !inFile.good( ) ) {
#if PRINT_DEBUG
        std::cout << "Error opening file: "<< file << std::endl;
#endif
        return false;
    }
    while( !inFile.eof( ) ) {
        inFile.getline( buffer, BUFFERSIZE ); 
        std::string s ( buffer );
        if( !processLine( s ) ) return false;;
    }
    return true;
}

// -----------------------------------------------------------------------------

bool
CSVReader::processLine( const std::string& line ){
#if PRINT_DEBUG
    std::cout << line << std::endl;
#endif
    size_t cpos = 0;
    std::string name;
    int arrivalTime = 0;
    for( unsigned int t = 0; t < ARGUMENT_COUNT; t++ ) {
        int npos = line.find( ',', cpos );
        int size = npos - cpos;
        std::string s;
#if PRINT_DEBUG
        std::cout << "Substring = " << line.substr( cpos, size ) << std::endl <<
            "    Between: " << cpos << " and " << npos << std::endl;
#endif
        switch ( t ) {
            case 0: 
                name = line.substr( cpos, size ); 
                break;
            case 1: 
                arrivalTime = atoi( line.substr( cpos, size ).c_str( ) );
                break;
            case 2:
                break;
            case 3:
/*                s = line.substr( cpos, size );
                if ( !s.compare( "CARGO" ) ) p.type = CARGO;
                else if ( !s.compare( "PASSENGER" ) ) 
                        p.type = PASSENGER;
                else std::cout << "ERROR: type not found in: " << 
                        s << std::endl;
                break;
*/            case 4:
//                p.fuel_remaining = atoi( line.substr( cpos, size ).c_str( ) );
                break;
            case 5:
//                p.fuel_usage = atoi( line.substr( cpos, size ).c_str( ) );
                break;
            default:
#if PRINT_DEBUG
                std::cout << "Argument count out of bounds" << std::endl;
#endif
                break;
        }
        cpos = npos + 1;
    }
    mModel->addPlane( name, arrivalTime );
    return true;
}
