/*
 * FIFOAlgorithm.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: Teun
 */

#define PRINT_DEBUG 1

#include "Bruteforce.h"

#include "../SortAlgorithms/BubbleSort.h"
#include "../Logger.h"

#if PRINT_DEBUG
#include <iostream>
#endif

Bruteforce::Bruteforce( ) : Algorithm( ) { }
Bruteforce::~Bruteforce( ) { }

#if PRINT_DEBUG
void inline print_order( std::vector< Plane* > planes ) {
    std::vector< Plane* >::iterator it;
    for( it = planes.begin( ); it != planes.end( ); it++ ) {
        std::cout << (*it)->getName( ) << ": " << 
            (*it)->getArrivalTime( ).getFormattedTime( ) << std::endl;
    }
}
#endif

std::vector<Plane*>& Bruteforce::schedule( std::vector<Plane*> &planes ) {
	BubbleSort * arrivalTimeSort = new BubbleSort();

	planes = arrivalTimeSort->scheduleByArrivalTimeAscending( planes );

    rescheduleEqualArrivals( planes );

#if PRINT_DEBUG
    std::cout << "Initial plane list" << std::endl;
    print_order( planes );
#endif

    //First plane can land at it's earliest convience
	Time lastPlane = planes[ 0 ]->getArrivalTime( );
    planes[ 0 ]->setFinalLandingTime( lastPlane );

    lastPlane = planes[ 0 ]->getFinalLandingTime( );
    unsigned int lastDuration = planes[ 0 ]->getLandingDuration( );

#if PRINT_DEBUG
    std::cout << "First Plane: " << planes[ 0 ]->getName( ) 
        << " scheduled to: " << lastPlane.getFormattedTime( )
        << std::endl << "Starting loop with: "
        << std::endl << "  lastPlane (Time): " << lastPlane.getFormattedTime( )
        << std::endl << "  lastDuration (int): " << lastDuration << std::endl;
#endif

    std::vector< Plane* >::iterator plane = planes.begin( ) + 1;
    while( plane != planes.end( ) ) {
        Time earliestLandingTime = lastPlane;
        earliestLandingTime.addMinute( lastDuration );

        Time currentPlaneArrival = (*plane)->getArrivalTime( );
        if( (*plane)->hasCrashed( ) ) {
            plane++;
            continue;
        }

        if( (*plane)->getDeadlineTime( ) < earliestLandingTime ) {
            if( plane != planes.begin( ) ) {
                std::vector< Plane* >::iterator new_spot = 
                    findSafeTime( planes, plane );
                if( (*plane)->hasCrashed( ) || new_spot == planes.end( ) ) {
                    Logger::getInstance( )->log( 
                        "Couldn't find safe landing time for " + 
                        ( *plane )->getName( ) + ". Plane is going down." );
                    ( *plane )->setCrashed( true );
                    std::vector< Plane* >::iterator foo = plane;
                    foo--;
                    lastPlane = (*foo)->getFinalLandingTime( );
                    lastDuration = (*foo)->getLandingDuration( );
                    plane++; 
                } else {
                    plane = new_spot;
                    std::vector< Plane* >::iterator foo = plane;
                    foo--;
                    lastPlane = (*foo)->getFinalLandingTime( );
                    lastDuration = (*foo)->getLandingDuration( );
                }
#if PRINT_DEBUG
            std::cout << "Plane list after deadline search" << std::endl;
            print_order( planes );
#endif
            continue;
            } else {
                Logger::getInstance( )->log (
                    "First plane: " + ( *plane )->getName( ) + 
                    " can not make deadline. Plane is going to crash" );
            } 
        } 
        if( plane != planes.begin( ) ) {
            std::vector< Plane* >::iterator new_spot = 
                    rescheduleForPlaneType( planes, plane, earliestLandingTime);
            if( new_spot != planes.end( ) &&
                    new_spot != plane ) {
                plane = new_spot;
                std::vector< Plane* >::iterator foo = plane;
                foo--;
                lastPlane = (*foo)->getFinalLandingTime( );
                lastDuration = (*foo)->getLandingDuration( );
#if PRINT_DEBUG
            std::cout << "plane variable is: " << (*plane)->getName( ) <<
                std::endl;
            std::cout << "Plane list after planetype search" << std::endl;
            print_order( planes );
#endif
                continue;
            }
        }
        if( earliestLandingTime < currentPlaneArrival ) {
            (*plane)->setFinalLandingTime( currentPlaneArrival );
        } else {
            (*plane)->setFinalLandingTime( earliestLandingTime );
        }

#if PRINT_DEBUG
        std::cout << "Plane: " << (*plane)->getName( ) << " set to: " << 
            (*plane)->getFinalLandingTime( ).getFormattedTime( ) 
                << std::endl;
#endif

        lastPlane = (*plane)->getFinalLandingTime( );
        lastDuration = (*plane)->getLandingDuration( );
#if PRINT_DEBUG
        std::cout << "Going to next loop with following values: " <<
        std::endl << "  lastPlane (Time) " << lastPlane.getFormattedTime( ) <<
        std::endl << "  lastDuration (int) " << lastDuration << std::endl;
#endif
        plane++;
	}
	return planes;
}

std::vector< Plane* >::iterator 
Bruteforce::findSafeTime( std::vector<Plane*> &planes,
                             const std::vector<Plane*>::iterator plane ) const{
    Time deadline = (*plane)->getDeadlineTime( );
    std::vector<Plane*>::iterator possibleSpace = plane - 1;
#if PRINT_DEBUG
        std::cout << "Deadline problem for: " << (*plane)->getName( ) <<
        ". Deadline is: " <<
            deadline.getFormattedTime( ) << std::endl;
#endif
    while( possibleSpace >= planes.begin( ) ) {
        Time nice_time = ( *possibleSpace )->getFinalLandingTime( ); 
        if( nice_time < deadline ) {
#if PRINT_DEBUG
        std::cout << nice_time.getFormattedTime( ) << 
            " is a possible time" << std::endl;
#endif
            Time other_time = nice_time;
            Plane* foo = *plane;
            other_time.addMinute( foo->getLandingDuration( ) );
            if( other_time > (*possibleSpace)->getDeadlineTime( ) ) {
#if PRINT_DEBUG
                std::cout << "A plane is going to crash:" << std::endl <<
                    (*possibleSpace)->getName( ) << 
                    " with deadline: " << 
                    (*possibleSpace)->getDeadlineTime( ).getFormattedTime( ) 
                    << std::endl << "or" << std::endl <<
                    foo->getName( ) << 
                    " with deadline: " << 
                    foo->getDeadlineTime( ).getFormattedTime( ) <<
                    std::endl << "both must land on: " <<
                    nice_time.getFormattedTime( ) << std::endl;
#endif
                //Conflict somebody has to crash
                if( foo->getPlaneType( ) < (*possibleSpace)->getPlaneType( ) ) {
                    (*possibleSpace)->setCrashed( true );
                    planes.erase( plane );
                    planes.insert( possibleSpace, foo );
                    return planes.end( );
                } else {
                    foo->setCrashed( true );
                    return planes.end( );
                }
            }
            planes.erase( plane );
            planes.insert( possibleSpace, foo );
            return possibleSpace;
         } else {
            --possibleSpace;
         }
    }
    return planes.end( );
}

size_t
Bruteforce::rescheduleEqualArrivals( std::vector< Plane* >& planes ) const {
    size_t swapped = 0;
    std::vector< Plane* >::iterator foo = planes.begin( );
    std::vector< Plane* >::iterator bar = foo + 1;
    Time fooTime; Time barTime;
    while( bar != planes.end( ) ) {
        fooTime = ( *foo )->getArrivalTime( );
        barTime = ( *bar )->getArrivalTime( ); 
        if( fooTime == barTime ) {
            fooTime = ( *foo )->getScheduledTime( );
            barTime = ( *bar )->getScheduledTime( ); 
            if( fooTime > barTime ){
                Plane* p = *bar;
                planes.erase( bar );
                planes.insert( foo, p );
                foo = planes.begin( );
                bar = foo + 1;
                swapped++;
                continue;
            }
        }
        foo++;
        bar++;
    }
    return swapped;
}

std::vector<Plane*>::iterator
Bruteforce::rescheduleForPlaneType( std::vector<Plane*>& planes,
                    const std::vector< Plane* >::iterator plane,
                    const Time expectedLandingTime ) const {
    std::vector< Plane* >::iterator possibleSpace = plane - 1;
    std::vector< Plane* >::iterator goodSpace = plane;
    Time realLandingTime = expectedLandingTime;
    realLandingTime.addMinute( (*plane)->getLandingDuration( ) );
    while( possibleSpace > planes.begin( ) ) {
        if( ( *possibleSpace )->getPlaneType( ) > 
                    ( *plane )->getPlaneType( ) &&
            ( *possibleSpace )->getFinalLandingTime( ) >
                    ( *plane )->getArrivalTime( ) &&
            ( *possibleSpace )->getDeadlineTime( ) > 
                    realLandingTime ) {
#if PRINT_DEBUG
            std::cout << "Plane: " << ( *plane )->getName( ) <<
                " has priority over: " << ( *possibleSpace )->getName( ) <<
                " by PlaneType." << std::endl;
#endif
            goodSpace = possibleSpace;
            possibleSpace--;
        } else if ( goodSpace != plane ) {
            Plane* foo = *plane;
#if PRINT_DEBUG
            std::cout << "Inserted: " << foo->getName( ) <<
                " on position of: " << (*goodSpace)->getName( ) << std::endl;
#endif
            planes.erase( plane );
            planes.insert( goodSpace, foo );
            return goodSpace;
        } else {
            return planes.end( );
        }
    }
    return planes.end( );
}
