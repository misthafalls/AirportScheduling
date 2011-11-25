/*
 * View.h
 *
 *  Created on: Oct 4, 2011
 *      Author: SANDER
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "../Model/Model.h"

#include <vector>

class View
{
public:
    class Stats {
        public:
            Stats( )
                :
                fuel_usage_total( 0 ), 
                number_planes_delay( 0 ),
                total_minutes_delay( 0 ),
                number_planes_early( 0 ),
                total_minutes_early( 0 ),
                number_crashes( 0 ),
                number_on_time( 0 )
            { }

            int fuel_usage_total; 
            int number_planes_delay;
            int total_minutes_delay;
            int number_planes_early;
            int total_minutes_early;
            int number_crashes;
            int number_on_time;
    };

	View(Model * model);
	virtual ~View();

	bool setup();

	void print();

    void printPlaneInfo( Plane* p, Stats& stats );
	void printScheduleStatistics(std::vector<Plane*> & planes);

protected:
	Model * model;

};

#endif /* VIEW_H_ */
