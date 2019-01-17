#ifndef simulation_h
#define simulation_h
#include "libraries.h"
#include "Lattice.h"
#include "Metropolis.h"
#include "Observable.h"
#include "DataManager.h"

class Simulation
{
	protected:
		std::string relPath = "../../data_files/";
		long N_conf;
		long N_cor;
		std::map<std::string, Observable> obs;
		//make these shared_ptr's???
		Lattice lat;
		Metropolis met;
		DataManager data;
	public:	
		double update_progress(double progress, double progress_rate, int bar_width);
		Simulation(long ensSize, long corSize, long sweepSize, long n_2, long n_fix, long time, double k_2) : lat(n_2, n_fix, time, k_2), met(lat, sweepSize) {N_conf = ensSize; N_cor = corSize;}	
		Simulation() : Simulation(0, 0, 0, 4, 4, 2, 0){}
		void params(long ensSize, long corSize, long sweepSize, long n_2, long n_fix, long time, double k_2){lat.N_2() = n_2; lat.N_fix() = n_fix; lat.TIME() = time; lat.K_2() = k_2; met.sweepSize = sweepSize; N_conf = ensSize; N_cor = corSize;}
		void start();
		//make checkpoint function at some point???
		
};
#endif
