#include "FitnessFunction.h"
#include "Genome.h"
#include "GeneSorter.h"

FitnessFunction::FitnessFunction() {}

FitnessFunction::~FitnessFunction() {}

int FitnessFunction::calculate_fitness(std::vector<Genome*>& population,
										int landing_strips,
										int landing_duration) {
	std::vector<Genome::Gene*> genes;
	Genome * genome;

	int sum_fitness = 0;

	for(unsigned int i = 0; i < population.size( ); i++) {
		genome = population[i];

		GeneSorter::sort((*genome->get_genes()), genes);

		int sum_crashes = 0;
		int sum_planes_delayed = 0;

		int same_landingtime_planes = 0;
		std::vector<Time> previous_times;
		int clear_previous_time = -1;

		for(std::vector<Genome::Gene*>::const_iterator gene = genes.begin();
			gene != genes.end(); ++gene) {
			const Plane* plane = (*gene)->getPlane();
			Time current_time = (*gene)->getTime();
			current_time.subMinute(landing_duration);

			if (plane->getDeadlineTime() > current_time) {
				++sum_crashes;
			} else {
				//BEGIN_CRASH
				//The following checks if the plane will crash and burn!
				previous_times.push_back((*gene)->getTime());
				for(unsigned int i = 0; i < previous_times.size(); i++) {
					if(current_time < previous_times[i]) {
						if(same_landingtime_planes == landing_strips) {
							++sum_crashes;
							break; //Stop the loop, because plane crashed!
						}
						++same_landingtime_planes;
					} else {
						clear_previous_time = i;
					}
				}
				//END_CRASH

				if(clear_previous_time != -1)
					previous_times.erase(previous_times.begin(), previous_times.begin()+clear_previous_time);

				same_landingtime_planes = 0;
				if (plane->getScheduledTime() < current_time)
					++sum_planes_delayed;
			}
		}

		int genome_fitness = sum_crashes * CONST_PLANES_CRASHED +
							 sum_planes_delayed * CONST_PLANES_DELAYED;

		genome->set_fitness(genome_fitness);

		sum_fitness += genome_fitness;
	}
	return sum_fitness;
}
