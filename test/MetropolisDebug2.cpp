#include "libraries.h"
#include "Lattice.h"
#include "Metropolis2.h"
#include "Observable.h"
#include "DataManager.h"
#include "Simulation.h"


int main(void)
{
	long N_2 = 4096;
	long N_fix = N_2;
	long TIME = 32;
	long sweepSize = N_2;
	double kmin = 0.65;
	double kmax = 0.75;
	int numPoints = 20;
	double kstep = (kmax - kmin)/numPoints;
	int num_sweeps = 1e4;
	int num_therm = num_sweeps/10;
	int num_cor = 1;
	int num_print = num_sweeps/10;
	Lattice lat(N_2, N_fix, TIME, kmin);
	Metropolis2 met(lat, sweepSize);	
	Simulation sim(num_sweeps, num_cor, sweepSize, N_2, N_fix, TIME, kmin);
	
	met.epsilon = 0;
	std::string relPath = "../data_files/";
	std::string ratioName = "avNOverN_i";
	std::string flucName = "avdeltaNOverN";
	std::string ratioFullName = relPath + ratioName + "_" + "test2" + ".txt";
	std::string flucFullName = relPath + flucName + "_" + "test2" + ".txt";
	Observable avN;
	Observable avNN;
	DataManager data;
	data.open(ratioFullName, std::ofstream::out | std::ofstream::app);
	data.open(flucFullName, std::ofstream::out | std::ofstream::app);
	double progress = 0.;
	int bar_width = 70;
	for(double k = kmin; k < kmax; k += kstep)
	{
		lat = Lattice(N_2, N_fix, TIME, k);
		met = Metropolis2(lat, sweepSize);
		met.epsilon = 0;
		avN = Observable();
		avNN = Observable();
		progress = 0;
		printf("Thermalizing...\n");
		for(int i = 1; i <= num_therm; i++)
		{
			met.sweep(lat);
			progress = sim.update_progress(progress, 1./(num_therm-1.), bar_width);
		}
		printf("\nThermalization Complete!\nGenerating ensemble...\n");
		progress = 0;
		for(int i = 1; i <= num_sweeps; i++)
		{
			for(int j = 1; j <= num_cor; j++)
				met.sweep(lat);
			progress = sim.update_progress(progress, 1./(num_sweeps-1.), bar_width);
			avN.record(lat.N_2());
			avNN.record(lat.N_2()*lat.N_2());
		}
		double aveN = avN.report(); 
		double aveNN = avNN.report();
		data.file(ratioFullName) << std::to_string(k) + " " +  " " + std::to_string(aveN/N_2) + "\n";
		data.file(flucFullName) <<  std::to_string(k) + " " + " " + std::to_string(sqrt(aveNN/(aveN*aveN) - 1)) + "\n";
		std::cout << "\nK_2 = " + std::to_string(k) + ", <N>/N_i = " + std::to_string(1.*aveN/N_2) + ", <dN/N> = " + std::to_string(sqrt(aveNN/(aveN*aveN) - 1.)) + "\n";		
		std::cout << met.toString() + "\n";
	}




	return 0;
}
