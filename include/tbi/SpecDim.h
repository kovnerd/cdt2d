#ifndef specdim_h
#define specdim_h
#include "libraries.h"

class SpecDim
{
	private:
		double DIFF_CONST;
		long sigma_max;
		std::vector<double> current_return_probs;
		std::vector<std::vector<double> > return_probs;//may not need if printing works correctly
			
		//or change to something else??
		std::unique_ptr<gsl_rng, void(*)(gsl_rng*)> r;
		std::map<long, double> diffKernel;//sigma
		std::map<long, double> nextKernel;//sigma + 1
		std::deque<long> labels;//labels accumulated over sigma time steps
		Lattice* refLat;
	public:
		SpecDim(long sigma_max, Lattice* lat);
		void prepK(long label_0);
		//haven't changed the following yet:
		void kWalk(long, long);
		void norm_check(long);
		double return_prob(long);
};
#endif
