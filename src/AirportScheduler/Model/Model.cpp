/*
 * Model.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#include "Model.h"
#include <memory>

Model::Model() {

}

Model::~Model() {

}

bool Model::setup() {
	return true;
}

bool Model::addPlane( std::string name, int arrivalTime ) {
    std::auto_ptr< Plane > newPlane ( new Plane( name, arrivalTime ) );
    if( !newPlane.get( ) ) return false;// No plane created.. error!
    planes[ name ] = newPlane.release( );
    return true;
}
