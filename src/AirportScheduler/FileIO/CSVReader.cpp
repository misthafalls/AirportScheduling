// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define PRINT_DEBUG 1


// -----------------------------------------------------------------------------

bool
CSVReader::readFile( const char* file ){
    char buffer[ BUFFERSIZE ];
    std::ifstream infile;

    infile.open( file, std::ios::binary );
    if( !infile.good( ) ) {
#if PRINT_DEBUG
        std::cout << "Error opening file: "<< file << std::endl;
#endif
        return false;
    }
    while( !infile.eof( ) ) {
        infile.getline( buffer, BUFFERSIZE ); 
        std::string s ( buffer );
        if( !processLine( s ) ) return false;;
    }
    return true;
}

// -----------------------------------------------------------------------------

bool
CSVReader::processLine( const std::string& line ){
    std::cout << line << std::endl;
    size_t cpos = 0;
    std::string name;
    int arrivalTime;
    for( int t = 0; t < ARGUMENT_COUNT; t++ ) {
        int npos = line.find( ',', cpos );
        int size = npos - cpos;
        std::string s;
        std::cout << "Substring = " << line.substr( cpos, size ) << std::endl <<
            "    Between: " << cpos << " and " << npos << std::endl;
        switch ( t ) {
            case 0: 
                name = line.substr( cpos, size ); 
                break;
            case 1: 
                arrivalTime = atoi( line.substr( cpos, size ).c_str( ) );
                break;
            case 2:
//                p.expected_time = line.substr( cpos, size );
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
                std::cout << "Argument count out of bounds" << std::endl;
                break;
        }
        cpos = npos + 1;
    }
    mModel->addPlane( name, arrivalTime );
    return true;
}
