// Teun van Dingenen
// -----------------------------------------------------------------------------
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

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
    if( !line.compare( 0, 1, "#" ) ) return true;

    std::auto_ptr< Plane > p ( new Plane( ) );
    size_t cpos = 0;
    std::string name;
    int fooInt;
    Time time;    
    for( unsigned int t = 0; t < ARGUMENT_COUNT; t++ ) {
        int npos = line.find( ',', cpos );
        if( npos == -1 ) return true;
        int size = npos - cpos;
        std::string s;
        Plane::PlaneType planeType;
#if PRINT_DEBUG
        std::cout << "Substring = " << line.substr( cpos, size ) << std::endl <<
            "    Between: " << cpos << " and " << npos << std::endl;
#endif
        switch ( t ) {
            case 0: 
                name = line.substr( cpos, size ); 
                p->setName( name );
                break;
            case 1: 
                s = line.substr( cpos, size );
                time = Time( s );
                p->setArrivalTime( time );
                break;
            case 2:
                time = Time( line.substr( cpos, size ) );
                p->setScheduledTime( time );
                break;
            case 3:
                s = line.substr( cpos, size );
                if ( !s.compare( "CARGO" ) ) 
                        planeType = Plane::CARGO;
                else if ( !s.compare( "PASSENGER" ) )  
                        planeType = Plane::PASSENGER;
                else std::cout << "ERROR: type not found in: " << 
                        s << std::endl;
                p->setPlaneType( planeType );
                break;
            case 4:
                fooInt = atoi( line.substr( cpos, size ).c_str( ) );
                p->setFuel( fooInt );
                break;
            case 5:
                fooInt = atoi( line.substr( cpos, size ).c_str( ) );
                p->setFuelUsage( fooInt );
                break;
            case 6:
                fooInt = atoi( line.substr( cpos, size ).c_str( ) );
                p->setLandingDuration( fooInt );
            default:
#if PRINT_DEBUG
                std::cout << "Argument count out of bounds" << std::endl;
#endif
                break;
        }
        cpos = npos + 1;
    }
    mModel->addPlane( p.release( ) );
    return true;
}
